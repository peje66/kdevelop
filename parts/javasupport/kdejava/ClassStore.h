/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_kde_koala_ClassStore */

#ifndef _Included_org_kde_koala_ClassStore
#define _Included_org_kde_koala_ClassStore
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_kde_koala_ClassStore
 * Method:    addClass
 * Signature: (Lorg/kde/koala/ParsedClass;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_addClass
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    addGlobalFunction
 * Signature: (Lorg/kde/koala/ParsedMethod;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_addGlobalFunction
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    addGlobalStruct
 * Signature: (Lorg/kde/koala/ParsedStruct;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_addGlobalStruct
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    addGlobalVar
 * Signature: (Lorg/kde/koala/ParsedAttribute;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_addGlobalVar
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    addScope
 * Signature: (Lorg/kde/koala/ParsedScopeContainer;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_addScope
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_finalize
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    getClassByName
 * Signature: (Ljava/lang/String;)Lorg/kde/koala/ParsedClass;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ClassStore_getClassByName
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    getScopeByName
 * Signature: (Ljava/lang/String;)Lorg/kde/koala/ParsedScopeContainer;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ClassStore_getScopeByName
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    getSortedClassNameList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ClassStore_getSortedClassNameList
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    hasClass
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ClassStore_hasClass
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    hasScope
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ClassStore_hasScope
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    hasStruct
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ClassStore_hasStruct
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    newClassStore
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_newClassStore
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    out
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_out
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    removeClass
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_removeClass
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    removeWithReferences
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_removeWithReferences
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    storeAll
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_storeAll
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ClassStore
 * Method:    wipeout
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ClassStore_wipeout
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
