#include <curl/curl.h>
#include <errno.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY1 "cle1"
#define KEY2 "cle2"
#define BADKEY "cle_fictive"
#define VALUE1 "valeur1"
#define VALUE2 "valeur2"

int main(int argc, char **argv) {
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
    const char *key;
    json_t *value;
    size_t index;
    FILE *stream;
    long status;
    char *url;

    server_url = argv[1];

    curl_global_init(CURL_GLOBAL_ALL);

    easy_handle = curl_easy_init();

    /******************************/
    /* Put of two key/value pairs */
    /******************************/
    /* building and setting put url */
    printf("\n\nPut of %s:%s and %s:%s\n\n", KEY1, VALUE1, KEY2, VALUE2);

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    free(url);

    /* preparing as a stream json put data */
    new_key_value_pairs_json = json_pack("{s:s, s:s}", KEY1, VALUE1, KEY2, VALUE2);

    stream_body = json_dumps(new_key_value_pairs_json, JSON_COMPACT);
    json_decref(new_key_value_pairs_json);

    stream_size = strlen(stream_body);
    stream = fmemopen(stream_body, stream_size, "r");

    /* setting easy_handle ready for PUT */
    curl_easy_setopt(easy_handle, CURLOPT_UPLOAD, 1L);

    curl_easy_setopt(easy_handle, CURLOPT_READDATA, stream);

    curl_easy_setopt(easy_handle, CURLOPT_INFILESIZE, stream_size);

    /* setting application/json as Content-Type */
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

    curl_easy_perform(easy_handle);
    fclose(stream);

    /*****************/
    /* Get one value */
    /*****************/
    printf("\n\nGetting one value from key %s\n\n", KEY2);

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    free(url);

    /* setting back stdout as curl write data */
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, stdout);

    /* setting back curl handle as a GET one */
    curl_easy_setopt(easy_handle, CURLOPT_HTTPGET, 1L);

    /* cleaning "Content-Type" header */
    curl_slist_free_all(headers);
    headers = NULL;
    headers = curl_slist_append(headers, "Content-Type:");

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

    curl_easy_perform(easy_handle);

    /************************************************/
    /* Post an existing key and an unregistered one */
    /************************************************/
    /* building and setting post url */
    printf("\n\nPost of keys %s and %s\n\n", KEY1, BADKEY);

    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    free(url);

    /* building json as post data */
    keys_json = json_pack("[s, s]", KEY1, BADKEY);

    keys_data = json_dumps(keys_json, JSON_COMPACT);
    json_decref(keys_json);

    curl_easy_setopt(easy_handle, CURLOPT_COPYPOSTFIELDS, keys_data);
    free(keys_data);

    /* setting application/json as Content-Type */
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

    /* preparing response buffer */
    stream = open_memstream(&stream_body, &stream_size);

    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, stream);

    /* performing http request */
    curl_easy_perform(easy_handle);
    fclose(stream);


    /* testing response status and getting json response */
    curl_easy_getinfo(easy_handle, CURLINFO_RESPONSE_CODE, &status);

    response_json = json_loads(stream_body, 0, &json_error);

    printf("We /post two keys, %ld are registered.\n",
           json_object_size(response_json));

    json_object_foreach(response_json, key, value) {
        printf("We got key:%s, value:%s\n", key, json_string_value(value));
    }
    json_decref(response_json);

    free(stream_body);
    curl_slist_free_all(headers);
    curl_easy_cleanup(easy_handle);
}
