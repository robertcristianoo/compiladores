# include <bits/stdc++.h>

#define tabelaIn "tabela.txt"

using namespace std;

typedef struct simb {
    char c[7];
} simb;

string **Tabela;
string *Symb;
int columnSize;
int lineSize;

void inicializacao() {
    FILE *arq = fopen(tabelaIn, "r");

    fscanf(arq, "%d %d", &lineSize, &columnSize);

    //Aloca tabela
    Tabela = (string**)malloc(lineSize * sizeof(string*));

    for (int index = 0; index < lineSize; ++index) {
        Tabela[index] = (string*)malloc(columnSize * sizeof(string));
    }

    //aloca vetor simb
    Symb = (string*)malloc(columnSize * sizeof (string));

    for(int i = 0; i < columnSize; ++i) {
        fscanf(arq, "%s ", &Symb[i]);
    }

    for(int i = 0; i < lineSize; ++i) {
        int lixo;
        fscanf(arq, "%d", &lixo);
        for (int j = 0; j < columnSize; ++j) {
            fscanf(arq, "%s ", &Tabela[i][j]);
        }
    }

    fclose(arq);
}

void imprimeTabela(int lineSize, int columnSize) {
    for(int i=0; i<lineSize; i++) {
        printf("%d ", i);
        for(int j=0; j<columnSize; j++) {
            printf("%s ", &Tabela[i][j]);
        }
        printf("\n");
    }
}

void desaloca() {
    //desaloca tudo
    for(int i = 0; i < lineSize; ++i) {
        free(Tabela[i]);
    }

    free(Tabela);
    free(Symb);
}

int findSymb(char *token) {
    for(int i = 0; i < columnSize; ++i) {
        if(Symb[i] == token)
            return i;
    }
    printf("Valor indeterminado\n");
    exit (EXIT_FAILURE);
}

int main () {
//    imprimeTabela(lineSize, columnSize);
    inicializacao();

    char input[1024];

    cin.getline(input, 1024);

    char *token;
    token = strtok(input, " ");
    //    cout<<token<<endl;

    stack<simb> pilha;
    simb aux;
    int variavel,pos,regra,reduziu;
    string acao, rs, regra_char;

    strcpy(aux.c,"0");
    pilha.push(aux);

    while (token != NULL) {
        sscanf(pilha.top().c,"%d",&pos);
        strcpy(aux.c,token);
        pilha.push(aux);

        //printf("%s ",pilha.top());

        variavel = findSymb(token);
        acao = Tabela[pos][variavel];

        if(acao == "acc" ) {
            //calcula o resultado
            return 0;
        } else if(variavel<24) {
            acao = (rs + regra_char);
        } else {
            regra_char = acao;
            rs = 'r';
        }

        if(rs == "s") {
//            aux.c = regra_char;
//            pilha.push(aux);
//
//            //printf("%s ",pilha.top());
//
//            token = strtok(NULL, " ");
        } else {
//            sscanf(regra_char,"%d",&regra);
//            aux = reduz(pilha,regra,Regras);
//            sscanf(aux.c,"%d",&pos);
//            reduziu = find_variavel(pilha.top().c);
//            strcpy(aux.c,Tabela[pos].celula[reduziu]);
//            //printf("%d\n",pos);
//            pilha.push(aux);

        }
        //printf ("%s\n",token);
    }

    return 0;
}
