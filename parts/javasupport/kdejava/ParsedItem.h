/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_kde_koala_ParsedItem */

#ifndef _Included_org_kde_koala_ParsedItem
#define _Included_org_kde_koala_ParsedItem
#ifdef __cplusplus
extern "C" {
#endif
#undef org_kde_koala_ParsedItem_PIT_UNKNOWN
#define org_kde_koala_ParsedItem_PIT_UNKNOWN 0L
#undef org_kde_koala_ParsedItem_PIT_CLASS
#define org_kde_koala_ParsedItem_PIT_CLASS 1L
#undef org_kde_koala_ParsedItem_PIT_METHOD
#define org_kde_koala_ParsedItem_PIT_METHOD 2L
#undef org_kde_koala_ParsedItem_PIT_ATTRIBUTE
#define org_kde_koala_ParsedItem_PIT_ATTRIBUTE 3L
#undef org_kde_koala_ParsedItem_PIT_STRUCT
#define org_kde_koala_ParsedItem_PIT_STRUCT 4L
#undef org_kde_koala_ParsedItem_PIT_SCOPE
#define org_kde_koala_ParsedItem_PIT_SCOPE 5L
#undef org_kde_koala_ParsedItem_PIE_GLOBAL
#define org_kde_koala_ParsedItem_PIE_GLOBAL 0L
#undef org_kde_koala_ParsedItem_PIE_PUBLIC
#define org_kde_koala_ParsedItem_PIE_PUBLIC 1L
#undef org_kde_koala_ParsedItem_PIE_PROTECTED
#define org_kde_koala_ParsedItem_PIE_PROTECTED 2L
#undef org_kde_koala_ParsedItem_PIE_PRIVATE
#define org_kde_koala_ParsedItem_PIE_PRIVATE 3L
/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    asString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_asString
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    clearDeclaration
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_clearDeclaration
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    clearDefinition
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_clearDefinition
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    copy
 * Signature: (Lorg/kde/koala/ParsedItem;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_copy
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_finalize
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    isGlobal
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedItem_isGlobal
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    isPrivate
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedItem_isPrivate
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    isProtected
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedItem_isProtected
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    isPublic
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_kde_koala_ParsedItem_isPublic
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemAccess
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_itemAccess
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemComment
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_itemComment
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDeclarationEndsOnLine
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_itemDeclarationEndsOnLine
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDeclaredInFile
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_itemDeclaredInFile
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDeclaredInScope
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_itemDeclaredInScope
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDeclaredOnLine
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_itemDeclaredOnLine
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDefinedInFile
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_itemDefinedInFile
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDefinedOnLine
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_itemDefinedOnLine
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemDefinitionEndsOnLine
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_itemDefinitionEndsOnLine
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    itemName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_itemName
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    out
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_out
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    parsedItemType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_kde_koala_ParsedItem_parsedItemType
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    path
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_kde_koala_ParsedItem_path
  (JNIEnv *, jobject);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setAccess
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setAccess
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setComment
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setComment
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDeclarationEndsOnLine
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDeclarationEndsOnLine
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDeclaredInFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDeclaredInFile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDeclaredInScope
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDeclaredInScope
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDeclaredOnLine
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDeclaredOnLine
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDefinedInFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDefinedInFile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDefinedOnLine
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDefinedOnLine
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setDefinitionEndsOnLine
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setDefinitionEndsOnLine
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setItemType
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setItemType
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_kde_koala_ParsedItem
 * Method:    setName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_kde_koala_ParsedItem_setName
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
