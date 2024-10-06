#ifndef __H_MCPROTO_JAVA_TYPES_POSITION__
#define __H_MCPROTO_JAVA_TYPES_POSITION__

#include <mcproto/common/utils.h>
#include <mcproto/common/mctype.h>
#include <cstring>
#include <cstdint>

namespace mcp {

class Position 
    : public MCType
{
public:
    Position() = default;
    Position(int32_t x, int32_t z, int16_t y)
        : _x {x}, _z {z}, _y {y}
    {}

    std::size_t size() const override {
        return 8;
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) override {
        int64_t x_position {};
        int64_t z_position {};
        int64_t y_position {};

        x_position |= _x;
        x_position <<= 38;

        z_position |= _z;
        z_position <<= 12;

        y_position |= _y;

        int64_t result {x_position | z_position | y_position};
        auto bytes = to_bytes(result);

        std::memcpy(begin, bytes.data(), bytes.size());
        begin += bytes.size();

        return bytes.size();
    }

private:
    int32_t _x {};
    int32_t _z {};
    int16_t _y {};
};

};

#endif
