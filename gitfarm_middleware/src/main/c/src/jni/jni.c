#include "jni/jni.h"

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_application_GitCurl_nativePostRequest(JNIEnv *jenv, jobject jobj, jstring jUrl) {
    int rc = 0;
    rc = CurlInit();

    if (rc != 0)
    {
        return NULL;
    }

    const char *cUrl = (*jenv)->GetStringUTFChars(jenv, jUrl, NULL);
    printf("Post, url : %s\n", cUrl);

    char *cResponse = CurlRequestPOST(cUrl);
    jstring jResponse = (*jenv)->NewStringUTF(jenv, cResponse);

    (*jenv)->ReleaseStringUTFChars(jenv, jUrl, cUrl);
    (*jenv)->ReleaseStringUTFChars(jenv, jResponse, cResponse);

    return jResponse;
}