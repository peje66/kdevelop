/***************************************************************************
*   Copyright 1999-2001 by Bernd Gehrmann                                 *
*   bernd@kdevelop.org                                                    *
*   Copyright 2007 Dukju Ahn <dukjuahn@gmail.com>                         *
*   Copyright 2010 Benjamin Port <port.benjamin@gmail.com>                *                                                                      *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#include "grepviewplugin.h"
#include "grepdialog.h"
#include "grepoutputmodel.h"
#include "grepoutputdelegate.h"

#include <QWhatsThis>
#include <QKeySequence>

#include <kpluginfactory.h>
#include <kpluginloader.h>
#include <kaboutdata.h>
#include <kactioncollection.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kaction.h>
#include <ktexteditor/document.h>
#include <ktexteditor/cursor.h>
#include <ktexteditor/view.h>

#include <interfaces/icore.h>
#include <outputview/ioutputview.h>
#include <interfaces/iplugincontroller.h>
#include <interfaces/iuicontroller.h>
#include <kparts/mainwindow.h>
#include <interfaces/idocument.h>
#include <interfaces/idocumentcontroller.h>
#include <interfaces/iproject.h>
#include <interfaces/iprojectcontroller.h>
#include <project/projectmodel.h>
#include <language/interfaces/editorcontext.h>

K_PLUGIN_FACTORY(GrepViewFactory, registerPlugin<GrepViewPlugin>(); )
K_EXPORT_PLUGIN(GrepViewFactory(KAboutData("kdevgrepview","kdevgrepview", ki18n("Find In Files"), "0.1", ki18n("Support for running grep over a list of files"), KAboutData::License_GPL)))

GrepViewPlugin::GrepViewPlugin( QObject *parent, const QVariantList & )
    : KDevelop::IPlugin( GrepViewFactory::componentData(), parent )
{
    setXMLFile("kdevgrepview.rc");


    KAction *action = actionCollection()->addAction("edit_grep");
    action->setText(i18n("Find in Fi&les..."));
    action->setShortcut( i18n("Ctrl+Alt+f") );
    connect(action, SIGNAL(triggered(bool)), this, SLOT(showDialog()));
    action->setToolTip( i18n("Search for expressions over several files") );
    action->setWhatsThis( i18n("<b>Find in files</b><p>"
            "Opens the 'Find in files' dialog. There you "
            "can enter a regular expression which is then "
            "searched for within all files in the directories "
            "you specify. Matches will be displayed, you "
            "can switch to a match directly.</p>") );
    action->setIcon(KIcon("edit-find"));

    // instantiate delegate, it's supposed to be deleted via QObject inheritance
    new GrepOutputDelegate(this);
}

GrepViewPlugin::~GrepViewPlugin()
{
}

KDevelop::ContextMenuExtension GrepViewPlugin::contextMenuExtension(KDevelop::Context* context)
{
    KDevelop::ContextMenuExtension extension = KDevelop::IPlugin::contextMenuExtension(context);
    if( context->type() == KDevelop::Context::ProjectItemContext ) {
        KDevelop::ProjectItemContext* ctx = dynamic_cast<KDevelop::ProjectItemContext*>( context );
        QList<KDevelop::ProjectBaseItem*> items = ctx->items();
        // verify if there is only one folder selected
        if ((items.count() == 1) && (items.first()->folder())) {
            KAction* action = new KAction( i18n( "Find and replace in this folder" ), this );
            action->setIcon(KIcon("edit-find"));
            m_contextMenuDirectory = items.at(0)->folder()->url().toLocalFile();
            connect( action, SIGNAL(triggered()), this, SLOT(showDialogFromProject()));
            extension.addAction( KDevelop::ContextMenuExtension::ExtensionGroup, action );
        }
    }

    if ( context->type() == KDevelop::Context::EditorContext ) {
        KDevelop::EditorContext *econtext = dynamic_cast<KDevelop::EditorContext*>(context);
        if ( econtext->view()->selection() ) {
            QAction* action = new QAction(KIcon("edit-find"), i18n("&Find in Files"), this);
            connect(action, SIGNAL(triggered(bool)), this, SLOT(showDialog()));
            extension.addAction(KDevelop::ContextMenuExtension::ExtensionGroup, action);
        }
    }

    return extension;
}

void GrepViewPlugin::showDialog()
{
    KDevelop::IDocument* doc = core()->documentController()->activeDocument();
    QString pattern;
    if( doc )
    {
        KTextEditor::Range range = doc->textSelection();
        if( range.isValid() )
        {
            kDebug() << "got valid range:" << range;
            pattern = doc->textDocument()->text( range );
            kDebug() << "context now:" << pattern;
        }
        if( pattern.isEmpty() )
        {
            kDebug() << "fetching current word";
            pattern = doc->textWord();
            kDebug() << "word is:" << pattern;
        }
    }

    GrepDialog* dlg = new GrepDialog( this, core()->uiController()->activeMainWindow() );
    // Before anything, this removes line feeds from the
    // beginning and the end.
    int len = pattern.length();
    if (len > 0 && pattern[0] == '\n')
    {
        pattern.remove(0, 1);
        len--;
    }
    if (len > 0 && pattern[len-1] == '\n')
        pattern.truncate(len-1);
    if (!pattern.isEmpty()) {
        dlg->setPattern( pattern );
    }

    dlg->enableButtonOk( !pattern.isEmpty() );

    if (!m_directory.isEmpty() && QFileInfo(m_directory).isDir()) {
        dlg->setDirectory(m_directory);
    }

    KUrl currentUrl;
    KDevelop::IDocument *document = core()->documentController()->activeDocument();
    dlg->setEnableProjectBox(false);
    if( document )
    {
        currentUrl = document->url();
    }
    if( currentUrl.isValid() )
    {
        KDevelop::IProject *proj =
                core()->projectController()->findProjectForUrl( currentUrl );
        if( proj && proj->folder().isLocalFile() )
        {
            dlg->setEnableProjectBox(! proj->files().isEmpty() );

            if (!m_directory.startsWith(proj->folder().toLocalFile()))
            {
                dlg->setDirectory( proj->folder().toLocalFile() );
            }
        }
    }

    dlg->show();
}

void GrepViewPlugin::showDialogFromProject()
{
    rememberSearchDirectory(m_contextMenuDirectory);
    showDialog();
}

void GrepViewPlugin::rememberSearchDirectory(QString const & directory)
{
    m_directory = directory;
}

#include "grepviewplugin.moc"
