/*
 * This file is part of qmljs, the QML/JS language support plugin for KDevelop
 * Copyright (c) 2013 Sven Brauch <svenbrauch@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "context.h"
#include "completionitem.h"
#include "modulecompletionitem.h"

#include <language/codecompletion/codecompletionitem.h>
#include <language/codecompletion/normaldeclarationcompletionitem.h>
#include <language/duchain/declaration.h>
#include <language/duchain/duchainlock.h>
#include <language/duchain/classdeclaration.h>
#include <language/duchain/namespacealiasdeclaration.h>
#include <language/duchain/codemodel.h>
#include <kstandarddirs.h>

#include <qmljs/qmljsdocument.h>
#include <qmljs/parser/qmljslexer_p.h>
#include <duchain/expressionvisitor.h>
#include <duchain/helper.h>

#include <QtCore/QDir>

using namespace KDevelop;

typedef QPair<Declaration*, int> DeclarationDepthPair;

namespace QmlJS {

CodeCompletionContext::CodeCompletionContext(const DUContextPointer& context, const QString& text,
                                             const CursorInRevision& position, int depth)
: KDevelop::CodeCompletionContext(context, extractLastLine(text), position, depth),
  m_completionKind(NormalCompletion)
{
    // Detect "import ..." and provide import completions
    if (m_text.startsWith("import ")) {
        m_completionKind = ImportCompletion;
    }

    // Detect whether the cursor is in a comment
    bool isLastLine = true;

    for (int index = text.size()-1; index > 0; --index) {
        const QChar c = text.at(index);
        const QChar prev = text.at(index - 1);

        if (c == QLatin1Char('\n')) {
            isLastLine = false;
        } else if (isLastLine && prev == QLatin1Char('/') && c == QLatin1Char('/')) {
            // Single-line comment on the current line, we are in a comment
            m_completionKind = CommentCompletion;
            break;
        } else if (prev == QLatin1Char('/') && c == QLatin1Char('*')) {
            // Start of a multi-line comment encountered
            m_completionKind = CommentCompletion;
            break;
        } else if (prev == QLatin1Char('*') && c == QLatin1Char('/')) {
            // End of a multi-line comment. Because /* and */ cannot be nested,
            // encountering a */ is enough to know that the cursor is outside a
            // comment
            break;
        }
    }
}

QList<CompletionTreeItemPointer> CodeCompletionContext::completionItems(bool& abort, bool fullCompletion)
{
    Q_UNUSED (fullCompletion);

    if (abort) {
        return QList<CompletionTreeItemPointer>();
    }

    switch (m_completionKind) {
    case NormalCompletion:
        return normalCompletion();
    case CommentCompletion:
        return commentCompletion();
    case ImportCompletion:
        return importCompletion();
    }
}

