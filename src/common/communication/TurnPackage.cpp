#include "TurnPackage.h"

TurnPackage::TurnPackage() {
}

TurnPackage::~TurnPackage() {
}

package_nr_t TurnPackage::get_package_nr() {
    return 6;
}


std::vector<unsigned char> TurnPackage::encode_payload() {
    std::vector<unsigned char> encoded;

    encoded.push_back(pos_x >>  0 & 0xFF);
    encoded.push_back(pos_x >>  8 & 0xFF);
    encoded.push_back(pos_x >> 16 & 0xFF);
    encoded.push_back(pos_x >> 24 & 0xFF);

    encoded.push_back(pos_x >>  0 & 0xFF);
    encoded.push_back(pos_y >>  8 & 0xFF);
    encoded.push_back(pos_y >> 16 & 0xFF);
    encoded.push_back(pos_y >> 24 & 0xFF);

    return encoded;
}

void TurnPackage::decode_payload(std::vector<unsigned char> command_data) {
    pos_x = command_data.at(0) <<  0 
          | command_data.at(1) <<  8
          | command_data.at(2) << 16 
          | command_data.at(3) << 24;
    pos_y = command_data.at(4) <<  0
          | command_data.at(5) <<  8
          | command_data.at(6) << 16
          | command_data.at(7) << 24;
}

void TurnPackage::set_pos_x(int pos_x) {
    this->pos_x = pos_x;
}

int TurnPackage::get_pos_x() {
    return pos_x;
}
void TurnPackage::set_pos_y(int pos_y) {
    this->pos_y = pos_y;
}

int TurnPackage::get_pos_y() {
    return pos_y;
}

