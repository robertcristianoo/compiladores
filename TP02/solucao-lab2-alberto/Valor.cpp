#include "Valor.hpp" 

Valor_t::  Valor_t() {
    tipo = ::indefinido;
    b = false;
    i = 0;
    d = 0.0;      
  }
Valor_t::  Valor_t(Tipo t, bool bb, int ii, double dd) {
    tipo = t;
    b = bb;
    i = ii;
    d = dd;
}

Valor_t Valor_t::Valor_indefinido() {
  return Valor_t(::indefinido, false, 0, 0.0);
}

Valor_t Valor_t::Valor_booleano(bool bb) {
  return Valor_t(::booleano, bb);
}

Valor_t Valor_t::Valor_inteiro(int ii) {
  return Valor_t(::inteiro, false, ii);
}

Valor_t Valor_t::Valor_flutuante(double dd) {
  return Valor_t(::flutuante, false, 0, dd);
}

string Valor_t::to_string() {
    switch(tipo) {
    case ::indefinido:
      return string("indefinido");
    case ::booleano:
      return (b ? string("true") : string("false"));
    case ::inteiro:
      return std::to_string(i);
    case ::flutuante:
      return std::to_string(d);
    }
    return string("erro");
  }
