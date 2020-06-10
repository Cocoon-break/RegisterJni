package com.example.staticregister;

public class StaticRegister {
    static {
        System.loadLibrary("static-lib");
    }

    public static native String stringFromJNI();

    public static native int addTwoSum(int x, int y);

}
