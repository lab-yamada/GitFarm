#include "application/curl.h"

int main(int argc, const char *const *argv)
{
    int rc = ExampleMethodGet();
    if (rc != 0)
    {
        return -1;
    }
    
    return 0;
}