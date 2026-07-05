/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

/****************** ESTRUTURAS ******************/

typedef struct pais {
    char *nome;
    char *descricao;
    struct pais *proximo;
} Pais;

typedef struct letra {
    char l;
    int total;
    Pais *paises;
    struct letra *anterior, *proximo;
} Letra;

void gotoXY(int, int);
void salvar();

/****************** VARIAVEIS ******************/
int opcao, linha, col;
char resp, nome[64] = {}, descricao[64] = {};

//COORD CursorPosition;
Pais *paisAux;
Letra *letraAux, preLetraLista = {};

/************ FUNÇÕES AUXILIARES ****************/

void lerTexto(char *txt) {
    fgets(txt, 64, stdin);
    txt[strcspn(txt, "\n")] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void freePais(Pais **noPais) {
    free((*noPais)->nome);
    free((*noPais)->descricao);
    free(*noPais);
    *noPais = NULL;
}

void escrever(char **destino, char *fonte) {
    free(*destino);
    *destino = strdup(fonte);
    if (!(*destino)) return;
}

Letra *existeLetra(const char busca) {
    Letra *aux = preLetraLista.proximo;

    while (aux && aux->l != toupper(busca)) aux = aux->proximo;
    return aux ? aux : NULL;
}

Pais *existePais(const char *nome) {
    Letra *auxL = existeLetra(nome[0]);
    if (!auxL) return NULL;

    Pais *auxP = auxL->paises;

    while (auxP) {
        if (stricmp(auxP->nome, nome) == 0) {
            return auxP;
        }
        auxP = auxP->proximo;
    }
    return NULL;
}

Pais *buscarNoDicionario(const char *busca) {
    return existePais(busca);

    /* if (existeLetra(toupper(busca[0]))) {
        return existePais(busca);
    } else {
        existePais(busca);
        return NULL;
    } */
}

typedef int (*Ordem)(Letra *);
int crescente(Letra *_eleito) {
    return letraAux->l > _eleito->l;
}

int decrescente(Letra *_eleito) {
    if (letraAux == &preLetraLista) return 0;
    return letraAux->l < _eleito->l;
}

void swap(Letra *eleito) {
    if (eleito->proximo) eleito->proximo->anterior = eleito->anterior;
    eleito->anterior->proximo = eleito->proximo;

    letraAux->anterior->proximo = eleito;
    eleito->anterior = letraAux->anterior;

    eleito->proximo = letraAux;
    letraAux->anterior = eleito;
}

void insertionSort(Ordem ordem) {
    int trocar = 0;
    letraAux = preLetraLista.proximo;
    Letra *eleito = letraAux->proximo, *pin;

    while (eleito) {
        pin = eleito->proximo;
        letraAux = eleito->anterior;

        while (ordem(eleito)) {
            letraAux = letraAux->anterior;
            trocar = 1;
            continue;
        }

        if (trocar == 1) {
            letraAux = letraAux->proximo;
            swap(eleito);

            trocar = 0;
        }

        eleito = pin;
    }
}

void bubbleSort(Ordem ordem) {
    int troca = 1;

    while (troca) {
        troca = 0;
        letraAux = preLetraLista.proximo;

        while (letraAux->proximo) {

            if (ordem(letraAux->proximo)) {
                swap(letraAux->proximo);
                troca = 1;
            } else {
                letraAux = letraAux->proximo;
            }
        }
    }
}

void Ordenar(void (*bbSort)(Ordem), Ordem ordem) {
    bbSort(ordem);
    puts("Entrou na função-ordenar()");
    puts("TRECHOS COMUM DE VÁRIOS TIPO DE CÓDIGO");
}

/****************** FUNCAO CABECALHO ******************/

void telaCabecalho() {
    system("cls");
    gotoXY(3, 5);
    printf("DICIONARIO DE PAISES");
    gotoXY(3, 7);
    printf("USANDO UMA LISTA SIMPLES E DUPLAMENTE ENCADEADA\n");
}

/****************** TELAS ******************/
int telaExibir() {
    if (preLetraLista.proximo) {
        system("cls"); gotoXY(1, 1);
        printf("────────────────────────  EXIBIR ────────────────────────"); gotoXY(1, 2);
        printf("[b/B] ORDENAR: BUBBLESORT CRESCENTE/DECRESCENTE\n");
        printf("[i/I] ORDENAR: INSERTIONSORT CRESCENTE/DECRESCENTE\n");

        printf("LETRA - TOTAIS/PAÍSES");
        printf("\n─────────────────────────────────────────────────────────\n");
        return 1;
    } else {
        gotoXY(15, 18);
        puts("NÃO HÁ PAISES REGISTRADO");
        system("pause");
        return 0;
    }
}

void telaMenu() {
    col = 10;
    gotoXY(col, 10);
    puts("──────────────── MENU ────────────────");
    gotoXY(col, 11);
    puts("*      Exibir.............[1]       *");
    gotoXY(col, 12);
    puts("*      Inserir............[2]       *");
    gotoXY(col, 13);
    puts("*      Remover............[3]       *");
    gotoXY(col, 14);
    puts("*      Editar.............[4]       *");
    gotoXY(col, 15);
    puts("*      Sair...............[0]       *");
    gotoXY(col, 16);
    printf("*      Digite a opção:              *");
    gotoXY(col, 17);
    puts("─────────────────────────────────────");
    gotoXY(37, 16);
}

Pais *telaInserir() {
    system("cls");
    printf("──────────────────── ADICIONAR PAÍS ────────────────────");
    gotoXY(1, 2);
    printf("*  Nome do País:                                                 *");
    gotoXY(1, 3);
    printf("*  Campo 1:                                                      *");
    gotoXY(1, 4);
    printf("*  Campo 3:                                                      *");

    printf("\n────────────────────────────────────────────────────────");

    gotoXY(20, 2); scanf(" %63[^\n]", nome); limparBuffer();
    gotoXY(20, 3); scanf(" %63[^\n]", descricao); limparBuffer();

    return buscarNoDicionario(nome);
}

Pais *telaRemover() {
    system("cls");
    puts("************************** REMOVER PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");

    gotoXY(20, 2); scanf(" %63[^\n]", nome); limparBuffer();

    return buscarNoDicionario(nome);
}

Pais *telaEditar() {
    system("cls");
    puts("************************** EDITAR PAÍS *****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("*  NOVO NOME:                                                      *");
    gotoXY(1, 4);
    puts("*  DESCRIÇÃO:                                                      *");
    puts("********************************************************************");

    gotoXY(20, 2); scanf(" %63[^\n]", nome); limparBuffer();
    gotoXY(20, 3);

    return buscarNoDicionario(nome);
}

/********************* FUNCAO EXIBIR *******************/

void exibir() {
    if (preLetraLista.proximo != NULL) {
        letraAux = preLetraLista.proximo;

        while (letraAux) {
            printf("[%c] - (%d)\n", letraAux->l, letraAux->total);
            paisAux = letraAux->paises;
            while (paisAux) {
                printf("    %s\n", paisAux->nome);
                paisAux = paisAux->proximo;
            }
            letraAux = letraAux->proximo; puts("");
        }

        printf("\n────────────────────────────────────────────────────────────\n");
        puts(""); puts("Escolha uma ordenação ou outra teclas para sair");
        scanf(" %c", &resp); getchar();
        switch (resp) {
            case 'i':
                insertionSort(crescente);
                goto refresh;
            case 'I':
                insertionSort(decrescente);
                goto refresh;
            case 'b':
                bubbleSort(crescente);
                goto refresh;
            case 'B':
                bubbleSort(decrescente);
                goto refresh;
            refresh:
                telaExibir();
                exibir();
                break;
            default:
                //Ordenar(bubbleSort, crescente);
                break;
        }
    }
}

/********************* FUNCAO INSERIR *******************/

void inserir(char *novoPais, char *novaDescricao) {
    Letra *letter = existeLetra(novoPais[0]);

    if (letter) {
        Pais *country = letter->paises;
        while (country->proximo) country = country->proximo;

        country->proximo = calloc(1, sizeof(Pais)); if (!country->proximo) return;
        country = country->proximo;

        escrever(&country->nome, novoPais);
        escrever(&country->descricao, novaDescricao);
        letter->total++;

    } else {
        letter = &preLetraLista;
        while (letter->proximo) letter = letter->proximo;

        letter->proximo = calloc(1, sizeof(Letra)); if (!letter->proximo) return;
        letter->proximo->paises = calloc(1, sizeof(Pais)); if (!letter->proximo->paises) return;

        letter->proximo->anterior = letter;

        letter->proximo->l = toupper(novoPais[0]);
        letter->proximo->total++;
        escrever(&letter->proximo->paises->nome, novoPais);
        escrever(&letter->proximo->paises->descricao, novaDescricao);

    }

    salvar();
}

/********************* FUNCAO REMOVER *******************/

void remover(Letra *letra, Pais *pais) {
    // Tratar os ponteiros
    if (pais == letra->paises) letra->paises = pais->proximo;
    else {
        paisAux = letra->paises;
        while (paisAux->proximo != pais) paisAux = paisAux->proximo;

        paisAux->proximo = pais->proximo;
    }

    // Libera memória
    freePais(&pais);
    letra->total--;

    // Verifica se letra é vazia
    if (letra->total == 0) {
        letra->anterior->proximo = letra->proximo;
        if (letra->proximo) {
            letra->proximo->anterior = letra->anterior;
        }
        free(letra);
        letra = NULL;
    }
}

void editar(Pais *paisTemp) {
    lerTexto(nome); gotoXY(20, 4);
    lerTexto(descricao);

    paisAux = buscarNoDicionario(nome);

    if (paisAux) {
        escrever(&paisAux->descricao, descricao);
    } else {
        inserir(nome, descricao);
        remover(existeLetra(paisTemp->nome[0]), paisTemp);
    }
}

/****************** ARQUIVO ******************/

void carregar() {
    FILE *f = fopen("dicionario.txt", "r");
    if (!f) { puts("Erro ao carregar!"); return; }

    while (1) {
        int lidos = fscanf(
            f,
            "%63[^|]|%63[^\n]\n",
            nome,
            descricao
        );

        if (lidos != 2) {
            break;
        }

        inserir(nome, descricao);
    }

    fclose(f);
}

void salvar() {
    FILE *f = fopen("dicionario.txt", "w");
    if (!f) { printf("Erro ao salvar"); return; }

    letraAux = &preLetraLista;
    letraAux = letraAux->proximo;

    while (letraAux) {
        paisAux = letraAux->paises;

        while (paisAux && fprintf(
            f,
            "%s|%s\n",
            paisAux->nome,
            paisAux->descricao) != EOF
        ) {
            paisAux = paisAux->proximo;
        }

        letraAux = letraAux->proximo;
    }

    fclose(f);
}

void liberarDicionario(Letra *cabeca) {
    if (!cabeca) return;

    Letra *atualL = cabeca->proximo;

    while (atualL) {
        Pais *atualP = atualL->paises;
        while (atualP) {
            Pais *proxP = atualP->proximo;
            freePais(&atualP);
            atualP = proxP;
        }

        Letra *proxL = atualL->proximo;
        free(atualL);
        atualL = proxL;
    }

    cabeca->proximo = NULL;
}

void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

/****************** FUNCAO PRINCIPAL ******************/

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".65001");

    int cont_tela = 1;

    preLetraLista.proximo = NULL; /* lista vazia */
    carregar();
    cont_tela++;

    do {
        if (cont_tela > 1) {
            telaCabecalho();
            telaMenu();
        }
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                liberarDicionario(&preLetraLista);
                exit(0);
                break;
            case 1:
                if (telaExibir() == 1) {
                    exibir();
                }
                break;
            case 2:
                if (telaInserir() == NULL) {
                    inserir(nome, descricao);
                }
                break;
            case 3:
                Pais * temp = telaRemover();
                if (temp) {
                    remover(existeLetra(nome[0]), temp);
                }
                break;
            case 4:
                Pais * selecionado = telaEditar();
                if (selecionado) {
                    editar(selecionado);
                }
                break;
            case 9:
                //inserirOrdem();
                break;
            default:
                gotoXY(15, 18);
                //cout << "ATENCAO: Opcao Invalida! ";
                system("pause");
        }

    } while (opcao != 0);

    return 0;
}
