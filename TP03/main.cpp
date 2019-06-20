# include <algorithm>
# include <vector>
# include <string>
# include <iostream>
# include <fstream>   
# include <sstream>
# include <map>
# include <stack>
# include <stdexcept>

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
	//var[0] = function

	int totalParams = 0; //total de parametros q serao passados para a função

	try {
		Arvore arv = parser.executa_parse(cin);
		// arv.debug(); //ok
		totalParams = arv.inicia(var); //chama árvore para a gramática inicial
		
		// for (int i = 1; i < 4; ++i) { //itera por todos os parametros
			// cout<<var[i].first.first<<"="<<var[i].second.to_string()<< endl;
		// }
		
		for (int i = totalParams; i > 0; --i) {
			No_arv_parse *no = new No_arv_parse;
			cout<<"\nDigite o tipo do param "<<totalParams-i+1<<": ";
			cin>>no->simb;
			cout<<"\nDigite o valor do param "<<totalParams-i+1<<": ";
			cin>>no->dado_extra;
			if(no->simb=="STRING"){
				Exp *exp = new ExpString(no->dado_extra);
				var[i].second = exp->calcula();
				continue;
			} else if(no->simb=="DOUBLE"){
				Exp *exp = new ExpNumFloat(stod(no->dado_extra));
				var[i].second = exp->calcula();
				continue;
			} else if(no->simb=="LONGINT") {
				Exp *exp = new ExpNum(stoi(no->dado_extra));
				var[i].second = exp->calcula();
				continue;
			} else {
				throw invalid_argument("Invalid type of argument. Expected STRING, DOUBLE or LONGINT");
			}	
		}
		
		// for (int i = var.size()-1; i >= 0; --i) {
			// cout<<var[i].first.first<<"="<<var[i].second.to_string()<< endl;
		// }
		
		arv.calcula(var);
		cout<<"Retorno da funcao " << var[0].first.first << " eh = "<<var[0].second.to_string()<< endl;
	} catch (const invalid_argument &ex) {
		cerr<<"Error during parsing.\n\t"<<ex.what()<<endl;
	} catch (const logic_error &ex) {
		cerr<<"Error: Identifier not found '"<<ex.what()<<"'"<<endl;
	}
	 
	
	// cout<<"Retorno da funcao " << var[0].first.first << " eh = "<<var[0].second.to_string()<< endl;

	return 0;
}
