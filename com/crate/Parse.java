package com.crate;

import java.util.List;

public class Parse {
    public static Program parse(List<Token> l) {

        Program prog = new Program();
        Node cur_node = new Node();
        String load_type = "";
        Token cur_token;
        boolean completeable = true;
        for (int tok = 0; tok < l.size(); tok ++) {
            cur_token = l.get(tok);
            if (cur_token.type == TokenTypes.ID) {
                completeable = false;
                if (load_type == "") {
                    cur_node = new Node(NodeTypes.BASE_ID, cur_token);
                    load_type = "BaseId";
                } else if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else if (load_type == "StemAssign") {
                    cur_node = new Node(NodeTypes.ROOT_ASSIGN, cur_node, cur_token);
                    load_type = "RootAssign";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected id.");
                }
            } else if (cur_token.type == TokenTypes.CONST) {
                completeable = false;
                if (load_type == "") {
                    cur_node = new Node(NodeTypes.BASE_CONST, cur_token);
                    load_type = "BaseConst";
                } else if (load_type == "StemAssign") {
                    cur_node = new Node(NodeTypes.ROOT_ASSIGN, cur_node, cur_token);
                    load_type = "RootAssign";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected const.");
                }
            } else if (cur_token.type == TokenTypes.TCONST) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected CONST.");
                }
            } else if (cur_token.type == TokenTypes.TSTR) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected STR.");
                }
            } else if (cur_token.type == TokenTypes.TCHR) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected CHAR.");
                }
            } else if (cur_token.type == TokenTypes.TBYT) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected BYTE.");
                }
            } else if (cur_token.type == TokenTypes.TSHR) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected SHORT.");
                }
            } else if (cur_token.type == TokenTypes.TINT) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected INT.");
                }
            } else if (cur_token.type == TokenTypes.TFLT) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected DOUBLE.");
                }
            } else if (cur_token.type == TokenTypes.TLIS) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected LIST.");
                }
            } else if (cur_token.type == TokenTypes.TDIC) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected DICT.");
                }
            } else if (cur_token.type == TokenTypes.TSET) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected SET.");
                }
            } else if (cur_token.type == TokenTypes.TCDC) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected CDICT.");
                }
            } else if (cur_token.type == TokenTypes.TBLN) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected BOOLEAN.");
                }
            } else if (cur_token.type == TokenTypes.NULL) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected NULL.");
                }
            } else if (cur_token.type == TokenTypes.TTYP) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected TYPE.");
                }
            } else if (cur_token.type == TokenTypes.TALL) {
                completeable = false;
                if (load_type == "StemTypify") {
                    cur_node = new Node(NodeTypes.GR_TYPIFY, cur_node, cur_token);
                    load_type = "GRTypify";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected type symbol.");
                }
            } else if (cur_token.type == TokenTypes.IS) {
                completeable = false;
                if (load_type == "BaseId" || load_type == "BaseConst" || load_type == "GRTypify") {
                    cur_node = new Node(NodeTypes.STEM_ASSIGN, cur_node);
                    load_type = "StemAssign";
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected assign symbol.");
                }
            } else if (cur_token.type == TokenTypes.SEMI) {
                completeable = false;
                if (load_type == "GRTypify") {
                    prog.list.add(new Node(NodeTypes.NODE_TYPIFY, cur_node));
                    load_type = "";
                    cur_node = null;
                    completeable = true;
                } else if (load_type == "RootAssign") {
                    prog.list.add(new Node(NodeTypes.NODE_ASSIGN, cur_node));
                    load_type = "";
                    cur_node = null;
                    completeable = true;
                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected semicolon.");
                }
            } else if (cur_token.type == TokenTypes.EOF) {
                if (completeable) {
                    return prog;
                } else {
                    Err.err(-1, -1, "Unexpected eof.");
                }
            } else if (cur_token.type == TokenTypes.EOL) {
                if (completeable) {

                } else {
                    Err.err(cur_token.row, cur_token.col, "Unexpected eol.");
                }
            } else {
                Err.err(cur_token.row, cur_token.col, "Unexpected token.");
            }
        
        }
        Err.err(-1, -1, "No EOF");
        return null;
    }

    public static void treep(Program p) {
        int tabs = 0;
        for (int node = 0; node < p.list.size(); node ++) {
            System.out.println("Node: " + p.list.get(node).type);
            tabs += 1;
            minitree(p.list.get(node), tabs);
            tabs -= 1;
        }
    }

    private static void minitree(Node p, int tabs) {
        if (p.tok.size() != 0) {
            for (int token = 0; token < p.tok.size(); token ++) {
                System.out.println(new String(new char[tabs]).replace("\0", "    ") + "Token: " + p.tok.get(token).type);
            }
        } else {
            System.out.println(new String(new char[tabs]).replace("\0", "    ") + "null");
        }
        if (p.tlist.size() != 0) {
            for (int node = 0; node < p.tlist.size(); node ++) {
                System.out.println(new String(new char[tabs]).replace("\0", "    ") + "Node: " + p.tlist.get(node).type);
                tabs += 1;
                minitree(p.tlist.get(node), tabs);
                tabs -= 1;
            }
        } else {
            System.out.println(new String(new char[tabs]).replace("\0", "    ") + "null");
        }
    }

}
