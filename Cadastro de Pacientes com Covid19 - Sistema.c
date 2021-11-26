#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h>

#define maxPacientes 1000 //número máximo de pacientes para cadastro.
char user[31] = "admin"; //coloque aqui o usuário padrão desejado, podendo conter no máximo 30 caractéres.
char password[31] = "123"; //coloque aqui a senha padrão desejada, podendo conter no máximo 30 caractéres.

FILE *arquivoPaciente;
FILE *arquivoRisco;
FILE *quantPacientesCovid;

static int id;//indice para manipular as informações de cada paciente.
int idade;//variável para fazer o calculo da idade do paciente.
int diaAtual, mesAtual, anoAtual;//variável para a data atual do sistema.

//armazenamento dos dados de cadastro dos pacientes.
typedef struct {
    char nome[50], rua[50], bairro[50], cidade[50], estado[50], email[50];
    char cpf[15], cep[10], telefone[13];
    int diaDiagnostico, mesDiagnostico, anoDiagnostico,  diaNascimento, mesNascimento, anoNascimento, numeroCasa, idadePaciente;
    char diabetes[4], obesidade[4], hipertensao[4], tuberculose[4];
}dados_paciente;
dados_paciente paciente[maxPacientes];
//fim do armazenamento dos dados dos pacientes.

//código main.
int main(void){
    int opcaoMenu;//variável para a manipulação do menu de opções.
    int permissaoEntrada = entradaSistema();//faz a chamada da função entradaSistema e atribui o seu retorno a permissaoEntrada.

    //struct para pegar a data atual do sistema. <time.h>.
    time_t meuTempo;
    meuTempo = time(NULL);
    struct tm data = *localtime(&meuTempo);
    anoAtual = data.tm_year+1900;
    mesAtual = data.tm_mon+1;
    diaAtual = data.tm_mday;
    //fim da struct de data atual.

    if (permissaoEntrada == 1){
        do{
            system("cls");//limpa as mensagens da tela.
            printf("========================== Bem-Vindo ==========================\n\n");
            printf("======================= MENU PRINCIPAL ========================");
            printf("\n                       Data: %d/%d/%d\n\n\n", diaAtual, mesAtual, anoAtual);
            printf(" Digite o numero equivalente para a opcao que deseja acessar:\n 1 - Cadastrar paciente\n 2 - Pesquisar pacientes cadastrados (pesquisa por CPF)\n 3 - Deletar algum paciente cadastrado\n 4 - Sair\n\n");
            fflush(stdin);//limpa o buffer do teclado, que pode conter alguma informação armazernada.
            scanf("%d", &opcaoMenu);
            switch(opcaoMenu){
                case 1://chama a função cadastroPaciente caso o usuário digite a opção 1.
                    cadastroPaciente();
                break;
                case 2://chama a função listarPacientes caso o usuário digite a opção 2.
                    listarPacientes();
                break;
                case 3://chama a função deletarCadastro caso o usuário digite a opção 3.
                    deletarCadastro();
                break;
                case 4://fecha o sistema caso o usuário digite a opção 4.
                    system("exit");
                break;
                default://caso o usuário não digite nenhuma das opções (1, 2 ou 3), o sistema informa que foi uma opção inválida.
                    printf(" Opcao invalida\n\n");
                    system("pause");
                break;
            }
        }while(opcaoMenu!=4);
    }
    return 0;
}
//fim do código main.

//inicio do código de login.
int entradaSistema(){
    char usuarioPadrao[30], senhaPadrao[30];//usuario pre-cadastrado e senha pre-cadastrada.
    char login[30], senha[30];//variáveis usadas para logar no sistema.
    int retornoLogin, retornoSenha;//verificacao do login e da senha.
    int contaExistente;//variavel que permite ou nao a entrada no sistema.
    
    strcpy(usuarioPadrao, user);//atribui user a variavel usuarioPadrao.
    strcpy(senhaPadrao, password);//atribui password a variavel senhaPadrao.
    do{//irá executar até que o login e senha estejam corretos.
        printf(" Digite seu login: ");
        scanf("%s", login);
        printf(" Digite sua senha: ");
        scanf("%s", senha);
        retornoLogin = strcmp(usuarioPadrao, login);//retorna o valor 0 quando os 2 argumentos sao iguais.
        retornoSenha = strcmp(senhaPadrao, senha);//retorna o valor 0 quando os 2 argumentos sao iguais.

        if ((retornoLogin == 0) && (retornoSenha == 0)){
            contaExistente=1;
        }else{
            contaExistente=0;
            printf(" Login e/ou senha invalidos.\nTente novamente.\n");
        }
    }while(contaExistente==0); 

    return contaExistente;
}   
//fim do cógido de login.

