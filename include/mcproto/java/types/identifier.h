#ifndef __H_MCPROTO_JAVA_TYPES_IDENTIFIER__
#define __H_MCPROTO_JAVA_TYPES_IDENTIFIER__

#include <mcproto/common/mctype.h>
#include <mcproto/java/types/string.h>
#include <mcproto/java/types/vars.h>
#include <string>

namespace mcp {

class Identifier 
    : public MCType 
{
public:
    Identifier() = default;
    Identifier(const std::string& value, const std::string& nspace = "minecraft")
        : _value {value}, _nspace {nspace}
    {
        if (_value.size() + _nspace.size() + 1 > MAXIMUM_STRING_SIZE) {
            throw std::runtime_error("Identifier::Identifier() - Maximum string limit reached.");
        }

        _size = VarInt(_value.size() + _nspace.size() + 1);
    }

    std::size_t size() const override {
        return _value.size() + _nspace.size() + _size.size() + 1;
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) override {
        std::size_t total {0};
        std::string full_identifier {_nspace + ':' + _value};

        total += _size.encode(begin, end);


        std::memcpy(begin, full_identifier.data(), full_identifier.size());
        total += full_identifier.size();
        begin += full_identifier.size();

        return total;
    }

private:
    std::string _nspace {};
    std::string _value {};
    VarInt _size {};
};

};

#endif
