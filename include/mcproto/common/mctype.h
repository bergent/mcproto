#ifndef __H_MCPROTO_TYPES_MCTYPE__
#define __H_MCPROTO_TYPES_MCTYPE__

#include <cstddef>
#include <cstdint>

namespace mcp {

class MCType {
public:
    virtual ~MCType() = default;

    virtual constexpr std::size_t size() const = 0;
    virtual std::size_t encode(uint8_t*& begin, uint8_t* const end) = 0;
};

};

#endif
