
#include "frames.h"


// ***** BASE FRAME ******

struct Frame {
    virtual void serialize(uint8_t* buffer) {
        buffer[0] = STX
        buffer[1] = frameType;
        buffer[2] = length;
        buffer[3] = checksum;
        buffer[4] = ETX;
    }
};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {
    uint8_t payload[BUF_SIZE];
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {
    uint8_t bootMessage[BUF_SIZE];
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {
    ReqFrame(uint8_t id) {
        frameType = REQUEST;
        length = 0;
        dataType = id;
        checksum = 0;  // TODO!!
    }

    void serialize(uint8_t* buffer) override {
        Frame::serialize(buffer)
        
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {
    AckFrame() {
        frameType = ACK;
        length = 0;
        checksum = 0;  // TODO!!
    }
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {
    NackFrame() {
        header = NACK;
        length = 0;
        checksum = 0;  // TODO!!
    }
};
