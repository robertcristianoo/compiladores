#include "Parser.hpp"

Parser::Parser(ifstream &arq_gramatica, ifstream &arq_tabela_lr1) :
  gram(arq_gramatica),
  tabela(arq_tabela_lr1) 
{}

string Parser::to_upper(string str) {
  transform(str.begin(), str.end(),str.begin(), ::toupper);
  return str;
}

Arvore Parser::executa_parse(istream &input) {
  int estado_atual = 0;
  string lookahead;
  string x;
  input >> x;
  lookahead = to_upper(x);
  do {
    //      cerr << "Estado:" << estado_atual << endl;
    Transicao t = tabela.Tab[estado_atual][tabela.simbolo_coluna[lookahead]];
    //      cerr << t.impressao();
    switch(t.tipo) {
    case 0: return Arvore(NULL); break; //erro
    case 1: // terminal
      {
        No_arv_parse * ap_no = new No_arv_parse;
        ap_no->simb = lookahead;
        if ((lookahead == string("ID")) ||
            (lookahead == string("NUM")) ||
            (lookahead == string("FLOAT_NUM")) ||
            (lookahead == string("STRING"))) {
          string dado;
          char linha_mesmo_com_espaco[1001];
          input.getline(linha_mesmo_com_espaco,1000);
          istringstream input_extra(linha_mesmo_com_espaco);
          string extra;
          input_extra >> std::skipws >> extra;
          ap_no->dado_extra = extra;
          //            cerr << "@:" << ap_no->dado_extra<<endl;
        }
        pilha.push(make_pair(ap_no,estado_atual));
        estado_atual = t.prox_estado;
        input >> x;
        lookahead = to_upper(x);
      }
      break;
    case 2: //goto
      cerr << "ERRO goto em lookahead."<<endl;
      return Arvore(NULL);
    case 3: //reducao
      {
        Regra r = gram.R[t.reducao];
        No_arv_parse * ap_no = new No_arv_parse;
        ap_no->simb = r.esq;
        ap_no->regra = t.reducao;
        ap_no->filhos.resize(r.dir.size());
        int estado = -1;
        for(int i = 0; i < r.dir.size(); ++i) {
          ap_no->filhos[r.dir.size() - i - 1] = pilha.top().first;
          estado = pilha.top().second;
          pilha.pop();
        }
        pilha.push(make_pair(ap_no,estado));
        Transicao go_to = tabela.Tab[estado][tabela.simbolo_coluna[r.esq]];
        if (go_to.tipo != 2) {
          cerr << "ausencia de goto apos reducao" << endl;
          return Arvore(NULL);
        }
        estado_atual = go_to.prox_estado;
      }
      break;
    case 4:
      return Arvore(pilha.top().first);
    default: 
      cerr << "Codigo invalido" << endl;
      return Arvore(NULL);
    }
  }while(!input.eof());
  return Arvore(NULL);
}

