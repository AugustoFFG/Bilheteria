#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


struct ESPETACULO{
    char ID[4];
    char titulo[21];
    char direcao[21];
    int duracao; //(em minutos)
    int etaria;
    char data[9]; //(dd/mm/aa)
    char horario[6]; //(hh:mm)
};

typedef struct ESPETACULO espetaculo;


struct USUARIO{
    char nome[21];
    char senha[11];
    char tipo;
};

typedef struct USUARIO usuario;


struct ASSENTOS{
    char sessao[4]; //ID
    char fileira;
    char cadeiras[17];
};

typedef struct ASSENTOS assentos;


FILE* arq_usuario;
FILE* arq_assentos;
FILE* arq_espetaculo;
FILE* arq_temp;

int numSessoes = 0;
int numAssentos = 0;
int numUsuarios = 0;

usuario ChecarUsuario;
assentos ChecarAssentos;
espetaculo ChecarEspetaculo;
espetaculo EscreverEspetaculo;


void Layout(char id[4]){

	arq_assentos = fopen("assentos.txt", "r");

    if (arq_assentos == NULL) {
        printf("\nErro na abertura dde arquivo!\n");
        return;
    }

	char matriz_cadeiras[7][17];
	matriz_cadeiras[0][0] = '-';
	matriz_cadeiras[1][0] = '-';
	matriz_cadeiras[2][0] = '-';
	matriz_cadeiras[3][0] = '-';
	matriz_cadeiras[4][0] = '-';
	matriz_cadeiras[5][0] = '-';
	matriz_cadeiras[6][0] = '-';

	assentos mostra;

	while(fscanf(arq_assentos, "%s %c %s", mostra.sessao, &mostra.fileira, mostra.cadeiras)==3){
		if(strcmp(id, mostra.sessao)==0){
			if(mostra.fileira == 'A'){
				matriz_cadeiras[0][0] = 'A';
				for(int i=1; i<17; i++){
					matriz_cadeiras[0][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'B'){
				matriz_cadeiras[1][0] = 'B';
				for(int i=1; i<17; i++){
					matriz_cadeiras[1][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'C'){
				matriz_cadeiras[2][0] = 'C';
				for(int i=1; i<17; i++){
					matriz_cadeiras[2][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'D'){
				matriz_cadeiras[3][0] = 'D';
				for(int i=1; i<17; i++){
					matriz_cadeiras[3][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'E'){
				matriz_cadeiras[4][0] = 'E';
				for(int i=1; i<17; i++){
					matriz_cadeiras[4][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'F'){
				matriz_cadeiras[5][0] = 'F';
				for(int i=1; i<17; i++){
					matriz_cadeiras[5][i] = mostra.cadeiras[i-1];
				}
			}else if(mostra.fileira == 'G'){
				matriz_cadeiras[6][0] = 'G';
				for(int i=1; i<17; i++){
					matriz_cadeiras[6][i] = mostra.cadeiras[i-1];
				}
			}
		}
	}

	for(int i = 0; i<7; i++){
		for(int j = 1; j<17; j++){
			if(matriz_cadeiras[i][0]!='-'){
				continue;
			}else{
				matriz_cadeiras[i][j] = '.';
			}
		}
	}

	matriz_cadeiras[0][0] = 'A';
	matriz_cadeiras[1][0] = 'B';
	matriz_cadeiras[2][0] = 'C';
	matriz_cadeiras[3][0] = 'D';
	matriz_cadeiras[4][0] = 'E';
	matriz_cadeiras[5][0] = 'F';
	matriz_cadeiras[6][0] = 'G';

	printf("\n===== Assentos =====\n\n");
	printf("   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16\n");
	for(int j=0;j<7;j++){
		for(int k=0; k<17; k++){
			printf("%c  ", matriz_cadeiras[j][k]);
		}
		printf("\n");
	}
	printf("\n");
	fclose(arq_assentos);
}


int verificarCredenciais(char *login, char *senha, char tipoAcesso, usuario *usuarios, int numUsuarios) {
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(login, usuarios[i].nome) == 0 && strcmp(senha, usuarios[i].senha) == 0) {
            if (tipoAcesso == usuarios[i].tipo) {
                if (tipoAcesso == 'G') {
                    return 1;
                } else if (tipoAcesso == 'B') {
                    return 2;
                }
            } else {
                return 0;
            }
        }
    }
    return 0;
}


void CadastrarUsuario(){
    usuario Inserir;

    arq_usuario = fopen ("usuarios.txt","a");

    if (arq_usuario == NULL) {
        printf("\nErro na abertura dde arquivo!\n");
        return;
    }

    system("clear || cls");

    fflush(stdin);
    printf("Digite o nome do usuário a ser incluido: ");
    scanf("%s", Inserir.nome);
    printf("Digite a senha do usuário a ser incluido: ");
    scanf("%s", Inserir.senha);
    fflush(stdin);
    printf("Digite o tipo do usuário a ser incluido: ");
    scanf(" %c", &Inserir.tipo);

    fprintf(arq_usuario,"\n%s %s %c",Inserir.nome, Inserir.senha, Inserir.tipo);

    system("clear || cls");

    printf("\nusuario cadastrado!!\n\n");

    fclose(arq_usuario);
}


void EditarUsuario(){

    usuario usuarioedit;
    char nomeUsuario[21];

    arq_usuario = fopen("usuarios.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if (arq_usuario == NULL || arq_temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    system("clear || cls");

    printf("digite o nome do usuario a ser editado: ");
    scanf("%s", nomeUsuario);

    while (fscanf(arq_usuario, "%s %s %c", usuarioedit.nome, usuarioedit.senha, &usuarioedit.tipo) == 3) {
        if (strcmp(usuarioedit.nome, nomeUsuario) == 0) {
            printf("Novo login: ");
            scanf("%s", usuarioedit.nome);
            printf("Nova senha: ");
            scanf("%s", usuarioedit.senha);
            printf("Novo tipo: ");
            scanf(" %c", &usuarioedit.tipo);
        }
        fprintf(arq_temp, "%s %s %c\n", usuarioedit.nome, usuarioedit.senha, usuarioedit.tipo);
    }

    fclose(arq_usuario);
    fclose(arq_temp);
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
    system("clear || cls");
    printf("\nUsuario editado!\n\n");
}


void ExcluirUsuario(){
    usuario UsuarioApagado;
    char NomeUsuario[10];

    arq_usuario = fopen("usuarios.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if(arq_usuario == NULL || arq_temp == NULL){
        printf("\nErro na abertura de arquivo!\n");
        exit(0);
    }

    system("clear || cls");

    printf("Qual o nome do usuario que deseja excluir:");
    printf("\nInsira o nome: ");
    scanf("%s", NomeUsuario);

    while (fscanf(arq_usuario,"%s %s %c",UsuarioApagado.nome, UsuarioApagado.senha, &UsuarioApagado.tipo) == 3){
        if(strcmp(NomeUsuario, UsuarioApagado.nome) != 0) {
            fprintf(arq_temp,"%s %s %c\n",UsuarioApagado.nome, UsuarioApagado.senha, UsuarioApagado.tipo);
        }

    }



    fclose(arq_usuario);
    fclose(arq_temp);
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
    system("clear || cls");
    printf("Usuário excluido!\n\n");
}


void VendaIngressos(){
    char id[4];
    char fileiras;
    int cadeira;
    char cortesia;

    system("clear || cls");

    printf("Digite o ID da sessao: ");
    scanf("%s", id);

    Layout(id);

    printf("Digite a fileira: ");
	scanf(" %c", &fileiras);

	printf("Digite o numero da cadeira: ");
	scanf("%d", &cadeira);

	arq_assentos = fopen("assentos.txt", "r");
	arq_temp = fopen("temp.txt", "w");

    if (arq_assentos == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    printf("O ingresso é pago ou cortesia (P/C)? ");
    scanf(" %c", &cortesia);

	while(fscanf(arq_assentos, "%s %c %s", ChecarAssentos.sessao, &ChecarAssentos.fileira, ChecarAssentos.cadeiras) == 3){
		if(strcmp(id, ChecarAssentos.sessao)==0){ // string compare
			if(fileiras ==ChecarAssentos.fileira){
				if(ChecarAssentos.cadeiras[cadeira-1] == '.'){

					if(cortesia == 'P'){
						ChecarAssentos.cadeiras[cadeira-1] = 'X';
						printf("Cadeira vendida!\n");
					}

					else{

						ChecarAssentos.cadeiras[cadeira-1] = 'C';
						printf("Cadeira reservada como cortesia!\n");
					}
				}

				else{

					printf("Assento inválido!\n");
				}
			}
		}

		fprintf(arq_temp, "%s %c %s\n", ChecarAssentos.sessao, ChecarAssentos.fileira, ChecarAssentos.cadeiras);
	}

	fclose(arq_assentos);
	fclose(arq_temp);
	remove("assentos.txt");
	rename("temp.txt", "assentos.txt");
	system("clear||cls");
	Layout(id);
}


void DevolucaoIngressos(){

    char id[4];
    char fileiras;
    int cadeira;

    system("clear || cls");

    printf("Digite o ID da sessao: ");
	scanf("%s", id);

	Layout(id);

    arq_assentos = fopen("assentos.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if (arq_assentos == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

	printf("Digite a fileira: ");
	scanf(" %c", &fileiras);

	printf("Digite o numero da cadeira: ");
	scanf("%d", &cadeira);

	while(fscanf(arq_assentos, "%s %c %s", ChecarAssentos.sessao, &ChecarAssentos.fileira, ChecarAssentos.cadeiras) == 3){
		if(strcmp(id, ChecarAssentos.sessao)==0){ // string compare
			if(fileiras == ChecarAssentos.fileira){
				if(ChecarAssentos.cadeiras[cadeira-1] == 'X' || ChecarAssentos.cadeiras[cadeira-1] == 'C'){
					ChecarAssentos.cadeiras[cadeira-1] = '.';
					printf("Assento devolvido!");
				}
				else{
					printf("Assento já vazio!");
				}
			}
		}
		fprintf(arq_temp, "%s %c %s\n", ChecarAssentos.sessao, ChecarAssentos.fileira, ChecarAssentos.cadeiras);
	}
	fclose(arq_assentos);
    fclose(arq_temp);
    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");
    system("clear||cls");
    Layout(id);
}


void QuantidadeIngressos(){
    char id[4];
    int quant = 0;

    system("clear || cls");

    printf("Digite o ID da sessao: ");
    scanf("%s", id);

	arq_assentos = fopen("assentos.txt", "r");

    if (arq_assentos == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

	while(fscanf(arq_assentos, "%s %c %s", ChecarAssentos.sessao, &ChecarAssentos.fileira, ChecarAssentos.cadeiras) == 3){
		if(strcmp(id, ChecarAssentos.sessao)==0){ // string compare
			for(int i = 0; i<16; i++){
				if(ChecarAssentos.cadeiras[i] == 'X' || ChecarAssentos.cadeiras[i] == 'C' || ChecarAssentos.cadeiras[i] == '*'){
					quant++;
				}
			}
		}
	}

	system("clear || cls");

	printf("Quantidade de cadeiras ocupadas na sessão: %d\n", quant);
	printf("Quantidade de cadeiras vagas na sessão: %d\n ", 112 - quant);
	fclose(arq_assentos);
    }


void CadastrarSessaoOuEditarSessao() {
    int marcador = 0;

    system("clear || cls");

    printf("Cadastrar/Alterar Sessão\n");

    printf("Digite o ID da sessao: ");
    scanf("%s", EscreverEspetaculo.ID);

    printf("Digite o titulo: ");
    scanf("%s", EscreverEspetaculo.titulo);

    printf("Digite o nome do(a) diretor(a): ");
    scanf("%s", EscreverEspetaculo.direcao);

    printf("Digite a duracao da peça em minutos: ");
    scanf("%d", &EscreverEspetaculo.duracao);

    printf("Digite a faixa etaria: ");
    scanf("%d", &EscreverEspetaculo.etaria);

    printf("Digite a data da sessao (dd/mm/aa): ");
    scanf("%s", EscreverEspetaculo.data);

    printf("Digite o horario da sessao (hh:mm): ");
    scanf("%s", EscreverEspetaculo.horario);

    arq_espetaculo = fopen("espetaculos.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if (arq_espetaculo == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    while(fscanf(arq_espetaculo, "%s %s %s %d %d %s %s", ChecarEspetaculo.ID, ChecarEspetaculo.titulo, ChecarEspetaculo.direcao, &ChecarEspetaculo.duracao,\
    &ChecarEspetaculo.etaria, ChecarEspetaculo.data, ChecarEspetaculo.horario) == 7){
        if(strcmp(ChecarEspetaculo.ID, EscreverEspetaculo.ID)==0){ // string compare
            fprintf(arq_temp, "%s %s %s %d %d %s %s\n", EscreverEspetaculo.ID, EscreverEspetaculo.titulo, EscreverEspetaculo.direcao, EscreverEspetaculo.duracao,\
            EscreverEspetaculo.etaria, EscreverEspetaculo.data, EscreverEspetaculo.horario);
            marcador = 1;
            system("clear || cls");
            printf("Sessao alterada com sucesso!\n");
        }
        else{
            fprintf(arq_temp, "%s %s %s %d %d %s %s\n", ChecarEspetaculo.ID, ChecarEspetaculo.titulo, ChecarEspetaculo.direcao, ChecarEspetaculo.duracao,\
            ChecarEspetaculo.etaria, ChecarEspetaculo.data, ChecarEspetaculo.horario);
        }
    }
    if(marcador == 0){
        fprintf(arq_temp, "%s %s %s %d %d %s %s\n", EscreverEspetaculo.ID, EscreverEspetaculo.titulo, EscreverEspetaculo.direcao, EscreverEspetaculo.duracao,\
        EscreverEspetaculo.etaria, EscreverEspetaculo.data, EscreverEspetaculo.horario);
        system("clear || cls");
        printf("Sessao criada com sucesso!\n");
    }

    fclose(arq_espetaculo);
	fclose(arq_temp);
	remove("espetaculos.txt");
	rename("temp.txt", "espetaculos.txt");

	arq_assentos = fopen("assentos.txt", "r");
	arq_temp = fopen("temp.txt", "w");

    if (arq_assentos == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    if(marcador == 0){
        for(int i = 0; i<7; i++){
            switch(i){

                case 0:{
                    fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'A', "................");
				break;
                }

				case 1:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'B', "................");
				break;
                }

				case 2:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'C', "................");
				break;
                }

				case 3:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'D', "................");
				break;
                }

				case 4:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'E', "................");
				break;
                }

				case 5:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'F', "................");
				break;
                }

				case 6:{
					fprintf(arq_temp, "%s %c %s\n", EscreverEspetaculo.ID, 'G', "................");
				break;
				}
            }
		}

		assentos EscreverAssentos;
		while(fscanf(arq_assentos, "%s %c %s", EscreverAssentos.sessao, &EscreverAssentos.fileira, EscreverAssentos.cadeiras)==3){
			fprintf(arq_temp, "%s %c %s\n", EscreverAssentos.sessao, EscreverAssentos.fileira, EscreverAssentos.cadeiras);
		}
		fclose(arq_assentos);
		fclose(arq_temp);
		remove("assentos.txt");
		rename("temp.txt", "assentos.txt");
	}
}


void PorcentagemIngressos(){
    char id[4];
    double ocup= 0;

    system("clear || cls");

    printf("Digite o ID da sessao: ");
	scanf("%s", id);

	arq_assentos = fopen("assentos.txt", "r");

    if (arq_assentos == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

	while(fscanf(arq_assentos, "%s %c %s", ChecarAssentos.sessao, &ChecarAssentos.fileira, ChecarAssentos.cadeiras) == 3){
        if(strcmp(id, ChecarAssentos.sessao)==0){ // string compare
            for(int i = 0; i<16; i++){
                if(ChecarAssentos.cadeiras[i] == 'X' || ChecarAssentos.cadeiras[i] == 'C' || ChecarAssentos.cadeiras[i] == '*'){
                    ocup++;
                }
			}
		}
	}

    fclose(arq_assentos);
    system("clear || cls");

	if(ocup == 112){
		printf("Percentual de cadeiras disponiveis para compra: 0%%\n"); //Total de cadeiras que podem ser compradas, contando as que já foram vendidas, ou seja, desconsidera-se as cadeiras com *
		printf("Percentual de cadeiras ocupadas: 100%%\n");
	}
	else{
		printf("Percentual de cadeiras disponiveis para: %.lf%%\n", ((112-ocup)/112)*100); //Total de cadeiras que podem ser compradas, contando as que já foram vendidas, ou seja, desconsidera-se as cadeiras com *
		printf("Percentual de cadeiras ocupadas: %.lf%%\n", (ocup/112)*100);
	}
}


void ExcluirSessao(){
    char id[4];

    system("clear || cls");

    printf("Digite o ID da sessao: ");
    scanf("%s", id);

    arq_espetaculo = fopen("espetaculos.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if (arq_espetaculo == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    while(fscanf(arq_espetaculo, "%s %s %s %d %d %s %s", ChecarEspetaculo.ID, ChecarEspetaculo.titulo, ChecarEspetaculo.direcao, &ChecarEspetaculo.duracao,\
    &ChecarEspetaculo.etaria, ChecarEspetaculo.data, ChecarEspetaculo.horario) == 7){
        if(strcmp(ChecarEspetaculo.ID, id)!=0){
            fprintf(arq_temp, "%s %s %s %d %d %s %s", ChecarEspetaculo.ID, ChecarEspetaculo.titulo, ChecarEspetaculo.direcao, ChecarEspetaculo.duracao,\
            ChecarEspetaculo.etaria, ChecarEspetaculo.data, ChecarEspetaculo.horario);
        }

    }

    fclose(arq_espetaculo);
    fclose(arq_temp);
    remove("espetaculos.txt");
    rename("temp.txt", "espetaculos.txt");

    arq_assentos = fopen("assentos.txt", "r");
    arq_temp = fopen("temp.txt", "w");

    if (arq_assentos == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    assentos EscreverAssentos;

    while(fscanf(arq_assentos, "%s %c %s", EscreverAssentos.sessao, &EscreverAssentos.fileira, EscreverAssentos.cadeiras)==3){
        if(strcmp(EscreverAssentos.sessao, id)==0){
            continue;
        }
        else{
            fprintf(arq_temp, "%s %c %s\n", EscreverAssentos.sessao, EscreverAssentos.fileira, EscreverAssentos.cadeiras);
        }
    }
    fclose(arq_assentos);
    fclose(arq_temp);
    remove("assentos.txt");
    rename("temp.txt", "assentos.txt");
    system("clear || cls");
    printf("sessão excluida!");
}


void ReservarAssento(){

	char fileira;
    char id[4];
    int cadeiras;

    system("clear || cls");

	printf("Digite o ID da sessao: ");
	scanf("%s", id);

	Layout(id);

	printf("Digite a fileira: ");
	scanf(" %c", &fileira);

	printf("Digite o numero da cadeira: ");
	scanf("%d", &cadeiras);

	arq_assentos = fopen("assentos.txt", "r");
	arq_temp = fopen("temp.txt", "w");

    if (arq_assentos == NULL || arq_temp == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

	while(fscanf(arq_assentos, "%s %c %s", ChecarAssentos.sessao, &ChecarAssentos.fileira, ChecarAssentos.cadeiras) == 3){
		if(strcmp(id, ChecarAssentos.sessao)==0){
			if(fileira == ChecarAssentos.fileira){
				if(ChecarAssentos.cadeiras[cadeiras-1] == '.'){
					ChecarAssentos.cadeiras[cadeiras-1] = '*';
				}
			}
		}
		fprintf(arq_temp, "%s %c %s\n", ChecarAssentos.sessao, ChecarAssentos.fileira, ChecarAssentos.cadeiras);
	}

	fclose(arq_assentos);
	fclose(arq_temp);
	remove("assentos.txt");
	rename("temp.txt", "assentos.txt");
	system("clear || cls");
    printf("Cadeira reservada!");
	Layout(id);
}


void MostraUsuarios(){

    char nome[20];
    char senha[20];
    char tipo;

    arq_usuario = fopen("usuarios.txt", "r");

    if (arq_usuario == NULL) {
        printf("\nErro na abertura de arquivo!\n");
        return;
    }

    system("clear || cls");

    printf("\n\n::::::::::::::::Usuários caddastrados::::::::::::::::\n");

    while (fscanf(arq_usuario, "%s %s %c", nome, senha, &tipo) == 3) {
        printf("Nome: %s\n", nome);
        printf("Senha: %s\n", senha);
        printf("Tipo: %c\n", tipo);
        printf("--------------------\n");
    }

    fclose(arq_usuario);
}


int main(){

    setlocale(LC_ALL, "Portuguese");

//----------------------------------------------------------------------------------------

    usuario usuarios[100];
    char id[4];
    char fileira;
    int cadeira;
    int escolha;
    int x = 3;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    arq_usuario = fopen("usuarios.txt", "r");
    if (arq_usuario == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return 1;
    }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    while (fscanf(arq_usuario, "%s %s %c", usuarios[numUsuarios].nome, usuarios[numUsuarios].senha, &usuarios[numUsuarios].tipo) == 3) {
        numUsuarios++;
    }

    fclose(arq_usuario);

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    char login[10];
    char senha[5];
    char tipoAcesso;
    int loginValido = 3;

    printf("\n::::::::::::::::SEJA BEM-VINDO AO TEATRO JOGRAL::::::::::::::::\n\n");

    do{
        printf("Login: ");
        scanf("%s", login);

        if (strcmp(login, "sair") == 0) {
            printf("\nAté mais!\n");
            return 0;
        }

        printf("Senha: ");
        scanf("%s", senha);
        fflush(stdin);

        printf("Tipo de Acesso (G ou B): ");
        scanf(" %c", &tipoAcesso);

        loginValido = verificarCredenciais(login, senha, tipoAcesso, usuarios, numUsuarios);

        if (loginValido == 0){
            printf("\nCredenciais invalidas!\n");
            printf("\nInsira um usuário válido ou digite ''sair'' para encerrar o programa\n\n");
        }
    }
    while(loginValido == 3 || loginValido == 0);

    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::\n\n");

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Verificar as credenciais do usuário

    if (loginValido == 1){
        printf("\nLogin bem-sucedido!\n");

        do{
            fflush(stdin);
            printf("\n<-=-=-=-=-=-=-=-=--=-=-=-=-=-=->\n");
            printf("opções:\n\n[1] Cadastrar usuário\n[2] Editar usuário\n[3] Apagar usuário\n[4] Vender Ingressos\n"
                   "[5] Devolução de ingressos\n[6] Quantidade de vendas\n[7] Cadastrar/ alterar sessão\n"
                   "[8] Porcentagem de ingressos\n[9] Excluir sessão\n[10] Reservar assento\n[11] Mostrar usuários cadastrados\n[0] Sair");
            printf("\n<-=-=-=-=-=-=-=-=--=-=-=-=-=-=->\n");

            printf("escolha uma opção: ");
            scanf("%d", &escolha);

            switch(escolha){
                case 1:{
                    CadastrarUsuario();
                break;
                }

                case 2:{
                    EditarUsuario();
                break;
                }

                case 3:{
                    ExcluirUsuario();
                break;
                }

                case 4:{
                    VendaIngressos();
                break;
                }

                case 5:{
                    DevolucaoIngressos();
                break;
                }

                case 6:{
                    QuantidadeIngressos();
                break;
                }

                case 7:{
                    CadastrarSessaoOuEditarSessao();
                break;
                }

                case 8:{
                    PorcentagemIngressos();
                break;
                }

                case 9:{
                     ExcluirSessao();
                break;
                }

                case 10:{
                    ReservarAssento();
                break;
                }
                case 11:{
                    MostraUsuarios();
                break;
                }


            }
        }while(escolha != 0);
    printf("Até mais!");
    }

    else if(loginValido == 2){
        printf("Login bem sucedido!");
        do{
            fflush(stdin);
            printf("\n<-=-=-=-=-=-=-=-=--=-=-=-=-=-=->\n");
            printf("opções:\n\n[1] Venda de ingressos\n[2] Devolução de  ingressos\n[0] Sair");
            printf("\n<-=-=-=-=-=-=-=-=--=-=-=-=-=-=->\n");
            printf("escolha uma opção: ");
            scanf("%d", &escolha);

            switch(escolha){

                case 1:{
                    VendaIngressos();
                break;
                }

                case 2:{
                    DevolucaoIngressos();
                break;
                }
            }
        }while(escolha != 0);

    printf("Até mais!");
    }

     else {
        printf("Credenciais inválidas!\n");
    }
}
