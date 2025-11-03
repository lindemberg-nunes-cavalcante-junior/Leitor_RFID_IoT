from flask import *

app = Flask(__name__)

@app.route('/autenticar', methods=['GET'])
def autenticar():
    token = request.headers.get('Token')
    print(request.headers)
    return make_response(f'Usuario de UID: {token}')

app.run('192.168.10.135',8080)



        