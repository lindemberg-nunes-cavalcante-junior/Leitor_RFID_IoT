from flask import *

app = Flask(__name__)

@app.route('/', methods=['GET'])
def main():
    return make_response(
        jsonify(response='Hellow World')
        )

@app.route('/entrar', methods=['POST'])
def enter():

    data = request.json
    print(data)

    return make_response(
        'Sua resposta chegou'
    ) 

app.run('192.168.10.135',8080)



        