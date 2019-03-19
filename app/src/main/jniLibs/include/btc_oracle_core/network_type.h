#ifndef NETWORK_TYPE_H
#define NETWORK_TYPE_H
#include <string>

namespace oracle
{
enum network_type
{
    main,
    testnet,
    regtest
};

std::string get_segwit_prefix(network_type type);

}

#endif