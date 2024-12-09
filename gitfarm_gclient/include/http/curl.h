#ifndef HTTP_CURL__H
#define HTTP_CURL__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/curlver.h>
#include <curl/easy.h>
#include <curl/urlapi.h>

#define LOG_GET "[GET]"
#define LOG_POST "[POST]"
#define LOG_PUT "[PUT]"
#define LOG_DELETE "[DELETE]"

typedef struct
{
    char name[100];
} CurlHeaderData;

typedef struct CurlHeader
{
    CurlHeaderData data;
    struct CurlHeader *link;
} CurlHeader;

typedef struct CurlResponse
{
    char *response;
    size_t size;
} CurlResponse;

extern CURL *curl_;

int CurlInit();
int CurlFini();
void CurlHeaderAdd(CurlHeader **head, const char *headerName);
void CurlHeaderFini(CurlHeader *head);
char *CurlRequestGET(const char *url, CurlHeader *headerArray);
char *CurlRequestPOST(const char *url, CurlHeader *headerArray);
static size_t CurlResponseCallback(void *contents, size_t size, size_t nmemb, void *userp);

#endif