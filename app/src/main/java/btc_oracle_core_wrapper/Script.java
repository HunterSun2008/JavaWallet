package btc_oracle_core_wrapper;

import java.util.ArrayList;


public class Script {
    static {
        System.loadLibrary("jni_btc_oracle_core_wrapper");
    }

    private long handle;
    public enum network_type{ main, testnet, regtest };

    public native String address(network_type type);
    public native String segwit_address(network_type type);
    public native String hash160();
    public native String hex();

    public native void cleanup();

    //return a csvBlocks
    public native static int lockTime(int day);

    /**
     *
     * @param csvBlocks
     * @param walletUnlockingCount
     * @param walletPubkeys
     * @param serverUnlockingCount
     * @param serverLockingCount
     * @return a locking Demand Deposit script
     */
    public native static Script createSegwitDemandDeposit(int csvBlocks, int walletUnlockingCount, ArrayList<String> walletPubkeys,
                                                                           int serverUnlockingCount, int serverLockingCount);

    /**
     * Create a P2WPKW script pubkey for locking
     * @param address   segwit address
     * @param type      network type
     * @return
     */
    public native static Script create_P2WPKH(String address, network_type type);
}
