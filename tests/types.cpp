#include <gtest/gtest.h>
#include <mcproto/java/types/vars.h>

TEST(MCProtoTypesTest, Empty_VarInt) {
    mcp::VarInt zero {};
    
    ASSERT_EQ(zero.size(), 0);
    ASSERT_EQ(zero.value(), 0);
}

TEST(MCProtoTypesTest, Zero_VarInt) {
    mcp::VarInt zero {0};
    
    ASSERT_EQ(zero.size(), 1);
    ASSERT_EQ(zero.value(), 0);
    ASSERT_EQ(zero.bytes()[0], 0);
}

TEST(MCProtoTypesTest, Different_VarInt) {
    mcp::VarInt one {1};
    ASSERT_EQ(one.size(), 1);
    ASSERT_EQ(one.value(), 1);
    ASSERT_EQ(one.bytes(0), 1);

    mcp::VarInt two {2};
    ASSERT_EQ(two.size(), 1);
    ASSERT_EQ(two.value(), 2);
    ASSERT_EQ(two.bytes(0), 2);

    mcp::VarInt bord {127};
    ASSERT_EQ(bord.size(), 1);
    ASSERT_EQ(bord.value(), 127);
    ASSERT_EQ(bord.bytes(0), 0x7f);

    mcp::VarInt twob {128};
    ASSERT_EQ(twob.size(), 2);
    ASSERT_EQ(twob.value(), 128);
    ASSERT_EQ(twob.bytes(0), 0x80);
    ASSERT_EQ(twob.bytes(1), 0x01);

    mcp::VarInt ex1 {25565};
    ASSERT_EQ(ex1.size(), 3);
    ASSERT_EQ(ex1.value(), 25565);
    ASSERT_EQ(ex1.bytes(0), 0xdd);
    ASSERT_EQ(ex1.bytes(1), 0xc7);
    ASSERT_EQ(ex1.bytes(2), 0x01);

    mcp::VarInt ex2 {2097151};
    ASSERT_EQ(ex2.size(), 3);
    ASSERT_EQ(ex2.value(), 2097151);
    ASSERT_EQ(ex2.bytes(0), 0xff);
    ASSERT_EQ(ex2.bytes(1), 0xff);
    ASSERT_EQ(ex2.bytes(2), 0x7f);

    mcp::VarInt ex3 {2147483647};
    ASSERT_EQ(ex3.size(), 5);
    ASSERT_EQ(ex3.value(), 2147483647);
    ASSERT_EQ(ex3.bytes(0), 0xff);
    ASSERT_EQ(ex3.bytes(1), 0xff);
    ASSERT_EQ(ex3.bytes(2), 0xff);
    ASSERT_EQ(ex3.bytes(3), 0xff);
    ASSERT_EQ(ex3.bytes(4), 0x07);

    mcp::VarInt nex1 {-1};
    ASSERT_EQ(nex1.size(), 5);
    ASSERT_EQ(nex1.value(), -1);
    ASSERT_EQ(nex1.bytes(0), 0xff);
    ASSERT_EQ(nex1.bytes(1), 0xff);
    ASSERT_EQ(nex1.bytes(2), 0xff);
    ASSERT_EQ(nex1.bytes(3), 0xff);
    ASSERT_EQ(nex1.bytes(4), 0x0f);

    mcp::VarInt nex2 {-2147483648};
    ASSERT_EQ(nex2.value(), -2147483648);
    ASSERT_EQ(nex2.bytes(0), 0x80);
    ASSERT_EQ(nex2.bytes(1), 0x80);
    ASSERT_EQ(nex2.bytes(2), 0x80);
    ASSERT_EQ(nex2.bytes(3), 0x80);
    ASSERT_EQ(nex2.bytes(4), 0x08);
}
