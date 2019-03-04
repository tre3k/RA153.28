//
// Created by alex on 04.03.19.
//

#include "controller_RA153_28.h"

using namespace cRA153_28;

controller_RA153_28::controller_RA153_28(PLX9030::plx9030 *p9030) {
    dev = p9030;
}

controller_RA153_28::~controller_RA153_28() {

}

void controller_RA153_28::setChannel(int channel) {
    c_channel = channel;
}
int controller_RA153_28::getChannel() { return  c_channel;}

void controller_RA153_28::setSpeed(uint32_t speed) {
    dev->write8(PLX9030::CS0, SSI_REGISTER, 0x00);
    dev->setMask(PLX9030::CS0, SSI_REGISTER, 0x01);             // up 0-bit

    dev->write24(PLX9030::CS0, SPEED_REGISTER+c_channel*16, c_ssi_speed*1000000/(speed*2));
    // c_ssi_speed * 10000000 ??? или это что-то другое?
    c_speed = speed;
}
uint32_t controller_RA153_28::getSpeed() { return c_speed;}


void controller_RA153_28::setSSISpeed(uint16_t speed) {
    dev->write16(PLX9030::CS0, SSI_SPEED_REGISTER, speed);
    c_ssi_speed = speed;
}
uint16_t controller_RA153_28::getSSISpeed() { return c_ssi_speed;}


void controller_RA153_28::initMotion() {
    uint32_t encoder_mask = 0;

    // port 3 ENFSSI=1; CLRFSSI=1; что это?
    dev->write8(PLX9030::CS0, SSI_REGISTER, 0x03);

    // just set null registers
    dev->write8(PLX9030::CS0, PARAMETERS_SSI_AND_MOTION+c_channel*16, 0x00);        // port 1
    dev->write8(PLX9030::CS0, CONTROL_SSI_AND_MOTION+c_channel*16, 0x00);           // port 0

    dev->setMask(PLX9030::CS0, CONTROL_SSI_AND_MOTION+c_channel*16, CLR_SSI);       //set 5bit

    // set encoder bit
    dev->write8(PLX9030::CS0, ENCODER_BITS_REG+c_channel*16, encoder_bits+1);
    for(int i=0;i<encoder_bits;i++) encoder_mask |= (1<<i);
    dev->write32(PLX9030::CS1, ENCODER_MASK+c_channel*16, encoder_mask);

    dev->setMask(PLX9030::CS0, CONTROL_SSI_AND_MOTION+c_channel*16, EN_SSI);        //set bit ENABLE SSI
    dev->setMask(PLX9030::CS0, PARAMETERS_SSI_AND_MOTION+c_channel*16, EN_ENDS);    //set 2-bit Enable ENDS
}