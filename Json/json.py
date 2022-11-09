#Schéma de structure du json
JSON_SCHEMA_EXEMPLE = {
        "type" : "object",
        "properties" : {
        "price" : {"type" : "number"}, "name" : {"type" : "string"},
        }
}

#######
# PUT #
#######

KEYS_JSON_SCHEMA = {
        "type": "array",
        "items": {"type": "string"},
}

@app.route("/put", methods=['PUT'])
def put():
    new_objects = request.get_json()
    try:
        validate(new_objects, PUT_JSON_SCHEMA)
    except ValidationError as exc:
        raise BadRequest(str(exc))

    for key, value in new_objects.items():
        current_app.key_value[key] = value

    return f"{new_objects} added"

#######
# GET #
#######

@app.route("/get", methods=['GET'])
def get():
    key = request.args.get('key')
    if not key:
        raise BadRequest("A get must have a key parameter")

    value = current_app.key_value.get(key)
    if not value:
        raise BadRequest(f"The asked key \'{key}\' is not a registered one.")

    return value

########
# POST #
########

@app.route("/post", methods=['POST'])
def post():
    keys = request.get_json()
    try:
        validate(keys, KEYS_JSON_SCHEMA)
    except ValidationError as exc:
        raise BadRequest(str(exc))

    response = {}
    for key in keys:
        value = current_app.key_value.get(key)
        if value:
            response[key] = value

    return jsonify(response)