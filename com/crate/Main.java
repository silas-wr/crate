package com.crate;

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String args[]) {
    	    	
        if (args.length == 0) {
            System.out.println("USAGE: crate FILE");  
        } 
        
        try {
            FileInputStream fi = new FileInputStream(args[0]);
            Program tree = Parse.parse(new Lex().lex(fi));
            Parse.treep(tree);
        } catch (IOException exc) {
            System.out.println("Error opening file.");
            System.out.println("Possible reasons: mistyped name, moved or deleted file, insufficient permission");
        }
    }
}
