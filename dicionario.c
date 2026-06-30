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

/****************** FUNCAO CABECALHO ******************/

void telaCabecalho() {
    system("cls");
    gotoXY(3, 5);
    printf("DICIONARIO DE PAISES");
    gotoXY(3, 7);
    printf("USANDO UMA LISTA SIMPLES E DUPLAMENTE ENCADEADA\n");
}

/****************** FUNCAO MENU ******************/

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
    //cout << "*      Sair...............[0]       *";
    gotoXY(col, 16);
    //cout << "*      Digite a opcao:              *";
    gotoXY(col, 17);
    //cout << "*************************************";
    gotoXY(42, 22);
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

void telaEditar() {
    system("cls");
    puts("************************** EDITAR PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");
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
        letraAux = listaLetra.proximo; // aponta para o inicio da lista
        system("cls");
        gotoXY(1, 1);
        printf("────────────────────  EXIBIR ────────────────────");
        gotoXY(1, 2); printf("PAÍS");
        printf("\n────────────────────────────────────────────────────────────\n");

        linha = 5;
        while (letraAux) {
            printf("[%c] - (%d)\n", letraAux->l, letraAux->total);
            paisAux = letraAux->paises;
            while (paisAux) {
                printf("    %s\n", paisAux->nome);
                paisAux = paisAux->proximo;
            }
            letraAux = letraAux->proximo;
            puts("");
        }
        printf("\n────────────────────────────────────────────────────────────\n");
        puts(""); system("pause");
    } else {
        gotoXY(15, 18);
        puts("NÃO HÁ PAISES REGISTRADO");
        system("pause");
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
    char letraGrupo = toupper(nome[0]);

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
    char textoNome[64], textoNovoNome[62], textoNovaDescricao[64];
    telaEditar();

    gotoXY(15, 2);
    lerTexto(textoNome);

    if (buscarNoDicionario(textoNome)) {
        // O país existe para editar
        lerTexto(textoNovoNome);

        // Verifica a existência do nome
        if (stricmp(textoNome, textoNovoNome) == 0) {
            // O novo nome é o mesmo, só mude a descrição.
            lerTexto(textoNovaDescricao);
            escrever(&paisAux->descricao, textoNovaDescricao);

        } else {
            // O novo nome não é o mesmo
            // Remove o nó antigo
            if (paisAnterior) paisAnterior->proximo = paisAux->proximo;
            else letraAux->paises = paisAux->proximo;

            letraAux->total--;
            freePais(&paisAux);

            if (letraAux->total == 0) {
                letraAux->anterior->proximo = letraAux->proximo;
                if (letraAux->proximo) letraAux->proximo->anterior = letraAux->anterior;
                free(letraAux);
                letraAux = NULL;
            }

            // Atualiza os auxiliares
            buscarNoDicionario(textoNovoNome);

            // Verifica a existência da letra do novo nome
            if (existeLetra(toupper(textoNovoNome[0]))) {
                // A letra do novo nome existe
                // Cria um nó de pais
                paisAux->proximo = calloc(1, sizeof(Pais));
                if (!paisAux->proximo) return;

                escrever(&paisAux->proximo->nome, textoNovoNome);
                lerTexto(textoNovaDescricao);
                escrever(&paisAux->proximo->descricao, textoNovaDescricao);
                letraAux->total++;

            } else {
                // A letra do novo nome não existe
                // Cria-se um novo nó de letra

                // Nova alocação, letraAux já é o último
                letraAux->proximo = calloc(1, sizeof(Letra));
                if (!letraAux->proximo) return;

                // Rearranjando os ponteiros
                letraAux->proximo->anterior = letraAux;

                // Preenchendo a letra do nó
                letraAux->proximo->l = toupper(textoNovoNome[0]);

                // Cria-se um novo nó de país
                letraAux->proximo->paises = calloc(1, sizeof(Pais));
                paisAux = letraAux->proximo->paises;

                // Inserindo os dados no nó
                escrever(&paisAux->nome, textoNovoNome);
                lerTexto(textoNovaDescricao);
                escrever(&paisAux->descricao, textoNovaDescricao);
                letraAux->proximo->total++;
            }
        }
    } else {
        gotoXY(15, 5); puts("NÃO HÁ PAISES REGISTRADO"); system("pause");
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
                break;
            case 1:
                exibir();
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
                editar();
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
