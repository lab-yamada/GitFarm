#ifndef HTTP_CURL__H
#define HTTP_CURL__H

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/urlapi.h>

extern CURL *curl_;

int Curl_Init();
int Curl_Fini();
int Curl_GET(const char *url);
int Curl_POST(const char *url);
size_t Curl_Res_Callback(char* ptr, size_t size, size_t nmemb, const char* stream);
int DoJsonRequest(const char* url, const char* body_data);

#endif