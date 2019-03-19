//
// Created by hunter on 19-3-19.
//
#include <jni.h>
#include <btc_oracle_core/btc_oracle_core.hpp>

#define package_name "btc_oracle_core_wrapper"

#ifdef __cplusplus
extern "C" {
#endif

jobject NewTransactionObject(JNIEnv *env, transaction_ptr transaction) {

    auto pTransaction = new transaction_ptr();
    *pTransaction = transaction;

    jclass cls = env->FindClass(package_name "$Transaction");

    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");

    jobject obj = env->NewObject(cls, constructor);

    jfieldID handleId = env->GetFieldID(cls, "handle", "J");

    env->SetLongField(obj, handleId, (jlong) pTransaction);

    return obj;
}
/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Transaction
 * Method:    create
 * Signature: (IILjava/util/Vector;Ljava/util/Vector;)Lcom/example/javawallet/btc_oracle_core_wrapper/Transaction;
 */
JNIEXPORT jobject JNICALL
Java_com_example_javawallet_btc_1oracle_1core_1wrapper_00024Transaction_create
        (JNIEnv *env, jclass caller, jint version, jint lockTime, jobject inputs, jobject outputs) {



}

#ifdef __cplusplus
}
#endif