#include<stdio.h>
#include<string.h>

struct turma{
    int id, dia, id_prof, minimo, maximo;
    char tipo, horario[6], faixa_etaria[6];
};

struct pessoa{
    int id;
    char nome[50], cpf[14], telefone[12], email[50];
};

int iniciarSistema(){
	FILE *ui_alunos,*ui_professores,*ui_aulas;

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
Parâmetros: char string
Retorno: void
*/
void retirarQuebraDeLinha(char str[]){
	str[strcspn(str,"\n")] = 0;
}

/*	
Obtem o último ID do tipo passado como parâmetro
Parâmetros: char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
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
Incrementa o ID do tipo como parâmetro.
Parâmetros: char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
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
Parâmetros: struct pessoa, char tipo ('a' ->Aluno | 'p' ->Professor)
Retorno: int (1 ->sucesso | 0 ->erro)			
*/
int cadastrarPessoa(struct pessoa psa, char tipo){
    FILE *arquivo;
	int ultimoId,proxId;
	
	retirarQuebraDeLinha(psa.nome);
	retirarQuebraDeLinha(psa.cpf);
	retirarQuebraDeLinha(psa.telefone);
	retirarQuebraDeLinha(psa.email);
	
	if(tipo=='a'){
		arquivo=fopen("alunos.txt","a");
		ultimoId=obterUltimoId('a');
		proxId=incrementarId('a');
	}else if(tipo=='p'){
		arquivo=fopen("professores.txt","a");
		ultimoId=obterUltimoId('p');
		proxId=incrementarId('p');
	}
    if(arquivo==NULL){
        printf("\nErro de I/O.\n\n");
        return 0;
    }

    fprintf(arquivo,"%d,%s,%s,%s,%s\n",proxId,psa.nome,psa.cpf,psa.telefone,psa.email);

    fclose(arquivo);
    
    return 1;
}

/*	
Cadastra uma nova turma no sistema
Parâmetros: struct turma
Retorno: int (1 ->sucesso | 0 ->erro)	
*/
int cadastrarTurma(struct turma turma){
	FILE *arquivo;
	int ultimoId,proxId;
	
	retirarQuebraDeLinha(turma.horario);
	retirarQuebraDeLinha(turma.faixa_etaria);
	
	ultimoId=obterUltimoId('t');
	proxId=incrementarId('t');
	
	arquivo=fopen("aulas.txt","a");
	if(arquivo==NULL){
		printf("\nErro de I/O.\n\n");
		return 0;
	}
	
	fprintf(arquivo,"%d,%c,%d,%s,%d,%d,%d,%s\n",proxId,turma.tipo,turma.dia,turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
	
	fclose(arquivo);
	
	return 1;
}

/*	
Inscreve um aluno em uma aula
Parâmetros: int id_aluno, int id_aula
Retorno: int (1 ->sucesso | 0 ->erro)		
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
	
	arquivo=fopen("inscricoes.txt","a");
	if(arquivo==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	fprintf(arquivo,"%d,%d\n",id_aluno,id_aula);
	
	fclose(arquivo);
	
	return 1;
}

/*	
Cancela a inscrição de um aluno em uma aula
Parâmetros: int id_aluno, int id_aula
Retorno: int (1 ->sucesso | 0 ->erro)
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
	
	fclose(arquivo);
	fclose(arquivoNovo);
	fclose(arqRelatorio);
	
	remove("inscricoes.txt");
	rename("inscricoesNovo.txt","inscricoes.txt");
	
	return 1;
}

/*
Fecha todas as turmas com menos inscrições do que o inteiro passado como parâmetro
Parâmetros: int min
Retorno: int = quantidade de turmas fechadas
*/
int fecharTurmas(int min){
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
			// Escreve o arquivo com as aulas canceladas e as informações do professor
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
	
	// Contagem do total de turmas fechadas
	for(int i=0;i<qtdTurmas;i++){
		if(alunosNaTurma[i]<min){
			totalFechado++;
		}
	}
	
	return totalFechado;
}
