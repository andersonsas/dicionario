/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>

void gotoXY(int, int);

/****************** ESTRUTURAS ******************/

typedef struct country {
    char *nome;
    struct country *proximo;
} Country;

typedef struct letra {
    char l;
    int total;
    Country *country;
    struct letra *proximo;
    struct letra *anterior;
} Letra;

/****************** VARIAVEIS ******************/
int opcao;
char resp;
int linha, col, matTemp;

//COORD CursorPosition;
Country listaCountry, *countryAux;
Letra listaLetra = {}, *letraAux;

/****************** FUNCAO CABECALHO ******************/

void cabecalho() {
    system("cls");
    gotoXY(3, 5);
    printf("DICIONARIO DE PAISES");
    gotoXY(3, 7);
    printf("USANDO UMA LISTA SIMPLES E DUPLAMENTE ENCADEADA\n");
}

/****************** FUNCAO MENU ******************/

void interfaceMenu() {
    col = 10;
    gotoXY(col, 10);
    puts("──────────────── MENU ────────────────");
    gotoXY(col, 11);
    puts("*      Exibir.............[1]       *");
    gotoXY(col, 12);
    puts("*      Inserir............[2]       *");
    gotoXY(col, 13);
    //cout << "*      Remover............[3]       *";
    gotoXY(col, 14);
    //cout << "*      Inserir em Ordem...[4]       *";
    gotoXY(col, 15);
    //cout << "*      Sair...............[0]       *";
    gotoXY(col, 16);
    //cout << "*      Digite a opcao:              *";
    gotoXY(col, 17);
    //cout << "*************************************";
    gotoXY(42, 22);
}

/******************** FUNCAO DIARIO *******************/

/* void diario() {
    gotoXY(3, 9);
    cout << "PREENCHER OS DADOS DO CABECALHO DO DIARIO";
    gotoXY(3, 11);
    cout << "Professor: ";
    fgets(professor, 99, stdin);
    gotoXY(3, 13);
    cout << "Disciplina: ";
    fgets(disciplina, 99, stdin);
    gotoXY(3, 15);
    cout << "Turma: ";
    fgets(turma, 99, stdin);
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
            countryAux = letraAux->country; // countryAux aponta para o inicio da lista
            while (countryAux) {
                gotoXY(1, linha);
                printf("%s", countryAux->nome);
                countryAux = countryAux->proximo;
                linha++;
            }

            letraAux = letraAux->proximo;
            linha++;
        }
        printf("\n────────────────────────────────────────────────────────────\n");
        puts(""); system("pause");
    } else {
        gotoXY(15, 18);
        printf("NÃO HÁ PAISES REGISTRADO");
        system("pause");
    }
}

void desenhar_inserir_pais() {
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

/* void desenhar_remover_aluno() {
    system("cls");
    cout << "************************** REMOVER ALUNO ****************************";
    gotoXY(1, 2);
    cout << "*  Matricula:                                                       *";
    gotoXY(1, 3);
    cout << "*********************************************************************";
} */

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

/********************* FUNCAO INSERIR *******************/

void inserir() {
    char buffer[32] = {}, *name;
    int podeAlocar = 1;
    Country *antes = NULL;

    do {
        desenhar_inserir_pais();
        letraAux = &listaLetra;
        gotoXY(20, 2);
        scanf(" %s", buffer); name = strdup(buffer);
        while (letraAux->proximo && (podeAlocar = letraAux->proximo->l != name[0])) {
            letraAux = letraAux->proximo;
        }

        if (podeAlocar) {
            letraAux->proximo = malloc(sizeof(Letra));
            if (!letraAux->proximo) return;
            letraAux->proximo->country = NULL;
            letraAux->proximo->proximo = NULL;

            letraAux->proximo->anterior = letraAux;
            letraAux->proximo->l = name[0];
            letraAux->proximo->total = 0;
        }

        letraAux = letraAux->proximo;

        // letraAux->country : Inicio da lista simples

        countryAux = letraAux->country;

        while (countryAux && strcmp(countryAux->nome, name) != 0) {
            antes = countryAux;
            countryAux = countryAux->proximo;
        }

        // Alocação e inserção de dados
        Country *novo = malloc(sizeof(Country));
        if (!novo) { printf("Falha: alloc country"); return; }
        //strcpy(novo->nome, nationName);
        novo->nome = name;
        novo->proximo = NULL;

        if (letraAux->country) {
            antes->proximo = novo;
        } else {
            // Se não há país na lista, o início da lista de países aponta para novo
            letraAux->country = novo;
        }
        letraAux->total++;

        //gotoXY(20, 3); cin.getline(pAux->nome, 50); //fgets(pAux->nome, 99, stdin);

        gotoXY(1, 7); puts("\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->");
        scanf(" %c", &resp);
        resp = toupper(resp);
    } while (resp == 'S');
    //salvar();
}

/********************* FUNCAO REMOVER *******************/

/* void remover() {
    do {
        desenhar_remover_aluno();
        resp = '0';

        gotoXY(15, 2);
        //cin >> matTemp;
        pAux = &inicio;
        while (pAux->matricula != matTemp && pAux->pProximo != NULL) {
            //pAux->pAnterior = pAux;
            pAux = pAux->pProximo;
        }
        if (pAux->matricula == matTemp) {
            gotoXY(3, 5);
            //  cout << "ATENCAO: Remover " << pAux->nome << "? Sim[S] Nao[outra tecla]---->";
              //cin >> resp;
            resp = toupper(resp);
            if (resp == 'S') {
                pAux->pAnterior->pProximo = pAux->pProximo;

                if (pAux->pProximo != NULL)
                    pAux->pProximo->pAnterior = pAux->pAnterior;

                pAux->pProximo = NULL;
                pAux->pAnterior = NULL;
                //  delete pAux;
            }
        } else {
            //gotoXY(20, 2); cout << "Matricula inexistente ";
            system("pause");
            //pAux->pAnterior = NULL;
            //pAux = NULL;
        }
        gotoXY(3, 6);
        //cout << "Continuar removendo dados? Sim[S] Nao[outra tecla]---->";
        //cin >> resp;
        resp = toupper(resp);
    } while (resp == 'S');
    salvar();
} */

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
    setlocale(LC_ALL, ".65001");
    int cont_tela = 1;

    listaLetra.proximo = NULL; /* lista vazia */
    //carregar();
    //cabecalho();
    //diario();
    cont_tela++;

    do {
        if (cont_tela > 1) {
            cabecalho();
            interfaceMenu();
        }
        scanf("%d", &opcao);
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
                //remover();
                break;
            case 4:
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
