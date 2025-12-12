#include "frames.h"
#include "uart.h"

#define HEADER_SIZE 4
#define TAIL_SIZE 2

static uint8_t frameCounter = 0;



// ***** BASE FRAME ******

Frame::Frame(const uint8_t *data, const size_t len) {

    length = HEADER_SIZE+TAIL_SIZE;


    id = frameCounter++;
    checksum = 0;
}

void Frame::structToBitstream(uint8_t* buffer) {
    buffer[0] = STX;
    buffer[1] = frameType;
    buffer[2] = id;
    buffer[3] = length;
    //		   <---- additional members go here
    //buffer[4] = checksum;
    buffer[5] = ETX;
}

void Frame::bitstreamToStruct(uint8_t* buffer) {
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


    *payload = data;
    length = HEADER_SIZE+len+TAIL_SIZE;
    checksum = 0; //TODO!!
}

void DataFrame::structToBitstream(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        buffer[4+i] = payload[i];
    }
    buffer[HEADER_SIZE+length] = checksum;
    buffer[HEADER_SIZE+length+1] = ETX;
}

void DataFrame::bitstreamToStruct(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        payload[i] = buffer[4+i];
    }
}




// ***** BOOT MSG FRAME ******

BootFrame::BootFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    *frameType = BOOTMESSAGE;

    bootMessage = data;
    length = HEADER_SIZE+len+TAIL_SIZE;
}

void BootFrame::structToBitstream(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        buffer[4+i] = bootMessage[i];
    }
    buffer[HEADER_SIZE+length] = checksum;
    buffer[HEADER_SIZE+length+1] = ETX;
}

void BootFrame::bitstreamToStruct(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        bootMessage[i] = buffer[4+i];
    }
}




// ***** REQUEST FRAME ******

ReqFrame::ReqFrame(const uint8_t *data, const size_t len)
    : Frame(data, len)
{
    frameType = REQUEST;

    *requests = data;
    length = len;
    checksum = 0;  // TODO!!
}

void ReqFrame::structToBitstream(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        buffer[4+i] = requests[i];
    }
    buffer[HEADER_SIZE+length] = checksum;
    buffer[HEADER_SIZE+length+1] = ETX;
}

void ReqFrame::bitstreamToStruct(uint8_t* buffer) {
    for (size_t i = 0; i < length; i++) {
        requests[i] = buffer[4+i];
    }
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

