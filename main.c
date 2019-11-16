#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

// Declarações das estruturas de dados
struct turma{
    int id, dia, id_prof, minimo, maximo;
    char tipo, horario[6], faixa_etaria[6];
};

struct pessoa{
    int id;
    char nome[50], cpf[14], telefone[12], email[50];
};

// Protótipos das funções
int iniciarSistema();
void retirarQuebraDeLinha(char str[]);
int obterUltimoId(char tipo);
int incrementarId(char tipo);
int cadastrarPessoa(struct pessoa psa, char tipo);
int cadastrarTurma(struct turma turma);
int inscreverAluno(int id_aluno, int id_aula);
int cancelarInscricao(int id_aluno, int id_aula);
int fecharTurmas(int min);

int main(){
	if(!iniciarSistema()){
		system("pause");
		exit(1);
	}
	
    setlocale(LC_ALL,"Portuguese");
    struct pessoa pessoa;
    struct turma turma;
    int opMenu=0, id_aluno, id_aula, min;
	
    while(opMenu!=8){
    	system("cls");
        printf("Sistema de gerenciamento Academia Superação!\n");
        printf("\n1- Cadastrar um aluno "
            "\n2- Cadastrar um professor"
            "\n3- Cadastrar turma"
            "\n4- Inscrever aluno em uma turma"
            "\n5- Cancelar inscrição"
            "\n6- Fechar turmas"
            "\n7- Confirmar turmas"
            "\n8- Fechar o programa");

        printf("\n\nInsira o número da função que deseja acessar: ");
        scanf("%d", &opMenu);
        switch(opMenu){
            case 1: // Cadastrar aluno
            	system("cls");
            	printf("Cadastrar novo aluno: \n\n");
            	// Entrada de dados
    			printf("Insira o nome: ");
    			fflush(stdin);
    			fgets(pessoa.nome,50,stdin);
    			printf("Insira o CPF: ");
    			fflush(stdin);
    			fgets(pessoa.cpf,14,stdin);
    			printf("Insira o telefone: ");
    			fflush(stdin);
    			fgets(pessoa.telefone,12,stdin);
   			    printf("Insira o e-mail: ");
    			fflush(stdin);
    			fgets(pessoa.email,50,stdin);
    			// Caso a função retorne 1 printa sucesso
                if(cadastrarPessoa(pessoa,'a')){
                	printf("\nAluno cadastrado com sucesso!\n\n");
				}
				system("pause");
                break;
            case 2: // Cadastrar professor
            	system("cls");
            	printf("Cadastrar novo professor: \n\n");
            	// Entrada de dados
    			printf("Insira o nome: ");
    			fflush(stdin);
    			fgets(pessoa.nome,50,stdin);
    			printf("Insira o CPF: ");
    			fflush(stdin);
    			fgets(pessoa.cpf,14,stdin);
    			printf("Insira o telefone: ");
    			fflush(stdin);
    			fgets(pessoa.telefone,12,stdin);
   			    printf("Insira o e-mail: ");
    			fflush(stdin);
    			fgets(pessoa.email,50,stdin);
    			// Caso a função retorne 1 printa sucesso
            	if(cadastrarPessoa(pessoa,'p')){
            		printf("\nProfessor cadastrado com sucesso!\n\n");
				}
            	system("pause");
                break;
            case 3: // Cadastrar turma
            	system("cls");
            	printf("Cadastrar nova turma: \n\n");
            	// Entrada de dados
				printf("Insira o tipo da aula(A=Artes Marciais, B=Boxe, C=Crossfit, D=Dança): ");
				fflush(stdin);
				fgets(&turma.tipo,2,stdin);
				printf("Insira o dia da semana da aula(1=Domingo,2=Segunda,...): ");
				scanf("%d", &turma.dia);
				printf("Insira o horário(HH:MM): ");
				fflush(stdin);
				fgets(turma.horario,6,stdin);
				printf("Insira o ID do professor: ");
				fflush(stdin);
				scanf("%d", &turma.id_prof);
				printf("Insira o número mínimo de alunos: ");
				scanf("%d", &turma.minimo);
				printf("Insira o número máximo de alunos: ");
				scanf("%d", &turma.maximo);
				printf("Insira a faixa etária da aula(XX-XX): ");
				fflush(stdin);
				fgets(turma.faixa_etaria,6,stdin);
				// Caso a função retorne 1 printa sucesso
            	if(cadastrarTurma(turma)){
            		printf("\nAula cadastrada com sucesso!\n\n");
				}
				system("pause");
                break;
            case 4: // Inscrever aluno
            	system("cls");
            	printf("Inscrever um aluno em uma turma: \n\n");
            	// Entrada de Dados
				printf("Insira o ID do aluno que deseja inscrever: ");
				scanf("%d",&id_aluno);
				printf("Insira o ID da aula que o aluno será inscrito: ");
				scanf("%d",&id_aula);
				// Caso a função retorne 1 printa sucesso
            	if(inscreverAluno(id_aluno,id_aula)){
            		printf("\nAluno inscrito com sucesso!\n\n");
            		system("pause");
				}
                break;
            case 5: // Cancelar inscrição
	            system("cls");
	            printf("Cancelar a inscrição de um aluno em uma turma: \n\n");
	            // Entrada de Dados
	            printf("Insira o ID do aluno que deseja cancelar: ");
				scanf("%d",&id_aluno);
				printf("Insira o ID da aula que deseja cancelar o aluno: ");
				scanf("%d",&id_aula);
				// Caso a função retorne 1 printa sucesso
				if(cancelarInscricao(id_aluno,id_aula)){
					printf("\nInscrição cancelada com sucesso!\n\n");
					system("pause");
				}
                break;
            case 6: // Fechar turmas
            	system("cls");
            	printf("Fechar turmas com menos alunos que:\n\n");
            	// Entrada de dados
            	printf("Insira o número minímo de alunos: ");
            	scanf("%d",&min);
            	// Printa o total de turmas fechadas
            	printf("Total de turmas fechadas: %d\n\n",fecharTurmas(min));
            	system("pause");
                break;
            case 7: // Confirmar turmas
                break;
            case 8: // Fechar o programa
                break;
            default:
                printf("\nOpção inválida, digite novamente!\n");
                system("pause");
                break;
        }
    }
    
    return 0;
}

