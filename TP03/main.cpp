# include <algorithm>
# include <vector>
# include <string>
# include <iostream>
# include <fstream>   
# include <sstream>
# include <map>
# include <stack>

using namespace std;

#include "Operador.hpp"
#include "Exp.hpp"
#include "Gramatica.hpp"
#include "Valor.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"

int main(int argc, char * argv[]) {
	if (argc != 3 && argc != 1) {
		cerr << "Os parametros de entrada sao o nome do arquivo da gramatica e nome do arquivo da tabela LR1" << endl;
		
		return 1;
	}

	string nome_gramatica, tabela;

	if (argc == 1) {
		//cerr << "Valores padrao utilizados: gramatica.conf e tabela.conf" << endl;
		nome_gramatica = string("gramatica.conf");
		tabela = string("tabela.csv");
	} else {
		nome_gramatica = string(argv[1]);
		tabela = string(argv[2]);
	}

	ifstream arq_gramatica(nome_gramatica);
	ifstream arq_tabela(tabela);

	if (arq_tabela.fail() || arq_gramatica.fail()) {
		cerr << "Falha ao abrir arquivos: " << ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
			((arq_tabela.fail()) ? tabela : "") << endl;
	  
	return 1;    
	}

	Parser parser(arq_gramatica, arq_tabela);
	// parser.gram.debug(); //ok
	// parser.tabela.debug(); //ok

	vector< pair< pair<string,int>, Valor_t> > var; //vetor de variaveis (ID)

	Arvore arv = parser.executa_parse(cin);
	// arv.debug();
	arv.inicia(var);
	
	cout<<"Retorno da funcao " << var[0].first.first << " eh = "<<var[0].second.to_string()<< endl;

	return 0;
}
