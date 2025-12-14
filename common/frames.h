#ifndef FRAMES_H
#define FRAMES_H

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>

#include <stdint.h>
//#include <iostream>
#include <cstddef>
//#include "sensors.h"

#endif // __ZEPHYR__

enum FrameType {
    BOOTMESSAGE,
    REQUEST,
    DATA,
    ACK,
    NACK,
    PING
};

static uint8_t frameCounter;
void frames_init(void);

// ***** BASE FRAME ******

struct Frame {

    uint8_t frameType;
    uint8_t id;
    uint8_t length;
    uint8_t checksum;

    public:
    Frame(uint8_t *data = nullptr, size_t len = 0);
    virtual void structToBitstream(uint8_t* buffer);
    virtual void bitstreamToStruct(uint8_t* buffer);
};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {

    uint8_t *payload;

    public:
    DataFrame( uint8_t *data,  size_t len);
    void structToBitstream(uint8_t* buffer) override;
    void bitstreamToStruct(uint8_t* buffer) override;
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {

    uint8_t *bootMessage;

    public:
    BootFrame( uint8_t *data,  size_t len);
    void structToBitstream(uint8_t* buffer) override;
    void bitstreamToStruct(uint8_t* buffer) override;
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {

    uint8_t *requests;

    public:
    ReqFrame( uint8_t *data,  size_t len);
    void structToBitstream(uint8_t* buffer) override;
    void bitstreamToStruct(uint8_t* buffer) override;
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {
    public:
    AckFrame( uint8_t *data,  size_t len);
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {
    public:
    NackFrame( uint8_t *data,  size_t len);
};

#endif


// ***** PING FRAME ******

struct PingFrame : public Frame {
    public:
    PingFrame( uint8_t *data, size_t len);
};
