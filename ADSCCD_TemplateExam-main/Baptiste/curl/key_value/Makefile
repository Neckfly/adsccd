all: flask_json_key_value_client

flask_json_key_value_client: flask_json_key_value_client.c
	gcc -o flask_json_key_value_client -D_GNU_SOURCE flask_json_key_value_client.c -lcurl \
        -ljansson

clean:
	rm flask_json_key_value_client
