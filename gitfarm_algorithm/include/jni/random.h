#include <jni.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>

#include "jni/jni.h"
#include "domain/item.hpp"
#include "algorithm/algorithm.hpp"

#define TAG "[Random]"
#ifndef _Included_com_yamadalab_gitfarm_middleware_algorithm_Random
#define _Included_com_yamadalab_gitfarm_middleware_alogrithm_Random
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_Random_nativeSetItems(JNIEnv *jenv, jobject jobj, jobjectArray jitems);

JNIEXPORT jobject JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_Random_nativeDraw(JNIEnv *jenv, jobject jobj);

#ifdef __cplusplus
}
#endif
#endif