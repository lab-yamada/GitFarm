#include <jni.h>

#ifndef _Included_com_yamadalab_gitcha_Jni
#define _Included_com_yamadalab_gitcha_Jni
#ifdef __cplusplus
extern "C" {
#endif

jint JNI_parse_to_jint(JNIEnv *jenv, jobject jobj);
jstring JNI_parse_to_jstring(JNIEnv *jenv, jobject jobj);
jdouble JNI_parse_to_jdouble(JNIEnv *jenv, jobject jobj);
jfloat JNI_parse_to_jfloat(JNIEnv *jenv, jobject jobj);


#ifdef __cplusplus
}

#endif
#endif