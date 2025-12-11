//#include <stdint.h>
//#include <iostream>


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

    //members
    virtual uint8_t frameType;
    virtual uint8_t id;
    virtual uint8_t length;
    virtual uint8_t checksum;

    //functions
    virtual void serialize(uint8_t* buffer);
    virtual void deserialize(uint8_t* buffer);
};


// ***** DATA PACKET FRAME ******

struct DataFrame : public Frame {

    //members
    uint8_t *payload;

    //functions
    DataFrame(uint8_t *payload, size_t len);
    serialize(uint8_t* buffer) override;
};


// ***** BOOT MSG FRAME ******

struct BootFrame : public Frame {

    //members
    uint8_t *bootMessage;

    //functions
    Bootframe(uint8_t *msg, size_t len);
    serialize(uint8_t* buffer) override;
    deserialize(uint8_t* buffer) override;
};


// ***** REQUEST FRAME ******

struct ReqFrame : public Frame {

    //members
    DataType requestType;

    //functions
    ReqFrame(uint8_t *reqs, size_t len);
    serialize(uint8_t* buffer) override;
    deserialize(uint8_t* buffer) override;
};


// ***** ACK FRAME ******

struct AckFrame : public Frame {

    //functions
    void AckFrame();
};


// ***** NACK FRAME ******

struct NackFrame : public Frame {

    //functions
    void NackFrame();
};

