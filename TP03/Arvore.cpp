#include "Arvore.hpp"
#include<iostream>
#include<string>
using namespace std;

No_arv_parse::No_arv_parse() {
  simb = "";
  regra = -1; //terminal
  dado_extra = "";
  filhos.clear();
}

Arvore::Arvore(No_arv_parse * rr) {
  raiz = rr;
}

Exp* expressao_de_terminal(No_arv_parse * no, vector< pair< pair<string,int>, Valor_t> > &var) {
	int index = -1; //não definido
	Valor_t v;
	
	if (no->simb == string("NUM")) {
		return new ExpNum(stoi(no->dado_extra));
	} if (no->simb == string("FLOAT_NUM")) {
		return new ExpNumFloat(stod(no->dado_extra));
	} if (no->simb == string("ID")) {
		for (int i = 0; i < var.size(); ++i) { //procura por todos os ID já identificados
			//se o atual já tiver sido declarado, pega o index dele
			if (var[i].first.first == no->dado_extra) {
				index = i;
			}
		}
		if (index != -1) {
			return new ExpID(no->dado_extra, var[index].second);
		}
		
		return new ExpID(no->dado_extra, v);
	} if (no->simb == string("STRING")) {
		return new ExpString(no->dado_extra);
	}
  
	return NULL;
}

void Arvore::simplificaFun(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var){	
	int index = -1; //não definido
	
	switch(nodo->regra) {
		case 47: //X -> Y M
		case 49: //Y -> Y M ;
			simplificaFun(nodo->filhos[0], var);
			simplificaExp(nodo->filhos[1]->filhos[0], var);
			
			for (int i = 0; i < var.size(); ++i) { //procura por todos os ID já identificados
				//se o atual já tiver sido declarado, pega o index dele
				if (var[i].first.first == nodo->filhos[1]->filhos[0]->dado_extra) {
					index = i;
				}
			}
			
			//se verdadeiro, significa q o ID atual não foi declarado no escopo, portanto apresenta erro.
			if (index == -1) {
				cerr << "Error: Identifier not found '" << nodo->filhos[1]->filhos[0]->dado_extra << "'" 
					<< endl;
			} else { 
				Exp *exp;
				exp = simplificaExp(nodo->filhos[1]->filhos[2], var);
				var[index].second = exp->calcula();
			}
			
			break;
			
		case 48: //X -> M
		case 50: //Y -> M ;
			simplificaExp(nodo->filhos[0]->filhos[0], var);
			
			for (int i = 0; i < var.size(); ++i) {
				if (var[i].first.first == nodo->filhos[0]->filhos[0]->dado_extra) {
					index = i;
				}
			}
			
			if (index == -1) {
				cerr << "Error: Identifier not found '" << nodo->filhos[1]->filhos[0]->dado_extra << "'" 
					<< endl;
			} else {
				Exp *exp;
				exp = simplificaExp(nodo->filhos[0]->filhos[2], var);
				var[index].second = exp->calcula();
			}
			
			break;
	}
}

void Arvore::simplificaIL(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var, int enumType) {
	pair< pair<string,int>, Valor_t> atual;
	
	switch(nodo->regra) {
		case 39: //IL -> ID , IL
			simplificaIL(nodo->filhos[2], var, enumType);
		case 40: //IL -> ID
			atual.first.first = nodo->filhos[0]->dado_extra; //pega o nome da variavel
			atual.first.second = enumType; //atualiza o tipo
			
			var.push_back(atual); //insere no vetor de variáveis
			break;
	}
}

void Arvore::simplificaVar(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var) {
	int enumType;
	
	switch(nodo->regra) {
		case 36: //K -> P ; K 
		case 44: //L -> P ; L
			simplificaVar(nodo->filhos[2], var);
			break;
		case 37: //K -> P ;
		case 45: //L -> P
			switch(nodo->filhos[0]->filhos[2]->regra) {
				case 41: //int
				  enumType = 2; //T -> Longint
				  break;
				case 42: //bool
				  enumType = 1; //T -> Boolean
				  break;
				case 43: //float
				  enumType = 3; //T -> Double
				  break;
			}
			
			simplificaIL(nodo->filhos[0]->filhos[0], var, enumType);
			break;
	}
}

/** Reaproveita nos e nao desaloca.*/
Exp* Arvore::simplificaExp(No_arv_parse * no, vector< pair< pair<string,int>, Valor_t> > &var) {
  switch(no->regra) {
  case -1: return expressao_de_terminal(no, var); //terminal
  case 1: case 10: case 16: case 28: case 29: case 30: case 31:
    return simplificaExp(no->filhos[0], var); // regra X -> Y e equivalentes
    break;
  case 24: return simplificaExp(no->filhos[1], var); // C -> ( E )
  case 2: case 9: case 15:
    return new ExpDoisOp(OperadorBin::gera_operador_bin(no->filhos[1]->regra), simplificaExp(no->filhos[0], var), simplificaExp(no->filhos[2], var));
  case 25: case 26: case 27: 
    return new ExpUmOp(OperadorUnario::gera_operador_unario(no->regra), simplificaExp(no->filhos[1], var));
  default:
    return NULL;
  }
}

void Arvore::inicia(vector< pair< pair<string,int>, Valor_t> > &var) {
	// cout<<"Inicia gramatica S' -> S $"<<endl;
	
	pair< pair<string,int>, Valor_t> atual;
	
	atual.first.first = raiz->filhos[0]->filhos[1]->dado_extra; //salva o ID
	
	switch(raiz->filhos[0]->filhos[6]->regra) { //regra 33-FUN -> function ID ( L ) : T ;
		case 41: //int
		  atual.first.second = 2; //T -> Longint
		  break;
		case 42: //bool
		  atual.first.second = 1; //T -> Boolean
		  break;
		case 43: //float
		  atual.first.second = 3; //T -> Double
		  break;
	}
	
	var.push_back(atual); //insere no vetor de variáveis
	
	simplificaVar(raiz->filhos[0]->filhos[3], var); //passando a lista de param para ser simplificada
	
	// cout<<"Simplificou Var"<<endl;
	
	if (raiz->filhos[1]->regra != 35) {
		simplificaVar(raiz->filhos[1]->filhos[1], var);
		// cout<<"Simplificou Var"<<endl;
	}
	
	simplificaFun(raiz->filhos[2]->filhos[1], var);
	// cout<<"Simplificou Fun"<<endl;
	// cout<<"acabou"<<endl;
}

void Arvore::imprime(No_arv_parse * no) {
  cerr << "[" <<no->simb<<","<< no->regra << ","<<no->dado_extra << ":";
  for (int i = 0; i < no->filhos.size(); ++i) {
    imprime(no->filhos[i]);
  }
  cerr << "]";
}

void Arvore::debug(){
  imprime(raiz);
  cerr << endl;
}