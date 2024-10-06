#ifndef __H_MCPROTO_COMMON_UTILS__
#define __H_MCPROTO_COMMON_UTILS__

#include <vector>
#include <cstdint>
#include <iostream>


namespace mcp {

using ByteArray = std::vector<uint8_t>;

template <typename T>
ByteArray to_bytes(T value) {
    union {
        T val;
        uint8_t bytes[sizeof(T)];
    } layout {};

    layout.val = value;
    
    return std::vector<uint8_t> {layout.bytes, layout.bytes + sizeof(T)};
}


};

std::ostream& operator<< (std::ostream& out, const mcp::ByteArray& ba);

#endif
