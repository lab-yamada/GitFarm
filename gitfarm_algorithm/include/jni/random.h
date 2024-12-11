#pragma once
#include <jni.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <map>

#include "jni/jni.h"
#include "domain/item.hpp"
#include "algorithm/algorithm.hpp"

#ifndef _Included_com_yamadalab_gitfarm_middleware_algorithm_application_Random
#define _Included_com_yamadalab_gitfarm_middleware_algorithm_application_Random

#define TAG "[Random]"
#define LOG_JNI "[JNI]"
#define JITEM_PATH "com/yamadalab/gitfarm/middleware/algorithm/domain/Item"
#define JITEM_GRADE_PATH "com/yamadalab/gitfarm/middleware/algorithm/domain/Grade"
#define JITEM_CONSTRUCTOR "(Ljava/lang/String;Lcom/yamadalab/gitfarm/middleware/algorithm/domain/Grade;)V"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jboolean JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeSetItems(JNIEnv *jEnv, jobject jObj, jobjectArray jItems);

JNIEXPORT jboolean JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeSetUser(JNIEnv *jEnv, jobject jObj, jobject jUser);

JNIEXPORT jobject JNICALL
Java_com_yamadalab_gitfarm_middleware_algorithm_application_Random_nativeDraw(JNIEnv *jEnv, jobject jObj);

#ifdef __cplusplus
}
#endif
#endif