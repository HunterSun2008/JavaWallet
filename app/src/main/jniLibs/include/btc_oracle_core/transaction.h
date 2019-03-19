#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "oracle_script.h"
#include "oracle_key.h"

class transaction
{
 public:
   virtual ~transaction() {}

   struct input
   {
      std::string prev_txid;
      uint32_t index;
      uint32_t sequence;
      oracle::script_ptr script_redeem;
      oracle::script_ptr script_witness;
   };

   struct output
   {
      uint64_t satoshi;
      oracle::script_ptr script_pubkey;
   };

   /**
    * 
    */
   static std::shared_ptr<transaction>
   raw_create(uint32_t version,
              uint32_t locktime,
              const std::vector<input> &inputs,
              const std::vector<output> &outputs);

   /**
    *   get a signature hash for signing
    *    index : index for vin array
    *    satoshi : the value of previous vout 
    *    type : sing type
    *    flag : 1 to generate a BIP 143 segwit signature, or 0 to generate a pre-segwit Bitcoin signature.
    */
   virtual std::vector<uint8_t> get_signature_hash(uint32_t index,
                                                   uint64_t satoshi,
                                                   key::sign_type type = key::sign_type::all,
                                                   int32_t flag = 0) = 0;

   /**
    *    Sign for a vin specified by index
    *    privkey :
    *    index : index for vin array
    *    satoshi : the value of previous vout 
    *    type : sing type
    *    flag : 1 to generate a BIP 143 segwit signature, or 0 to generate a pre-segwit Bitcoin signature.
    */
   virtual key::signature raw_sign(const key::privkey &privkey,
                                   uint32_t index,
                                   uint64_t satoshi,
                                   key::sign_type type = key::sign_type::all,
                                   int32_t flag = 0) = 0;

   /**
    * Set scriptSig for a vin of index 
    * index : the index of vin
    * signatures : an array of all of signaute to be added to scriptSig
    * redeem : the redeem script whoes address was paied to   
    */
   virtual void set_script_sig(uint32_t index, oracle::script_ptr script_sig) = 0;

   /**
    * Set witness for input
    * Prameters : 
    *    index : the index of inputs
    *    witness_stack : the witness stack crated by witness::create_xxx
    */
   virtual void set_input_witness(uint32_t index, oracle::witness_ptr witness) = 0;

   virtual std::string to_hex() = 0;
};

typedef std::shared_ptr<transaction> transaction_ptr;

#endif
