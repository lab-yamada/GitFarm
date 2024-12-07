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

void CurlHeaderAdd(CurlHeader **head, const char *headerName)
{
    CurlHeader *newHeader = (CurlHeader *)malloc(sizeof(CurlHeader));

    if (!newHeader)
	{
        perror("Failed to allocate memory for new header");
        return;
    }

    strcpy(newHeader->data.name, headerName);
    newHeader->link = NULL;

    if (*head == NULL)
	{
        *head = newHeader;
    }
	else
	{
        CurlHeader *current = *head;
        while (current->link != NULL)
		{
            current = current->link;
        }
        current->link = newHeader;
    }
}

void CurlHeaderFini(CurlHeader *head)
{
	CurlHeader *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->link;
		free(temp);
	}
}

char *CurlRequestGET(const char *url, CurlHeader *headerArray)
{
	if (curl_ == NULL)
    {
        fprintf(stderr, "%s, Curl is NULL\n", LOG_GET);
        return NULL;
    }

	CurlResponse response = {NULL, 0};
	struct curl_slist *header = NULL;

	CurlHeader *current = headerArray;
    while (current != NULL)
	{
		fprintf(stdout, "%s, Header : %s\n", LOG_GET, current->data.name);
        header = curl_slist_append(header, current->data.name);
        current = current->link;
    }

	if (header == NULL)
	{
		fprintf(stderr, "%s, Header is NULL\n", LOG_GET);
		return NULL;
	}

	curl_easy_setopt(curl_, CURLOPT_URL, url);
	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)&response);

	CURLcode res = curl_easy_perform(curl_);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "%s, Response is not OK\n", LOG_GET);
		curl_slist_free_all(header);
        free(response.response);
		return NULL;
	}
	else
    {
        fprintf(stdout, "%s, Response is OK\n", LOG_GET);
    	// fprintf(stdout, "%s, ===== Response =====\n%s\n====================================================\n", LOG_GET, response.response);
    }

	CurlHeaderFini(headerArray);
    curl_slist_free_all(header);

	return response.response;
}

char *CurlRequestPOST(const char *url, CurlHeader *headerArray)
{
    if (curl_ == NULL)
    {
        fprintf(stderr, "%s, Curl is NULL\n", LOG_POST);
        return NULL;
    }

    CurlResponse response = {NULL, 0};
    struct curl_slist *header = NULL;

    const char *jsonData = "{\"key\":\"value\"}";

	CurlHeader *current = headerArray;
    while (current != NULL)
	{
		fprintf(stdout, "%s, Header : %s\n", LOG_POST, current->data.name);
        header = curl_slist_append(header, current->data.name);
        current = current->link;
    }

	if (header == NULL)
	{
		fprintf(stderr, "%s, Header is NULL\n", LOG_POST);
		return NULL;
	}

    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_POST, 1L);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, jsonData);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)&response);

    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode res = curl_easy_perform(curl_);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "%s, Response is not OK: %s\n", LOG_POST, curl_easy_strerror(res));
        curl_slist_free_all(header);
        free(response.response);
        return NULL;
    }
    else
    {
        fprintf(stdout, "%s, Response is OK\n", LOG_POST);
    	// fprintf(stdout, "%s, ===== Response =====\n%s\n====================================================\n", LOG_POST, response.response);
    }

	CurlHeaderFini(headerArray);
    curl_slist_free_all(header);
    
	return response.response;
}

static size_t CurlResponseCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
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