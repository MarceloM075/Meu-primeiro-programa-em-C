<h1 align="center">Meu-primeiro-programa-em-C</h1>

Esse é um programa que fiz para um projeto de trabalho da faculdade.

### O que o programa faz
É um sistema para cadastrar pacientes com o diagnóstico positivo para Covid 19.
Após feito o login no sistema, aparecerá um menu com as opções para cadastrar, pesquisar paciente já cadastrado (via CPF) e deletar algum cadastro (via CPF, também).

### Cadastro do paciente
Selecionando a opção de cadastro, o sistema verificará se existe um arquivo .bin que armazena a quantidade de pacientes já cadastrados, caso não exista, ele criará um.
Assim, que abrir o menu de cadastro, o sistema pedirá as informações dos pacientes. Colocando as todas as informações pedidas, o sistema criará um arquivo .txt de nome igual ao CPF de cada paciente, para que as informações possam ser consultadas posteriormente. 
O sistema também salva em um arquivo .txt os pacientes que pertencem ao grupo de risco.

### Pesquisa de paciente
Neste menu, é possível ver todos os dados de um paciente desejado, basta digitar o CPF do paciente que deseja ver os dados.
Caso não exista nenhum paciente com o CPF digitado, o sistema avisará.

### Deletar dados do paciente
Neste menu, assim como no de pesquisa, basta digitar o CPF do paciente. O sistema irá mostrar os dados do paciente, e perguntará se estes são so dados desejados para deletar. Se sim, o sistema deletará o arquivo com as informações do paciente.
Caso o arquivo não exista, o sistema avisará.
