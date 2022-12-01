#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void cabecalho()
{
    printf("\t\t\t============================================================ \n");
    printf("\t\t\t\t\t\t SICAD-19 \n");
    printf("\t\t\t============================================================ \n");
}

void limparbuffer(void)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

struct ficha_do_paciente
{
    char nome_paciente[200];
    char cpf[12];
    char telefone[12];

    char rua[200];
    char numero_residencia[10];
    char bairro[200];
    char cidade[200];
    char estado[20];
    int cep;

    int nascimento_dia;
    int nascimento_mes;
    int nascimento_ano;

    char e_mail[200];

    char diagnostico_dia[3];
    char diagnostico_mes[3];
    char diagnostico_ano[5];
    char comorbidades[500];

    char grupo_risco[30];

}form_paciente;

struct dia_atual
{
    int dia_atual;
    int mes_atual;
    int ano_atual;
} data_hoje;

int risco_65(int nascimento_dia, int nascimento_mes, int nascimento_ano)
{

    if (nascimento_ano > (data_hoje.ano_atual - 65))
    {
        return 0;
    }
    else if (nascimento_ano == (data_hoje.ano_atual - 65))
    {
        if (nascimento_mes >= data_hoje.mes_atual)
        {
            if (nascimento_dia <= data_hoje.dia_atual)
            {
                return 1;
                ;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

void tela_login()
{
    char login[15];
    char syslogin[15] = "hospital123";
    char senha[15];
    char syssenha[15] = "hospital123";

    cabecalho();
    printf("\nSeja bem vindo ao sistema de cadastro de pacientes com Covid-19 \n");

    system("pause");
    system("cls");

telalogin:
    cabecalho();
    printf("Login: \n");
    scanf("%s", &login);
    printf("Senha: \n");
    scanf("%s", &senha);

    if (strcmp(login, syslogin) == 0 && strcmp(senha, syssenha) == 0)
    {
        printf("Bem vindo!");
        system("pause");
        system("cls");

        cabecalho();
        limparbuffer();
        printf("Digite o dia atual\n");
        scanf("%d", &data_hoje.dia_atual);
        limparbuffer();
        system("cls");

        cabecalho();
        printf("Digite o mes atual\n");
        scanf("%d", &data_hoje.mes_atual);
        limparbuffer();
        system("cls");

        cabecalho();
        printf("Digite o ano atual\n");
        scanf("%d", &data_hoje.ano_atual);
        limparbuffer();
        system("cls");
        MenuOpcoes();
    }
    else
    {
        printf("Login ou senha incorretos. \n");

        system("pause");
        system("cls");
        goto telalogin;
    }
}

void CadastroPacientes()
{

    int resposta;

    cabecalho();
    printf ("Digite o nome do paciente: \n");
    fgets(form_paciente.nome_paciente, 200, stdin);
    system("cls");

    cabecalho();
    printf("Digite o CPF sem pontos ou tracos: \n");
    fgets(form_paciente.cpf, 12, stdin);
    system("cls");
    limparbuffer();

    cabecalho();
    printf ("Digite o numero de telefone sem parenteses ou espacos: \n");
    fgets(form_paciente.telefone, 12, stdin);
    system("cls");
    limparbuffer();

    cabecalho();
    printf ("Qual o nome da rua em que o paciente mora? \n");
    fgets(form_paciente.rua, 200, stdin);
    system("cls");


    cabecalho();
    printf ("Qual o numero de residencia do paciente? \n");
    fgets(form_paciente.numero_residencia, 10, stdin);
    system("cls");

    cabecalho();
    printf ("Qual o bairro em que o paciente mora? \n");
    fgets(form_paciente.bairro, 200, stdin);
    system("cls");

    cabecalho();
    printf ("Qual a cidade esta situado este bairro? \n");
    fgets(form_paciente.cidade, 200, stdin);
    system("cls");

    cabecalho();
    printf ("Em qual Estado esta situado esta cidade? \n");
    fgets(form_paciente.estado, 20, stdin);
    system("cls");

    cabecalho();
    printf ("Em qual CEP esta situado este bairro? \n");
    scanf("%d", &form_paciente.cep);
    system("cls");

    cabecalho();
    printf("Qual o dia do nascimento do paciente? \n");
    scanf("%d", &form_paciente.nascimento_dia);
    system("cls");

    cabecalho();
    printf("Qual o mes do nascimento do paciente? \n");
    scanf("%d", &form_paciente.nascimento_mes);
    system("cls");

    cabecalho();
    printf("Qual o ano de nascimento do paciente? \n");
    scanf("%d", &form_paciente.nascimento_ano);
    system("cls");
    limparbuffer();

    cabecalho();
    printf ("Qual o e-mail do paciente? \n");
    fgets(form_paciente.e_mail, 200, stdin);
    system("cls");

    cabecalho();
    printf("Qual o dia do diagnostico do paciente? \n");
    fgets(form_paciente.diagnostico_dia, 3, stdin);
    system("cls");
    limparbuffer();

    cabecalho();
    printf("Qual o mes do diagnostico do paciente? \n");
    fgets(form_paciente.diagnostico_mes, 3, stdin);
    system("cls");
    limparbuffer();

    cabecalho();
    printf("Qual o ano do diagnostico do paciente? \n");
    fgets(form_paciente.diagnostico_ano, 5, stdin);
    system("cls");
    limparbuffer();

    cabecalho();
    printf ("O paciente possui comorbidades? Quais? \n");
    fgets(form_paciente.comorbidades, 500, stdin);
    system("cls");

    resposta = risco_65(form_paciente.nascimento_dia, form_paciente.nascimento_mes, form_paciente.nascimento_ano);

    if (resposta == 1)
    {
        strcpy(form_paciente.grupo_risco, "Maior de 65");
    }
    else if (resposta == 0)
    {
        strcpy(form_paciente.grupo_risco, "Menor de 65");
    }

    FILE *cadastro_paciente;
    cadastro_paciente = fopen(form_paciente.cpf, "w");
    if (cadastro_paciente == NULL)
    {
        printf("Erro ao gerar arquivo!");
        system("cls");
        MenuOpcoes();
    }

    fprintf(cadastro_paciente, "NOME: %s \n", form_paciente.nome_paciente);
    fprintf(cadastro_paciente, "CPF: %s \n", form_paciente.cpf);
    fprintf(cadastro_paciente, "TELEFONE: %s \n", form_paciente.telefone);
    fprintf(cadastro_paciente, "RUA: %s \n", form_paciente.rua);
    fprintf(cadastro_paciente, "NUMERO: %s \n", form_paciente.numero_residencia);
    fprintf(cadastro_paciente, "BAIRRO: %s \n", form_paciente.bairro);
    fprintf(cadastro_paciente, "CIDADE: %s \n", form_paciente.cidade);
    fprintf(cadastro_paciente, "ESTADO: %s \n", form_paciente.estado);
    fprintf(cadastro_paciente, "CEP: %d \n", form_paciente.cep);
    fprintf(cadastro_paciente, "DATA DE NASCIMENTO: %d / %d / %d\n", form_paciente.nascimento_dia, form_paciente.nascimento_mes, form_paciente.nascimento_ano);
    fprintf(cadastro_paciente, "E-MAIL: %s \n", form_paciente.e_mail);
    fprintf(cadastro_paciente, "DATA DO DIAGNOSTICO: %s / %s / %s \n", form_paciente.diagnostico_dia, form_paciente.diagnostico_mes, form_paciente.diagnostico_ano);
    fprintf(cadastro_paciente, "COMORBIDADES DO PACIENTE: %s \n", form_paciente.comorbidades);
    fprintf(cadastro_paciente, "PACIENTE PERTENCE AO GRUPO DE RISCO? %s \n", form_paciente.grupo_risco);

    fclose(cadastro_paciente);

    cabecalho();
    printf("\nCadastro completo!\n");
    system("pause");
    system("cls");

    MenuOpcoes();
}

void ConsultarPacientes()
{
    FILE *cadastro_paciente;
    char informacoes_paciente[20];
    char cpf[12];

    cabecalho();
    printf("Digite o CPF que deseja consultar: \n");
    scanf("%s", cpf);
    system("cls");

    cadastro_paciente = fopen(cpf, "r");

    if (cadastro_paciente == NULL)
    {
        cabecalho();
        printf("Erro na abertura do arquivo\n"); // se não houver o arquivo
        system("pause");
        system("cls");
        MenuOpcoes();
    }

    while (fgets(informacoes_paciente, 20, cadastro_paciente) != NULL)
    {
        printf("%s", informacoes_paciente);
    }

    fclose(cadastro_paciente);
    system("pause");
    system("cls");
    MenuOpcoes();
}

void MenuOpcoes()
{

    int opcao;

    cabecalho();
    printf("O que deseja fazer? \n");
    printf("[1] Cadastro de pacientes. \n");
    printf("[2] Consultar informacoes de pacientes. \n");
    printf("[3] Fechar o programa. \n");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
        system("cls");
        limparbuffer();
        CadastroPacientes();

    case 2:
        system("cls");
        ConsultarPacientes();
    case 3:
        system("cls");
        cabecalho();
        printf("Ate a proxima.\n");
        system("pause");
        exit(0);
    default:
        printf("Opcao Invalida.");
        break;
    }
}

int main()
{
    tela_login();
    system("cls");
}
