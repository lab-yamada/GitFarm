#include "http/curl.h"

CURL *curl_;

int CurlInit()
{
	int rc = 0;
	curl_global_init(CURL_GLOBAL_ALL);
	curl_ = curl_easy_init();

	if (curl_ == NULL)
	{
		rc = -1;
		fprintf(stderr, "Curl Initialize Failed\n");
	}
	else
	{
		fprintf(stdout, "Curl Initialized\n");
	}

	return rc;
}

int CurlFini()
{
	curl_easy_cleanup(curl_);
	curl_global_cleanup();
}

int CurlRequestGET(const char *url)
{
	int rc = 0;

	if (curl_ == NULL)
	{
		rc = -1;
		return rc;
	}

	struct CurlResponse chunk = { .response = NULL, .size = 0 };

	curl_easy_setopt(curl_, CURLOPT_URL, url);
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)&chunk);

	CURLcode res = curl_easy_perform(curl_);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "Curl GET Response is not OK\n");
		free(chunk.response);
		return -1;
	}
	else
	{
		fprintf(stdout, "Curl GET Response is OK\n");
		printf("Response:\n%s\n", chunk.response);
	}

	free(chunk.response);

	return 0;
}

char *CurlRequestPOST(const char *url)
{
    if (curl_ == NULL)
    {
        fprintf(stderr, "Curl is NULL\n");
        return NULL;
    }

    struct CurlResponse chunk = { .response = NULL, .size = 0 };
    struct curl_slist *header = NULL;

    const char *jsonData = "{\"key\":\"value\"}";

    header = curl_slist_append(header, "Content-Type: application/json");

    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonData);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)&chunk);

    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl_);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "Curl POST Response is not OK: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(header);
        free(chunk.response);
        return NULL;
    }
    else
    {
        fprintf(stdout, "Curl POST Response is OK\n");
        printf("Response:\n%s\n", chunk.response);
    }

    curl_slist_free_all(header);
    
	return chunk.response;
}

static size_t CurlResponseCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct CurlResponse *mem = (struct CurlResponse *)userp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);

    if (ptr == NULL)
	{
        fprintf(stderr, "Not enough memory (realloc failed)\n");
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), contents, total_size);
    mem->size += total_size;
    mem->response[mem->size] = '\0';

    return total_size;
}

int DoJsonRequest(const char* url, const char* body_data)
{
	if (curl_ == NULL)
	{
		return -1;
	}

	int body_data_len = strlen(body_data);
	struct curl_slist *header = NULL;

	curl_easy_setopt(curl_, CURLOPT_URL, url);

	header = curl_slist_append(header, "Content-Type: application/json");
	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);

	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0);

	curl_easy_setopt(curl_, CURLOPT_POST, 1L);

	curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, body_data);
	curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, body_data_len);

	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlResponseCallback); 

	CURLcode res = curl_easy_perform(curl_);

	if (res != CURLE_OK)
	{
		curl_slist_free_all(header);
		fprintf(stderr, "\nCurl POST Response is not OK\n");
		return -1;
	}
	else
	{
		fprintf(stdout, "\nCurl POST Response is OK\n");
	}

	curl_slist_free_all(header);

	return 0;
}