// Funções do programa

int iniciarSistema(){
	FILE *ui_alunos,*ui_professores,*ui_aulas;
	
	// Inicia o arquivo de ID dos alunos caso não exista
	ui_alunos=fopen("ultimoIdAlunos.txt","r");
	if(ui_alunos==NULL){
		ui_alunos=fopen("ultimoIdAlunos.txt","w");
		if(ui_alunos==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(ui_alunos,"0");
		fclose(ui_alunos);
	}
	
	// Inicia o arquivo de ID dos professores caso não exista
	ui_professores=fopen("ultimoIdProfessores.txt","r");
	if(ui_professores==NULL){
		ui_professores=fopen("ultimoIdProfessores.txt","w");
		if(ui_professores==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(ui_professores,"0");
		fclose(ui_professores);
	}
	
	// Inicia o arquivo de ID das aulas caso não exista
	ui_aulas=fopen("ultimoIdAulas.txt","r");
	if(ui_aulas==NULL){
		ui_aulas=fopen("ultimoIdAulas.txt","w");
		if(ui_aulas==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(ui_aulas,"0");
		fclose(ui_aulas);
	}
	
	return 1;
}

/*	
	Retira quebra de linha da string.
	Parâmetros: char = Vetor de caracter
	Retorno: void
*/
void retirarQuebraDeLinha(char str[]){
	/* A função strcspn retorna a posição do vetor de caracter que contém o caracter 
	passado como parâmetro. Nesse caso, substituimos o \n(quebra de linha) do final da
	string por 0 */
	str[strcspn(str,"\n")] = 0;
}

/*	
	Obtem o ID(inteiro) salvo no arquivo passado como parâmetro.
	se o arquivo não existir, a função cria o arquivo iniciando com 0.
	Parâmetros: char = Nome do Arquivo
	Retorno: int = o ID lido		
*/
int obterUltimoId(char tipo){
	FILE *arquivo;
	int ultimoId;
	
	if(tipo=='a'){
		arquivo=fopen("ultimoIdAlunos.txt","r");
	}
	if(tipo=='p'){
		arquivo=fopen("ultimoIdProfessores.txt","r");
	}
	if(tipo=='t'){
		arquivo=fopen("ultimoIdAulas.txt","r");
	}
	
	if(arquivo==NULL){
		printf("Erro de I/O.\n\n");
		exit(1);
	}
	
	fscanf(arquivo,"%d",&ultimoId);
	fclose(arquivo);
	
	return ultimoId;
}

/*	
	Incrementa o ID(inteiro) salvo no arquivo passado como parâmetro.
	Parâmetros: char = Nome do Arquivo
	Retorno: int = o ID incrementado	
*/
int incrementarId(char tipo){
	FILE *arquivo;
	int IdIncrementado,ultimoId=obterUltimoId(tipo);
	
	if(tipo=='a'){
		arquivo=fopen("ultimoIdAlunos.txt","w");
	}
	if(tipo=='p'){
		arquivo=fopen("ultimoIdProfessores.txt","w");
	}
	if(tipo=='t'){
		arquivo=fopen("ultimoIdAulas.txt","w");
	}
	
	if(arquivo==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	IdIncrementado=ultimoId+1;
	fprintf(arquivo,"%d",IdIncrementado);
	
	fclose(arquivo);
	
	return IdIncrementado;
}

int atualizarUltimoId(){
	
}

/*	
	Cadastra uma nova pessoa no sistema
	Parâmetros: struct pessoa psa, char tipo
	Tipos:
	'a' -> Aluno
	'p' -> Professor
	Retorno: void			
*/
int cadastrarPessoa(struct pessoa psa, char tipo){
    FILE *arquivo;
	int ultimoId,proxId;
	
	// Retira a quebra de linha do final de cada string
	retirarQuebraDeLinha(psa.nome);
	retirarQuebraDeLinha(psa.cpf);
	retirarQuebraDeLinha(psa.telefone);
	retirarQuebraDeLinha(psa.email);
	
	// Abertura do arquivo "alunos.txt" ou "professores.txt" para escrita
	if(tipo=='a'){
		arquivo=fopen("alunos.txt","a");
		ultimoId=obterUltimoId('a');
		proxId=incrementarId('a');
	}else if(tipo=='p'){
		arquivo=fopen("professores.txt","a");
		ultimoId=obterUltimoId('p');
		proxId=incrementarId('p');
	}
    // Verifica se o ponteiro para o arquivo é nulo
    if(arquivo==NULL){
        printf("\nErro de I/O.\n\n");
        return 0;
    }

    // Escrita no arquivo
    fprintf(arquivo,"%d,%s,%s,%s,%s\n",proxId,psa.nome,psa.cpf,psa.telefone,psa.email);

    // Fechamento do arquivo "alunos.txt" ou "professores.txt"
    fclose(arquivo);
    
    return 1;
}

/*	
	Cadastra uma nova turma no sistema
	Parâmetros: struct turma turma
	Retorno: void			
*/
int cadastrarTurma(struct turma turma){
	FILE *arquivo;
	int ultimoId,proxId;
	
	// Retira a quebra de linha no final das strings
	retirarQuebraDeLinha(turma.horario);
	retirarQuebraDeLinha(turma.faixa_etaria);
	
	ultimoId=obterUltimoId('t');
	proxId=incrementarId('t');
	
	// Abertura do arquivo "aulas.txt"
	arquivo=fopen("aulas.txt","a");
	// Verifica se o ponteiro para o arquivo é nulo
	if(arquivo==NULL){
		printf("\nErro de I/O.\n\n");
		return 0;
	}
	
	// Escrita no arquivo
	fprintf(arquivo,"%d,%c,%d,%s,%d,%d,%d,%s\n",proxId,turma.tipo,turma.dia,turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
	
	// Fechamento do arquivo "aulas.txt"
	fclose(arquivo);
	
	return 1;
}

/*	
	Inscreve um aluno em uma aula
	Parâmetros: int id_aluno, int id_aula
	Retorno: int 1 se teve sucesso / 0 se não			
*/
int inscreverAluno(int id_aluno, int id_aula){
	FILE *arquivo;
	
	// Verifica se a turma e o aluno existem no sistema
	if(id_aluno>obterUltimoId('a')){
		printf("\nID do aluno não existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	if(id_aula>obterUltimoId('t')){
		printf("\nID da aula não existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	// Abertura do arquivo "inscricoes.txt"
	arquivo=fopen("inscricoes.txt","a");
	// Verifica se o ponteiro para o arquivo é nulo
	if(arquivo==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	// Escrita no arquivo
	fprintf(arquivo,"%d,%d\n",id_aluno,id_aula);
	
	// Fechamento do arquivo
	fclose(arquivo);
	
	return 1;
}

/*	
	Cancela a inscrição de um aluno em uma aula
	Parâmetros: int id_aluno, int id_aula
	Retorno: void			
*/
int cancelarInscricao(int id_aluno, int id_aula){
	int id_alunoAtual,id_aulaAtual;
	FILE *arquivo,*arquivoNovo,*arqRelatorio;
	
	// Verifica se a turma e o aluno existem no sistema
	if(id_aluno>obterUltimoId('a')){
		printf("\nID do aluno não existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	if(id_aula>obterUltimoId('t')){
		printf("\nID da aula não existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	// Abertura dos arquivos
	arquivo=fopen("inscricoes.txt","r");
	arquivoNovo=fopen("inscricoesNovo.txt","w");
	arqRelatorio=fopen("r_inscricoesCanceladas.csv","a");
	if(arquivo==NULL || arquivoNovo==NULL || arqRelatorio==NULL){
		printf("Erro de I/O.");
		return 0;
	}
	
	/* Compara as inscrições do arquivo com a que pediu para ser cancelada
	e escreve um arquivo novo sem elas */
	while(fscanf(arquivo,"%d,%d\n",&id_alunoAtual,&id_aulaAtual) != EOF){
		if(id_alunoAtual==id_aluno && id_aulaAtual==id_aula){
			fprintf(arqRelatorio,"%d,%d\n",id_alunoAtual,id_aulaAtual);
		}else{
			fprintf(arquivoNovo,"%d,%d\n",id_alunoAtual,id_aulaAtual);
		}
	}
	
	// Fechamento dos arquivos
	fclose(arquivo);
	fclose(arquivoNovo);
	fclose(arqRelatorio);
	
	// Exclui o arquivo antigo de inscrições
	remove("inscricoes.txt");
	
	// Renomeia o arquivo novo
	rename("inscricoesNovo.txt","inscricoes.txt");
	
	return 1;
}

int fecharTurmas(int min){
	// Cria um vetor com a quantidade de turmas atual no sistema
	int qtdTurmas=obterUltimoId('t');
	int alunosNaTurma[qtdTurmas];
	int id_aluno,id_aula,totalFechado=0;
	struct pessoa prof;
	struct turma turma;
	FILE *arquivo,*arquivoNovo,*arqRelatorio,*arqProf;
	
	// Inicia o vetor das turmas com 0
	for(int i=0;i<qtdTurmas;i++){
		alunosNaTurma[i]=0;
	}
	
	// Remoção da Inscrição
	arquivo=fopen("inscricoes.txt","r");
	arquivoNovo=fopen("inscricoesTemp.txt","w");
	if(arquivo==NULL || arquivoNovo==NULL){
		printf("\nErro de I/O.\n\n");
		return 0;
	}
	
	while(fscanf(arquivo,"%*d,%d",&id_aula) != EOF){
		alunosNaTurma[id_aula-1]++;
	}
	
	fseek(arquivo,0,0);

	while(fscanf(arquivo,"%d,%d",&id_aluno,&id_aula) != EOF){
		if(alunosNaTurma[id_aula-1]>=min){
			fprintf(arquivoNovo,"%d,%d\n",id_aluno,id_aula);
		}
	}
	
	fclose(arquivo);
	fclose(arquivoNovo);
	
	remove("inscricoes.txt");
	rename("inscricoesTemp.txt","inscricoes.txt");
	
	// Remoção da Aula
	arquivo=fopen("aulas.txt","r");
	arquivoNovo=fopen("aulasTemp.txt","w");
	arqProf=fopen("professores.txt","r");
	arqRelatorio=fopen("r_aulasCanceladas.csv","w");
	if(arquivo==NULL || arquivoNovo==NULL || arqRelatorio==NULL || arqProf==NULL){
		printf("\nErro de I/O.\n\n");
		return 0;
	}
	
 	while(fscanf(arquivo,"%d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
	 turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		if(alunosNaTurma[turma.id-1]>=min){
			fprintf(arquivoNovo,"%d,%c,%d,%s,%d,%d,%d,%s\n",turma.id,turma.tipo,turma.dia,
			turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
		}else{
			fprintf(arqRelatorio,"%c,%d,%s,%d",turma.tipo,turma.dia,turma.horario,turma.id_prof);
			while(fscanf(arqProf,"%d,%*[^,],%*[^,],%[^,],%[^\n]",&prof.id,prof.telefone,prof.email) != EOF){
				if(prof.id==turma.id_prof){
					fprintf(arqRelatorio,",%s,%s\n",prof.telefone,prof.email);
					break;
				}
			}
			fseek(arqProf,0,0);
		}
	}
	
	fclose(arquivo);
	fclose(arquivoNovo);
	fclose(arqProf);
	fclose(arqRelatorio);
	
	remove("aulas.txt");
	rename("aulasTemp.txt","aulas.txt");
	
	for(int i=0;i<qtdTurmas;i++){
		if(alunosNaTurma[i]<min){
			totalFechado++;
		}
	}
	
	return totalFechado;
}