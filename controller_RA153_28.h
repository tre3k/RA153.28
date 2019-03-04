//
// Created by alex on 04.03.19.
//

#ifndef RA153_28_CONTROLLER_RA153_28_H
#define RA153_28_CONTROLLER_RA153_28_H

#include "plx9030c.h"

namespace cRA153_28 {

    /* CS0 */
    #define CONTROL_SSI_AND_MOTION 0x00
    #define CLR_FS0 0x00                                // 0-bit set/unset frequency formier
    #define ENF_FS0 0x01                                // 1-bit enable/disable frequency formier
    #define CLR_STEP0 0x02                              // 2-bit enable/clear steps
    #define EN_STEP0 0x04                               // 3-bit enable/disable steps
    #define CLR_SSI 0x08                                // 4-bit
    #define EN_SSI 0x10                                 // 5-bit

    #define PARAMETERS_SSI_AND_MOTION 0x01
    #define EN_ENDS 0x02                                // 2-bit enable ends (концевики)

    #define SPEED_REGISTER 0x04

    #define ENCODER_BITS_REG 0x0d                       // (offset: 13)

    /* without channels */
    #define SSI_REGISTER 0x03                           // может называться по-другому...
    #define SSI_SPEED_REGISTER 0x13                     // (offset: 19)


    /* CS1 */
    #define ENCODER_MASK 0x04


    class controller_RA153_28 {
    /*global class private variable */
    private:
        PLX9030::plx9030 *dev;              // device

        int c_channel;
        uint32_t c_speed;
        uint16_t c_ssi_speed;


    /* global class public variable */
    public:
        uint8_t encoder_bits;

    /* Contructor */
    public:
        explicit controller_RA153_28(PLX9030::plx9030 *p9030);
        ~controller_RA153_28();

    public:
        void setChannel(int channel);
        int getChannel(void);

        /* Set and get motion speed */
        void setSpeed(uint32_t speed);
        uint32_t getSpeed(void);

        /* Set and get SSI Speed */
        void setSSISpeed(uint16_t speed);
        uint16_t getSSISpeed(void);

        /* init motion */
        void initMotion(void);

    };

}

#endif //RA153_28_CONTROLLER_RA153_28_H
