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

// void Arvore::resultado(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var){	
	// int index = -1; //não definido
	
	// switch(nodo->regra) {
		// case 47: //X -> Y M
		// case 49: //Y -> Y M ;
			// simplificaFun(nodo->filhos[0], var);
			// simplificaExp(nodo->filhos[1]->filhos[0], var);
			
			// Exp *exp;
			// exp = simplificaExp(nodo->filhos[1]->filhos[2], var);
			// var[index].second = exp->calcula();
			
			// break;
		// case 48: //X -> M
		// case 50: //Y -> M ;
			// simplificaExp(nodo->filhos[0]->filhos[0], var);
			
			// Exp *exp;
			// exp = simplificaExp(nodo->filhos[0]->filhos[2], var);
			// var[index].second = exp->calcula();
			
			// break;
	// }
// }

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
				//mensagem erro padrão do pascal
				// cerr<<"Error: Identifier not found '"<<nodo->filhos[1]->filhos[0]->dado_extra<<"'"<<endl;
				throw logic_error(nodo->filhos[1]->filhos[0]->dado_extra); //não tá imprimindo a exception..
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
				// cout<<"passou"<<endl;
			if (index == -1) {
				//mensagem erro padrão do pascal
				// cerr<<"Error: Identifier not found '"<<nodo->filhos[1]->filhos[0]->dado_extra<<"'"<<endl;
				throw logic_error(nodo->filhos[1]->filhos[0]->dado_extra); //não tá imprimindo a exception..
			} else {
				Exp *exp;
				exp = simplificaExp(nodo->filhos[0]->filhos[2], var);
				var[index].second = exp->calcula();
			}
			
			break;
	}
}

int Arvore::simplificaIL(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var, int enumType) {
	pair< pair<string,int>, Valor_t> atual;
	int cnt = 0;
	switch(nodo->regra) {
		case 39: //IL -> ID , IL
			cnt += simplificaIL(nodo->filhos[2], var, enumType);
		case 40: //IL -> ID
			atual.first.first = nodo->filhos[0]->dado_extra; //pega o nome da variavel
			atual.first.second = enumType; //atualiza o tipo
			var.push_back(atual); //insere no vetor de variáveis
			
			cnt++;
			
			break;
	}
	
	return cnt;
}

int Arvore::simplificaListaParam(No_arv_parse * nodo, vector< pair< pair<string,int>, Valor_t> > &var) {
	int enumType;
	int cnt = 0;
	
	switch(nodo->regra) {
		case 36: //K -> P ; K 
		case 44: //L -> P ; L
			cnt += simplificaListaParam(nodo->filhos[2], var);
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
			
			cnt += simplificaIL(nodo->filhos[0]->filhos[0], var, enumType);
			break;
	}
	
	return cnt;
}

int Arvore::inicia(vector< pair< pair<string,int>, Valor_t> > &var) {
	 // cout<<"Iniciando gramatica..."<<endl;
	 // cout<<"regra: "<<raiz->regra<<endl;
	
	pair< pair<string,int>, Valor_t> atual;
	
	atual.first.first = raiz->filhos[0]->filhos[1]->dado_extra; //salva o ID da função
	
	//salva o retorno da função
	switch(raiz->filhos[0]->filhos[6]->regra) { //FUN -> FUNCTION ID ( L ) : T ;
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
	
	int cnt = simplificaListaParam(raiz->filhos[0]->filhos[3], var); //passando a lista de param para ser simplificada
	// cout<<"quantidade de parametros passados: "<<cnt<<endl;
	
	 // cout<<"Simplificou ListaParam"<<endl;
	
	switch(raiz->regra) { //2 possibilidades: (função sem declaração de var) e (função com declaração de var)
		case 32: //S -> FUN BEG
			simplificaFun(raiz->filhos[1]->filhos[1], var);
			break;
		case 33: //S -> FUN V BEG
			simplificaListaParam(raiz->filhos[1]->filhos[1], var);
			// cout<<"Simplificou Var"<<endl;
			simplificaFun(raiz->filhos[2]->filhos[1], var);
			
			break;
	}
	
	// cout<<"Simplificou Fun"<<endl;
	// cout<<"acabou"<<endl;
	
	return cnt;
}

void Arvore::calcula(vector< pair< pair<string,int>, Valor_t> > &var) {
	switch(raiz->regra) { //2 possibilidades: (função sem declaração de var) e (função com declaração de var)
		case 32: //S -> FUN BEG
			simplificaFun(raiz->filhos[1]->filhos[1], var);
			break;
		case 33: //S -> FUN V BEG
			simplificaFun(raiz->filhos[2]->filhos[1], var);
			break;
	}
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