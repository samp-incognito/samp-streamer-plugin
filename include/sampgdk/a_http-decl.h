#ifndef DOXYGEN
#undef  HTTP
#define HTTP sampgdk_HTTP
#endif


/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/HTTP">HTTP on SA-MP Wiki</a> */
SAMPGDK_NATIVE(bool, HTTP(int index, int type, const char * url, const char * data));

#define HTTP_GET (1)
#define HTTP_POST (2)
#define HTTP_HEAD (3)
#define HTTP_ERROR_BAD_HOST (1)
#define HTTP_ERROR_NO_SOCKET (2)
#define HTTP_ERROR_CANT_CONNECT (3)
#define HTTP_ERROR_CANT_WRITE (4)
#define HTTP_ERROR_CONTENT_TOO_BIG (5)
#define HTTP_ERROR_MALFORMED_RESPONSE (6)


/**
 * \ingroup callbacks
 * \see <a href="http://wiki.sa-mp.com/wiki/OnHTTPResponse">OnHTTPResponse on SA-MP Wiki</a> */
SAMPGDK_CALLBACK(void, OnHTTPResponse(int index, int response_code, const char * data));
