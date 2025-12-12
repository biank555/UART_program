#include "frames.h"	
#include "uart.h"

#define HEADER_SIZE 4
#define TAIL_SIZE 2

static uint8_t frameCounter = 0;



// ***** BASE FRAME ******

Frame::Frame(const uint8_t *data, const size_t len) {
    id = frameCounter++;
    length = HEADER_SIZE+TAIL_SIZE;
    checksum = 0;
}

void Frame::serialize(uint8_t* buffer) {
    buffer[0] = STX;
    buffer[1] = frameType;
    buffer[2] = id;
    buffer[3] = length;
    //		   <---- additional members go here
    //buffer[4] = checksum;
    buffer[5] = ETX;
}

void Frame::deserialize(uint8_t* buffer) {
    frameType = buffer[1];
    id = buffer[2];
    length = buffer[3];
    //checksum = buffer[4];
}




// ***** DATA PACKET FRAME ******

DataFrame::DataFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    frameType = DATA;
    const uint8_t *payload = data;
    length = HEADER_SIZE+len+TAIL_SIZE;
    checksum = 0; //TODO!!
}

void DataFrame::serialize(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        buffer[4+i] = payload[i];
    }
    buffer[HEADER_SIZE+length] = checksum;
    buffer[HEADER_SIZE+length+1] = ETX;
}

void DataFrame::deserialize(uint8_t* buffer) {

}




// ***** BOOT MSG FRAME ******

BootFrame::BootFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    frameType = BOOTMSG;
    const uint8_t *bootMessage = data;
    length = HEADER_SIZE+len+TAIL_SIZE;
}

void BootFrame::serialize(uint8_t* buffer) {

}

void BootFrame::deserialize(uint8_t* buffer) {

}




// ***** REQUEST FRAME ******

ReqFrame::ReqFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    frameType = REQUEST;
    length = len;
    const uint8_t *requests = data;
    checksum = 0;  // TODO!!
}

void ReqFrame::serialize(uint8_t* buffer) {

}

void ReqFrame::deserialize(uint8_t* buffer) {

}




// ***** ACK FRAME ******

AckFrame::AckFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    frameType = ACK;
    length = 0;
    checksum = 0;  // TODO!!
};




// ***** NACK FRAME ******


NackFrame::NackFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
        frameType = NACK;
        length = 0;
        checksum = 0;  // TODO!!
}

