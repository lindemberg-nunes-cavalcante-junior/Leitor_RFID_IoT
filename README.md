# Leitor_RFID_IoT

<h1>Funções da API</h1>

<h2>Função: Autenticar (Autenticação via JWT)</h2>

<p>Ao receber os dados do leitor RFID, a API deve prover uma authenticação segura através do processamento da UID e geração de token de acesso pelo JWT. A ideia é fazer a API gerar esse token de acesso vinculado, não só a UID, como também ao uma conta (usuário e senha) do local a ser implementado, para garantir o acesso certo ao tipo de usuário certo, possívelmente necessitaria de algo para vincular o local implementado aos tipos de acessos, exemplo: Sala1 (Acesso somente a: usuario1), então ao colocar o UID, já vinculado a uma conta do local, ser processado a UID, pegando o token de acesso e ver se ele está descrito no local correspondente ao acesso, para que assim seja liberado o acesso.</p>
