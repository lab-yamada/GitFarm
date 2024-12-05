#include "jni/git.h"

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_application_Git_nativeGetCommits(JNIEnv *jenv, jobject jobj, jstring jUser, jstring jStartDate, jstring jEndDate, jstring jToken)
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
    const char *cStartDate = (*jenv)->GetStringUTFChars(jenv, jStartDate, NULL);
    const char *cEndDate = (*jenv)->GetStringUTFChars(jenv, jEndDate, NULL);

    char cUrl[512];
    snprintf(cUrl, sizeof(cUrl), GITHUB_API_URL, cUser, cStartDate, cEndDate);
    fprintf(stdout, "%s, GetCommits : %s\n", LOG_JNI, cUrl);

    char *cResponse = CurlRequestGET(cUrl, cHeaderArray);

    if (cResponse == NULL)
    {
        fprintf(strerror, "%s, GetCommits Response is NULL\n", LOG_JNI);
        return NULL;
    }

    jstring jResponse = (*jenv)->NewStringUTF(jenv, cResponse);

    (*jenv)->ReleaseStringUTFChars(jenv, jUser, cUser);
    (*jenv)->ReleaseStringUTFChars(jenv, jStartDate, cStartDate);
    (*jenv)->ReleaseStringUTFChars(jenv, jEndDate, cEndDate);
    (*jenv)->ReleaseStringUTFChars(jenv, jResponse, cResponse);

    CurlFini();

    return jResponse;
}