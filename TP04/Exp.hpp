#ifndef _EXP_HPP_
#define _EXP_HPP_
#include "Operador.hpp"

# include <vector>

using namespace std;

class Exp {
protected:
	int caso = -1; //possibilidade de azulejamento
	int sum = -1; //soma do custo
public:
  virtual int calcula(vector < pair <int, Exp *> > instrucoes) = 0;
  virtual int sum_azulejamento(Exp * nodo_atual, vector < pair <int, Exp *> > instrucoes) = 0;
  virtual bool existe_azulejo(Exp * nodo_atual) = 0;
};

class OperadorBin;
class ExpDoisOp : public Exp {
public:
  OperadorBin *op;
  Exp *esq;
  Exp *dir;
  ExpDoisOp(int c, OperadorBin *op,  Exp *esq,  Exp *dir);
  int calcula(vector < pair <int, Exp *> > instrucoes);
  int sum_azulejamento(Exp * nodo_atual, vector < pair <int, Exp *> > instrucoes);
  bool existe_azulejo(Exp * nodo_atual);
};

class OperadorUnario;
class ExpUmOp : public Exp {
public:
  OperadorUnario *op;
  Exp *unico;
  ExpUmOp(int c, OperadorUnario *op, Exp *unico);
  int calcula(vector < pair <int, Exp *> > instrucoes);
  int sum_azulejamento(Exp * nodo_atual, vector < pair <int, Exp *> > instrucoes);
  bool existe_azulejo(Exp * nodo_atual);
};

class ExpNum : public Exp {
public:
  int i;
  ExpNum(int ii);
  int calcula(vector < pair <int, Exp *> > instrucoes);
  int sum_azulejamento(Exp * nodo_atual, vector < pair <int, Exp *> > instrucoes);
  bool existe_azulejo(Exp * nodo_atual);
};

// ===================SOMENTE NUM============================== //
// class ExpNumFloat : public Exp {
// public:
  // double d;
  // ExpNumFloat(double dd);
  // Valor_t calcula();  
// };

// class ExpID : public Exp {
// public:
  // string id;
  // ExpID(string iid);
  // Valor_t calcula();  
// };

// class ExpString : public Exp {
// public:
  // string s;
  // ExpString(string ss);
  // Valor_t calcula();  
// };

#endif
