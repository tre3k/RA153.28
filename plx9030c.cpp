//
// Created by kirill on 26.02.19.
//

#include "plx9030c.h"

using namespace PLX9030;

plx9030::plx9030(std::string device) {
    fd = open(device.c_str(),O_RDWR);
    if(fd < 0){
        status = STATUS_FD_ERROR;
        return;
    }
    status = STATUS_OK;
}

plx9030::~plx9030() {
    close(fd);
}

int plx9030::getStatus() {
    return status;
}

int plx9030::getFileDescriptor() {
    return fd;
}

/* Function for write/read CS0..3 */
char plx9030::read8(unsigned long int base, long int offset) {
    unsigned char byte = 0x00;
    if(ioctl(fd,base,offset) < 0) status = STATUS_IOCTL_ERROR;
    if(read(fd,&byte,1) < 0) status = STATUS_READ_ERROR;
    return byte;
}

void plx9030::write8(unsigned long int base, long int offset, char byte) {
    if(ioctl(fd,base,offset) < 0) status = STATUS_IOCTL_ERROR;
    if(write(fd,&byte,1) <0 ) status = STATUS_WRITE_ERROR;
}

uint16_t plx9030::read16(unsigned long int base, long int offset) {
    uint16_t retval;

    return retval;
}