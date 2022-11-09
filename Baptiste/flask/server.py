#!/usr/bin/env python3
from flask import Flask

app = Flask(__name__)

menu={}
menu["monday"]="burger"
menu["tuesday"]="pizza"
menu["wednesday"]="salad"
menu["thursday"]="burger"
menu["friday"]="pizza"
menu["saturday"]="salad"
menu["sunday"]="pasta"

@app.route('/menu/<day>')
def per_day_menu(day):
    print(f"Menu of {day} was asked")
    return menu[day]

@app.route('/rating/<dish>/<int:rate>')
def rating(dish, rate):
    print(f"Rate {rate} registered for dish {dish}")
    return f"Rate {rate} registered for dish {dish}"

if __name__ == '__main__':
    app.run()