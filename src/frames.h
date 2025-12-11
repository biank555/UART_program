#include <stdint.h>
#include <iostream>


enum FrameType : uint8_t {
    BOOTINFO,
    REQUEST
    DATA
    ACK
    NACK
};

enum DataType : uint8_t {
    TEMP
}


// ***** BASE FRAME ******

struct Frame {
    virtual uint8_t frameType;
    virtual uint8_t length;
    virtual uint8_t checksum;

    virtual void serialize(uint8_t* buffer);
};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {
    uint8_t payload[BUF_SIZE];
    DataFrame(uint8_t payload[BUF_SIZE]);
    serialize(uint8_t* buffer) override;
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {
    uint8_t bootMessage[BUF_SIZE];
    Bootframe();
    serialize(uint8_t* buffer) override;
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {
    DataType requestType;
    ReqFrame(uint8_t type);
    void serialize(uint8_t* buffer) override;
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {
    void AckFrame();
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {
    void NackFrame();
};

