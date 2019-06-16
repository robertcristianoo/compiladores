#ifndef _EXP_HPP_
#define _EXP_HPP_
#include "Operador.hpp"
#include "Valor.hpp"

class Valor_t;

class Exp {
public:
  virtual Valor_t calcula() = 0;
};

class OperadorBin;
class ExpDoisOp : public Exp {
public:
  OperadorBin *op;
  Exp *esq;
  Exp *dir;
  ExpDoisOp(OperadorBin *op,  Exp *esq,  Exp *dir);
  Valor_t calcula();
};

class OperadorUnario;
class ExpUmOp : public Exp {
public:
  OperadorUnario *op;
  Exp *unico;
  ExpUmOp(OperadorUnario *op, Exp *unico);
  Valor_t calcula();
};

class ExpNum : public Exp {
public:
  int i;
  ExpNum(int ii);
  Valor_t calcula();  
};

class ExpNumFloat : public Exp {
public:
  double d;
  ExpNumFloat(double dd);
  Valor_t calcula();  
};

class ExpID : public Exp {
public:
  string id;
  ExpID(string iid);
  Valor_t calcula();  
};

class ExpString : public Exp {
public:
  string s;
  ExpString(string ss);
  Valor_t calcula();  
};

#endif
