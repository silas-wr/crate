package com.crate;

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String args[]) {
    	List<String> keys = new ArrayList<>();
    	keys.add("compile");
   	keys.add("build");
   	keys.add("run");
   	keys.add("arc");
   	keys.add("project");
   	keys.add("module");
   	keys.add("init");
   	keys.add("reset");
   	keys.add("refresh");
   	keys.add("commit");
   	keys.add("install");
   	keys.add("register");
   	keys.add("remove");
    	
        if (args.length == 0) {
            System.out.println("USAGE: crate COMMAND [options] ARGUMENT(S)");  
        } else if (keys.indexOf(args[0]) == 0) {
            if (args.length == 1) {
                System.out.println("USAGE: crate compile [options] FILE(S)");
            } else {
                String argument;
                System.out.println("W: Cannot compile file(s) due to unfinished program");
                for (int arg = 1; arg < args.length; arg ++) {
                    argument = args[arg];
                    try {
                        FileInputStream fi = new FileInputStream(args[arg]);
                       	Program tree = Parse.parse(new Lex().lex(fi));
                        Parse.treep(tree);
                        Compile.compile(tree);
                    } catch (IOException exc) {
                        System.out.println("Error opening file.");
                        System.out.println("Possible reasons: mistyped name, moved or deleted file, insufficient permission");
                    }
                }
            }
        } else if (keys.indexOf(args[0]) == 1) {
            if (args.length == 1) {
                System.out.println("USAGE: crate build [options] FILE(S)");
            } else {
                String argument;
                System.out.println("W: Cannot build file(s) due to unfinished program");
                for (int arg = 1; arg < args.length; arg ++) {
                    argument = args[arg];                    
                    try {
                        FileInputStream fi = new FileInputStream(args[arg]);
                       	Program tree = Parse.parse(new Lex().lex(fi));
                        Parse.treep(tree);
                        Compile.compile(tree);
                        Interpret.interpret();
                    } catch (IOException exc) {
                        System.out.println("Error opening file.");
                        System.out.println("Possible reasons: mistyped name, moved or deleted file, insufficient permission");
                    }
                }
            }
        } else if (keys.indexOf(args[0]) == 2) {
            if (args.length == 1) {
                System.out.println("USAGE: crate run [options] FILE(S)");
            } else {
                System.out.println("W: Cannot run file(s) due to unfinished program");
                String argument;
                for (int arg = 1; arg < args.length; arg ++) {
                    argument = args[arg];
                    try {
                        Interpret.interpret();
                    } catch (Exception exc) {
                        System.out.println("Error opening file.");
                        System.out.println("Possible reasons: mistyped name, moved or deleted file, insufficient permission");
                    }
                }
            }
        } else if (keys.indexOf(args[0]) == 3) {
            if (args.length == 1) {
                System.out.println("USAGE: crate arc [options] MAIN-CLASS");
            } else {
                String argument;
                for (int arg = 1; arg < args.length; arg ++) {
                                        
                }
                System.out.println("W: No arc created due to unfinished program");
            }
        } else if (keys.indexOf(args[0]) == 4) {
            if (args.length == 1) {
                System.out.println("USAGE: crate project COMMAND [options] NAME");
            } else if (args.length == 2) {
            	if (keys.indexOf(args[1]) < 6 || keys.indexOf(args[1]) > 9) {
            	    System.out.println(new String("Unknown command " + args[1] + " on crate project."));
            	} else {
            	    System.out.println(new String("USAGE: crate project " + args[1] + " [options] NAME"));
            	}
            } else if (args.length > 2) {
                System.out.println("W: No project initialized/modified due to unfinished program");
                String argument;
                for (int arg = 1; arg < args.length; arg ++) {
                                        
                }                
            }
        } else if (keys.indexOf(args[0]) == 5) {
            if (args.length == 1) {
                System.out.println("USAGE: crate module [options] NAME");
            } else if (args.length == 2) {
            	if (keys.indexOf(args[1]) < 10) {
            	    System.out.println(new String("Unknown command " + args[1] + " on crate module."));
            	} else {
            	    System.out.println(new String("USAGE: crate module " + args[1] + " [options] NAME"));
            	}
            } else if (args.length > 2) {
                System.out.println("W: No module installed/registered/removed due to unfinished program");
                String argument;
                for (int arg = 1; arg < args.length; arg ++) {
                                        
                }                
            }
        } else {        
            System.out.println(new String("Unexpected argument " + args[0]));
        }
    }
}
