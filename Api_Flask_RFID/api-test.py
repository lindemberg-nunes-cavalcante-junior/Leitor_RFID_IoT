from flask import *

app = Flask(__name__)

@app.route('/', methods=['GET'])
def main():
    return open('index.html','r')

app.run()



        