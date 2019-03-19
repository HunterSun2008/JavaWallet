package btc_oracle_core_wrapper;

import java.util.ArrayList;

public class Transaction {
    static {
        System.loadLibrary("jni_btc_oracle_core_wrapper");
    }

    private long handle;

    /**
     *
     */
    public static class Input {
        String prev_txid;
        int index;
        int sequence;
        Script script_redeem;
        Script script_witness;
    }

    /**
     *
     */
    public static class Output {
        long satoshi;
        Script script_pubkey;
    }

    /**
     * create a transaction
     * @param version
     * @param lockTime
     * @param inputs
     * @param outputs
     * @return
     */
    public native static Transaction create(int version, int lockTime,
                                            ArrayList<Input> inputs,
                                            ArrayList<Output> outputs);
    public native void cleanup();
}
