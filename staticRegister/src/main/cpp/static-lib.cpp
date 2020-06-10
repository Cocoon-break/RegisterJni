#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_staticregister_StaticRegister_stringFromJNI(
        JNIEnv *env,
        jclass jclazz) {
    std::string hello = "Hello from static jni C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_staticregister_StaticRegister_addTwoSum(JNIEnv *env, jclass clazz, jint x,
                                                         jint y) {
    return x + y;
}