#include <jni.h>
#include "http/curl.h"

#define GITHUB_API_URL "https://api.github.com/search/commits?q=author:%s+committer-date:%s"
#define GITHUB_ACCEPT_HEADER "Accept: application/vnd.github.cloak-preview"
#define GITHUB_USER_AGENT_HEADER "User-Agent: MyApp/1.0"
#define GITHUB_AUTH_HEADER_FORMAT "Authorization: Bearer %s"

#ifndef _Included_com_yamadalab_gitfarm_middleware_Git
#define _Included_com_yamadalab_gitfarm_middleware_Git
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_yamadalab_gitfarm_middleware_application_Git_nativeGetCommits(JNIEnv *jenv, jobject jobj, jstring jUser, jstring jDate, jstring jToken);

#ifdef __cplusplus
}

#endif
#endif