QList<KDevelop::CompletionTreeItemPointer> CodeCompletionContext::normalCompletion()
{
    QList<CompletionTreeItemPointer> items;
    QChar lastChar = m_text.size() > 0 ? m_text.at(m_text.size() - 1) : QLatin1Char('\0');

    if (lastChar == QLatin1Char('.') || lastChar == QLatin1Char('[')) {
        // Offer completions for object members and array subscripts
        items << fieldCompletions(
            m_text.left(m_text.size() - 1),
            lastChar == QLatin1Char('[') ? CompletionItem::QuotesAndBracket : CompletionItem::NoDecoration
        );
    }

    // "object." must only display the members of object, the declarations
    // available in the current context.
    if (lastChar != QLatin1Char('.')) {
        bool inQmlObjectScope = (m_duContext->type() == DUContext::Class && containsOnlySpaces(m_text));

        if (inQmlObjectScope) {
            DUChainReadLocker lock;

            // The cursor is in a QML object and there is nothing before it. Display
            // a list of properties and signals that can be used in a script binding.
            // Note that the properties/signals of parent QML objects are not displayed here
            items << completionsInContext(m_duContext,
                                          CompletionOnlyLocal | CompletionHideWrappers,
                                          CompletionItem::Colon);
            items << completionsInContext(DUContextPointer(m_duContext->topContext()),
                                          CompletionHideWrappers,
                                          CompletionItem::NoDecoration);
        } else {
            items << completionsInContext(m_duContext,
                                          0,
                                          CompletionItem::NoDecoration);
        }
    }

    return items;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::commentCompletion()
{
    return QList<CompletionTreeItemPointer>();
}

QList<CompletionTreeItemPointer> CodeCompletionContext::importCompletion()
{
    QList<CompletionTreeItemPointer> items;

    // List $KDEDATA/kdevqmljssupport/qmlplugins/ and add one completion item
    // per file found there
    QString dataDir = KGlobal::dirs()->findDirs("data",
        QLatin1String("kdevqmljssupport/qmlplugins")
    ).at(0);
    QDir dir(dataDir);

    for (const QString &entry : dir.entryList(QDir::Files, QDir::Name)) {
        items.append(CompletionTreeItemPointer(new ModuleCompletionItem(entry)));
    }

    return items;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::completionsInContext(const DUContextPointer& context,
                                                                             CompletionInContextFlags flags,
                                                                             CompletionItem::Decoration decoration)
{
    QList<CompletionTreeItemPointer> items;
    DUChainReadLocker lock;

    if (context) {
        const QList<DeclarationDepthPair>& declarations = context->allDeclarations(
            CursorInRevision::invalid(),
            context->topContext(),
            !flags.testFlag(CompletionOnlyLocal)
        );

        foreach (const DeclarationDepthPair& decl, declarations) {
            DeclarationPointer declaration(decl.first);

            if (declaration->kind() == Declaration::NamespaceAlias) {
                continue;
            } else if (declaration->qualifiedIdentifier().isEmpty()) {
                continue;
            } else if (decoration == CompletionItem::NoDecoration &&
                       declaration->abstractType() &&
                       declaration->abstractType()->whichType() == AbstractType::TypeFunction) {
                // Decorate function calls with brackets
                decoration = CompletionItem::Brackets;
            } else if (flags.testFlag(CompletionHideWrappers)) {
                ClassDeclaration* classDecl = dynamic_cast<ClassDeclaration*>(declaration.data());

                if (classDecl && classDecl->classType() == ClassDeclarationData::Interface) {
                    continue;
                }
            }

            items << CompletionTreeItemPointer(new CompletionItem(declaration, decl.second, decoration));
        }
    }

    return items;
}

QList<CompletionTreeItemPointer> CodeCompletionContext::fieldCompletions(const QString& expression,
                                                                         CompletionItem::Decoration decoration)
{
    // expression is an incomplete expression. Try to parse as much as possible
    // of it, in order to get the most complete AST possible.
    // For instance, if expression is "test(foo.bar", test(foo.bar is invalid,
    // but foo.bar is valid and should be used (bar is also valid, but too small
    // to provide any useful context)
    QStack<int> bracketPositions;
    QmlJS::Lexer lexer(nullptr);
    bool atEnd = false;

    lexer.setCode(expression, 1, false);
    bracketPositions.push(0);

    while (!atEnd) {
        switch (lexer.lex()) {
        case QmlJSGrammar::EOF_SYMBOL:
            atEnd = true;
            break;
        case QmlJSGrammar::T_LBRACE:
        case QmlJSGrammar::T_LBRACKET:
        case QmlJSGrammar::T_LPAREN:
            bracketPositions.push(lexer.tokenStartColumn());
            break;
        case QmlJSGrammar::T_RBRACE:
        case QmlJSGrammar::T_RBRACKET:
        case QmlJSGrammar::T_RPAREN:
            bracketPositions.pop();
            break;
        case QmlJSGrammar::T_IDENTIFIER:
        case QmlJSGrammar::T_DOT:
            break;
        default:
            // "a == b", "a + b", "a && b", "typeof b", etc are not expressions
            // whose type is interesting for code-completion, but "b" is.
            // "foo(a, b", is not a valid expression, "b" is. "var a = b" is not
            // understood by ExpressionVisitor, b is.
            // Shift the current position so that everything before the unwanted char is
            // ignored. Because a stack is used, "foo(a, b)" will still correctly
            // be identified a an expression if the closing brace in present
            bracketPositions.top() = lexer.tokenStartColumn();
        }
    }

    // The last un-matched paren/brace/bracket correspond to the start of something
    // that should be a valid expression.
    QmlJS::Document::MutablePtr doc = QmlJS::Document::create("inline", Language::JavaScript);

    doc->setSource(expression.mid(bracketPositions.top()));
    doc->parseExpression();

    if (!doc || !doc->isParsedCorrectly()) {
        return QList<CompletionTreeItemPointer>();
    }

    // Use ExpressionVisitor to find the type (and associated declaration) of
    // the snippet that has been parsed. The inner context of the declaration
    // can be used to get the list of completions
    ExpressionVisitor visitor(m_duContext.data());
    doc->ast()->accept(&visitor);

    DUContext* context = getInternalContext(visitor.lastDeclaration());

    if (context) {
        return completionsInContext(DUContextPointer(context),
                                    CompletionOnlyLocal,
                                    decoration);
    } else {
        return QList<CompletionTreeItemPointer>();
    }
}

bool CodeCompletionContext::containsOnlySpaces(const QString& str)
{
    for (int i=0; i<str.size(); ++i) {
        if (!str.at(i).isSpace()) {
            return false;
        }
    }

    return true;
}

}
