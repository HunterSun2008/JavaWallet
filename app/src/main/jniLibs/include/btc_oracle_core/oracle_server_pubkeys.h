#ifndef ORACLE_SERVER_PUBKEYS_H
#define ORACLE_SERVER_PUBKEYS_H
#include <array>
#include <string>
#include "oracle_key.h"

namespace oracle
{
static key::pubkey g_server_pubkeys[]
{
    key::pubkey("02b6fb6c30c4d29e6073091564e1b4c0b0a7b3406dda49b09493f456de17e21cdf"),
    key::pubkey("031d674ea43b0eee2d1307c8244bcb46823f477b8270baa8f17af14bde64a1f5a5"),
    key::pubkey("037982270eca456b4d978df2c4fb03f681e320fc6682ea042dcff15766b8360e42")
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey(""),
    // key::pubkey("")
};
}



#endif