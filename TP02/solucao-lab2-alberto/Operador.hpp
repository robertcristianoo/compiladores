#ifndef _OPERADOR_HPP_
#define _OPERADOR_HPP_
#include "Valor.hpp" 
#include "Exp.hpp"
#include "Arvore.hpp"

class Exp;
class Valor_t;

class OperadorBin {
public:
  virtual Valor_t opera_valor(Valor_t esq, Valor_t dir) = 0;
  Valor_t opera(Exp *esq, Exp  *dir);
  static OperadorBin * gera_operador_bin(int regra);
};

class Menor : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class MenorIgual : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Maior : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class MaiorIgual : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class Igual : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Diferente : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Xor : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class Soma : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Subtrai : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class Or : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};
 
class And : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class Multiplica : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Divide : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class DivideInteiro : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Mod : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};


class Shl : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};

class Shr : public OperadorBin {
  Valor_t opera_valor(Valor_t esq, Valor_t dir);
};




class OperadorUnario {
public:
  virtual Valor_t opera_valor(Valor_t v) = 0;
  Valor_t opera(Exp * un);
  static OperadorUnario * gera_operador_unario(int regra);
};

class MenosUnario : public OperadorUnario {
public:
  Valor_t opera_valor(Valor_t v);
};

class MaisUnario : public OperadorUnario {
public:
  Valor_t opera_valor(Valor_t v);
};

class Not : public OperadorUnario {
public:
  Valor_t opera_valor(Valor_t v);
};

#endif
