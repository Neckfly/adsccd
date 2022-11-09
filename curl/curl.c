#include <curl/curl.h>


struct curl_slist *headers = NULL;
json_t *new_key_value_pairs_json;
char *stream_body = NULL;
json_error_t json_error;
json_t *response_json;
size_t stream_size;
CURL *easy_handle;
json_t *keys_json;
char *server_url;
char *keys_data;
CURLcode rc = 0;
json_t *value;
size_t index;
FILE *stream;
long status;
char *url;
char *key;

/* Initialisation curl */

rc = curl_global_init(CURL_GLOBAL_ALL);
easy_handle = curl_easy_init();

/* Construction de l'URL */

if (asprintf(&url, "%s/put", server_url) < 0) {
    fprintf(stderr, "Error on creating put url.\n");
    rc = ENOMEM; goto easy_clean;
}

rc = curl_easy_setopt(easy_handle, CURLOPT_URL, url);

/* preparation du JSON */

new_key_value_pairs_json = json_pack("{s:s, s:s}", KEY1, VALUE1, KEY2, VALUE2);
stream_body = json_dumps(new_key_value_pairs_json, JSON_COMPACT);
json_decref(new_key_value_pairs_json);
stream_size = strlen(stream_body);
stream = fmemopen(stream_body, stream_size, "r");


/* Option PUT */

rc = curl_easy_setopt(easy_handle, CURLOPT_UPLOAD, 1L);
rc = curl_easy_setopt(easy_handle, CURLOPT_READDATA, stream);
rc = curl_easy_setopt(easy_handle, CURLOPT_INFILESIZE, stream_size);
headers = curl_slist_append(headers, "Content-Type: application/json");
rc = curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);
rc = curl_easy_perform(easy_handle);













