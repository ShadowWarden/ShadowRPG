import json
import os
import flask


app = flask.Flask(__name__)

@app.route("/")
def render_index():

    mapping = []
    with open('tile_ascii_mapping.json') as mapping_file:    
        mapping = json.load(mapping_file)

    return flask.render_template('index.html', mapping=mapping)

if __name__ == "__main__":
    app.run(host="127.0.0.1", debug=True, port=8888, threaded=True)