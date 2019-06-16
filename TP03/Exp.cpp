#include "Exp.hpp"
#include "Operador.hpp"

class Valor_t;

class OperadorBin;
ExpDoisOp::ExpDoisOp(OperadorBin *opp,  Exp *ee,  Exp *dd) : op(opp), esq(ee), dir(dd) {}
Valor_t ExpDoisOp::calcula() {
  return op->opera(esq,dir);
}

Valor_t ExpUmOp::calcula() {
  return op->opera(unico);
}

class OperadorUnario;
ExpUmOp::ExpUmOp(OperadorUnario *opp, Exp *u):op(opp), unico(u){}

ExpNum::ExpNum(int ii) : i(ii){}
Valor_t ExpNum::calcula() {
  return Valor_t::Valor_inteiro(this->i);
}

ExpNumFloat::ExpNumFloat(double dd) : d(dd){}
Valor_t ExpNumFloat::calcula() {
  return Valor_t::Valor_flutuante(this->d);
}

ExpID::ExpID(string ss) : id(ss){} //consulta tabela de simbolos
Valor_t ExpID::calcula() {
  return Valor_t::Valor_indefinido();
}

ExpString::ExpString(string ss) : s(ss){}
Valor_t ExpString::calcula() {
  return Valor_t::Valor_indefinido();
}
