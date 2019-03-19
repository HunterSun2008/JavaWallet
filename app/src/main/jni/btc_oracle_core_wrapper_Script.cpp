//
// Created by hunter on 19-3-18.
//
//#include <jni.h>
#include <vector>
#include <string>
#include <btc_oracle_core/btc_oracle_core.hpp>
#include "jni_utils.h"
#include "btc_oracle_core_wrapper_Script.h"

using namespace std;

#define package_name "btc_oracle_core_wrapper"

extern "C"
{
/**
 * new a Java wrapper script from oracle::scirpt_ptr
 * @param script
 * @param env
 * @return
 */
static jobject NewScriptObject( JNIEnv *env, oracle::script_ptr script) {

    auto pScirpt = new oracle::script_ptr();
    *pScirpt = script;

    jclass cls = env->FindClass(package_name "/Script");

    jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");

    jobject obj = env->NewObject(cls, constructor);

    jfieldID handleId = env->GetFieldID(cls, "handle", "J");

    env->SetLongField(obj, handleId, (jlong) pScirpt);

    return obj;
}
/**
 * Get oracle::scirpt_ptr from a Java object
 * @param env
 * @param caller
 * @return
 */
static oracle::script_ptr GetScriptFromObject(JNIEnv *env, jobject obj) {
    //
    jclass cls = env->FindClass(package_name "/Script");

    jfieldID handleId = env->GetFieldID(cls, "handle", "J");

    jlong handle = env->GetLongField(obj, handleId);

    oracle::script_ptr *pScript = reinterpret_cast<oracle::script_ptr *>(handle);

    return *pScript;
}

/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Script
 * Method:    address
 * Signature: (Lcom/example/javawallet/btc_oracle_core_wrapper/network_type;)Ljava/lang/String;
 */

JNIEXPORT jstring JNICALL Java_btc_1oracle_1core_1wrapper_Script_address
        (JNIEnv *env, jobject caller, jobject network_type) {

    auto script = GetScriptFromObject(env, caller);

    auto address = script->address(oracle::network_type::testnet);

    return env->NewStringUTF(address.c_str());
}

/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Script
 * Method:    segwit_address
 * Signature: (Lcom/example/javawallet/btc_oracle_core_wrapper/network_type;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_btc_1oracle_1core_1wrapper_Script_segwit_1address
        (JNIEnv *env, jobject caller, jobject network_type) {
    //
    auto script = GetScriptFromObject(env, caller);

    auto segwit_address = script->segwit_address(oracle::network_type::testnet);

    return env->NewStringUTF(segwit_address.c_str());
}

/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Script
 * Method:    hash160
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_btc_1oracle_1core_1wrapper_Script_hash160
        (JNIEnv *env, jobject caller) {

    auto script = GetScriptFromObject(env, caller);

    auto hash = script->hash160();

    auto strHash = utils::hex(&hash[0], hash.size());

    return env->NewStringUTF(strHash.c_str());
}

/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Script
 * Method:    hex
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_btc_1oracle_1core_1wrapper_Script_hex
        (JNIEnv *env, jobject caller) {

    auto script = GetScriptFromObject(env, caller);

    return env->NewStringUTF(script->hex().c_str());
}
/*
 * Class:     com_example_javawallet_btc_oracle_core_wrapper_Script
 * Method:    cleanup
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_btc_1oracle_1core_1wrapper_Script_cleanup
        (JNIEnv *env, jobject
        caller) {
    jclass cls = env->FindClass(package_name "/Script");

    jfieldID handleId = env->GetFieldID(cls, "handle", "J");

    jlong handle = env->GetLongField(caller, handleId);

    oracle::script_ptr *pScript = reinterpret_cast<oracle::script_ptr *>(handle);
    delete pScript;

    env->SetLongField(caller, handleId, 0);
}

/*
 * Class:     btc_oracle_core_wrapper_Script
 * Method:    lockTime
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_btc_1oracle_1core_1wrapper_Script_lockTime
        (JNIEnv *, jclass, jint days)
{
    return oracle::script::locktime(days);
}

/*
 * Class:     btc_oracle_core_wrapper_Script
 * Method:    createSegwitDemandDeposit
 * Signature: (IILjava/util/ArrayList;II)Lbtc_oracle_core_wrapper/Script;
 */
JNIEXPORT jobject JNICALL Java_btc_1oracle_1core_1wrapper_Script_createSegwitDemandDeposit
        (JNIEnv *env, jclass,
         jint csvBlocks,
         jint walletUnlockingCount, jobject walletPubkeys,
         jint serverUnlockingCount, jint serverLockingCount) {
    //
    //  initialize server public key list
    //
    int count = min(serverLockingCount, (int) size(oracle::g_server_pubkeys));
    vector<key::pubkey> server_pubkeys(oracle::g_server_pubkeys, oracle::g_server_pubkeys + count);

    vector<string> hex_pubkeys = convertArray<string>(env, walletPubkeys);

    //
    //  create demand deposit script
    //
    auto demand_deposit = oracle::script::create_demand_deposit(csvBlocks,
                                                                walletUnlockingCount,
                                                                {begin(hex_pubkeys),
                                                                 end(hex_pubkeys)},
                                                                serverUnlockingCount,
                                                                {oracle::g_server_pubkeys[0],
                                                                 oracle::g_server_pubkeys[1],
                                                                 oracle::g_server_pubkeys[2]});
    return NewScriptObject(env, demand_deposit);
}
}