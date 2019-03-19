//
// Created by hunter on 19-3-15.
//

#include "jni_utils.h"

using namespace std;

vector<int> convertJintArray(JNIEnv *env, jintArray jarr)
{
    vector<int> ints;

    jint *arr = env->GetIntArrayElements(jarr, NULL);

    int size = env->GetArrayLength(jarr);

    for (int i = 0; i < size; i++)
              ints.push_back( arr[i] );

    env->ReleaseIntArrayElements(jarr, arr, 0);

    return ints;
}

jobject  newObject(JNIEnv *env, std::string className, std::string method, ...)
{
    //jclass cls = env->FindClass(className.c_str());

    //jmethodID constructor = env->GetMethodID(cls, "<init>", "(L" package_name ";II)V");

    //jobject point = env->NewObject(cls, constructor, caller, 5, 6);

    return 0;
}