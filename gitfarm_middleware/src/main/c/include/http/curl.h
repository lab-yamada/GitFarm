#ifndef HTTP_CURL__H
#define HTTP_CURL__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/urlapi.h>

typedef struct CurlResponse {
    char *response;
    size_t size;
} CurlResponse;

extern CURL *curl_;

int CurlInit();
int CurlFini();
int CurlRequestGET(const char *url);
int CurlRequestPOST(const char *url);
static size_t CurlResponseCallback(void *contents, size_t size, size_t nmemb, void *userp);
int DoJsonRequest(const char* url, const char* body_data);

#endif