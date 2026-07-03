/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

void gotoXY(int, int);
void inserir(void);

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
int opcao, linha, col;
char resp, nome[64] = {}, descricao[64] = {};

//COORD CursorPosition;
Pais *paisAux, *paisAnterior, *ultimoPaisLocal;
Letra listaLetra = {}, *letraAux;

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

int existePais(const char *nome) {
    if (!letraAux) return 0; // Se não há letra selecionada, não existe país

    paisAux = letraAux->paises;
    paisAnterior = NULL;

    while (paisAux) {
        if (stricmp(paisAux->nome, nome) == 0) {
            return 1; // País encontrado
        }
        paisAnterior = paisAux; // Guarda o país anterior
        paisAux = paisAux->proximo; // Entrada no país
    }
    paisAux = paisAnterior; // Entra no último país
    return 0; // País não encontrado
}

int existeLetra(const char busca) {
    letraAux = &listaLetra;
    while (letraAux->proximo && letraAux->proximo->l != busca) {
        letraAux = letraAux->proximo;
    }

    if (letraAux->proximo) {
        letraAux = letraAux->proximo; // Entra no nó da letra
        return 1;
    } else {
        return 0; // Entra na última letra
    }
}

int buscarNoDicionario(const char *busca) {
    if (existeLetra(toupper(busca[0]))) {
        return existePais(busca);
    } else {
        existePais(busca);
        return 0;
    }
}

typedef int (*Ordem)(void);
int crescente(void) {
    return letraAux->l > letraAux->proximo->l;
}

int descrecente(void) {
    return letraAux->l < letraAux->proximo->l;
}

