#ifndef ORACLE_KEY_H
#define ORACLE_KEY_H
#include <string>
#include <vector>
#include <array>
#include "oracle_utils.h"
#include "network_type.h"
#ifdef __APPLE__
#include <sys/types.h>
#endif

#define EC_SIGNATURE_LEN 64

namespace key
{

enum sign_type
{
  all = 0x01,
  none = 0x02,
  single = 0x03,
  forkid = 0x40,
  anyonecanpay = 0x80
};

class signature
{
public:
  std::vector<uint8_t> to_der() const;

  signature(std::array<uint8_t, EC_SIGNATURE_LEN> data, sign_type type);

  std::string to_hex();

  static signature from_hex(const std::string &hex, sign_type type);

private:
  std::array<uint8_t, EC_SIGNATURE_LEN> m_data;
  sign_type m_type;
};

class pubkey
{
public:
  pubkey(uint8_t *buffer, uint32_t length);
  pubkey(const std::string &base58);
  using network_type=oracle::network_type;
  
  //return a string encoded with SHA256 + PRIME160
  std::string address(oracle::network_type type = oracle::network_type::main);

  std::string sigwit_address(oracle::network_type type = oracle::network_type::main, uint8_t version = 0);

  std::vector<uint8_t> data() const;

private:
  std::vector<uint8_t> m_data;
};

class privkey
{
public:
  privkey(uint8_t *buffer, size_t len);

  privkey(const std::string &base58check);

  privkey(const privkey &key) = delete;

  privkey(privkey &&key) noexcept;

  privkey &operator=(privkey &&key) noexcept;

  uint32_t prefix() { return m_prefix; }
  uint32_t suffix() { return m_suffix; }
  
  //
  //  load privkey encrypted by BIP38 from a file
  //  file_name : file name
  //  pwd       : password for decrypting
  //
  static privkey load_from_bip38(const std::string &file_name, const std::string &pwd);

  std::string encrypt_bip38(const std::string &password);

  //
  // Convert a private key to Wallet Import Format
  //
  std::string to_wif(uint32_t prefix = 0x80);
  
  pubkey get_pubkey();

  signature sign(const uint8_t *input, uint32_t len, sign_type type) const;

private:
  std::vector<uint8_t> m_data;
  uint32_t m_prefix;
  uint32_t m_suffix;
};
} // namespace key

#endif
