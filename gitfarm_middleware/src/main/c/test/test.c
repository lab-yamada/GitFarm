#include "http/curl.h"

int main(int argc, const char *const *argv)
{
    const char *get_url = "https://jsonplaceholder.typicode.com/posts/1";

    int rc = 0;
    rc = CurlInit();

    if (rc != 0)
    {
        return -1;
    }

    rc = CurlRequestGET(get_url);

    if (rc != 0)
    {
        return -1;
    }

    const char *post_rul = "http://localhost:8080/curl";

    rc = CurlRequestPOST(post_rul);

    if (rc != 0)
    {
        return -1;
    }

    CurlFini();

    return 0;
}