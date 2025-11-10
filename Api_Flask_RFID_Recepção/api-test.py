from flask import *
from flask_jwt_extended import *
from datetime import timedelta

app = Flask(__name__)

app.config["JWT_SECRET_KEY"] = "teste"
app.config["JWT_ACCESS_TOKEN_EXPIRES"] = timedelta(days=999)

jwt = JWTManager(app)

Banco = {}

@app.route('/teste', methods=['GET'])
def main():
    return make_response('Conectado')

#O hardware necessita enviar um Json contendo:
#UID: (UID da tag)
#USER: (usuario da conta/tag)
#PASS: (Senha do usuario da conta/tag)
@app.route('/autenticar', methods=['GET'])
def autenticar():

    print(request.headers["Token"])
    print(request.headers["Host"])
    
    access = create_access_token(identity=[request.headers["Host"],request.headers["Token"]])

    print(access)

    return ''


app.run('192.168.10.135',8080)



'''
Plano de Funções para a Api:

1- Gerador de Token: Uma função, que possivelmente vai precisar de uma pagina para fazer o login, que irá pegar o login e fazer o token.
2- autenticar: a função principal da api que irá receber o token e liberar a passagem.
'''


'''@app.route('/', methods=['GET'])
@jwt_required()
def connect():

    current_user = get_jwt_identity()
    
    if("ALUNO" in current_user and current_user["ALUNO"]):
        return make_response(f'acesso garantido,aluno')
    elif("PROFESSOR" in current_user and current_user["PROFESSOR"]):
        return make_response(f'Acesso garantido, professor')'''

        