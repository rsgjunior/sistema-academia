#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "academia.h"

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
