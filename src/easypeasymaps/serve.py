import json
import os

import flask

app = flask.Flask(__name__)

@app.route("/")
def render_index():
    return flask.render_template('index.html')

if __name__ == "__main__":
    app.run(host="127.0.0.1", debug=True, port=8888, threaded=True)
