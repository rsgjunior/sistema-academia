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
 * Função: iniciarSistema
 * --------------------------
 * Verifica se os arquivos necessários para o sistema funcionar
 * exitem, caso não exista cria eles.
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)
 */
int iniciarSistema();

/* 
 * Função: retirarQuebraDeLinha
 * --------------------------
 * Retira quebra de linha de uma string
 *
 * Parâmetro:
 * char str[] -> string que será removida a quebra de linha
 *
 * Retorno: void
 */
void retirarQuebraDeLinha(char str[]);

/* 
 * Função: obterUltimoId
 * --------------------------
 * Obtem o último ID do tipo passado como parâmetro
 *
 * Parâmetro:
 * char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
 *
 * Retorno: int -> o ID lido
 */
int obterUltimoId(char tipo);

/* 
 * Função: incrementarId
 * --------------------------
 * Incrementa o ID do tipo como parâmetro
 *
 * Parâmetro:
 * char tipo ('a' ->Aluno | 'p' ->Professor | 't' ->Turma(Aula))
 *
 * Retorno: int -> o ID incrementado
 */
int incrementarId(char tipo);

/* 
 * Função: cadastrarPessoa
 * --------------------------
 * Cadastra uma nova pessoa no sistema
 *
 * Parâmetro:
 * struct pessoa pessoa -> Estrutura com as informações da pessoa
 * char tipo ('a' ->Aluno || 'p' ->Professor)
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cadastrarPessoa(struct pessoa psa, char tipo);

/* 
 * Função: cadastrarTurma
 * --------------------------
 * Cadastra uma nova turma no sistema
 *
 * Parâmetro:
 * struct turma turma -> Estrutura com as informações da turma
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cadastrarTurma(struct turma turma);

/* 
 * Função: inscreverAluno
 * --------------------------
 * Inscreve um aluno em uma aula
 *
 * Parâmetro:
 * int id_aluno -> ID do aluno que será inscrito
 * int id_aula -> ID da aula que será inscrito
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int inscreverAluno(int id_aluno, int id_aula);

/* 
 * Função: cancelarInscricao
 * --------------------------
 * Cancela a inscrição de um aluno em uma aula
 * ou de todos os alunos em uma aula(se o id_aluno = -1)
 *
 * Parâmetro:
 * int id_aluno -> ID do aluno que será cancelada a inscrição
 * int id_aula -> ID da aula que será cancelada a inscrição
 *
 * Retorno: int (1 ->sucesso || 0 ->erro)	
 */
int cancelarInscricao(int id_aluno, int id_aula);

/* 
 * Função: fecharTurmas
 * --------------------------
 * Fecha todas as turmas com menos inscrições do que o inteiro passado como parâmetro
 *
 * Parâmetro:
 * int min -> quantidade mínima de inscrições que a turma deve ter para não ser cancelada
 *
 * Retorno: int -> quantidade de turmas fechadas
 */
int fecharTurmas(int min);

/* 
 * Função: confirmarTurmas
 * --------------------------
 * Confirma todas as turmas que existem no arquivo de aulas no momento
 *
 * Retorno: int -> quantidade de turmas confirmadas
 */
int confirmarTurmas();

#endif
