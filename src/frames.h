#ifndef FRAMES_H
#define FRAMES_H

#include <stdint.h>
//#include <iostream>
#include <cstddef>

enum FrameType {
    BOOTMSG,
    REQUEST,
    DATA,
    ACK,
    NACK
};

enum DataType {
    TEMP
};


// ***** BASE FRAME ******

struct Frame {

    //members
    uint8_t frameType;
    uint8_t id;
    uint8_t length;
    uint8_t checksum;

    public:
    //functions
    Frame(const uint8_t *data, const size_t len);
    virtual void serialize(uint8_t* buffer);
    virtual void deserialize(uint8_t* buffer);
};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {

    //members
    uint8_t *payload;

    //functions
    DataFrame(const uint8_t *data, const size_t len);
    void serialize(uint8_t* buffer) override;
    void deserialize(uint8_t* buffer) override;
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {

    //members
    uint8_t *bootMessage;

    //functions
    BootFrame(const uint8_t *data, const size_t len);
    void serialize(uint8_t* buffer) override;
    void deserialize(uint8_t* buffer) override;
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {

    //members
    DataType requests;

    //functions
    ReqFrame(const uint8_t *data, const size_t len);
    void serialize(uint8_t* buffer) override;
    void deserialize(uint8_t* buffer) override;
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {
    public:
    //functions
    AckFrame(const uint8_t *data, const size_t len);
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {

    //functions
    NackFrame(const uint8_t *data, const size_t len);
};

#endif


