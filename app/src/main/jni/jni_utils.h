//
// Created by hunter on 19-3-15.
//

#ifndef JAVAWALLET_JNI_UTILS_H
#define JAVAWALLET_JNI_UTILS_H

#include <jni.h>
#include <vector>
#include <string>

template<typename T>
std::vector<T> convertArray(JNIEnv *env, jobject jList) {
    //
    std::vector<T> sVector;

    // retrieve the java.util.List interface class
    jclass cList = env->FindClass("java/util/List");

    // retrieve the size and the get method
    jmethodID mSize = env->GetMethodID(cList, "size", "()I");
    jmethodID mGet = env->GetMethodID(cList, "get", "(I)Ljava/lang/Object;");

    if (mSize == NULL || mGet == NULL)
        return sVector;

    // get the size of the list
    jint size = env->CallIntMethod(jList, mSize);


    // walk through and fill the vector
    for (jint i = 0; i < size; i++) {

        jobject obj = env->CallObjectMethod(jList, mGet, i);
        T t;

        if constexpr (std::is_same<T, std::string>::value) {
            jstring str = (jstring) obj;

            const char *chr = env->GetStringUTFChars(str, nullptr);
            t = chr;

            env->ReleaseStringUTFChars(str, chr);
        } else if constexpr (std::is_integral<T>::value) {

            jclass integerClass = env->FindClass("java/lang/Integer");
            jmethodID intValueMid = env->GetMethodID(integerClass, "intValue", "()I");

            t = env->CallIntMethodA(obj, intValueMid, nullptr);
        };

        sVector.push_back(t);

    }

    return sVector;
}

std::vector<int> convertJintArray(JNIEnv *env, jintArray array);

jobject  newObject(JNIEnv *env, std::string className, std::string method, ...);


#endif //JAVAWALLET_JNI_UTILS_H
