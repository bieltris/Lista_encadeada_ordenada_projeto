#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *nomesArquivosListas;
const char ARQUIVO_NOMES_LISTAS[] = "nome_dos_arquivos.txt";
typedef struct tarefa
{
    char nome[50];
    int prioridade;
    struct tarefa *prox;
} Tarefa;

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void liberarLista(Tarefa *inicio)
{
    Tarefa *temp;
    while (inicio != NULL)
    {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
}


void liberarTarefa(Tarefa **inicio, Tarefa *tarefaApagarei) {

    Tarefa *atual = *inicio;
    Tarefa *anterior = NULL;
    while(atual != NULL && atual != tarefaApagarei){
        anterior = atual;
        atual = atual->prox;
    }

    if(anterior != NULL) {
        anterior->prox = atual->prox;
        free(atual);
    } else {
        *inicio = atual->prox;
        free(atual);

    }
}

void inserirOrdenado(Tarefa **inicio, Tarefa *novaTarefa)
{
    if (*inicio == NULL || (*inicio)->prioridade > novaTarefa->prioridade)
    {
        novaTarefa->prox = *inicio;
        *inicio = novaTarefa;
        return;
    }

    Tarefa *atual = *inicio;
    while(atual != NULL)
    {
        if(atual->prioridade == novaTarefa->prioridade && strcmp(atual->nome, novaTarefa->nome)== 0)
        {
            printf("Ja existe uma tarefa com esses dados!\n");
            return;
        }
        atual = atual->prox;
    }


    atual = *inicio;
    Tarefa *anterior = NULL;

    while (atual != NULL && atual->prioridade < novaTarefa->prioridade)
    {
        anterior = atual;
        atual = atual->prox;
    }

    while (atual != NULL && atual->prioridade == novaTarefa->prioridade &&
            strcmp(atual->nome, novaTarefa->nome) < 0)
    {
        anterior = atual;
        atual = atual->prox;
    }


    novaTarefa->prox = atual;
    if (anterior != NULL)
    {
        anterior->prox = novaTarefa;
    }
    else
    {
        *inicio = novaTarefa;
    }
}

void reinserirNovaAtualOrdenado(Tarefa **inicio, Tarefa *atual) {

    Tarefa *NovaAtual = malloc(sizeof(Tarefa));
    strcpy(NovaAtual->nome, atual->nome);
    NovaAtual->prioridade = atual->prioridade;
    NovaAtual->prox = NULL;
    liberarTarefa(inicio, atual);
    inserirOrdenado(inicio, NovaAtual);

}


void apagarTarefaPelaPrioridade(Tarefa **inicio)
{
    int prioridadeProcurada;
    printf("Digite a prioridade da tarefa que deseja apagar: ");
    scanf(" %d", &prioridadeProcurada);
    limparBuffer();

    Tarefa *atual = *inicio;
    int enumerarTarefas = 0;

    while (atual != NULL)
    {
        if (atual->prioridade == prioridadeProcurada)
        {
            printf("[%d] %s\t| prioridade %d\n",
                   enumerarTarefas, atual->nome, prioridadeProcurada);
            enumerarTarefas++;
        }
        atual = atual->prox;
    }

    if (enumerarTarefas == 0)
    {
        printf("Nao existem tarefas com essa prioridade.\n");
        return;
    }

    int tarefaApagar;
    printf("Digite o numero da tarefa que deseja apagar: ");
    scanf(" %d", &tarefaApagar);
    limparBuffer();
    atual = *inicio;
    Tarefa *anterior = NULL;
    int contador = 0;

    while (atual != NULL)
    {
        if (atual->prioridade == prioridadeProcurada)
        {
            if (contador == tarefaApagar)
            {
                if (anterior == NULL)
                {
                    *inicio = atual->prox;
                }
                else
                {
                    anterior->prox = atual->prox;
                }
                free(atual);
                printf("Tarefa removida com sucesso.\n");
                return;
            }
            contador++;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Tarefa nao encontrada para remocao.\n");
}

void alterarNome(Tarefa **inicio)
{
    Tarefa *atual = *inicio;
    int indice = 0;

    while(atual != NULL)
    {
        printf("[%d] %s\n", indice, atual->nome);
        indice++;
        atual = atual->prox;
    }

    int indiceApagar = 0;
    char novoNome[50];
    printf("Digite o indice da tarefa que deseja mudar o nome: ");
    scanf(" %d", &indiceApagar);
    limparBuffer();
    printf("Escreva o novo nome: ");
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';

    atual = *inicio;

    for(int i = 0; i <= indiceApagar; i++)
    {
        if (atual == NULL)
        {
            printf("Indice invalido.\n");
            return;
        }

        if(i == indiceApagar)
        {
            strcpy(atual->nome, novoNome);
            reinserirNovaAtualOrdenado(inicio, atual);
            return;
        }
        atual = atual->prox;
    }
}

void apagarTarefaPeloNome(Tarefa **inicio)
{

    Tarefa *atual = *inicio;
    Tarefa *anterior = NULL;

    char nomeApagarei[sizeof(atual->nome)];
    printf("Escreva o nome da tarefa que sera deletada: ");
    fgets(nomeApagarei, sizeof(nomeApagarei), stdin);
    nomeApagarei[strcspn(nomeApagarei, "\n")] = '\0';


    while(atual != NULL)
    {

        if(strcmp(atual->nome, nomeApagarei) == 0)
        {
            if(anterior != NULL)
            {
                printf("Tarefa apagada %s | %d", atual->nome, atual->prioridade);
                anterior->prox = atual->prox;
                free(atual);
                return;
            }
            else
            {
                printf("Tarefa apagada %s | %d", atual->nome, atual->prioridade);
                *inicio = atual->prox;
                free(atual);
                return;
            }
        }

        anterior = atual;
        atual = atual->prox;
    }
    printf("Nao existe este nome na lista!\n");

}

void imprimirLista(Tarefa *inicio)
{
    printf("Lista de Tarefas:\n\n");

    if(inicio == NULL){
        printf("Lista vazia!\n");
        return;
    }

    while (inicio != NULL)
    {
        printf("Tarefa: %s\t|\tPrioridade: %d\n", inicio->nome, inicio->prioridade);
        inicio = inicio->prox;
    }



}

void alterarPrioridade(Tarefa **inicio)
{

    int prioridadeProcurada;
    imprimirLista(*inicio);
    printf("Digite a prioridade da tarefa que deseja apagar\n>");
    scanf(" %d", &prioridadeProcurada);
    limparBuffer();
    Tarefa *atual = *inicio;
    int contador = 0;
    while(atual != NULL)
    {

        if(atual->prioridade == prioridadeProcurada)
        {
            printf("[%d] %s\t%d\n", contador, atual->nome, atual->prioridade);
            contador++;
        }

        atual = atual->prox;
    }

    if(contador == 0)
    {
        printf("Nao existe Tarefa com essa prioridade\n");
        return;
    }

    int indice;
    printf("Digite o indice da prioridade que deseja alterar:\n>");
    scanf("%d", &indice);
    limparBuffer();

    atual = *inicio;
    while(atual != NULL && atual->prioridade != prioridadeProcurada)
    {
        atual = atual->prox;
    }


    int avancarLista = 0;
    while(avancarLista < indice)
    {
        atual = atual->prox;
    }

    int novaPrioridade;
    printf("Nova prioridade da Tarefa:\n>");
    scanf(" %d", &novaPrioridade);
    limparBuffer();

    atual->prioridade = novaPrioridade;
    reinserirNovaAtualOrdenado(inicio, atual);
}

void apagarDeterminadaPrioridade(Tarefa **inicio)
{

    Tarefa *atual = *inicio;

    if (atual == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    int prioridadeQueApagarei;
    printf("Digite a prioridade que deseja remover de toda a lista: ");
    scanf(" %d", &prioridadeQueApagarei);
    limparBuffer();
    while(*inicio != NULL && (*inicio)->prioridade == prioridadeQueApagarei)
    {
        Tarefa *temp = *inicio;
        *inicio = (*inicio)->prox;
        free(temp);
        printf("Apagando prioridade do inicio\n");

    }




    atual = *inicio;
    Tarefa *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->prioridade == prioridadeQueApagarei)
        {
            Tarefa *temp = atual;
            atual = atual->prox;
            if (anterior != NULL)
                anterior->prox = atual;
            free(temp);
        }
        else
        {
            anterior = atual;
            atual = atual->prox;
        }
    }

    printf("Remocao concluida.\n");
}

Tarefa *interseccaoEntreListas(Tarefa *inicio, Tarefa *inicio_2)
{

    Tarefa *interList = NULL;
    Tarefa *atual_1 = inicio;
    Tarefa *atual_2 = inicio_2;

    while(atual_1 != NULL)
    {
        atual_2 = inicio_2;
        while(atual_2 != NULL)
        {
            if(atual_1->prioridade == atual_2->prioridade && (strcmp(atual_1->nome, atual_2->nome) == 0))
            {
                Tarefa *temp = malloc(sizeof(Tarefa));
                strcpy(temp->nome, atual_1->nome);
                temp->prioridade = atual_1->prioridade;
                temp->prox = NULL;
                printf("Novo item iterseccionado!\n");
                inserirOrdenado(&interList, temp);
            }
            printf("Avancando atual_2...\n");
            atual_2 = atual_2->prox;
        }
        printf("Avancando atual_1...\n");
        atual_1 = atual_1->prox;
    }

    return interList;
}

void salvarLista(Tarefa *inicio, char nomeDoArquivo[])
{

    if(strcmp(nomeDoArquivo, ".txt") == 0)
    {
        printf("Salvando %s...\n", nomeDoArquivo);
    }
    else
    {

        strcat(nomeDoArquivo, ".txt");
        printf("Adicionando .txt...\n%s\n", nomeDoArquivo);
    }



    FILE *listaf = fopen(nomeDoArquivo, "ab");
    if(listaf == NULL)
    {
        listaf = fopen(nomeDoArquivo, "wb");
    }

    Tarefa *atual = inicio;

    while(atual != NULL)
    {
        fwrite(atual, sizeof(Tarefa), 1, listaf);
        atual = atual->prox;
    }

    fclose(listaf);
}

void salvarNomeDoArquivo(char nomeDoArquivo[], size_t tamanho)
{

    nomesArquivosListas = fopen(ARQUIVO_NOMES_LISTAS, "a+b");
    if(nomesArquivosListas == NULL)
    {
        nomesArquivosListas = fopen(ARQUIVO_NOMES_LISTAS, "wb");
    }

    char nomesArquivosJaSalvos[tamanho];
    while(strcmp(nomesArquivosJaSalvos, nomeDoArquivo) != 0){

        fread(nomesArquivosJaSalvos, sizeof(char), tamanho, nomesArquivosListas);
        printf("Lendo nomes..\n");
        if(feof(nomesArquivosListas)){
            break;
        }
    }
    if(strcmp(nomesArquivosJaSalvos, nomeDoArquivo) == 0){
        printf("Escolhido nome existente.\n");
        return;
    }
    fwrite(nomeDoArquivo, sizeof(char), tamanho, nomesArquivosListas);

    fclose(nomesArquivosListas);
}

void listarNomeDosArquivos()
{
    char nomeArquivo[15];
    int contador = 0;
    nomesArquivosListas = fopen(ARQUIVO_NOMES_LISTAS, "rb");
    printf("\n");
    while(fread(nomeArquivo, sizeof(char), 15, nomesArquivosListas))
    {
        printf("[%d]%s\n", contador, nomeArquivo);
        contador++;
    }
    if(contador == 0) {
        printf("Nao existem arquivos ainda!\n");
    }
    fclose(nomesArquivosListas);
}

void carregarListaDoArquivo(Tarefa **inicio, char nomeDoArquivo[])
{

    if (strstr(nomeDoArquivo, ".txt") == NULL)
    {
        printf("Adicionando .txt...\n%s.txt\n", nomeDoArquivo);
        strcat(nomeDoArquivo, ".txt");
    }


    nomesArquivosListas = fopen(nomeDoArquivo, "rb");
    if(nomesArquivosListas == NULL)
    {
        printf("Erro ao ler arquivo...\n");
        exit(1);
    }

    liberarLista(inicio);

    while(1)
    {
        Tarefa *nova = malloc(sizeof(Tarefa));
        if (fread(nova, sizeof(Tarefa), 1, nomesArquivosListas) != 1)
        {
            free(nova);
            break;
        }

        nova->prox = NULL;
        inserirOrdenado(inicio, nova);
    }


    fclose(nomesArquivosListas);
}

void editarListaEncadeada(Tarefa **inicio)
{

    int alterarOuApagar;
    int NomeOuPrioridade;
    printf("Deseja alterar dados ou apagar determinadas tarefas?\n");
    printf("[0] EDITAR\n[1] APAGAR\n");
    scanf(" %d", &alterarOuApagar);
    printf("Buscar por NOME ou PRIORIDADE a Tarefa?\n");
    printf("[0] NOME\n[1] PRIORIDADE\n");
    scanf(" %d", &NomeOuPrioridade);
    limparBuffer();
    if(alterarOuApagar == 0)
    {
        if(NomeOuPrioridade == 0)
        {
            alterarNome(inicio);
        }
        else if(NomeOuPrioridade)
        {
            alterarPrioridade(inicio);
        }
    }
    else if(alterarOuApagar == 1)
    {
        if(NomeOuPrioridade == 0)
        {
            apagarTarefaPeloNome(inicio);
        }
        else if (NomeOuPrioridade == 1)
        {
            int umaTarefa;
            printf("Deseja apagar todas as Tarefas de determinada prioridade ou uma Tareda apenas\n");
            printf("[0] Uma Tarefa\n[1] Todas Taredas de determinda prioridade\n>");
            scanf(" %d", &umaTarefa);
            limparBuffer();
            if(umaTarefa == 0)
            {

                apagarTarefaPelaPrioridade(inicio);
            }
            else
            {
                apagarDeterminadaPrioridade(inicio);
            }
        }
    }
}

void mostrarListaEmManipulacao(int numDaLista)
{


    if(numDaLista == 1)
    {
        printf("Lista: Lista_1\n");
    }
    else if(numDaLista == 2)
    {
        printf("Lista: Lista_2\n");
    }
    else if(numDaLista == 3)
    {
        printf("Lista: Lista de intersseccao\n");
    }

}



int main()
{
    int opcao;
    Tarefa *inicio = NULL;
    Tarefa *inicio_lista_2 = NULL;
    Tarefa *listaInter = NULL;
    int listaEscolhida = 1;
    char nomeDoArquivo[15];

    printf("Criacao de lista encadeada ordenada!\n");

    do
    {

        printf("\nO que voce deseja?\n");
        printf(" 0 - Sair\n");
        printf(" 1 - Criar uma tarefa\n");
        printf(" 2 - Editar Lista\n");
        printf(" 3 - Imprimir lista ordenada\n");
        printf(" 4 - Criar lista de interseccao entre as duas listas\n");
        printf(" 5 - ALterar lista em manipulacao\n");
        printf(" 6 - Salvar lista em um arquivo\n");
        printf(" 7 - Carregar lista de um arquivo\n");
        mostrarListaEmManipulacao(listaEscolhida);


        printf(">");
        scanf(" %d", &opcao);
        limparBuffer();

        if(opcao == 1)
        {
            char novoNome[50];
            int novaPrioridade;


            printf("Digite o nome da tarefa: ");
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = '\0';

            printf("Digite a prioridade: ");
            scanf("%d", &novaPrioridade);
            limparBuffer();

            Tarefa *nova = malloc(sizeof(Tarefa));
            strcpy(nova->nome, novoNome);
            nova->prioridade = novaPrioridade;
            nova->prox = NULL;


            if(listaEscolhida == 1)
            {
                inserirOrdenado(&inicio, nova);
            }
            else if(listaEscolhida == 2)
            {
                inserirOrdenado(&inicio_lista_2, nova);
            }
            else if(listaEscolhida == 3)
            {
                inserirOrdenado(&listaInter, nova);
            }

        }
        else if(opcao == 2)
        {


            if(listaEscolhida == 1)
            {
                editarListaEncadeada(&inicio);
            }
            else if(listaEscolhida == 2)
            {
                editarListaEncadeada(&inicio_lista_2);
            }
            else if(listaEscolhida == 3)
            {
                editarListaEncadeada(&listaInter);
            }

        }
        else if(opcao == 3)
        {

            if(listaEscolhida == 1)
            {
                imprimirLista(inicio);
            }
            else if(listaEscolhida == 2)
            {
                imprimirLista(inicio_lista_2);
            }
            else if(listaEscolhida == 3)
            {
                imprimirLista(listaInter);
            }



        }
        else if(opcao == 4)
        {

            listaInter = interseccaoEntreListas(inicio, inicio_lista_2);

            printf("Lista de interseccao:\n");
            imprimirLista(listaInter);
        }
        else if(opcao == 5)
        {

            printf("Qual lista voce deseja ter controle?\n");
            printf("[1]  Lista_1\n");
            printf("[2]  Lista_2\n");
            printf("[3]  Lista de intersseccao\n");
            scanf(" %d", &listaEscolhida);
            limparBuffer();
            if(listaEscolhida < 1 || listaEscolhida > 3)
            {
                listaEscolhida = 1;
                printf("Valor invalida!\nLista padrao(LIsta_1) em manipulacao\n");
            }

        }
        else if(opcao == 6)
        {


            printf("Digite o nome do arquivo para salvar a lista ou crie escrevendo um novo nome.\n");

            listarNomeDosArquivos();

            fgets(nomeDoArquivo, sizeof(nomeDoArquivo), stdin);
            nomeDoArquivo[strcspn(nomeDoArquivo, "\n")] = '\0';

            salvarNomeDoArquivo(nomeDoArquivo, sizeof(nomeDoArquivo));
            if(listaEscolhida == 1)
            {
                salvarLista(inicio, nomeDoArquivo);
            }
            else if(listaEscolhida == 2)
            {
                salvarLista(inicio_lista_2, nomeDoArquivo);
            }
            else if(listaEscolhida == 3)
            {
                salvarLista(listaInter, nomeDoArquivo);
            }

        }
        else if(opcao == 7)
        {
            char nomeArquivoCarregado[15];
            printf("Digite o nome do arquivo para carregar a lista.\n");
            listarNomeDosArquivos();

            fgets(nomeArquivoCarregado, sizeof(nomeArquivoCarregado), stdin);
            nomeArquivoCarregado[strcspn(nomeArquivoCarregado, "\n")] = '\0';

            if(listaEscolhida == 1)
            {
                carregarListaDoArquivo(&inicio, nomeArquivoCarregado);
            }
            else if(listaEscolhida == 2)
            {
                carregarListaDoArquivo(&inicio_lista_2, nomeArquivoCarregado);
            }
            else if(listaEscolhida == 3)
            {
                carregarListaDoArquivo(&listaInter, nomeArquivoCarregado);
            }

        }

    }
    while (opcao != 0);

    liberarLista(inicio);
    liberarLista(inicio_lista_2);

    return 0;
}