void bubbleSort(Ordem ordem) {
    int swap;

    Letra *letraFutura, *letraPassada, *letra1, *letra2;

    while (1) {
        swap = 0;
        letraAux = listaLetra.proximo;

        while (letraAux->proximo) {
            letraPassada = letraAux->anterior;
            letra1 = letraAux;
            letra2 = letraAux->proximo;
            letraFutura = letraAux->proximo->proximo;

            if (ordem()) {
                if (letraFutura) letraFutura->anterior = letra1;
                letra1->anterior = letra2;
                letra2->anterior = letraPassada;

                letraPassada->proximo = letra2;
                letra2->proximo = letra1;
                letra1->proximo = letraFutura;

                swap = 1;
            }
            /* if (letraAux->l > letraAux->proximo->l) {

                if (letraAux->proximo->proximo) { letraAux->proximo->proximo->anterior = letraAux; }
                letraAux->proximo->anterior = letraAux->anterior;

                letraAux->anterior->proximo = letraAux->proximo;
                letraAux->anterior = letraAux->proximo;

                letraAux->proximo = letraAux->proximo->proximo;
                letraAux->anterior->proximo = letraAux;

                swap = 1;
            } */
            else {
                letraAux = letraAux->proximo;
            }
        }
        if (swap == 0) {
            break;
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
    if (listaLetra.proximo) {
        system("cls"); gotoXY(1, 1);
        printf("────────────────────────  EXIBIR ────────────────────────"); gotoXY(1, 2);
        printf("[B] ORDENAR: CRESCENTE\n"); printf("LETRA - TOTAIS/PAÍSES");
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

int telaInserir() {
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

    return !buscarNoDicionario(nome);
}

int telaRemover() {
    system("cls");
    puts("************************** REMOVER PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");

    gotoXY(20, 2); scanf(" %63[^\n]", nome); limparBuffer();

    return buscarNoDicionario(nome);
}

int telaEditar() {
    system("cls");
    puts("************************** EDITAR PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");

    gotoXY(20, 2); scanf(" %63[^\n]", nome); limparBuffer();

    return buscarNoDicionario(nome);
}

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

        buscarNoDicionario(nome);
        inserir();
    }

    fclose(f);
}

/* void salvar() {
    FILE *f = fopen("Alunos.txt", "w");
    if (!f) { cout << "Erro ao salvar"; return; }

    pAux = &inicio;
    pAux = pAux->pProximo;

    while (pAux && fprintf(
        f,
        "%d|%s|%.2f|%.2f|%.2f\n",
        pAux->matricula, pAux->nome,
        pAux->notas[0],
        pAux->notas[1],
        pAux->notas[2]) != EOF
    ) {
        pAux = pAux->pProximo;
    }

    fclose(f);
} */

/********************* FUNCAO EXIBIR *******************/

void exibir() {
    if (listaLetra.proximo != NULL) {
        letraAux = listaLetra.proximo;

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
        puts(""); puts("Pressione C (crescente) ou D (descrescente) para ordenar ou qualquer outra tecla para sair");
        scanf(" %c", &resp); getchar();
        switch (resp) {
            case 'C':
            case 'c':
                bubbleSort(crescente);
                goto refresh;
            case 'D':
            case 'd':
                bubbleSort(descrecente);
                goto refresh;
            refresh:
                telaExibir();
                exibir();
                break;
            default:
                Ordenar(bubbleSort, crescente);
                break;
        }
    }
}

/********************* FUNCAO INSERIR *******************/

void inserir() {
    char letraGrupo = toupper(nome[0]);

    if (existeLetra(letraGrupo)) {
        paisAux->proximo = calloc(1, sizeof(Pais)); if (!paisAux->proximo) return;
        paisAux = paisAux->proximo;

        escrever(&paisAux->nome, nome);
        escrever(&paisAux->descricao, descricao);
        letraAux->total++;

    } else {
        letraAux->proximo = calloc(1, sizeof(Letra)); if (!letraAux->proximo) return;
        letraAux->proximo->paises = calloc(1, sizeof(Pais)); if (!letraAux->proximo->paises) return;

        letraAux->proximo->anterior = letraAux;

        letraAux->proximo->l = letraGrupo;
        letraAux->proximo->total++;
        escrever(&letraAux->proximo->paises->nome, nome);
        escrever(&letraAux->proximo->paises->descricao, descricao);
    }
}

/********************* FUNCAO REMOVER *******************/

void remover() {
    // Tratar os ponteiros
    if (paisAnterior == NULL) letraAux->paises = paisAux->proximo;
    else paisAnterior->proximo = paisAux->proximo;

    // Libera memória
    freePais(&paisAux);
    letraAux->total--;

    // Verifica se letra é vazia
    if (letraAux->total == 0) {
        letraAux->anterior->proximo = letraAux->proximo;
        if (letraAux->proximo) {
            letraAux->proximo->anterior = letraAux->anterior;
        }
        free(letraAux);
        letraAux = NULL;
    }
}

void editar() {
    Pais *paisTemp = paisAux;

    lerTexto(nome);
    lerTexto(descricao);

    if (buscarNoDicionario(nome)) {
        escrever(&paisAux->descricao, descricao);
    } else {
        inserir();
        buscarNoDicionario(paisTemp->nome);
        remover();
    }
}

/********************* FUNCAO INSERIR EM ORDEM *******************/

/*
void inserirOrdem() {
    Aluno *pMenor, *pMaior;

    do {
        desenhar_cadastrar_aluno();
        pMaior = &inicio; // aponta para o inicio da lista
        pMenor = pMaior;
        pAux = new Aluno;

        gotoXY(20, 2); cin >> pAux->matricula; getchar();
        gotoXY(20, 3); fgets(pAux->nome, 99, stdin);
        gotoXY(20, 4); cin >> pAux->notas[0];
        gotoXY(20, 5); cin >> pAux->notas[1];
        pAux->notas[2] = (pAux->notas[0] + pAux->notas[1]) / 2;
        pAux->pProximo = NULL;

        if (pMaior->pProximo == NULL) {
            pMaior->pProximo = pAux;
            pAux->pProximo = NULL;
        } else {
            pMaior = pMaior->pProximo;
            while (pAux->matricula > pMaior->matricula && pMaior->pProximo != NULL) {
                pMenor = pMaior;
                pMaior = pMaior->pProximo;
            }

            if (pAux->matricula > pMaior->matricula && pMaior->pProximo == NULL) {
                pMaior->pProximo = pAux;
                pAux->pAnterior = pMaior;
                pAux->pProximo = NULL;
            } else {
                pMenor->pProximo = pAux;
                pAux->pProximo = pMaior;
                pAux->pAnterior = pMenor;
                pMaior->pAnterior = pAux;
            }
        }
        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    } while (resp == 'S');
    salvar();
} */

void gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
    /* HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition); */
}

/****************** FUNCAO PRINCIPAL ******************/

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".65001");

    int cont_tela = 1;

    listaLetra.proximo = NULL; /* lista vazia */
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
                exit(1);
                break;
            case 1:
                if (telaExibir() == 1) {
                    exibir();
                }
                break;
            case 2:
                if (telaInserir() == 1) {
                    inserir();
                }
                break;
            case 3:
                if (telaRemover() == 1) {
                    remover();
                }
                break;
            case 4:
                if (telaEditar() == 1) {
                    editar();
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
