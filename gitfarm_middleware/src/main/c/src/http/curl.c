#include "http/curl.h"

CURL *curl_;

int Curl_Init()
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

int Curl_Fini()
{
	curl_easy_cleanup(curl_);
	curl_global_cleanup();
}

int Curl_GET(const char *url)
{
	int rc = 0;

	if (curl_ == NULL)
	{
		rc = -1;
		return rc;
	}

	curl_easy_setopt(curl_, CURLOPT_URL, url);

	CURLcode res = curl_easy_perform(curl_);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "Curl GET Response is not OK\n");
		return -1;
	}
	else
	{
		fprintf(stdout, "Curl GET Response is OK\n");
	}

	return 0;
}

int Curl_POST(const char *url)
{
	if (curl_ == NULL)
	{
		fprintf(stderr, "Curl is NULL\n");
		return -1;
	}

	struct curl_slist *header = NULL;

	curl_easy_setopt(curl_, CURLOPT_URL, url);
	curl_easy_setopt(curl_, CURLOPT_POST, 1L);

	header = curl_slist_append(header, "Content-Type: application/json");
	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, header);

	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 1L);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 1L);

	curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, "data");

	CURLcode res = curl_easy_perform(curl_);

	if (res != CURLE_OK)
	{
		curl_slist_free_all(header);
		fprintf(stderr, "Curl POST Response is not OK\n");
		return -1;
	}
	else
	{
		fprintf(stdout, "Curl POST Response is OK\n");
	}

	curl_slist_free_all(header);

	return 0;
}

size_t Curl_Res_Callback(char* ptr, size_t size, size_t nmemb, const char* stream)
{
	int real_size = size * nmemb;

	fprintf(stdout, "Curl Res Callback real_size : %d\n", real_size);

	return real_size;
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

	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, Curl_Res_Callback); 

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