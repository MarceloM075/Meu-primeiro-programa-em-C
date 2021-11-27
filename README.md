<h1 align="center">Meu-primeiro-programa-em-C</h1>

Esse é um programa que fiz para um projeto de trabalho da faculdade.

### O que o programa faz
É um sistema para cadastrar pacientes com o diagnóstico positivo para Covid 19.
Após feito o login no sistema, aparecerá um menu com as opções para cadastrar, pesquisar paciente já cadastrado (via CPF), listar todos os pacientes cadastrados e deletar algum cadastro.

### Login e senha
Login: admin <br/>
Senha: 123

É possível fazer a alteração do login e senha abrindo o código fonte e alterando o valor de user e password (linhas 6 e 7, respectivamente).

### Cadastro do paciente
O sistema pedirá as informações dos pacientes, ao colocar todas as informações pedidas, o sistema criará um arquivo .bin, caso não exista, de nome Pacientes cadastrados, para que as informações possam ser consultadas posteriormente. 
O sistema também salva em um arquivo .txt os pacientes que pertencem ao grupo de risco.

### Listar pacientes cadastrados
Nesta opção, o sistema listará todos os pacientes já cadastrados.

### Pesquisa de paciente
Neste menu, é possível ver todos os dados de um paciente desejado, basta digitar o CPF do paciente que deseja ver os dados.
Caso não exista nenhum paciente com o CPF digitado, o sistema avisará.

### Deletar dados do paciente
Neste menu, assim como no de pesquisa, basta digitar o CPF do paciente. O sistema irá mostrar os dados do paciente, e perguntará se estes são so dados desejados para deletar. Se sim, o sistema deletará o arquivo com as informações do paciente.
Caso o arquivo não exista, o sistema avisará.
