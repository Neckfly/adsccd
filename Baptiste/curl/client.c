#include <curl/curl.h>
#include <errno.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    struct curl_slist *headers = NULL;
    json_t *val_json;
    char *val_data = NULL;

    FILE *response_stream;
    char *response = NULL;
    size_t response_size;

    CURL *easy_handle;
    long status;
    char *url = "http://127.0.0.1:5000";

    curl_global_init(CURL_GLOBAL_ALL);
    easy_handle = curl_easy_init();

    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(easy_handle, CURLOPT_URL, url);
    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);
    // CURLOPT_URL                  set targetURL
    // CURLOPT_HTTPHEADER           set request header
    // CURLOPT_READFUNCTION
    // CURLOPT_READDATA
    // CURLOPT_WRITEFUNCTION
    // CURLOPT_WRITEDATA
    // CURLOPT_UPLOAD
    // CURLOPT_INFILESIZE
    // CURLOPT_HTTPGET
    // CURLOPT_COPYPOSTFIELDS

    val_json = json_pack("{s:s, s:i}", "key1", "val1", "key2", 42);
    val_data = json_dumps(val_json, JSON_COMPACT);
    json_decref(val_json);

    curl_easy_setopt(easy_handle, CURLOPT_COPYPOSTFIELDS, val_data);

    /* preparing response buffer */
    response_stream = open_memstream(&response, &response_size);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, response_stream);

    curl_easy_perform(easy_handle);
    fclose(response_stream); 

    /* testing response status */
    curl_easy_getinfo(easy_handle, CURLINFO_RESPONSE_CODE, &status);
   
    switch (status) {
        case 200:
            printf("%s\n", response);
            break;
        case 201:
            break;
        case 202:
            break;

    curl_slist_free_all(headers);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();
}