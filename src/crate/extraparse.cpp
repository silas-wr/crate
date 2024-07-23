#include "crate.hpp"

void nodes(Node n, int tb) {
  cout << string(tb, '\t') << "Node " << n.ntype << ": \n";
  tb++;
  for (int i = 0; i < n.nodes.size(); i++) {
    nodes(n.nodes.at(i), tb);
  }

  for (int j = 0; j < n.tokens.size(); i++) {
    cout << string(tb, '\t') << " Token " << n.tokens.at(j).ttype << ": " << n.tokens.at(j).value << "\n";
  }
  tb--;
}

void prog(Program p) {
  int tab = 0;
  for (int i = 0; i < p.nodes.size(); i++) {
    nodes(p.nodes.at(i), tab);
  }
}
