/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

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

/****************** VARIAVEIS ******************/

char nome[64] = {}, descricao[64] = {};
Letra preLetraLista = {};

/************ FUNÇÕES AUXILIARES ****************/

void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerTexto(char *txt) {
    fgets(txt, 64, stdin);
    txt[strcspn(txt, "\n")] = '\0';
}

void escrever(char **destino, char *fonte) {
    free(*destino);
    *destino = strdup(fonte);
    if (!(*destino)) return;
}

void freePais(Pais **pais) {
    free((*pais)->nome);
    free((*pais)->descricao);
    free(*pais);
    *pais = NULL;
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

Letra *existeLetra(const char busca) {
    Letra *auxL = preLetraLista.proximo;

    while (auxL && auxL->l != toupper(busca)) auxL = auxL->proximo;
    return auxL ? auxL : NULL;
}

Pais *buscarNoDicionario(const char *nome) {
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

/************************** ORDENAÇÃO *******************************/

typedef int (*Ordem)(Letra *A, Letra *B);
int crescente(Letra *_aux, Letra *_eleito) {
    return _aux->l > _eleito->l;
}

int decrescente(Letra *_aux, Letra *_eleito) {
    if (_aux == &preLetraLista) return 0;
    return _aux->l < _eleito->l;
}

void swap(Letra *auxL, Letra *eleito) {
    if (eleito->proximo) eleito->proximo->anterior = eleito->anterior;
    eleito->anterior->proximo = eleito->proximo;

    auxL->anterior->proximo = eleito;
    eleito->anterior = auxL->anterior;

    eleito->proximo = auxL;
    auxL->anterior = eleito;
}

void insertionSort(Ordem ordem) {
    int trocar = 0;
    Letra *auxL = preLetraLista.proximo;
    Letra *eleito = auxL->proximo, *pin;

    while (eleito) {
        pin = eleito->proximo;
        auxL = eleito->anterior;

        while (ordem(auxL, eleito)) {
            auxL = auxL->anterior;
            trocar = 1;
            continue;
        }

        if (trocar == 1) {
            auxL = auxL->proximo;
            swap(auxL, eleito);
        }

        eleito = pin;
    }
}

void bubbleSort(Ordem ordem) {
    int troca = 1;

    while (troca) {
        troca = 0;
        Letra *auxL = preLetraLista.proximo;

        while (auxL->proximo) {

            if (ordem(auxL, auxL->proximo)) {
                swap(auxL, auxL->proximo);
                troca = 1;
            } else {
                auxL = auxL->proximo;
            }
        }
    }
}

void ordenar(void (*sortType)(Ordem), Ordem ordem) {
    sortType(ordem);
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
    int col = 10;
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
    printf("*  NOME DO PAÍS:                                                 *");
    gotoXY(1, 3);
    printf("*  DESCRIÇÃO:                                                      *");
    printf("\n────────────────────────────────────────────────────────");

    gotoXY(20, 2); lerTexto(nome);
    gotoXY(20, 3); lerTexto(descricao);

    return buscarNoDicionario(nome);
}

Pais *telaRemover() {
    system("cls");
    puts("************************** REMOVER PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");

    gotoXY(20, 2); lerTexto(nome);

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

    gotoXY(20, 2); lerTexto(nome);
    gotoXY(20, 3);

    return buscarNoDicionario(nome);
}

/********************* FUNCAO EXIBIR *******************/

void exibir() {
    Letra *auxL = preLetraLista.proximo;
    Pais *auxP;

    char resp;
    if (preLetraLista.proximo != NULL) {

        while (auxL) {
            printf("[%c] - (%d)\n", auxL->l, auxL->total);
            auxP = auxL->paises;

            while (auxP) {
                printf("    %s\n", auxP->nome);
                auxP = auxP->proximo;
            }
            auxL = auxL->proximo; puts("");
        }

        printf("\n────────────────────────────────────────────────────────────\n");
        puts(""); puts("Escolha uma ordenação ou outra teclas para sair");
        scanf(" %c", &resp); getchar();
        switch (resp) {
            case 'b':
                ordenar(bubbleSort, crescente);
                goto refresh;
            case 'B':
                ordenar(bubbleSort, decrescente);
                goto refresh;
            case 'i':
                ordenar(insertionSort, crescente);
                goto refresh;
            case 'I':
                ordenar(insertionSort, decrescente);
                goto refresh;
            refresh:
                telaExibir();
                exibir();
                break;
            default:
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
}

/********************* FUNCAO REMOVER *******************/

void remover(Letra *letra, Pais *pais) {
    Pais *auxP;

    // Tratar os ponteiros
    if (pais == letra->paises) letra->paises = pais->proximo;
    else {
        Pais *auxP = letra->paises;
        while (auxP->proximo != pais) auxP = auxP->proximo;

        auxP->proximo = pais->proximo;
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

    Pais *auxP = buscarNoDicionario(nome);

    if (auxP) {
        escrever(&auxP->descricao, descricao);
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
    Letra *auxL = preLetraLista.proximo;
    Pais *auxP;

    FILE *f = fopen("dicionario.txt", "w");
    if (!f) { printf("Erro ao salvar"); return; }

    while (auxL) {
        auxP = auxL->paises;

        while (auxP && fprintf(
            f,
            "%s|%s\n",
            auxP->nome,
            auxP->descricao) != EOF
        ) {
            auxP = auxP->proximo;
        }

        auxL = auxL->proximo;
    }

    fclose(f);
}

typedef void (*CallbackMensagem)(char *);

void disparar_aviso_no_rodape(char *msg) {
    gotoXY(1, 20); printf("[Notificacao]: %s \033[33m[%s]\033[0m\n", msg, nome);
}

void gerenciar_edicao(CallbackMensagem on_erro) {
    int dado_existe = 0;

    if (!dado_existe) {
        on_erro(descricao);
    }

    on_erro = NULL;
}

/****************** FUNCAO PRINCIPAL ******************/

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int opcao, cont_tela = 1;

    preLetraLista.proximo = NULL;
    carregar();
    cont_tela++;
    CallbackMensagem delegate = NULL;

    do {
        if (cont_tela > 1) {
            telaCabecalho();
            if (delegate) gerenciar_edicao(disparar_aviso_no_rodape);
            delegate = NULL;
            telaMenu();
        }
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                salvar();
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
                    strcpy(descricao, "🟢 Removido com sucesso");
                    delegate = disparar_aviso_no_rodape;
                } else {
                    strcpy(descricao, "🔴 Não há registro de");
                    delegate = disparar_aviso_no_rodape;
                }
                break;
            case 4:
                Pais * selecionado = telaEditar();
                if (selecionado) {
                    editar(selecionado);
                    strcpy(descricao, "🟢 Editado com sucesso");
                    delegate = disparar_aviso_no_rodape;
                } else {
                    strcpy(descricao, "🔴 Inválido");
                    delegate = disparar_aviso_no_rodape;
                }
                break;
            default:
                gotoXY(15, 18);
                printf("Opção Inválida");
                system("pause");
        }

    } while (opcao != 0);

    return 0;
}
