package btc_oracle_core_wrapper;

import java.util.ArrayList;

public class Transaction {
    static {
        System.loadLibrary("jni_btc_oracle_core_wrapper");
    }

    private long handle;

    public static class Input {
        private String txid;
        private int index;
        private int sequence;
        private Script redeem;
        private Script witness;

        public Input(String _txid, int _index, int _sequence, Script _redeem, Script _witness)
        {
            txid = _txid;
            index = _index;
            sequence = _sequence;
            redeem = _redeem;
            redeem = _witness;
        }
    }

    public static class Output {
        private long satoshi;
        private Script script_pubkey;

        /**
         *
         * @param _satoshi  : spend coin with unit satoshi
         * @param _script_pubkey : locking script
         */
        public Output(long _satoshi, Script _script_pubkey)
        {
            satoshi = _satoshi;
            script_pubkey = _script_pubkey;
        }
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
