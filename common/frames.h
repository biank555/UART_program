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

void frame_id_init(void);
uint8_t frame_id_next();

// ***** BASE FRAME ******

struct Frame {

    uint8_t frameType;
    uint8_t id;
    uint8_t payload_length;
    uint8_t checksum;

    public:
    Frame(uint8_t *data = nullptr, size_t payload_len = 0);

    virtual void bitstreamToStruct(uint8_t* rx_buffer);
    static void readFrame(uint8_t *rx_buffer); // -> destructor?
    //virtual void makeFrame(uint8_t *buffer, size_t payload_len); -> zie constructor
    virtual void structToBitstream(uint8_t* tx_buffer);


};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {

    uint8_t *payload;

    public:
    DataFrame( uint8_t *data,  size_t payload_len);
    void structToBitstream(uint8_t* tx_buffer) override;
    void bitstreamToStruct(uint8_t* rx_buffer) override;
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {

    uint8_t *message;

    public:
    BootFrame( uint8_t *data,  size_t payload_len);
    void structToBitstream(uint8_t* tx_buffer) override;
    void bitstreamToStruct(uint8_t* rx_buffer) override;
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {

    uint8_t *requests;

    public:
    ReqFrame( uint8_t *data,  size_t payload_len);
    void structToBitstream(uint8_t* tx_buffer) override;
    void bitstreamToStruct(uint8_t* rx_buffer) override;
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {
    public:
    AckFrame( uint8_t *data,  size_t payload_len);
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {
    public:
    NackFrame( uint8_t *data,  size_t payload_len);
};

#endif


// ***** PING FRAME ******

struct PingFrame : public Frame {
    public:
    PingFrame( uint8_t *data, size_t payload_len);
};
