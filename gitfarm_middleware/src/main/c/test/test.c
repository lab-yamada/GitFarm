#include "http/curl.h"

int main(int argc, const char *const *argv)
{
    const char *url = "http://localhost:8080/curl";

    int rc = 0;
    rc = Curl_Init();

    if (rc != 0)
    {
        return -1;
    }

    // rc = Curl_GET(url);

    // if (rc != 0)
    // {
    //     return -1;
    // }

    rc = Curl_POST(url);

    if (rc != 0)
    {
        return -1;
    }

    Curl_Fini();

    return 0;
}