
/***************************************************************************
                            KDevLanguageSupport.cpp -  description
                             -------------------
    begin                : Thu May 24 12:31:20 2001
    copyright            : (C) 2000-2001 Lost Highway Ltd.
    email                : Richard_Dale@tipitina.demon.co.uk
    generated by         : duke@tipitina on Thu May 24 12:31:20 2001, using kdoc parser/custom Java conversion backend.
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
#include <kdevlanguagesupport.h>
#include <qstring.h>
#include <qcstring.h>

#include <qtjava/QtSupport.h>
#include <kdejava/KDevLanguageSupport.h>

void KDevLanguageSupportJBridge::updatedJavaSourceInfo()
{
	emit updatedSourceInfo();
}

KDevLanguageSupport::Features KDevLanguageSupportJBridge::features()
{
	return (KDevLanguageSupport::Features) _features;
}

void KDevLanguageSupportJBridge::setFeatures(KDevLanguageSupport::Features features)
{
	_features = features;
}

QStringList KDevLanguageSupportJBridge::fileFilters()
{
     return _fileFilters;
}

void KDevLanguageSupportJBridge::setFileFilters(QStringList fileFilters)
{
	_fileFilters = fileFilters;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_updatedJavaSourceInfo(JNIEnv *env, jobject obj)
{
	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->updatedJavaSourceInfo();
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_newKDevLanguageSupport__Lorg_kde_koala_KDevApi_2Lorg_kde_qt_QObject_2Ljava_lang_String_2(JNIEnv *env, jobject obj, jobject api, jobject parent, jstring name)
{
static QCString * _qstring_name = 0;
	if (QtSupport::getQt(env, obj) == 0) {
		QtSupport::setQt(env, obj, new KDevLanguageSupportJBridge((KDevApi*) QtSupport::getQt(env, api), (QObject*) QtSupport::getQt(env, parent), (char*) QtSupport::toCharString(env, name, &_qstring_name)));
		QtSupport::setObjectForQtKey(env, obj, QtSupport::getQt(env, obj));
	}
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_newKDevLanguageSupport__Lorg_kde_koala_KDevApi_2(JNIEnv *env, jobject obj, jobject api)
{
	if (QtSupport::getQt(env, obj) == 0) {
		QtSupport::setQt(env, obj, new KDevLanguageSupportJBridge((KDevApi*) QtSupport::getQt(env, api), 0, 0));
		QtSupport::setObjectForQtKey(env, obj, QtSupport::getQt(env, obj));
	}
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_finalize(JNIEnv *env, jobject obj)
{
	if (QtSupport::allocatedInJavaWorld(env, obj)) {
		delete (KDevLanguageSupport*)QtSupport::getQt(env, obj);
		QtSupport::setQt(env, obj, 0);
	}
	return;
}

JNIEXPORT jint JNICALL
Java_org_kde_koala_KDevLanguageSupport_features(JNIEnv *env, jobject obj)
{
	return (jint) ((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->features();
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_setFeatures(JNIEnv *env, jobject obj, jint features)
{
	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->setFeatures((KDevLanguageSupport::Features) features);
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_addClass(JNIEnv *env, jobject obj)
{
//	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->addClass();
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_addMethod(JNIEnv *env, jobject obj, jstring className)
{
//static QString * _qstring_className = 0;
//	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->addMethod((QString&) * (QString *) QtSupport::toQString(env, className, &_qstring_className));
	return;
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_addAttribute(JNIEnv *env, jobject obj, jstring className)
{
//static QString * _qstring_className = 0;
//	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->addAttribute((QString&) * (QString *) QtSupport::toQString(env, className, &_qstring_className));
	return;
}

JNIEXPORT jobject JNICALL
Java_org_kde_koala_KDevLanguageSupport_fileFilters(JNIEnv *env, jobject obj)
{
	QStringList  _qlist;
	_qlist = ((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->fileFilters();
	return (jobject) QtSupport::arrayWithQStringList(env, (QStringList *) &_qlist);
}

JNIEXPORT void JNICALL
Java_org_kde_koala_KDevLanguageSupport_setFileFilters(JNIEnv *env, jobject obj, jobjectArray fileFilters)
{
static QStringList * _qlist_fileFilters = 0;
	((KDevLanguageSupportJBridge*) QtSupport::getQt(env, obj))->setFileFilters((QStringList&) * (QStringList *) QtSupport::toQStringList(env, fileFilters, &_qlist_fileFilters));
	return;
}

#include "KDevLanguageSupport.moc"

