#include <jni.h>
#include "algorithm/algorithm.hpp"

#ifndef _Included_com_yamadalab_gitcha_Random
#define _Included_com_yamadalab_gitcha_Random
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_com_yamadalab_gitcha_Random_wrsRandom(
    JNIEnv *jenv, jobject jobj,
    jlongArray jweights);

JNIEXPORT jboolean JNICALL Java_com_yamadalab_gitcha_Random_pityRandom(
    JNIEnv *jenv, jobject jobj,
    jint jbase_chance, jint jmax_fails, jint jcurrent_fails);


#ifdef __cplusplus
}
#endif
#endif