#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Funcionario Funcionario;

struct Funcionario
{
    int salario;
    char nome[50];
    Funcionario *next;
};
/*
void insertAtTop(char *nome, int salario, Funcionario *head)
{
    Funcionario *novo = (Funcionario *)malloc(sizeof(Funcionario));

    strcpy(novo->nome, nome);
    novo->salario = salario;
    novo->next = head;

    head = novo;
}
*/

/*
void insertAtPosition(char *nome, int salario, Funcionario *head)
{
}
*/

void insertAtBottom(char *nome, int salario, Funcionario *head)
{
    Funcionario *novo = (Funcionario *)malloc(sizeof(Funcionario));

    strcpy(novo->nome, nome);
    novo->salario = salario;
    novo->next = NULL;

    Funcionario *ptr = head;

    while (ptr->next)
    {
        ptr = ptr->next;
    }

    ptr->next = novo;
}

void printTable(Funcionario *head)
{
    Funcionario *temp = head;

    while (temp)
    {
        printf("\n%s      %d", temp->nome, temp->salario);
        temp = temp->next;
    }

    puts("\n\nFim da lista de funcionários, siga no menu.");
}

void initMenu(int *resposta)
{
    printf("\n============================");
    printf("\n 1. Adicionar funcionário");
    printf("\n 2. Listar funcionários");
    printf("\n 3. Salvar e sair");
    printf("\n============================\n\nResposta: ");

    int test = scanf("%d", resposta);

    if (test != 1 || *resposta > 3 || *resposta < 1)
    {
        puts("\n\n Resposta inválida, responda novamente. \n");
        initMenu(resposta);
    }
}

void freeLinkedList(Funcionario *head)
{
    Funcionario *temp = head;
    while (head != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
}

void writeListToTXT(Funcionario *head, FILE *fp)
{
    Funcionario *ptr = head;

    while (ptr)
    {
        fprintf(fp, "%s     %d\n", ptr->nome, ptr->salario);
        ptr = ptr->next;
    }
}

int main()
{
    Funcionario *head = (Funcionario *)malloc(sizeof(Funcionario));

    if (head == NULL)
    {
        return 1;
    }

    head->next = NULL;
    strcpy(head->nome, "Eduardo");
    head->salario = 1920;

    FILE *fp = fopen("funcionarios.txt", "w");

    if (fp == NULL)
    {
        return 1;
    }

    int resposta = 0;
    char nome[50];
    int salario = 0;

    while (resposta != 3)
    {
        initMenu(&resposta);
        if (resposta == 1)
        {
            for (;;)
            {
                puts("\nInsira o nome do novo funcionario (ate 50 caracteres): ");
                scanf("%s", nome);

                if (strlen(nome) > 50)
                {
                    puts("\nO nome tem mais de 50 caracteres, tente novamente.\n");
                }
                else
                {

                    break;
                }
            }

            for (;;)
            {
                puts("\nInsira o salario do novo funcionario (maior que zero): ");
                scanf("%d", &salario);

                if (salario <= 0)
                {
                    puts("\nO salario deve ser maior que 0, tente novamente.\n");
                }
                else
                {

                    break;
                }
            }

            insertAtBottom(nome, salario, head);

            puts("\nNovo funcionario adicionado ao fim da lista, prossiga no menu.");
        }
        else if (resposta == 2)
        {
            printTable(head);
        }
    }

    writeListToTXT(head, fp);

    fclose(fp);
    freeLinkedList(head);

    return 0;
}