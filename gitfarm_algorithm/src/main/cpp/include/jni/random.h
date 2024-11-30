#include <jni.h>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

#include "jni/jni.h"
#include "algorithm/algorithm.hpp"

#define TAG "[Random]"

#ifndef _Included_com_yamadalab_gitfarm_application_Random
#define _Included_com_yamadalab_gitfarm_application_Random
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jobject JNICALL Java_com_yamadalab_gitfarm_application_Random_wrs_draw(JNIEnv *jenv, jobject jobj);
JNIEXPORT jstring JNICALL Java_com_yamadalab_gitfarm_application_Random_cdraw(JNIEnv *jenv, jobject jobj, jobjectArray jitems);

#ifdef __cplusplus
}
#endif
#endif