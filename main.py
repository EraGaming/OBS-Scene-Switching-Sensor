from flask import Flask
from flask_restful import reqparse, abort, Api, Resource
import sys
import time
from obswebsocket import obsws, requests

host = "localhost"
port = 4444
password = "secret"

ws = obsws(host, port, password)
ws.connect()

app = Flask(__name__)
api = Api(app)

class SwitchScene(Resource):
    def get(self, scene_name):
        scene = ws.call(requests.GetCurrentScene())
        name = scene.getName()
        if name != scene_name:
            ws.call(requests.SetCurrentScene(scene_name))


api.add_resource(SwitchScene, '/<scene_name>')

if __name__ == '__main__':
    app.run(host="0.0.0.0", debug=True)
     