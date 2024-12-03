#include <jni.h>
#include "http/curl.h"

#ifndef _Included_com_yamadalab_gitfarm_middleware_Jni
#define _Included_com_yamadalab_gitfarm_middleware_Jni
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_application_GitCurl_nativePostRequest(JNIEnv *jenv, jobject jobj, jstring jUrl);

#ifdef __cplusplus
}

#endif
#endif