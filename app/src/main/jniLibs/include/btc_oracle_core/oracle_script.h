#ifndef ORACLE_SCRIPT_H
#define ORACLE_SCRIPT_H
#include <vector>
#include <array>
#include <memory>
#include "oracle_server_pubkeys.h"
#include "network_type.h"

namespace oracle
{

class script
{
public:
  virtual ~script() {}

  virtual std::vector<uint8_t> data() = 0;

  virtual std::string hex() = 0;

  virtual std::vector<uint8_t> hash160() = 0;

  virtual std::string address(network_type type = network_type::main) = 0;

  virtual std::string segwit_address(network_type type = network_type::main, uint8_t version = 0) = 0;

  //
  //  convert day to CSV time format
  //  paramter
  //        day - between 1 and 365
  //
  static uint32_t locktime(uint32_t day);

  /**
   * Create a deposit script for locking
   * Paramete :    
   *          csv_blocks - the locked time
   *          m         - the count of signature for unlocking scirpt   
   *          pubkeys - client's public kyes, its size() must be less than or equal to 3
   * return : 
   *          the following scritp           
   *          <some days> CHECKSEQUENCEVERIFY DROP m <Client's Pubkey 1> <Client's Pubkey 2> <Client's Pubkey 3> 3 CHECKMULTISIG
   */
  static std::shared_ptr<script>
  create_deposit(uint32_t csv_blocks, uint32_t m, const std::vector<key::pubkey> &pubkeys);

  /**
   * Create a deposit scriptSig for unlocking
   * 
   */
  static std::shared_ptr<script>
  create_deposit_sig(const std::vector<key::signature> &signatures,
                     std::shared_ptr<script> deposit);
  /**
   * Create a demand deposit script for locking
   * 
   * Paramete : 
   *      csv_blocks      - the locked time   
   *      mc              - mc is the number of client's signatue for unlocking script, must be between 1 and 3
   *      pubkeys         - client's public kyes, its size() must be between 1 and 3
   *      ms              - ms is a number that of 15 sign can spend this redeem script 
   *      oracle_pubkeys  - oracles' public key, its size() must be less than or equal to 15
   *    
   * Return : 
   *      the follwing script :
   *      IF
   *          mc <Client's Pubkey 1> <Client's Pubkey 2> <Client's Pubkey 3> 3 CHECKMULTISIG ms <Oracle1's Pubkey> ...... <Oracle15's Pubkey> 15 CHECKMULTISIG 
   *      ELSE
   *          <some days> CHECKSEQUENCEVERIFY DROP ms <Client's Pubkey 1> <Client's Pubkey 2> <Client's Pubkey 3> 3 CHECKMULTISIG	        
   *      ENDIF
   */
  static std::shared_ptr<script>
  create_demand_deposit(uint32_t csv_blocks,
                        uint32_t mc,
                        const std::vector<key::pubkey> &client_pubkeys,
                        uint32_t ms = 10,
                        const std::vector<key::pubkey> &oracle_pubkeys = std::vector<key::pubkey>(std::begin(oracle::g_server_pubkeys), std::end(oracle::g_server_pubkeys)));

  /**
   *  Create a demand deposit scriptSig for unlocking
   * 
   */
  static std::shared_ptr<script>
  create_demand_deposit_sig(bool demand,
                            const std::vector<key::signature> &client_signatures,
                            const std::vector<key::signature> &oracle_signatures,
                            std::shared_ptr<script> demand_deposit);

  /**
   * create a script public for locking 
   * address : An address encoded by base58 for P2PKH transaction  
   */
  static std::shared_ptr<script>
  create_p2pkh(const std::string &address);

  /**
   * create a P2PKH script public for signing 
   * pubkey : a public key for redeem script 
   */
  static std::shared_ptr<script>
  create_p2pkh_redeem(const key::pubkey &pubkey);

  /**
   * create a P2PKH script sig for unlocking
   * signature :
   * pubkey: 
   */
  static std::shared_ptr<script>
  create_p2pkh_sig(const key::signature &signature, const key::pubkey &pubkey);

  /**
   * create a P2WPKH sigwit script public for locking
   * 
   * address : bech32 address
   */
  static std::shared_ptr<script>
  create_p2wpkh(const std::string &address, network_type type);

  /**
   * create a P2WPKH sigwit script sig for signing
   * 
   * address : bech32 address
   */
  static std::shared_ptr<script>
  create_p2wpkh_redeem(const key::pubkey &pubkey);
};

typedef std::shared_ptr<script> script_ptr;

class witness
{
public:
  virtual ~witness() {}

  //return the pointer of wally_tx_witness_stack
  virtual void *get() = 0;

  /**
   *  Create a deposit witness stack for unlocking
   */
  static std::shared_ptr<witness>
  create_deposit(const std::vector<key::signature> &signatures,
                 std::shared_ptr<script> redeem);
  /**
   *  Create a demand deposit witness stack for unlocking
   */
  static std::shared_ptr<witness>
  create_demand_deposit(bool demand,
                        const std::vector<key::signature> &client_signatures,
                        const std::vector<key::signature> &oracle_signatures,
                        std::shared_ptr<script> demand_deposit);

  /**
   * Create a P2WPKH sigwit witness for unlocking
   * 
   * pubkey     : a public key for sicript sig
   * signature  : signature for P2PKH
   */
  static std::shared_ptr<witness>
  create_p2wpkh(const key::signature &signature, const key::pubkey &pubkey);
};

typedef std::shared_ptr<witness> witness_ptr;

} // namespace oracle

#endif
