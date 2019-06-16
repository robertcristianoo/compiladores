#ifndef _VALOR_HPP_
#define _VALOR_HPP_
#include<string>
using namespace std;

enum Tipo {
  indefinido,
  booleano,
  inteiro,
  flutuante
};


class Valor_t {
public:
  Tipo tipo;
  bool b;
  int i;
  double d;
  Valor_t();
  Valor_t(Tipo t, bool bb=false, int ii=0, double dd=0.0);
  static Valor_t Valor_indefinido();
  static Valor_t Valor_booleano(bool bb);
  static Valor_t Valor_inteiro(int ii);
  static Valor_t Valor_flutuante(double dd);
  string to_string();
};

#endif
