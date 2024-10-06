#ifndef __H_MCPROTO_JAVA_TYPES_BASIC_TYPES__
#define __H_MCPROTO_JAVA_TYPES_BASIC_TYPES__

#include <cstring>
#include <mcproto/common/mctype.h>
#include <mcproto/common/utils.h>
#include <type_traits>
#include <cstdint>

namespace mcp {

template <typename ValueType>
class BasicType 
    : public MCType
{
   static_assert(std::is_arithmetic<ValueType>(), "BasicType might be only instantied with basic arithmetic types");
public:
    BasicType() = default;
    BasicType(const ValueType& value)
        : _value {value}
    {}

    ~BasicType() = default;

    std::size_t size() const override {
        return sizeof(ValueType);
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) override {
        auto bytes = to_bytes(_value);

        std::memcpy(begin, bytes.data(), bytes.size());
        begin += bytes.size();

        return bytes.size();
    }

private:
    ValueType _value {};
};


// Aliases
using Boolean = BasicType<bool>;
using Byte = BasicType<int8_t>;
using UByte = BasicType<uint8_t>;
using Short = BasicType<int16_t>;
using UShort = BasicType<uint16_t>;
using Int = BasicType<int32_t>;
using Long = BasicType<int64_t>;
using Float = BasicType<float>;
using Double = BasicType<double>;

};

#endif
