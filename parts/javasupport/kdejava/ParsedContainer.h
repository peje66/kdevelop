/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_kde_koala_ParsedContainer */

#ifndef _Included_org_kde_koala_ParsedContainer
#define _Included_org_kde_koala_ParsedContainer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    addAttribute
 * Signature: (Lorg/kde/koala/ParsedAttribute;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_addAttribute
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    addMethod
 * Signature: (Lorg/kde/koala/ParsedMethod;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_addMethod
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    addStruct
 * Signature: (Lorg/kde/koala/ParsedStruct;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_addStruct
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    attributeList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_attributeList
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    clear
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_clear
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_finalize
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getAttributeByName
 * Signature: (Ljava/lang/String;)Lorg/kde/koala/ParsedAttribute;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getAttributeByName
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getMethod
 * Signature: (Lorg/kde/koala/ParsedMethod;)Lorg/kde/koala/ParsedMethod;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getMethod
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getMethodByNameAndArg
 * Signature: (Ljava/lang/String;)Lorg/kde/koala/ParsedMethod;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getMethodByNameAndArg
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getSortedAttributeAsStringList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getSortedAttributeAsStringList
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getSortedStructNameList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getSortedStructNameList
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    getStructByName
 * Signature: (Ljava/lang/String;)Lorg/kde/koala/ParsedStruct;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_getStructByName
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    hasAttribute
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedContainer_hasAttribute
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    hasStruct
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedContainer_hasStruct
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    methodList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_methodList
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    newParsedContainer
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_newParsedContainer
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    out
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_out
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    removeAttribute
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_removeAttribute
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    removeMethod
 * Signature: (Lorg/kde/koala/ParsedMethod;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_removeMethod
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    removeStruct
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_removeStruct
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    removeWithReferences
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_removeWithReferences
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    setUseFullpath
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedContainer_setUseFullpath
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_kde_koala_ParsedContainer
 * Method:    structList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_org_kde_koala_ParsedContainer_structList
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
