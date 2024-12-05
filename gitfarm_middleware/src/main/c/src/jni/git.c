#include "jni/git.h"

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_application_Git_nativeGetCommits(JNIEnv *jenv, jobject jobj, jstring jUser, jstring jDate, jstring jToken)
{
    int rc = CurlInit();

    if (rc != 0)
    {
        return NULL;
    }

    CurlHeader *cHeaderArray = NULL;

    CurlHeaderAdd(&cHeaderArray, GITHUB_ACCEPT_HEADER);
    CurlHeaderAdd(&cHeaderArray, GITHUB_USER_AGENT_HEADER);

    if (jToken != NULL)
    {
        const char *cToken = (*jenv)->GetStringUTFChars(jenv, jToken, NULL);
        fprintf(stdout, "%s, Token : %s\n", LOG_POST, cToken);
        char cAuthHeader[512];
        snprintf(cAuthHeader, sizeof(cAuthHeader), GITHUB_AUTH_HEADER_FORMAT, cToken);
        CurlHeaderAdd(&cHeaderArray, cAuthHeader);
        (*jenv)->ReleaseStringUTFChars(jenv, jToken, cToken);
    }


    if (cHeaderArray == NULL)
    {
        return NULL;
    }

    const char *cUser = (*jenv)->GetStringUTFChars(jenv, jUser, NULL);
    const char *cDate = (*jenv)->GetStringUTFChars(jenv, jDate, NULL);

    char cUrl[512];
    snprintf(cUrl, sizeof(cUrl), GITHUB_API_URL, cUser, cDate);
    fprintf(stdout, "%s, GetCommits : %s\n", LOG_POST, cUrl);

    char *cResponse = CurlRequestGET(cUrl, cHeaderArray);
    jstring jResponse = (*jenv)->NewStringUTF(jenv, cResponse);

    (*jenv)->ReleaseStringUTFChars(jenv, jUser, cUser);
    (*jenv)->ReleaseStringUTFChars(jenv, jDate, cDate);
    (*jenv)->ReleaseStringUTFChars(jenv, jResponse, cResponse);

    CurlFini();

    return jResponse;
}