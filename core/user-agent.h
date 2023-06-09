/** @file user-agent.h */

#ifndef USER_AGENT_H
#define USER_AGENT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <curl/curl.h>

#include "error.h" /* CCORDcode */
#include "logconf.h" /* logging facilities */

/** @brief HTTP methods */
enum http_method {
    HTTP_INVALID = -1,
    HTTP_DELETE,
    HTTP_GET,
    HTTP_POST,
    HTTP_MIMEPOST,
    HTTP_PATCH,
    HTTP_PUT
};

/**
 * @brief Get the HTTP method name string
 *
 * @param method the HTTP method
 * @return the HTTP method name
 */
const char *http_method_print(enum http_method method);

/**
 * @brief Get the HTTP method enumerator from a string
 *
 * @param method the HTTP method string
 * @return the HTTP method enumerator
 */
enum http_method http_method_eval(char method[]);

/** @defgroup HttpStatusCode
 * @see https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 *  @{ */
#define HTTP_OK                   200
#define HTTP_CREATED              201
#define HTTP_NO_CONTENT           204
#define HTTP_NOT_MODIFIED         304
#define HTTP_BAD_REQUEST          400
#define HTTP_UNAUTHORIZED         401
#define HTTP_FORBIDDEN            403
#define HTTP_NOT_FOUND            404
#define HTTP_METHOD_NOT_ALLOWED   405
#define HTTP_UNPROCESSABLE_ENTITY 422
#define HTTP_TOO_MANY_REQUESTS    429
#define HTTP_GATEWAY_UNAVAILABLE  502
/** @} */

/**
 * @brief Get the HTTP status code name string
 *
 * @param httpcode the HTTP status code
 * @return the HTTP status code name
 */
const char *http_code_print(int httpcode);

/**
 * @brief Get the HTTP status code reason string
 *
 * @param httpcode the HTTP status code
 * @return the HTTP status code reason
 */
const char *http_reason_print(int httpcode);

/**
 * @struct user_agent
 * @brief Opaque User-Agent handle
 *
 * @see ua_init(), ua_cleanup(), ua_set_url(), ua_get_url(), ua_set_opt()
 */
struct user_agent;

/**
 * @struct ua_conn
 * @brief Opaque connection handle
 *
 * @see ua_conn_start(), ua_conn_setup(), ua_conn_reset(), ua_conn_stop(),
 *       ua_conn_easy_perform(), ua_conn_add_header(), ua_conn_print_header(),
 *       ua_conn_set_mime(), ua_conn_get_easy_handle()
 */
struct ua_conn;

/** @brief User-Agent handle initialization attributes */
struct ua_attr {
    /** pre-initialized logging module */
    struct logconf *conf;
};

/** @brief Read-only generic sized buffer */
struct ua_szbuf_readonly {
    /** the buffer's start */
    const char *start;
    /** the buffer's size in bytes */
    size_t size;
};

/** @brief header fields to have its contents hidden when logging */
struct ua_log_filter {
    /** list of headers */
    struct ua_szbuf_readonly *headers;
    /** amount of headers to be filtered */
    size_t length;
};

/** @brief Connection attributes */
struct ua_conn_attr {
    /** the HTTP method of this transfer (GET, POST, ...) */
    enum http_method method;
    /** the optional request body, can be NULL */
    char *body;
    /** the request body size */
    size_t body_size;
    /** the endpoint to be appended to the base URL */
    char *endpoint;
    /** optional base_url to override ua_set_url(), can be NULL */
    char *base_url;
    /** @brief header fields to have its contents filtered when logging */
    struct ua_log_filter log_filter;
};

/** Maximum amount of header pairs */
#define UA_MAX_HEADER_PAIRS 100 + 1

/** @brief Structure for storing the request's response header */
struct ua_resp_header {
    /** response header buffer */
    char *buf;
    /** response header string length */
    size_t len;
    /** real size occupied in memory by buffer */
    size_t bufsize;
    /** array of header field/value pairs */
    struct {
        struct {
            /** offset index of 'buf' for the start of field or value */
            size_t idx;
            /** length of individual field or value */
            size_t size;
        } field, value;
    } pairs[UA_MAX_HEADER_PAIRS];
    /** amount of pairs initialized */
    int n_pairs;
};

/** @brief Structure for storing the request's response body */
struct ua_resp_body {
    /** response body buffer */
    char *buf;
    /** response body string length */
    size_t len;
    /** real size occupied in memory by buffer */
    size_t bufsize;
};

/** @brief Informational handle received on request's completion */
struct ua_info {
    /** logging informational */
    struct loginfo loginfo;
    /** response code for latest request */
    CCORDcode code;
    /** the HTTP response code */
    long httpcode;

    /** @privatesection */

    /** the response header */
    struct ua_resp_header header;
    /** the response body */
    struct ua_resp_body body;
};

/**
 * @brief Callback to be called on each libcurl's easy handle initialization
 *
 * @param ua the User-Handle created with ua_init()
 * @param data user data to be passed along to `callback`
 * @param callback the user callback
 */
void ua_set_opt(struct user_agent *ua,
                void *data,
                void (*callback)(struct ua_conn *conn, void *data));

/**
 * @brief Initialize User-Agent handle
 *
 * @param attr optional attributes to override defaults
 * @return the user agent handle
 */
struct user_agent *ua_init(struct ua_attr *attr);

