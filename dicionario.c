/*
   Implementando um dicionário utilizando listas simplesmente e duplamente encadeadas.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

/****************** VARIAVEIS GLOBAIS ******************/

COORD CursorPosition;

int opcao;
char resp;
int linha, col, matTemp;

typedef struct country {
    char *nome;
    struct country *proximo; /* Ponteiro para o proximo aluno */
} Country;

typedef struct letra {
    char l;
    Country *country;
    struct letra *letraPosterior;
    struct letra *letraAnterior;
} Letra;

Country listaCountry, *countryAux;
Letra listaLetra, *letraAux;

void gotoXY(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed
}

/****************** FUNCAO CABECALHO ******************/

void cabecalho() {
    system("cls");
    gotoXY(3, 5);
    //cout << "PROGRAMA PARA GERENCIAR A MATRICULA, O NOME E AS NOTAS";
    gotoXY(3, 7);
    //cout << "DE UM ALUNO USANDO UMA LISTA DUPLAMENTE ENCADEADA\n";
}

/****************** FUNCAO MENU ******************/

void interfaceMenu() {
    col = 10;
    gotoXY(col, 2);
    puts("──────────────── MENU ────────────────");
    gotoXY(col, 3);
    //puts("*      Exibir.............[1]       *");
    gotoXY(col, 4);
    puts("*      Inserir............[2]       *");
    gotoXY(col, 5);
    //cout << "*      Remover............[3]       *";
    gotoXY(col, 6);
    //cout << "*      Inserir em Ordem...[4]       *";
    gotoXY(col, 7);
    //cout << "*      Sair...............[0]       *";
    gotoXY(col, 8);
    //cout << "*      Digite a opcao:              *";
    gotoXY(col, 9);
    //cout << "*************************************";
    gotoXY(42, 16);
    scanf("%d", &opcao);
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

/* void exibir() {
    if (inicio.pProximo != NULL) {
        pAux = inicio.pProximo; // aponta para o inicio da lista
        system("cls");
        gotoXY(1, 5);
        //cout << "********************************  DIARIO *********************************";
        gotoXY(1, 7);
        //cout << "Professor: " << professor;
        gotoXY(1, 8);
        //cout << "Disciplina: " << disciplina;
        gotoXY(1, 9);
        //cout << "Turma: " << turma;
        linha = 12;
        //cout << "\n---------------------------------------------------------------------------";
        gotoXY(1, linha);
        //cout << "Matricula";
        gotoXY(15, linha);
        //cout << "Nome";
        gotoXY(50, linha);
        //cout << "Nota1";
        gotoXY(60, linha);
        //cout << "Nota2";
        gotoXY(70, linha);
        //cout << "Media";
        linha = 14;
        //cout << "\n---------------------------------------------------------------------------";
        while (pAux) {
            gotoXY(1, linha);
            //cout << pAux->matricula;
            gotoXY(15, linha);
            //cout << pAux->nome;
            gotoXY(50, linha);
            //cout << pAux->notas[0];
            gotoXY(60, linha);
            //cout << pAux->notas[1];
            gotoXY(70, linha);
            //cout << pAux->notas[2];
            pAux = pAux->pProximo;
            linha++;
        }
        //cout << "\n---------------------------------------------------------------------------\n";
        system("pause");
    } else {
        gotoXY(15, 18);
        //cout << "ATENCAO: Alunos inexistentes! ";
        system("pause");
    }
} */

void desenhar_inserir_pais() {
    system("cls");
    printf("************************* ADICIONAR PAÍS *************************");
    gotoXY(1, 2);
    printf("*  Nome do País:                                                       *");
    gotoXY(1, 3);
    printf("*  Campo 1:                                                   *");
    gotoXY(1, 4);
    printf("*  Campo 3:                                                           *");

    printf("\n*********************************************************************");
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
    int existe = 1;
    Country *antes = NULL;

    do {
        desenhar_inserir_pais();
        letraAux = &listaLetra;
        gotoXY(20, 2);
        scanf(" %s", buffer); name = strdup(buffer);
        while (letraAux->letraPosterior && (existe = letraAux->letraPosterior->l != name[0])) {
            letraAux = letraAux->letraPosterior;
        }

        if (existe) {
            letraAux->letraPosterior = malloc(sizeof(Letra));
            if (!letraAux->letraPosterior) return;
            letraAux->letraPosterior->country = NULL;
            letraAux->letraPosterior->letraPosterior = NULL;

            letraAux->letraPosterior->letraAnterior = letraAux;
            letraAux->letraPosterior->l = name[0];
        }

        letraAux = letraAux->letraPosterior;

        // letraAux->country : Inicio da lista simples
        // countryAux: Iterador

        countryAux = letraAux->country;

        while (countryAux && strcmp(countryAux->nome, name) != 0) {
            antes = countryAux;
            countryAux = countryAux->proximo;
        }

        // Alocacao e insercao de dados
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



/****************** FUNCAO PRINCIPAL ******************/

int main() {
    setlocale(LC_ALL, ".65001");
    int cont_tela = 1;

    listaLetra.letraPosterior = NULL; /* lista vazia */
    //carregar();

    //cabecalho();
    //diario();
    cont_tela++;

    do {
        if (cont_tela > 1) {
            //cabecalho();
            interfaceMenu();
        }
        switch (opcao) {
            case 0:
                break;
            case 1:
                //exibir();
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
