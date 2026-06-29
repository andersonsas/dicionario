/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void gotoXY(int, int);

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
int opcao;
char resp;
int linha, col;

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

void removerNodo(Pais **noPais) {
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

void telaInserir() {
    system("cls");
    printf("──────────────────── ADICIONAR PAÍS ────────────────────");
    gotoXY(1, 2);
    printf("*  Nome do País:                                                 *");
    gotoXY(1, 3);
    printf("*  Campo 1:                                                      *");
    gotoXY(1, 4);
    printf("*  Campo 3:                                                      *");

    printf("\n────────────────────────────────────────────────────────");
}

void telaRemover() {
    system("cls");
    puts("************************** REMOVER PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");
}

void telaEditar() {
    system("cls");
    puts("************************** EDITAR PAÍS ****************************");
    gotoXY(1, 2);
    puts("*  PAÍS:                                                           *");
    gotoXY(1, 3);
    puts("********************************************************************");
}

/* void carregar() {
    FILE *f = fopen("Alunos.txt", "r");
    if (!f) { cout << "Erro ao carregar!"; return; }

    inicio.pProximo = NULL;
    pAux = &inicio;

    while (true) {
        Aluno *novo = new Aluno;

        int lidos = fscanf(
            f,
            "%d|%49[^|]|%f|%f|%f\n",
            &novo->matricula,
            novo->nome,
            &novo->notas[0],
            &novo->notas[1],
            &novo->notas[2]
        );

        if (lidos != 5) {
            delete novo; break;
        }

        novo->pProximo = NULL;
        novo->pAnterior = pAux;
        pAux->pProximo = novo;
        pAux = novo;
    }

    fclose(f);
} */

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
    char buffer[63] = {};

    do {
        telaInserir();

        gotoXY(20, 2);
        scanf(" %63[^\n]", buffer); limparBuffer();
        char *name = strdup(buffer); if (!name) return;

        char letraGrupo = toupper(name[0]);

        if (!existeLetra(letraGrupo)) {
            letraAux->proximo = calloc(1, sizeof(Letra));
            if (!letraAux->proximo) { free(name); return; }

            letraAux->proximo->anterior = letraAux;
            letraAux->proximo->l = letraGrupo;

            letraAux = letraAux->proximo;
        }

        paisAux = letraAux->paises;

        // Verifica se já existe o país
        int duplicato = 0;
        while (paisAux) {
            if (stricmp(paisAux->nome, name) == 0) { // Compara com a entrada do usuário
                duplicato = 1;
                break; // Encontrou, então interrompe
            }
            ultimoPaisLocal = paisAux;
            paisAux = paisAux->proximo; // Atualiza o auxiliar
        }

        if (duplicato) {
            free(name);
            gotoXY(1, 6);
            printf("País já registrado");
        } else {
            Pais *novo = calloc(1, sizeof(Pais));
            if (!novo) {
                gotoXY(1, 6);
                printf("Falha: país não alocado");
                free(name);
                return;
            }
            novo->nome = name;

            gotoXY(20, 3);
            scanf(" %63[^\n]", buffer); limparBuffer();
            novo->descricao = strdup(buffer); if (!novo->descricao) return;

            if (letraAux->paises) { // Se há países na lista
                ultimoPaisLocal->proximo = novo; // vincula o "novo" ao "próximo do último"
            } else {
                ultimoPaisLocal = letraAux->paises = novo;
            }
            letraAux->total++;
        }

        gotoXY(1, 7); puts("\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->");
        scanf(" %c", &resp); limparBuffer();
        resp = toupper(resp);
    } while (resp == 'S');
    //salvar();
}

/********************* FUNCAO REMOVER *******************/

void remover() {
    char minhaBusca[64], letraGrupo;

    do {
        telaRemover();

        gotoXY(15, 2);
        lerTexto(minhaBusca);
        letraGrupo = toupper(minhaBusca[0]);

        // 1. Verifica se a letra existe
        if (existeLetra(letraGrupo)) {

            // 2. Verifica se o país existe dentro da letra (isso já configura paisAux e paisAnterior)
            if (existePais(minhaBusca)) {

                gotoXY(1, 6);
                printf("ATENCAO: Remover %s? Sim[S] Nao[outra tecla]----> ", paisAux->nome);
                scanf(" %c", &resp); limparBuffer();
                resp = toupper(resp);

                if (resp == 'S') {
                    // Desvincula o país da lista simplesmente encadeada
                    if (paisAnterior == NULL) {
                        letraAux->paises = paisAux->proximo; // Era o primeiro da lista
                    } else {
                        paisAnterior->proximo = paisAux->proximo; // Estava no meio ou fim
                    }

                    // Libera a memória alocada dinamicamente pelo strdup e calloc
                    free(paisAux->nome);
                    free(paisAux->descricao);
                    free(paisAux);
                    paisAux = NULL;

                    letraAux->total--; // Diminui a contagem de países na letra

                    // Se a letra não tem mais países, removemos o nó da letra (Lista Duplamente Encadeada)
                    if (letraAux->total == 0) {
                        letraAux->anterior->proximo = letraAux->proximo;
                        if (letraAux->proximo) {
                            letraAux->proximo->anterior = letraAux->anterior;
                        }
                        free(letraAux);
                        letraAux = NULL;
                    }

                    gotoXY(1, 7);
                    printf("País removido com sucesso!\n");
                } else {
                    gotoXY(1, 7);
                    printf("Remoção cancelada.\n");
                }
            } else {
                gotoXY(1, 7);
                printf("País não encontrado sob a letra [%c].\n", letraGrupo);
            }
        } else {
            gotoXY(1, 7);
            printf("Letra [%c] não possui registros.\n", letraGrupo);
        }

        gotoXY(1, 10);
        printf("Continuar removendo dados? Sim[S] Nao[outra tecla]----> ");
        scanf(" %c", &resp); limparBuffer();
        resp = toupper(resp);

    } while (resp == 'S');
    //salvar();
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
            removerNodo(&paisAux);

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

    int cont_tela = 1;

    listaLetra.proximo = NULL; /* lista vazia */
    //carregar();
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
                inserir();
                break;
            case 3:
                remover();
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
