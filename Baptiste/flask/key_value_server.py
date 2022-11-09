#!/usr/bin/env python3
from flask import Flask, current_app, request
from flask.json import jsonify

from jsonschema import validate, ValidationError

class KeyValueFlask(Flask):

    def __init__(self, *args, **kwargs):
        super(KeyValueFlask, self).__init__(*args, **kwargs)
        self.key_value = {}

app = KeyValueFlask(__name__)

# Any json dict with string as key and string as value provides key-value pairs.
PUT_JSON_SCHEMA = {
    "type": "object",
    "additionalProperties": {"type": "string"},
}

@app.route("/put", methods=['PUT'])
def put():
    new_objects = request.get_json()
    validate(new_objects, PUT_JSON_SCHEMA)

    for key, value in new_objects.items():
        current_app.key_value[key] = value

    return f"{new_objects} added"

@app.route("/get", methods=['GET'])
def get():
    key = request.args.get('key')

    value = current_app.key_value.get(key)

    return value

KEYS_JSON_SCHEMA = {
        "type": "array",
        "items": {"type": "string"},
}

@app.route("/post", methods=['POST'])
def post():
    keys = request.get_json()
    validate(keys, KEYS_JSON_SCHEMA)

    response = {}
    for key in keys:
        value = current_app.key_value.get(key)
        if value:
            response[key] = value

    return jsonify(response)

if __name__ == '__main__':
    app.run()