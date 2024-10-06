#ifndef __H_MCPROTO_JAVA_TYPES_VARS__
#define __H_MCPROTO_JAVA_TYPES_VARS__

#include <mcproto/common/mctype.h>
#include <mcproto/common/utils.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <type_traits>

namespace mcp {

static constexpr uint8_t SEGMENT_BITS = 0x7F;
static constexpr uint8_t CONTINUE_BIT = 0x80;

template<typename T, typename Unsigned>
ByteArray to_var_repr(T value) {
    ByteArray repr {};
    
    Unsigned uvalue { static_cast<Unsigned>(value) };

    if (not uvalue) {
        repr.push_back(0);
        return repr;
    }

    while (uvalue) {
        uint8_t byte = uvalue & SEGMENT_BITS;    
        uvalue >>= 7;

        if (uvalue) {
            byte |= CONTINUE_BIT;
        }

        repr.push_back(byte);
    }

    return repr;
}

template <typename ValueType, typename UnsignedPart>
class VarType
    : public MCType 
{
   static_assert(not std::is_same_v<ValueType, int32_t> or not std::is_same_v<ValueType, int64_t>,
                 "VarType might be only instantied with int32_t or int64_t types");
public:
    VarType() = default;
    VarType(ValueType value)
        : _value {value}, _var_repr{to_var_repr<ValueType, UnsignedPart>(value)}
    {}
    ~VarType() = default;
    
    std::size_t size() const override {
        return _var_repr.size();
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) {
        std::memcpy(begin, _var_repr.data(), _var_repr.size());
        begin += _var_repr.size();

        return _var_repr.size();
    }

    const ValueType& value() const {
        return _value;
    }

    const ByteArray& bytes() const {
        return _var_repr;
    }

    uint8_t bytes(std::size_t idx) const {
        if (size() == 0 || idx < 0 || idx >= size()) {
            throw std::out_of_range("VarInt::bytes() - out of bytes representation indexation");
        } 
        return _var_repr[idx];
    }

private:
    ValueType _value {};
    ByteArray _var_repr {};
};


// Aliases
using VarInt = VarType<int32_t, uint32_t>;
using VarLong = VarType<int64_t, uint64_t>;


};

#endif
