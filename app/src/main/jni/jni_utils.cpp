//
// Created by hunter on 19-3-15.
//
#include <iostream>
#include "jni_utils.h"

using namespace std;
namespace utils {
    //
    std::string jstringToString(JNIEnv *env, jstring str) {
        string t;

        const char *chr = env->GetStringUTFChars(str, nullptr);
        t = chr;

        env->ReleaseStringUTFChars(str, chr);

        return t;
    }

    vector<int> convertJintArray(JNIEnv *env, jintArray jarr) {
        vector<int> ints;

        jint *arr = env->GetIntArrayElements(jarr, NULL);

        int size = env->GetArrayLength(jarr);

        for (int i = 0; i < size; i++)
            ints.push_back(arr[i]);

        env->ReleaseIntArrayElements(jarr, arr, 0);

        return ints;
    }

    jobject newObject(JNIEnv *env, std::string className, std::string method, ...) {
        //jclass cls = env->FindClass(className.c_str());

        //jmethodID constructor = env->GetMethodID(cls, "<init>", "(L" package_name ";II)V");

        //jobject point = env->NewObject(cls, constructor, caller, 5, 6);

        return 0;
    }

    const std::string CLS_JNIEXCEPTION = "cn/wisenergy/pi/workflow/JNIException";

    void ThrowJNIException(JNIEnv *env, const std::string &errorMsg) {

        jclass e_cls = env->FindClass(CLS_JNIEXCEPTION.c_str());
        if (e_cls == NULL) {
            std::cerr << "find class:" << CLS_JNIEXCEPTION << " error!" << std::endl;
            return;
        }

        int r = env->ThrowNew(e_cls, errorMsg.c_str());
    }

    void testException(JNIEnv *env) {
        try {
            //doSomeThing //this line throws some exception.
        } catch (std::exception &e) {
            std::string exceptionClass = "java/lang/NullPointerException";
            ThrowJNIException(env, e.what());

            //recommend return, otherwise the following code will continue to be run
            return;
        }
    }
}

