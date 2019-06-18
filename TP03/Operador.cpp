#include "Operador.hpp"
#include "Exp.hpp"
#include "Valor.hpp"
#include<iostream>

/*OperadorBin*/
OperadorBin * OperadorBin::gera_operador_bin(int regra){
  switch(regra) {
  case 3: return new Menor();
  case 4: return new MenorIgual();
  case 5: return new Maior();
  case 6: return new MaiorIgual();
  case 7: return new Igual();
  case 8: return new Diferente();
  case 11: return new Soma();
  case 12: return new Subtrai();
  case 13: return new Or();
  case 14: return new Xor();
  case 17: return new Multiplica();
  case 18: return new Divide();
  case 19: return new DivideInteiro();
  case 20: return new Mod();
  case 21: return new And();
  case 22: return new Shl();
  case 23: return new Shr();
  default:
    std::cerr << "Nao existe correspondencia para esse operador na gramatica" << endl;
    return NULL;
  }
}

Valor_t OperadorBin::opera(Exp *esq, Exp  *dir) {
  return this->opera_valor(esq->calcula(),dir->calcula());
}

bool checa_operandos_bin_num(Valor_t esq, Valor_t dir){
  if ((esq.tipo == ::indefinido) ||
      (dir.tipo == ::indefinido) ||
      (esq.tipo == ::booleano) ||
      (dir.tipo == ::booleano)) {
    return false;
  }
  return true;
}

bool checa_operandos_bin_num_ou_bool(Valor_t esq, Valor_t dir) {
  if ((esq.tipo == ::indefinido) || (dir.tipo == ::indefinido) ||
      ((esq.tipo == ::booleano) && (dir.tipo != ::booleano)) ||
      ((dir.tipo == ::booleano) && (esq.tipo != ::booleano))) {
    return false;
  }
  return true;
}

Valor_t Menor::opera_valor(Valor_t esq, Valor_t dir) {
   if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i < dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de < dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t MenorIgual::opera_valor(Valor_t esq, Valor_t dir) {
   if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i <= dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de <= dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t Maior::opera_valor(Valor_t esq, Valor_t dir) {
   if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i > dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de > dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t MaiorIgual::opera_valor(Valor_t esq, Valor_t dir) {
   if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i >= dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de >= dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

bool checa_operandos_igualaveis(Valor_t esq, Valor_t dir) {
  if (((esq.tipo == ::booleano) && (dir.tipo != ::booleano)) || 
      ((esq.tipo != ::booleano) && (dir.tipo == ::booleano))) {
    return false;
  }
  return true;
}

Valor_t Igual::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_igualaveis(esq,dir)) return Valor_t::Valor_indefinido();
  if (esq.tipo == ::booleano) {
    return Valor_t::Valor_booleano(esq.b == dir.b);
  }
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i == dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de == dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t Diferente::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_igualaveis(esq,dir)) return Valor_t::Valor_indefinido();
  if (esq.tipo == ::booleano) {
    return Valor_t::Valor_booleano(esq.b != dir.b);
  }
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_booleano(esq.i != dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_booleano(de != dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t And::opera_valor(Valor_t esq, Valor_t dir) {
  if (esq.tipo != dir.tipo) return Valor_t::Valor_indefinido();
  if (esq.tipo == ::booleano) {
    return Valor_t::Valor_booleano(esq.b && dir.b);
  }
  if(esq.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i & dir.i);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t Or::opera_valor(Valor_t esq, Valor_t dir) {
  if (esq.tipo != dir.tipo) return Valor_t::Valor_indefinido();
  if (esq.tipo == ::booleano) {
    return Valor_t::Valor_booleano(esq.b || dir.b);
  }
  if(esq.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i | dir.i);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t Xor::opera_valor(Valor_t esq, Valor_t dir) {
  if (esq.tipo != dir.tipo) return Valor_t::Valor_indefinido();
  if (esq.tipo == ::booleano) {
    return Valor_t::Valor_booleano(esq.b != dir.b);
  }
  if(esq.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i ^ dir.i);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}

Valor_t Soma::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i + dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_flutuante(de + dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t Subtrai::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i - dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_flutuante(de - dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t Multiplica::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i * dir.i);
  } else {
    double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
    double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
    return Valor_t::Valor_flutuante(de * dd);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t Divide::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  double de =  (esq.tipo == ::inteiro ? esq.i : esq.d);
  double dd =  (dir.tipo == ::inteiro ? dir.i : dir.d);
  return Valor_t::Valor_flutuante(de / dd);
}


Valor_t DivideInteiro::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i / dir.i);
  }
  return Valor_t::Valor_indefinido();
}


Valor_t Mod::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i % dir.i);
  }
  return Valor_t::Valor_indefinido(); 
}


Valor_t Shl::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i << dir.i);
  }
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}


Valor_t Shr::opera_valor(Valor_t esq, Valor_t dir) {
  if (!checa_operandos_bin_num(esq,dir)) return Valor_t::Valor_indefinido();
  if(esq.tipo == ::inteiro && dir.tipo == ::inteiro){
    return Valor_t::Valor_inteiro(esq.i >> dir.i);
  } 
  return Valor_t::Valor_indefinido(); // nao deveria acontecer.
}







/*OperadorUnario*/
OperadorUnario * OperadorUnario::gera_operador_unario(int regra){
  switch(regra) {
  case 25: return new MenosUnario();
  case 26: return new MaisUnario();
  case 27: return new Not();
  default:
    std::cerr << "Nao existe correspondencia para esse operador na gramatica" << endl;
    return NULL;
  }
}

Valor_t OperadorUnario::opera(Exp * un) {
  return this->opera_valor(un->calcula());
}

Valor_t MenosUnario::opera_valor(Valor_t v) {
  switch(v.tipo) {
  case (::indefinido):
  case (::booleano):
    return Valor_t::Valor_indefinido();
  case (::inteiro):
    return Valor_t::Valor_inteiro(-v.i);
  case (::flutuante):
    return Valor_t::Valor_flutuante(-v.d);
  }
}


Valor_t MaisUnario::opera_valor(Valor_t v) {
  return v;
}

Valor_t Not::opera_valor(Valor_t v) {
  if  (v.tipo == ::booleano)
    return Valor_t::Valor_booleano(! v.b);
  return Valor_t::Valor_indefinido();
}
