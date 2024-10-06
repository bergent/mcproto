#include <mcproto/common/utils.h>
#include <iomanip>


std::ostream& operator<< (std::ostream& out, const mcp::ByteArray& ba) {
    std::size_t rows {ba.size() % 16 == 0 
                      ? ba.size() / 16 
                      : 1 + (ba.size() / 16) };

    std::size_t idx {0};

    for (int row {0}; row != rows; ++row) {
        for (int col {0}; col != 16 && idx < ba.size(); ++col) {
            out << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ba[idx]) << ' ';
            ++idx;
        }
        out << '\n';
    }

    return out;

}