/**
 * @brief Cleanup User-Agent handle resources
 *
 * @param ua the User-Agent handle created with ua_init()
 */
void ua_cleanup(struct user_agent *ua);

/**
 * @brief Set the request url
 *
 * @param ua the User-Agent handle created with ua_init()
 * @param base_url the base request url
 */
void ua_set_url(struct user_agent *ua, const char base_url[]);

/**
 * @brief Get the request url
 *
 * @param ua the User-Agent handle created with ua_init()
 * @return the request url set with ua_set_url()
 */
const char *ua_get_url(struct user_agent *ua);

/** @brief Callback for object to be loaded by api response */
typedef void (*ua_load_obj_cb)(char *str, size_t len, void *p_obj);

/** @brief User callback to be called on request completion */
struct ua_resp_handle {
    /** callback called when a successful transfer occurs */
    ua_load_obj_cb ok_cb;
    /** the pointer to be passed to ok_cb */
    void *ok_obj;
    /** callback called when a failed transfer occurs */
    ua_load_obj_cb err_cb;
    /** the pointer to be passed to err_cb */
    void *err_obj;
};

/**
 * @brief Perform a blocking REST transfer
 *
 * @param ua the User-Agent handle created with ua_init()
 * @param info optional informational handle on how the request went
 * @param handle the optional response callbacks, can be NULL
 * @param attr connection attributes
 * @param body the optional request body, can be NULL
 * @param method the HTTP method of this transfer (GET, POST, ...)
 * @param endpoint the endpoint to be appended to the URL set at ua_set_url()
 * @CCORD_return
 * @note This is an easy, yet highly abstracted way of performing requests.
 *        If a higher control is necessary, users are better off using the
 *        functions of `ua_conn_xxx()` family.
 */
CCORDcode ua_easy_run(struct user_agent *ua,
                      struct ua_info *info,
                      struct ua_resp_handle *handle,
                      struct ua_conn_attr *attr);

/**
 * @brief Get a connection handle and mark it as running
 *
 * @param conn the User-Agent handle created with ua_init()
 * @return a connection handle
 */
struct ua_conn *ua_conn_start(struct user_agent *ua);

/**
 * @brief Perform a blocking transfer
 *
 * @param conn the connection handle
 * @CCORD_return
 */
CCORDcode ua_conn_easy_perform(struct ua_conn *conn);

/**
 * @brief Add a field/value pair to the request header
 *
 * @param conn the connection handle
 * @param field header's field to be added
 * @param value field's value
 */
void ua_conn_add_header(struct ua_conn *conn,
                        const char field[],
                        const char value[]);

/**
 * @brief Remove a header field
 *
 * @param conn the connection handle
 * @param field header's field to be removed
 */
void ua_conn_remove_header(struct ua_conn *conn, const char field[]);

/**
 * @brief Fill a buffer with the request header
 *
 * @param conn the connection handle
 * @param buf the user buffer to be filled
 * @param bufsize the user buffer size in bytes
 * @param log_filter headers to have its contents hidden when logging
 * @return the user buffer
 */
char *ua_conn_print_header(struct ua_conn *conn,
                           char *buf,
                           size_t bufsize,
                           struct ua_log_filter *log_filter);
/**
 * @brief Multipart creation callback for `conn`
 *
 * @param conn the connection handle to send multipart body
 * @param data user data to be passed along to `callback`
 * @param callback the user callback
 * @see https://curl.se/libcurl/c/smtp-mime.html
 */
void ua_conn_set_mime(struct ua_conn *conn,
                      void *data,
                      void (*callback)(curl_mime *mime, void *data));

/**
 * @brief Reset a connection handle fields
 *
 * @param conn connection handle to be reset
 * @warning this won't deactivate the handle, for that purpose check
 *        ua_conn_stop()
 */
void ua_conn_reset(struct ua_conn *conn);

/**
 * @brief Stop a connection handle and mark it as idle
 *
 * @param conn connection handle to be deactivated
 */
void ua_conn_stop(struct ua_conn *conn);

/**
 * @brief Setup transfer attributes
 *
 * @param conn the connection handle
 * @param attr attributes to be set for transfer
 */
void ua_conn_setup(struct ua_conn *conn, struct ua_conn_attr *attr);

/**
 * @brief Get libcurl's easy handle assigned to `conn`
 *
 * @param conn the connection handle
 * @return the libcurl's easy handle
 */
CURL *ua_conn_get_easy_handle(struct ua_conn *conn);

/**
 * @brief Extract information from `conn` previous request
 *
 * @param conn the connection handle
 * @param info handle to store information on previous request
 * @CCORD_return
 */
CCORDcode ua_info_extract(struct ua_conn *conn, struct ua_info *info);

/**
 * @brief Cleanup informational handle
 *
 * @param info handle containing information on previous request
 */
void ua_info_cleanup(struct ua_info *info);

/**
 * @brief Get a value's from the response header
 *
 * @param info handle containing information on previous request
 * @param field the header field to fetch the value
 * @return a @ref ua_szbuf_readonly containing the field's value
 */
struct ua_szbuf_readonly ua_info_get_header(struct ua_info *info,
                                            char field[]);

/**
 * @brief Get the response body
 *
 * @param info handle containing information on previous request
 * @return a @ref ua_szbuf_readonly containing the response body
 */
struct ua_szbuf_readonly ua_info_get_body(struct ua_info *info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USER_AGENT_H */
