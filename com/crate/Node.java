package com.crate;

import java.util.ArrayList;
import java.util.List;

public class Node {
    NodeTypes type;
    List<Token> tok = new ArrayList<>();
    List<Node> tlist = new ArrayList<>();

    Node () {

    }

    Node (NodeTypes typ, Token t) {
        type = typ;
        tok.add(t);
    }

    Node (NodeTypes typ, Node n) {
        type = typ;
        for (int token = 0; token < n.tok.size(); token ++) {
            tok.add(n.tok.get(token));
        }
        tlist.add(n);
    }

    Node (NodeTypes typ, Node n, Token t) {
        type = typ;
        for (int token = 0; token < n.tok.size(); token ++) {
            tok.add(n.tok.get(token));
        }
        tok.add(t);
        tlist.add(n);
    }
}
