#ifndef __H_MCPROTO_PACKET__
#define __H_MCPROTO_PACKET__

#include <cstddef>
#include <cstdint>

namespace mcp {

class MCPacket {
public:
    virtual ~MCPacket() = default;

    virtual constexpr std::size_t size() const = 0;
    virtual std::size_t encode(uint8_t*& begin, uint8_t* const end) = 0;

private:

};

};

#endif
