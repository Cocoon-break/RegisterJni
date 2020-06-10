package com.example.dynamicregister;

public class DynamicRegister {
    static {
        System.loadLibrary("dynamic-lib");
    }

    public static native String stringFromJNIZ();

    public static native int addTwoSum(int x, int y);
}
