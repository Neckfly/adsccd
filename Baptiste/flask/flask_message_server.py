#!/usr/bin/env python3
from flask import Flask, current_app, request

class MessageFlask(Flask):

    def __init__(self, *args, **kwargs):
        super(MessageFlask, self).__init__(*args, **kwargs)
        self.MESSAGE_MAX_SIZE = 32
        self.user_message = "Undefined\n"

app = MessageFlask(__name__)

# adding a route using the decorator "route"
@app.route('/')
def root_message():
    return "Try '/message' to see the message or '/set_message' to change it\n"

# adding a route using the add_url_route function
def print_user_message():
    return current_app.user_message
app.add_url_rule('/message', 'user_message', print_user_message)

# adding a route with restricted POST method
def set_user_message():
    current_app.user_message = request.get_data(as_text=True)
    return "New message registered"

app.add_url_rule('/set_message', 'set_message', set_user_message,
                  methods=['POST'])    

if __name__ == '__main__':
    app.run()