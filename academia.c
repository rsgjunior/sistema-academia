#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "academia.h"

/* 
 * Fun��o: iniciarSistema
 * --------------------------
 * Verifica se os arquivos necess�rios para o sistema funcionar
 * exitem, caso n�o exista cria eles.
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)
 */
int iniciarSistema(){
	FILE *arqUI;

	arqUI=fopen("ultimoIdAlunos.csv","r");
	if(arqUI==NULL){
		arqUI=fopen("ultimoIdAlunos.csv","w");
		if(arqUI==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(arqUI,"0");
		fclose(arqUI);
	}else{
		fclose(arqUI);
	}
	
	arqUI=fopen("ultimoIdProfessores.csv","r");
	if(arqUI==NULL){
		arqUI=fopen("ultimoIdProfessores.csv","w");
		if(arqUI==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(arqUI,"0");
		fclose(arqUI);
	}else{
		fclose(arqUI);
	}

	arqUI=fopen("ultimoIdAulas.csv","r");
	if(arqUI==NULL){
		arqUI=fopen("ultimoIdAulas.csv","w");
		if(arqUI==NULL){
			printf("Erro de I/O.\n\n");
			return 0;
		}
		fprintf(arqUI,"0");
		fclose(arqUI);
	}else{
		fclose(arqUI);
	}
	
	return 1;
}

/* 
 * Fun��o: retirarQuebraDeLinha
 * --------------------------
 * Retira quebra de linha de uma string
 *
 * Par�metro:
 * char str[] -> string que ser� removida a quebra de linha
 *
 * Retorno: void
 */
void retirarQuebraDeLinha(char str[]){
	str[strcspn(str,"\n")] = 0;
}

/* 
 * Fun��o: obterUltimoId
 * --------------------------
 * Obtem o �ltimo ID do tipo passado como par�metro
 *
 * Par�metro:
 * char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
 *
 * Retorno: int -> o ID lido
 */
int obterUltimoId(char tipo){
	FILE *arquivo;
	int ultimoId;
	
	if(tipo=='a'){
		arquivo=fopen("ultimoIdAlunos.csv","r");
	}
	if(tipo=='p'){
		arquivo=fopen("ultimoIdProfessores.csv","r");
	}
	if(tipo=='t'){
		arquivo=fopen("ultimoIdAulas.csv","r");
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
 * Fun��o: incrementarId
 * --------------------------
 * Incrementa o ID do tipo como par�metro
 *
 * Par�metro:
 * char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
 *
 * Retorno: int -> o ID incrementado
 */
int incrementarId(char tipo){
	FILE *arquivo;
	int IdIncrementado,ultimoId=obterUltimoId(tipo);
	
	if(tipo=='a'){
		arquivo=fopen("ultimoIdAlunos.csv","w");
	}
	if(tipo=='p'){
		arquivo=fopen("ultimoIdProfessores.csv","w");
	}
	if(tipo=='t'){
		arquivo=fopen("ultimoIdAulas.csv","w");
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

/* 
 * Fun��o: cadastrarPessoa
 * --------------------------
 * Cadastra uma nova pessoa no sistema
 *
 * Par�metro:
 * struct pessoa pessoa -> Estrutura com as informa��es da pessoa
 * char tipo ('a' ->Aluno || 'p' ->Professor)
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cadastrarPessoa(struct pessoa psa, char tipo){
    FILE *arquivo;
	int ultimoId,proxId;
	
	retirarQuebraDeLinha(psa.nome);
	retirarQuebraDeLinha(psa.cpf);
	retirarQuebraDeLinha(psa.telefone);
	retirarQuebraDeLinha(psa.email);
	
	if(tipo=='a'){
		arquivo=fopen("alunos.csv","a");
		ultimoId=obterUltimoId('a');
		proxId=incrementarId('a');
	}else if(tipo=='p'){
		arquivo=fopen("professores.csv","a");
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
 * Fun��o: cadastrarTurma
 * --------------------------
 * Cadastra uma nova turma no sistema
 *
 * Par�metro:
 * struct turma turma -> Estrutura com as informa��es da turma
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cadastrarTurma(struct turma turma){
	FILE *arquivo;
	int ultimoId,proxId;
	
	retirarQuebraDeLinha(turma.horario);
	retirarQuebraDeLinha(turma.faixa_etaria);
	
	ultimoId=obterUltimoId('t');
	proxId=incrementarId('t');
	
	arquivo=fopen("aulas.csv","a");
	if(arquivo==NULL){
		printf("\nErro de I/O.\n\n");
		return 0;
	}
	
	fprintf(arquivo,"%d,%c,%d,%s,%d,%d,%d,%s\n",proxId,turma.tipo,turma.dia,turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
	
	fclose(arquivo);
	
	return 1;
}

/* 
 * Fun��o: qtdAlunosNaTurma
 * --------------------------
 * Conta a quantidade de inscri��es de uma turma
 *
 * Par�metro:
 * int idTurma -> ID da turma que ir� contar as inscri��es
 *
 * Retorno: int -> quantidade de inscri��es na turma
 */
int qtdAlunosNaTurma(int idTurma){
	int contagem=0, idTurma_atual;
	FILE *arqInscricoes = fopen("inscricoes.csv","r");
	
	if(arqInscricoes==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	while(fscanf(arqInscricoes,"%*d,%d\n",&idTurma_atual) != EOF){
		if(idTurma_atual == idTurma){
			contagem++;
		}
	}
	
	fclose(arqInscricoes);
	
	return contagem;
}

/* 
 * Fun��o: inscreverAluno
 * --------------------------
 * Inscreve um aluno em uma aula
 *
 * Par�metro:
 * int id_aluno -> ID do aluno que ser� inscrito
 * int id_aula -> ID da aula que ser� inscrito
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int inscreverAluno(int id_aluno, int id_aula){
	FILE *arqInscricoes,*arqAulas;
	struct turma turma;
	char tipo;
	int id;
	
	// Verifica se a turma e o aluno existem no sistema
	if(id_aluno>obterUltimoId('a')){
		printf("\nID do aluno n�o existe no sistema\n\n");
		system("pause");
		return 0;
	}	
	if(id_aula>obterUltimoId('t')){
		printf("\nID da aula n�o existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	// Verifica se a turma esta lotada
	arqAulas=fopen("aulas.csv","r");
	if(arqAulas==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	arqInscricoes=fopen("inscricoes.csv","a");
	if(arqInscricoes==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	while(fscanf(arqAulas,"%d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
	turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		if(turma.id==id_aula){
			if(qtdAlunosNaTurma(turma.id) < turma.maximo){
				fprintf(arqInscricoes,"%d,%d\n",id_aluno,id_aula);
			}else{
				tipo=turma.tipo;
				id=turma.id;
				fseek(arqAulas,0,0);
				printf("\nA turma %d esta lotada, segue uma lista de outras turmas desta atividade: \n\n", turma.id);
				while(fscanf(arqAulas,"%d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
		 		turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		 			if(turma.tipo==tipo && turma.id!=id){
		 				printf("%d,%c,%d,%s,%d,%d,%d,%s\n",turma.id,turma.tipo,turma.dia,turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
					}
				}
				printf("\n");
				return 0;
			}
		}
	}
	
	fclose(arqAulas);
	fclose(arqInscricoes);
	
	return 1;
}

/* 
 * Fun��o: cancelarInscricao
 * --------------------------
 * Cancela a inscri��o de um aluno em uma aula
 * ou de todos os alunos em uma aula(se o id_aluno = -1)
 *
 * Par�metro:
 * int id_aluno -> ID do aluno que ser� cancelada a inscri��o
 * int id_aula -> ID da aula que ser� cancelada a inscri��o
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cancelarInscricao(int id_aluno, int id_aula){
	int id_alunoAtual,id_aulaAtual;
	struct turma turma;
	struct pessoa aluno;
	FILE *arqInscricoes,*arqInscricoesNovo,*arqRelatorio,*arqAulas,*arqAlunos;
	
	if(id_aluno>obterUltimoId('a')){
		printf("\nID do aluno n�o existe no sistema\n\n");
		system("pause");
		return 0;
	}
	if(id_aula>obterUltimoId('t')){
		printf("\nID da aula n�o existe no sistema\n\n");
		system("pause");
		return 0;
	}
	
	arqInscricoes=fopen("inscricoes.csv","r");
	arqInscricoesNovo=fopen("inscricoesNovo.csv","w");
	arqRelatorio=fopen("r_inscricoesCanceladas.csv","a");
	arqAulas=fopen("aulas.csv","r");
	arqAlunos=fopen("alunos.csv","r");
	if(arqInscricoes==NULL || arqInscricoesNovo==NULL || arqRelatorio==NULL || arqAulas==NULL || arqAlunos==NULL){
		printf("Erro de I/O.");
		exit(1);
	}
	
	while(fscanf(arqInscricoes,"%d,%d\n",&id_alunoAtual,&id_aulaAtual) != EOF){
		if((id_alunoAtual==id_aluno && id_aulaAtual==id_aula) || (id_aluno==-1 && id_aula==id_aulaAtual)){
			while(fscanf(arqAulas,"%d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
		 	turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		 		if(turma.id==id_aula){
		 			fprintf(arqRelatorio,"%c,%d,%s",turma.tipo,turma.dia,turma.horario);
		 			break;
				}
		 	}
		 	while(fscanf(arqAlunos,"%d,%*[^,],%*[^,],%[^,],%[^\n]",&aluno.id,aluno.telefone,aluno.email) != EOF){
		 		if(aluno.id==id_alunoAtual){
		 			fprintf(arqRelatorio,",%d,%s,%s\n",aluno.id,aluno.telefone,aluno.email);
				}
			}
			fseek(arqAulas,0,0);
			fseek(arqAlunos,0,0);
		}else{
			fprintf(arqInscricoesNovo,"%d,%d\n",id_alunoAtual,id_aulaAtual);
		}
	}
	
	fclose(arqInscricoes);
	fclose(arqInscricoesNovo);
	fclose(arqRelatorio);
	fclose(arqAulas);
	fclose(arqAlunos);
	
	remove("inscricoes.csv");
	rename("inscricoesNovo.csv","inscricoes.csv");
	
	return 1;
}

/* 
 * Fun��o: fecharTurmas
 * --------------------------
 * Fecha todas as turmas com menos inscri��es do que o inteiro passado como par�metro
 *
 * Par�metro:
 * int min -> quantidade m�nima de inscri��es que a turma deve ter para n�o ser cancelada
 *
 * Retorno: int -> quantidade de turmas fechadas
 */
int fecharTurmas(int min){
	int qtdTurmas=obterUltimoId('t');
	int *alunosNaTurma;
	int id_aluno,id_aula,totalFechado=0;
	struct pessoa prof;
	struct turma turma;
	FILE *arqAulas,*arqAulasNovo,*arqInscricoes,*arqRelatorio,*arqProf;
	
	alunosNaTurma=(int*)malloc(qtdTurmas*sizeof(int));
	if(alunosNaTurma==NULL){
		printf("Erro de aloca��o de mem�ria.");
		exit(1);
	}
	
	// Preenche o vetor com a quantidade de inscri��es em cada turma
	for(int i=0;i<qtdTurmas;i++){
		alunosNaTurma[i]=qtdAlunosNaTurma(i+1);
	}
	
	// Remo��o da Aula
	arqAulas=fopen("aulas.csv","r");
	arqAulasNovo=fopen("aulasTemp.csv","w");
	arqProf=fopen("professores.csv","r");
	arqRelatorio=fopen("r_aulasCanceladas.csv","w");
	if(arqAulas==NULL || arqAulasNovo==NULL || arqRelatorio==NULL || arqProf==NULL){
		printf("\nErro de I/O.\n\n");
		exit(1);
	}
	
 	while(fscanf(arqAulas,"%*d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
	 turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		if(alunosNaTurma[turma.id-1]>=min){
			fprintf(arqAulasNovo,"%d,%c,%d,%s,%d,%d,%d,%s\n",turma.id,turma.tipo,turma.dia,
			turma.horario,turma.id_prof,turma.minimo,turma.maximo,turma.faixa_etaria);
		}else{
			// Escreve o arquivo com as aulas canceladas e as informa��es do professor
			fprintf(arqRelatorio,"%c,%d,%s,%d",turma.tipo,turma.dia,turma.horario,turma.id_prof);
			while(fscanf(arqProf,"%d,%*[^,],%*[^,],%[^,],%[^\n]",&prof.id,prof.telefone,prof.email) != EOF){
				if(prof.id==turma.id_prof){
					fprintf(arqRelatorio,",%s,%s\n",prof.telefone,prof.email);
					break;
				}
			}
			cancelarInscricao(-1,turma.id);
			fseek(arqProf,0,0);
		}
	}
	
	fclose(arqAulas);
	fclose(arqAulasNovo);
	fclose(arqProf);
	fclose(arqRelatorio);
	
	remove("aulas.csv");
	rename("aulasTemp.csv","aulas.csv");
	
	// Contagem do total de turmas fechadas
	for(int i=0;i<qtdTurmas;i++){
		if(alunosNaTurma[i]<min){
			totalFechado++;
		}
	}
	
	return totalFechado;
}

/* 
 * Fun��o: confirmarTurmas
 * --------------------------
 * Confirma todas as turmas que existem no arquivo de aulas no momento
 *
 * Retorno: int -> quantidade de turmas confirmadas
 */
int confirmarTurmas(){
	FILE *arqAulas,*arqRelatorio;
	struct turma turma;
	int cont=0,qtdAlunos;
	
	arqAulas=fopen("aulas.csv","r");
	arqRelatorio=fopen("r_aulasConfirmadas.csv","w");
	
	if(arqAulas==NULL || arqRelatorio==NULL){
		printf("Erro de I/O.\n\n");
		exit(1);
	}
	
	while(fscanf(arqAulas,"%d,%c,%d,%[^,],%d,%d,%d,%[^\n]",&turma.id,&turma.tipo,&turma.dia,
	turma.horario,&turma.id_prof,&turma.minimo,&turma.maximo,turma.faixa_etaria) != EOF){
		qtdAlunos=qtdAlunosNaTurma(turma.id);
		fprintf(arqRelatorio,"%c,%d,%s,%d,%d\n",turma.tipo,turma.dia,turma.horario,turma.id_prof,qtdAlunos);
		cont++;
	}
	
	fclose(arqAulas);
	fclose(arqRelatorio);
	
	return cont;
}
