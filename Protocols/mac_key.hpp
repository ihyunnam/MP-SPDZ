/*
 * mac_key.hpp
 *
 */

#ifndef PROTOCOLS_MAC_KEY_HPP_
#define PROTOCOLS_MAC_KEY_HPP_

#include "Networking/Player.h"
#include "Math/Setup.h"

#include "fake-stuff.hpp"

template<class T>
typename T::mac_key_type read_or_generate_mac_key(const Player& P,
        string directory = "")
{
    if (directory == "")
        directory = get_prep_sub_dir<T>(P.num_players());
    typename T::mac_key_type res;
    T::read_or_generate_mac_key(directory, P, res);
    return res;
}

template<class T>
void check_field_size()
{
    int sec = OnlineOptions::singleton.security_parameter;
    if (T::length() < sec)
    {
        // MAC/field types with a fixed length (the 64-bit binary MAC key,
        // SPDZ2k with s = 64) cannot reach a higher statistical parameter.
        // Warn once instead of aborting, so that the parameter still governs
        // the edaBit and triple cut-and-choose; this component stays at
        // T::length() bits.
        static bool warned = false;
        if (not warned)
        {
            cerr << "WARNING: MAC/field length " << T::length()
                    << " is below the statistical security parameter " << sec
                    << "; this component provides only " << T::length()
                    << "-bit security" << endl;
            warned = true;
        }
    }
}

#endif /* PROTOCOLS_MAC_KEY_HPP_ */
