#include <jansson.h>


/* building json as post data */
new_objects_json = json_pack("[{s:s, s:i, s:s}, {s:s, s:i, s:s}]",
                             "name", "new_object_one", "price", 3,
                             "description", "cheep fashionable object one",
                             "name", "new_object_two", "price", 375,
                             "description", "expensive object two");

new_objects_data = json_dumps(new_objects_json, JSON_COMPACT);
json_decref(new_objects_json);