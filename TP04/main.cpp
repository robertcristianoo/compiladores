#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>   
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Operador.hpp"
#include "Exp.hpp"
#include "Gramatica.hpp"
#include "Valor.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"

int custo_minimo_azulejar(Exp * exp, vector<pair<int, Exp *> > instrucoes) {
  /*debug. Remover*/
  cerr << "exp=" << exp << endl;
  for (int i = 0; i < instrucoes.size(); i++) {
    cerr << "inst("<< instrucoes[i].first << ")=" << instrucoes[i].second << endl;
  }
  /*remover*/

  return -1;
}

string i_esimo_nome(string prefixo, int i) {
  std::ostringstream ss;
  ss << i;
  return string(prefixo + "." + ss.str());
}

int main(int argc, char * argv[]) {
  if (argc != 5 && argc != 2 && argc!=3) {
    cerr << "Parametro unico: K=numero de arquivos descrevendo instrucoes, ou" << endl;
    cerr << "Parametro duplo: 1) prefixo do nome dos arquivos das instrucoes 2) K=numero de arquivos descrevendo instrucoes, ou" << endl;
    cerr << "Parametros: 1) nome do arquivo csv com gramática e 2) nome do arquivo csv com tabela LR1, 3) prefixo do nome dos arquivos das instrucoes 4) numero de arquivos descrevendo instrucoes" << endl;
    cerr << argc << " parametros passados"<< endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1, prefixo_instrucoes;
  int n_instrucoes;
  if (argc == 2 || argc == 3) {
    nome_gramatica = string("gramatica.conf");
    nome_tab_lr1 = string("tabela_lr1.conf");
  }
  if (argc == 2) {
    //cerr << "Valores padrao utilizados: gramatica.conf e tabela_lr1.conf" << endl;
    prefixo_instrucoes = string("inst");
    n_instrucoes = atoi(argv[1]);
  } else  if (argc == 3) {
    prefixo_instrucoes = string(argv[1]);
    n_instrucoes = atoi(argv[2]);    
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
    prefixo_instrucoes = string(argv[3]);
    n_instrucoes = atoi(argv[4]);
  }
  // cout<<"passou-1"<<endl;
  if (n_instrucoes) { //se #instruções não for 0
	  ifstream arq_gramatica(nome_gramatica);
	  ifstream arq_tabela_lr1(nome_tab_lr1);
	  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
		cerr << "Falha ao abrir arquivos: " << 
		  ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
		  ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
		return 1;    
	  }
	  // cout<<"passou-2"<<endl;

	  Parser parser(arq_gramatica, arq_tabela_lr1);
	  //  parser.tabela.debug();
	  Arvore_parse arv = parser.executa_parse(cin);
	  // cout<<"passou-3"<<endl;
	  Exp * exp = arv.simplifica_simbolos();
	  // cout<<"passou-4"<<endl;

	  vector<pair<int, Exp *> > instrucoes;
	  for (int i = 0; i < n_instrucoes; ++i) {
		ifstream arq_instrucao(i_esimo_nome(prefixo_instrucoes, i));
		if (arq_instrucao.fail()) {
		  cerr << "Falha ao abrir instrucao " << i << ":" << i_esimo_nome(prefixo_instrucoes, i) << endl;
		  return 2;
		}
		pair<int, Exp *> inst;
		arq_instrucao >> inst.first;
		Arvore_parse arv_inst = parser.executa_parse(arq_instrucao);
		inst.second = arv_inst.simplifica_simbolos();
		// arv_inst.debug();
		instrucoes.push_back(inst);
	  }
	  
	  cout << "Custo minimo para azulejar = " << exp->calcula(instrucoes) << endl;
  } else {
	  cerr << "Informe ao menos uma instrucao k>=1!!" << endl;
  }
  
  return 0;
}
