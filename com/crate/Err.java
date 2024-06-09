package com.crate;

public class Err {
    public static void err(int row, int col, String msg) {
        System.out.println(String.format("[%d, %d]: %s", row, col, msg));
        System.exit(1);
    }
}
