from flask import *

app = Flask(__name__)

@app.route('/', methods=['GET'])
def main():
    return make_response(
        jsonify(response='Hellow World')
        )

app.run('10.235.93.245',8080)



        