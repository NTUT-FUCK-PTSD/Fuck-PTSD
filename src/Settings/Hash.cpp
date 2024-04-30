#include "Hash.h"

Settings::Hash::ht Settings::Hash::HashConvert(const std::string& str) {
    ht ret = basis;

    for (std::size_t i = 0; i < str.size(); ++i) {
        ret ^= static_cast<std::size_t>(str[i]);
        ret *= prime;
    }

    return ret;
}
