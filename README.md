### java jni使用

#### 静态注册

这个方式是经常用到的，比较常见。

主要流程是

1. 在Java文件编写native 方法
2. 可以通过javah命令来声明头文件
3. 对第2步生成的头文件进行实现。（也可以不声明头文件）

具体的可以通过staticRegister下查看实现

#### 动态注册

因为静态注册的方式，JNI 方法名字必须遵循规则且名字很长，编写代码起来比较繁琐。

动态注册的方式就书写代码就比价方便了

主要流程：

1. 在Java文件中编写native 方法
2. 在jni文件中实现JNI_OnLoad方法
3. 通过FindClass获取带有native方法的类文件
4. 最后通过RegisterNatives传入Java对象以及JNINativeMethod数组



这里有几个知识需要留意的是

JNINativeMethod结构体的含义

```c++
jni中定义的JNINativeMethod
typedef struct {
    const char* name; //Java方法的名字
    const char* signature; //Java方法的签名信息
    void*       fnPtr; //JNI中对应的方法指针
} JNINativeMethod;
```
这里Java方法的签名信息需要根据官方的映射来书写

基本数据类型的映射关系

| Java Type | Native Type | Description      |
| --------- | ----------- | ---------------- |
| boolean   | jboolean    | unsigned 8 bits  |
| byte      | jbyte       | signed 8 bits    |
| char      | jchar       | unsigned 16 bits |
| short     | jshort      | signed 16 bits   |
| int       | jint        | signed 32 bits   |
| long      | jlong       | signed 64 bits   |
| float     | jfloat      | 32 bits          |
| double    | jdouble     | 64 bits          |
| void      | void        | N/A              |

其他数组引用类型和对象引用类型可以参考[官方文档](https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html)

本工程中的dynamicRegister可以查看相关的实现，里面遇到了一些问题都写在代码注释中了。



如果不确定方法的签名怎么写可以通过

```shell
#将类文件编成字节码文件
javac com/example/dynamicregister/DynamicRegister.java 
#查看签名信息
javap -s com.example.dynamicregister.DynamicRegister
```



使用动态注册遇到的问题

1. 在加载动态的时候报**Failed to register native method**

   因为在签名是String的时候没有加";"导致无法找到方法，具体的查看dynamic-lib.cpp的第29行