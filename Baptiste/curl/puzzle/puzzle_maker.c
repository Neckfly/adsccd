#include <curl/curl.h>
#include <errno.h>
#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    struct curl_slist *headers = NULL;
    char *new_piece_data = NULL;
    json_t *new_piece_json;
    json_error_t json_error;
    json_t *response_json;
    FILE *response_stream;
    char *response = NULL;
    size_t response_size;
    CURL *easy_handle;
    char *new_piece_url = "http://127.0.0.1:5000/puzzle";
    CURLcode rc = 0;
    long status;
    unsigned int piece_number;
    unsigned int x;
    unsigned int y;
    bool next_piece = false;

    curl_global_init(CURL_GLOBAL_ALL);
    easy_handle = curl_easy_init();

    curl_easy_setopt(easy_handle, CURLOPT_URL, new_piece_url);

    /* setting application/json as Content-Type */
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

    /* try each piece at each place */
    for (piece_number = 1; piece_number <= 100; piece_number++) {
        next_piece = false;
        printf("Try piece %u\n", piece_number);
        for (x = 1; x <= 10 && next_piece == false; x++) {
            for (y = 1; y <= 10 && next_piece == false; y++) {
                /* building json as post data */
                new_piece_json = json_pack("{s:i, s:i, s:i}", "piece", piece_number, "x_abscissa", x, "y_ordinate", y);

                new_piece_data = json_dumps(new_piece_json, JSON_COMPACT);
                json_decref(new_piece_json);
            
                curl_easy_setopt(easy_handle, CURLOPT_COPYPOSTFIELDS, new_piece_data);
                free(new_piece_data);
            
                /* preparing response buffer */
                response_stream = open_memstream(&response, &response_size);
            
                curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, response_stream);
            
                /* performing http request */
                curl_easy_perform(easy_handle);
                fclose(response_stream);        
            
                /* testing response status */
                curl_easy_getinfo(easy_handle, CURLINFO_RESPONSE_CODE, &status);
            
                switch (status) {
                case 200:
                    next_piece = true;
                    printf("Puzzle terminé, voici la réponse du serveur :\n%s\n", response);
                free(response);
                break;
                    case 201:
                        free(response);
                        next_piece = true;
                if (piece_number == 71)
                            printf("Piece 71 : x %u, y %u.\n", x, y);
                        break;
                    case 202:
                        free(response);
                break;
            }
        }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();
}