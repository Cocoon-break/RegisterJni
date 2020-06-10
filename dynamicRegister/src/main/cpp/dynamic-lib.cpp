#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MEGFACESDK_JNI", __VA_ARGS__)

#define NUM_ARRAY_ELEMENTS(p) ((int) sizeof(p) / sizeof(p[0]))


jstring stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from dynamic jni C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jint JNICALL addTwoSum(JNIEnv *env, jclass thiz, jint x, jint y) {
    return x + y;
}

/** jni中定义的JNINativeMethod
 * typedef struct {
    const char* name; //Java方法的名字
    const char* signature; //Java方法的签名信息
    void*       fnPtr; //JNI中对应的方法指针
} JNINativeMethod;
 */
static JNINativeMethod methods[] = {
        {"addTwoSum",      "(II)I",                (void *) addTwoSum},
        {"stringFromJNIZ", "()Ljava/lang/String;", (void *) stringFromJNI},//注意签名后面的";"如果不加则会出现Failed to register native method

};


jint registerNativeMethods(JNIEnv *env, const char *class_name, JNINativeMethod *methods,
                           int num_methods) {

    jclass clazz = env->FindClass(class_name);
    if (clazz == NULL) {
        LOGD("registerNativeMethods: class'%s' not found", class_name);
        return JNI_FALSE;
    }

    jint result = env->RegisterNatives(clazz, methods, num_methods);
    if (result < 0) {
        LOGD("registerNativeMethods failed(class=%s)", class_name);
        return JNI_FALSE;
    }

    return result;
}

//回调函数
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    LOGD("JNI_OnLoad");

    JNIEnv *env = NULL;
    //获取JNIEnv
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOGD("JNI_OnLoad GetEnv fail");
        return -1;
    }
    assert(env != NULL);
    const char *className = "com/example/dynamicregister/DynamicRegister";
    registerNativeMethods(env, className, methods, NUM_ARRAY_ELEMENTS(methods));
    /*
     * 如果这么写会报JNI_ERR returned from JNI_OnLoad
     *jint result = registerNativeMethods(env, className, methods, NUM_ARRAY_ELEMENTS(methods));
     *if (result == JNI_FALSE) {
     *   return -1;
     *}
     */

    return JNI_VERSION_1_6;
}

