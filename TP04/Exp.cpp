#include "Exp.hpp"
#include "Operador.hpp"
# include <limits.h>

class OperadorBin;
class OperadorUnario;

// ===================================== ExpDoisOp begin =====================================
ExpDoisOp::ExpDoisOp(int c, OperadorBin *opp,  Exp *ee,  Exp *dd) : op(opp), esq(ee), dir(dd) {
	caso = c;
}

int ExpDoisOp::calcula(vector<pair<int, Exp *> > instrucoes) {
  int lower = -1; //menor azulejo encontrado
  int greater = INT_MAX; //infinito só para comparação
  
  if (this->sum != -1) { //se já foi calculado
	  return this->sum;
  }
  
  lower = esq->calcula(instrucoes) + dir->calcula(instrucoes) + 10;
  
  for (int i = 0; i < instrucoes.size(); ++i) { // para cada instrução
	if (this->existe_azulejo(instrucoes[i].second)) { //verifica se o nó atual é azulejado
	  greater = instrucoes[i].first + this->sum_azulejamento(instrucoes[i].second, instrucoes); //calcula o sum
	} 
	/*
	se não tiver entrado no if anterior, nunca vai acontecer. Portanto, a instrução atual 
	não azuleja essa árvore
	*/
	if (greater < lower){ 
	  lower = greater;
	}
  }
  
  this->sum = lower;
  
  return this->sum;
}

int ExpDoisOp::sum_azulejamento(Exp * nodo_atual, vector<pair<int, Exp *> > instrucoes) { 
  if (ExpDoisOp* az_2 = dynamic_cast<ExpDoisOp*>(nodo_atual)) { //se for 2 op, soma os dois filhos
    return esq->sum_azulejamento(az_2->esq, instrucoes) + dir->sum_azulejamento(az_2->dir, instrucoes);
  } else if (ExpNum* az_num = dynamic_cast<ExpNum*>(nodo_atual)) { //se for const, soma o sum
	return calcula(instrucoes);
  }
  return 0;
}

bool ExpDoisOp::existe_azulejo(Exp * nodo_atual) { //cod alberto
  if (ExpDoisOp* az_2 = dynamic_cast<ExpDoisOp*>(nodo_atual)){
    return ((caso == az_2->caso)
            && esq->existe_azulejo(az_2->esq)
                && (dir->existe_azulejo(az_2->dir)));
  } else if (ExpNum* az_num = dynamic_cast<ExpNum*>(nodo_atual)) {
    return true;
  }
  return false;
}

// ===================================== ExpDoisOp end =====================================


// ===================================== ExpUmOp begin =====================================
ExpUmOp::ExpUmOp(int c, OperadorUnario *opp, Exp *u):op(opp), unico(u) {
	caso = c;
}

int ExpUmOp::calcula(vector<pair<int, Exp *> > instrucoes) {
  int lower = -1; //menor azulejo encontrado
  int greater = INT_MAX; //infinito só para comparação
  
  if (this->sum != -1) { //se já foi calculado
	  return this->sum;
  }
  
  lower = this->unico->calcula(instrucoes) + 10;
  
  for (int i = 0; i < instrucoes.size(); ++i) { // para cada instrução
	if (this->existe_azulejo(instrucoes[i].second)) { //verifica se o nó atual é azulejado
	  greater = instrucoes[i].first + this->sum_azulejamento(instrucoes[i].second, instrucoes); //calcula o sum
	} 
	/*
	se não tiver entrado no if anterior, nunca vai acontecer. Portanto, a instrução atual 
	não azuleja essa árvore
	*/
	if (greater < lower){ 
	  lower = greater;
	}
  }
  
  this->sum = lower;
  
  return this->sum;
}

int ExpUmOp::sum_azulejamento(Exp * nodo_atual, vector<pair<int, Exp *> > instrucoes) {
  if (ExpUmOp* az_1 = dynamic_cast<ExpUmOp*>(nodo_atual)){
    return unico->sum_azulejamento(az_1->unico, instrucoes); //retorna soma acumulada
  } else if (ExpNum* az_num = dynamic_cast<ExpNum*>(nodo_atual)) {
    return calcula(instrucoes); //soma o sum
  }
  return 0;
}

bool ExpUmOp::existe_azulejo(Exp * nodo_atual) {
  if (ExpUmOp* az_1 = dynamic_cast<ExpUmOp*>(nodo_atual)){
    return ((caso == az_1->caso)
            && unico->existe_azulejo(az_1->unico));
  } else if (ExpNum* az_num = dynamic_cast<ExpNum*>(nodo_atual)) {
    return true;
  }
  return false;
}

// ===================================== ExpDoisOp end =====================================

// ===================================== ExpNum begin =====================================
ExpNum::ExpNum(int ii) : i(ii){}

int ExpNum::calcula(vector<pair<int, Exp *> > instrucoes) { //caso trivial
  sum = 0;
  
  return 0;
}

int ExpNum::sum_azulejamento(Exp * nodo_atual, vector<pair<int, Exp *> > instrucoes) {
  return 0;  
}

bool ExpNum::existe_azulejo(Exp * nodo_atual) {
  if (ExpNum* az_num = dynamic_cast<ExpNum*>(nodo_atual)){
    return true;
  } 
  return false;
}

// ===================================== ExpNum end =====================================

// ===================SOMENTE NUM============================== //
// ExpNumFloat::ExpNumFloat(double dd) : d(dd){}
// Valor_t ExpNumFloat::calcula() {
  // return Valor_t::Valor_flutuante(this->d);
// }

// ExpID::ExpID(string ss) : id(ss){}
// Valor_t ExpID::calcula() {
  // return Valor_t::Valor_indefinido();
// }

// ExpString::ExpString(string ss) : s(ss){}
// Valor_t ExpString::calcula() {
  // return Valor_t::Valor_indefinido();
// }