#ifndef __H_MCPROTO_JAVA_TYPES_ENTITY_METADATA__
#define __H_MCPROTO_JAVA_TYPES_ENTITY_METADATA__

#include <mcproto/java/types/basic_types.h>
#include <mcproto/java/types/vars.h>

namespace mcp {

template <typename MetadataValue>
class EntityMetadata 
    : public MCType
{
public:
    EntityMetadata() = default;
    EntityMetadata(uint8_t index, int32_t type, const MetadataValue& value)
        : _index {index}, _type {type}, _value {value}
    {};

    std::size_t size() const override {
        return _index.size() + _type.size() + _value.size();
    }

    std::size_t encode(uint8_t*& begin, uint8_t* const end) override {
        std::size_t total {0};
        total += _index.encode(begin, end);
        total += _type.encode(begin, end);
        total += _value.encode(begin, end);

        return total;
    }
private:
    UByte _index {};
    VarInt _type {};
    MetadataValue _value {};
};

};

#endif
