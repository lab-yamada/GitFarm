#include "jni/jni.h"

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_nativePostRequest(JNIEnv *env, jobject obj, jstring jUrl) {
    const char *cUrl = (*env)->GetStringUTFChars(env, jUrl, NULL);

    struct CurlResponse chunk = {.response = NULL, .size = 0};
    int result = CurlRequestPOST(cUrl);

    (*env)->ReleaseStringUTFChars(env, jUrl, cUrl);

    if (result != 0 || chunk.response == NULL)
    {
        return NULL;
    }

    jstring jResponse = (*env)->NewStringUTF(env, chunk.response);

    free(chunk.response);

    return jResponse;
}