//inicio do código para o cadastro dos pacientes.
void cadastroPaciente(){
    int opcaoMenuCadastro;//variável para a manipulação do cadastro.
    int quantPacientes = 0;//variável para definir o valor da quantidade de pacientes caso não exista um arquivo ou um valor salvo.
    char nomeArquivo[50];//variável para salvar o nome do arquivo, antes de criar o arquivo.
    char txt[] = ".txt";//complemento do nome do arquivo.

    system("cls");

    quantPacientesCovid = fopen("Quantidade de pacientes com Covid19.bin", "rb");//abre o arquivo que mantém salvo a quantidade de pacientes cadastrados.

    //inicio do teste de abertura do arquivo que armazena a quantida de pacientes cadastrados.
    if(quantPacientesCovid == NULL){
        quantPacientesCovid = fopen("Quantidade de pacientes com Covid19.bin", "wb");
        fwrite(&quantPacientes, sizeof(quantPacientes), 5, quantPacientesCovid);
        printf(" Erro ao ler o numero de pacientes cadastrados!\n");
        printf(" Tentando criar o arquivo 'Quantidade de pacientes com Covid19.bin'...\n\n");
        printf(" Tente novamente, por favor!\n\n");
        system("pause");
        fclose(quantPacientesCovid);
        return 1;
    }else{
        fread(&id, sizeof(id), 5, quantPacientesCovid);
        fclose(quantPacientesCovid);
        printf("              %d pacientes cadastrados\n", id);
    }
    //fim do teste de abertura do arquivo.

    //teste para saber se a quantidade de pacientes cadastrados já não está no limite.
    if (id >= maxPacientes){
        printf("\n Limite de pacientes cadastrados alcancado.\n");
        printf(" Obrigado! Retornando ao menu principal...");
        system("pause");
        opcaoMenuCadastro = 0;
        return opcaoMenuCadastro;
    }
    //fim do teste.

    //incio do cadastro dos pacientes.
    do{
        printf("\n---------- Insira as informacoes do paciente %d ----------\n", id+1);
                
        printf("\n Nome: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].nome);
            
        printf(" CPF (apenas numeros): ");
        fflush(stdin);
        scanf("%s", nomeArquivo);
        strcpy(paciente[id].cpf, nomeArquivo);
        cpfPadronizador();

        printf(" Telefone: ");
        fflush(stdin);
        scanf("%12[^\n]", paciente[id].telefone);

        printf(" Rua: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].rua);

        printf(" Numero da casa: ");
        fflush(stdin);
        scanf("%d", &paciente[id].numeroCasa);

        printf(" Bairro: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].bairro);

        printf(" Cidade: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].cidade);;

        printf(" Estado: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].estado);

        printf(" CEP (apenas numeros): ");
        fflush(stdin);
        scanf("%9[^\n]", paciente[id].cep);
        cepPadronizador();

        printf(" Dia do nascimento: ");
        fflush(stdin);
        scanf("%2d", &paciente[id].diaNascimento);

        printf(" Mes do nascimento: ");
        fflush(stdin);
        scanf("%2d", &paciente[id].mesNascimento);

        printf(" Ano do nascimento: ");
        fflush(stdin);
        scanf("%4d", &paciente[id].anoNascimento);

        //calculo da idade do paciente.
        idade = anoAtual-paciente[id].anoNascimento;
        if(mesAtual<paciente[id].mesNascimento){
            idade -= 1;
        }else if(mesAtual==paciente[id].mesNascimento){
            if(diaAtual<paciente[id].diaNascimento){
                idade -= 1;
            }
        }
        paciente[id].idadePaciente = idade;
        //fim do calculo da idade do paciente.

        printf(" Email: ");
        fflush(stdin);
        scanf("%50[^\n]", paciente[id].email);

        printf(" Dia do diagnostico: ");
        fflush(stdin);
        scanf("%2d", &paciente[id].diaDiagnostico);

        printf(" Mes do diagnostico: ");
        fflush(stdin);
        scanf("%2d", &paciente[id].mesDiagnostico);

        printf(" Ano do diagnostico: ");
        fflush(stdin);
        scanf("%4d", &paciente[id].anoDiagnostico);

        printf("\n\n Diabetes?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente[id].diabetes);

        printf(" Hipertensao?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente[id].hipertensao);

        printf(" Tuberculose?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente[id].tuberculose);

        printf(" Obesidade?(sim/nao) ");
        fflush(stdin);
        scanf("%3[^\n]", paciente[id].obesidade);

        strcat(nomeArquivo, txt);

        arquivoPaciente = fopen(nomeArquivo, "w");

        fprintf(arquivoPaciente, " Nome: %s\n", paciente[id].nome);
        fprintf(arquivoPaciente, " CPF: %s\n", paciente[id].cpf);
        fprintf(arquivoPaciente, " Telefone: %s\n", paciente[id].telefone);
        fprintf(arquivoPaciente, " Endereco: Rua: %s, No.: %d, %s - %s/%s\n", paciente[id].rua, paciente[id].numeroCasa, paciente[id].bairro, paciente[id].cidade, paciente[id].estado);
        fprintf(arquivoPaciente, " CEP: %s\n", paciente[id].cep);
        fprintf(arquivoPaciente, " Nascimento: %d/%d/%d\n", paciente[id].diaNascimento, paciente[id].mesNascimento, paciente[id].anoNascimento);
        fprintf(arquivoPaciente, " Idade: %d\n", paciente[id].idadePaciente);
        fprintf(arquivoPaciente, " Email: %s\n", paciente[id].email);
        fprintf(arquivoPaciente, " Data do diagnostico: %d/%d/%d\n", paciente[id].diaDiagnostico, paciente[id].mesDiagnostico, paciente[id].anoDiagnostico);
        fprintf(arquivoPaciente, " Diabetes: %s\n", paciente[id].diabetes);
        fprintf(arquivoPaciente, " Hipertensao: %s\n", paciente[id].hipertensao);
        fprintf(arquivoPaciente, " Tuberculose: %s\n", paciente[id].tuberculose);
        fprintf(arquivoPaciente, " Obesidade: %s\n", paciente[id].obesidade);

        fclose(arquivoPaciente);

        retornoRisco();

        id++;
        quantPacientesCovid = fopen("Quantidade de pacientes com Covid19.bin", "wb");
        fwrite(&id, sizeof(id), 5, quantPacientesCovid);
        fclose(quantPacientesCovid);
        printf("\n\n");
        printf(" Deseja cadastrar mais pacientes? Digite 1 para sim ou qualquer outro numero para nao.\n\n");
        fflush(stdin);
        scanf("%d", &opcaoMenuCadastro);

    }while(opcaoMenuCadastro == 1);
    //fim do cadastro dos pacientes.
    fclose(arquivoPaciente);

}
//fim do código de cadastro dos pacientes.

//código para salvar os dados dos pacientes do grupo de risco.
void retornoRisco(){
    int retornoDiabetes, retornoHipertensao, retornoTuberculose, retornoObesidade;//variavel para a verificação do valor de .diabetes, .hipertensao, .tuberculose e .obesidade.

    if( (strcmp(paciente[id].diabetes, "sim")) || (strcmp(paciente[id].diabetes, "Sim")) || (strcmp(paciente[id].diabetes, "SIM"))){
        retornoDiabetes = 1;
    }else{
        retornoDiabetes = 0;
    }

    if( (strcmp(paciente[id].hipertensao, "sim")) || (strcmp(paciente[id].hipertensao, "Sim")) || (strcmp(paciente[id].hipertensao, "SIM"))){
        retornoHipertensao = 1;
    }else{
        retornoHipertensao = 0;
    }

    if( (strcmp(paciente[id].tuberculose, "sim")) || (strcmp(paciente[id].tuberculose, "Sim")) || (strcmp(paciente[id].tuberculose, "SIM"))){
        retornoTuberculose = 1;
    }else{
        retornoTuberculose = 0;
    }

    if( (strcmp(paciente[id].obesidade, "sim")) || (strcmp(paciente[id].obesidade, "Sim")) || (strcmp(paciente[id].obesidade, "SIM"))){
        retornoObesidade = 1;
    }else{
        retornoObesidade = 0;
    }

    //teste da abertura do arquivo de Grupo de Risco.
    arquivoRisco = fopen("Grupo de Risco.txt", "a");
    if(arquivoRisco == NULL){
        printf("\n Erro ao tentar abrir o arquivo Grupo de Risco!");
        printf("\n Tentando criar o arquivo...\n\n");
        arquivoRisco = fopen("Grupo de Risco", "w");
    }
    //fim do teste da abertura do arquivo de Grupo de Risco.

    //teste para saber se o paciente pertence ao grupo de risco e salvamento no arquivo.
    if((idade >= 65) || (retornoHipertensao == 1) || (retornoTuberculose == 1) || (retornoObesidade == 1)){
        fprintf(arquivoRisco, "-------------------------------------------------------\n"); 
        fprintf(arquivoRisco, " Nome do paciente: %s\n", paciente[id].nome);
        fprintf(arquivoRisco, " CEP: %s", paciente[id].cep);
        fprintf(arquivoRisco, "\n Idade: %d\n", paciente[id].idadePaciente);
        fprintf(arquivoRisco, "-------------------------------------------------------\n\n");            
    }
    //fim do teste para saber se o paciente pertence ao grupo de risco e salvamento no arquivo.
    fclose(arquivoRisco);
}
//fim do código para salvar os dados dos pacientes do grupo de risco.

//código para transformar o CPF de apenas números no padrao xxx.xxx.xxx-xx.
void cpfPadronizador(){
    char traco = '-';
    char ponto = '.';

    paciente[id].cpf[13] = paciente[id].cpf[10];
    paciente[id].cpf[12] = paciente[id].cpf[9];

    paciente[id].cpf[10] = paciente[id].cpf[8];
    paciente[id].cpf[9] = paciente[id].cpf[7];
    paciente[id].cpf[8] = paciente[id].cpf[6];

    paciente[id].cpf[6] = paciente[id].cpf[5];
    paciente[id].cpf[5] = paciente[id].cpf[4];
    paciente[id].cpf[4] = paciente[id].cpf[3];

    paciente[id].cpf[11] = traco;
    paciente[id].cpf[7] = ponto;
    paciente[id].cpf[3] = ponto;
}
//fim do código padronizador de CPF.

//código para transformar o cep de apenas números no padrão xxxxx-xxx.
void cepPadronizador(){
    char traco = '-';

    paciente[id].cep[8] = paciente[id].cep[7];
    paciente[id].cep[7] = paciente[id].cep[6];
    paciente[id].cep[6] = paciente[id].cep[5];

    paciente[id].cep[5] = traco;
}
//fim do código padronizador de CEP.

//código para listar os dados de um paciente pesquisando pelo CPF.
void listarPacientes(){
    char cpfPesquisa[50];
    char txt[] = ".txt";
    char lerDados[5000];
    int opcaoMenu;

    do{
        system("cls");
        printf(" Digite o numero do CPF do paciente para a pesquisa (apenas numeros): \n");
        fflush(stdin);
        scanf("%s", cpfPesquisa);
        
        strcat(cpfPesquisa, txt);

        arquivoPaciente = fopen(cpfPesquisa, "r");

        if (arquivoPaciente == NULL){
            printf("\n Nao foi possivel abrir o arquivo!\n");
            printf(" Verifique se o CPF esta correto!\n\n\n");
            system("pause");
            return 1;
        }

        system("cls");
        while (fgets(lerDados, 5000, arquivoPaciente) != NULL){
            printf("%s", lerDados);
        }
        fclose(arquivoPaciente);
        printf("\n\n Deseja visualizar os dados de mais pacientes? Digite 1 para sim ou qualquer outro numero para nao.\n\n");
        fflush(stdin);
        scanf("%d", &opcaoMenu);

    }while (opcaoMenu == 1);

}
//fim do código de pesquisa.

//código para deletar os dados dos pacientes.
void deletarCadastro(){
    char nomeArquivo[50];
    char txt[] = ".txt";
    char lerDados[5000];
    int confirmacaoDados;
    int opcaoMenu;
    int quantPacientes = 0;

    do{
        system("cls");
        printf(" Digite o numero do CPF do paciente que deseja apagar os dados (apenas numeros): \n");
        fflush(stdin);
        scanf("%s", nomeArquivo);

        strcat(nomeArquivo, txt);

        arquivoPaciente = fopen(nomeArquivo, "r");

        if (arquivoPaciente == NULL){
        printf("\n Nao foi possivel abrir o arquivo!\n");
        printf(" Verifique se o CPF esta correto!\n\n\n");
        system("pause");
        return 1;
        }

        system("cls");
        while (fgets(lerDados, 5000, arquivoPaciente) != NULL){
            printf("%s", lerDados);
        }

        fclose(arquivoPaciente);

        printf("\n\n Esses sao os dados do paciente que deseja excluir? Digite 1 para sim ou qualquer outro numero para nao.\n");
        fflush(stdin);
        scanf("%d", &confirmacaoDados);

        if(confirmacaoDados == 1){
            remove(nomeArquivo);
            quantPacientesCovid = fopen("Quantidade de pacientes com Covid19.bin", "rb");
            fread(&id, sizeof(id), 5, quantPacientesCovid);
            fclose(quantPacientesCovid);
            id--;
            quantPacientesCovid = fopen("Quantidade de pacientes com Covid19.bin", "wb");
            fwrite(&id, sizeof(id), 5, quantPacientesCovid);
            fclose(quantPacientesCovid);
        }

        printf("\n Deseja excluir mais algum dado de algum paciente? Digite 1 para sim e qualquer outro numero para nao.\n");
        fflush(stdin);
        scanf("%d", &opcaoMenu);

    }while(opcaoMenu == 1);
}
//fim do código para deletar os dados dos pacientes.
