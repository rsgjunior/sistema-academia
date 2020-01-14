#ifndef ACADEMIA_H
#define ACADEMIA_H

struct turma{
    int id, dia, id_prof, minimo, maximo;
    char tipo, horario[6], faixa_etaria[6];
};

struct pessoa{
    int id;
    char nome[50], cpf[14], telefone[12], email[50];
};

/* 
 * Fun��o: iniciarSistema
 * --------------------------
 * Verifica se os arquivos necess�rios para o sistema funcionar
 * exitem, caso n�o exista cria eles.
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)
 */
int iniciarSistema();

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
void retirarQuebraDeLinha(char str[]);

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
int obterUltimoId(char tipo);

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
int incrementarId(char tipo);

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
int cadastrarPessoa(struct pessoa psa, char tipo);

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
int cadastrarTurma(struct turma turma);

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
int inscreverAluno(int id_aluno, int id_aula);

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
int cancelarInscricao(int id_aluno, int id_aula);

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
int fecharTurmas(int min);

/* 
 * Fun��o: confirmarTurmas
 * --------------------------
 * Confirma todas as turmas que existem no arquivo de aulas no momento
 *
 * Retorno: int -> quantidade de turmas confirmadas
 */
int confirmarTurmas();

#endif

