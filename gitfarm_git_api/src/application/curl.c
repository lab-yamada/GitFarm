#include "application/curl.h"

int ExampleMethodGet()
{
	const char* url = "https://www.postman-echo.com/";

	CURL* curl = curl_easy_init();

	if (curl == NULL)
	{
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	{
		return -1;
	}

	curl_easy_cleanup(curl);

	return 0;
}