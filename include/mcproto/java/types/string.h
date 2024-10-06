#ifndef __H_MCPROTO_JAVA_TYPES_STRING__
#define __H_MCPROTO_JAVA_TYPES_STRING__

#include <mcproto/common/mctype.h>
#include <mcproto/java/types/vars.h>
#include <string>

namespace mcp {

constexpr std::size_t MAXIMUM_STRING_SIZE {32767};

class String 
    : public MCType
{
public:
    String() = default;
    String(const std::string& value) {
        if (value.size() > MAXIMUM_STRING_SIZE) {
            throw std::runtime_error("Java String should be equal or less than 32767 bytes");
        }
        _value = value;
        _size = VarInt(value.size());
    }

    std::size_t size() const override {
        return _value.size() + _size.size();
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) override {
        std::size_t total {0};

        total += _size.encode(begin, end);
        std::memcpy(begin, _value.data(), _value.size());
        total += _value.size();
        begin += total;

        return total;
    }

private:
    std::string _value {};
    VarInt _size {};
};

};

#endif

