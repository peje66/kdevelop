/***************************************************************************
                            DocumentationContext.cpp -  description
                             -------------------
    begin                : Mon May 21 09:39:20 2001
    copyright            : (C) 2000-2001 Lost Highway Ltd.
    email                : Richard_Dale@tipitina.demon.co.uk
    generated by         : duke@tipitina on Mon May 21 09:39:20 2001, using kdoc parser/custom Java conversion backend.
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
***************************************************************************/

#define _BOOL_H_
#include <kdevcore.h>
#include <qstring.h>
#include <qcstring.h>

#include <qtjava/QtSupport.h>
#include <kdejava/DocumentationContext.h>

class DocumentationContextJBridge : public DocumentationContext
{
public:
	DocumentationContextJBridge(const QString& url, const QString& selection) : DocumentationContext(url, selection) {}
	~DocumentationContextJBridge() {}
};


JNIEXPORT void JNICALL
Java_org_kde_koala_DocumentationContext_newDocumentationContext(JNIEnv *env, jobject obj, jstring url, jstring selection)
{
static QString * _qstring_selection = 0;
static QString * _qstring_url = 0;
	if (QtSupport::getQt(env, obj) == 0) {
		QtSupport::setQt(env, obj, new DocumentationContextJBridge((QString&) * (QString *) QtSupport::toQString(env, url, &_qstring_url), (QString&) * (QString *) QtSupport::toQString(env, selection, &_qstring_selection)));
		QtSupport::setObjectForQtKey(env, obj, QtSupport::getQt(env, obj));
	}
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_DocumentationContext_finalize(JNIEnv *env, jobject obj)
{
	if (QtSupport::allocatedInJavaWorld(env, obj)) {
		delete (DocumentationContext*)QtSupport::getQt(env, obj);
		QtSupport::setQt(env, obj, 0);
	}
	return;
}

JNIEXPORT jstring JNICALL
Java_org_kde_koala_DocumentationContext_url(JNIEnv *env, jobject obj)
{
	QString  _qstring;
	_qstring = ((DocumentationContextJBridge*) QtSupport::getQt(env, obj))->url();
	return QtSupport::fromQString(env, &_qstring);
}

JNIEXPORT jstring JNICALL
Java_org_kde_koala_DocumentationContext_selection(JNIEnv *env, jobject obj)
{
	QString  _qstring;
	_qstring = ((DocumentationContextJBridge*) QtSupport::getQt(env, obj))->selection();
	return QtSupport::fromQString(env, &_qstring);
}

