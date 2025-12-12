#include "frames.h"
#include "uart.h"
#include <zephyr/kernel.h>

#define HEADER_SIZE 4
#define TAIL_SIZE 2

void frames_init(void) {
    frameCounter = 0;
}



// ***** BASE FRAME ******

Frame::Frame( uint8_t *data,  size_t len) {

    length = HEADER_SIZE+TAIL_SIZE;


    id = frameCounter++;
    printf("frameCounter = %d\n", frameCounter);
    checksum = 0;
}

void Frame::structToBitstream(uint8_t* buffer) {
    buffer[0] = STX;
    buffer[1] = frameType;
    buffer[2] = id;
    buffer[3] = length;
    //		   <---- additional members go here
    buffer[4] = checksum;//TODO implement!!
    buffer[5] = ETX;
}

void Frame::bitstreamToStruct(uint8_t* buffer) {
    frameType = buffer[1];
    id = buffer[2];
    length = buffer[3];
    checksum = buffer[4];//TODO:expand!!
}



// ***** DATA PACKET FRAME ******

DataFrame::DataFrame( uint8_t *data,  size_t len)
    : Frame(data, len)
{
    frameType = DATA;


    payload = data;
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

BootFrame::BootFrame( uint8_t *data,  size_t len)
    : Frame(data, len)
{
    frameType = BOOTMESSAGE;

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

ReqFrame::ReqFrame( uint8_t *data,  size_t len)
    : Frame(data, len)
{
    frameType = REQUEST;

    requests = data;
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

AckFrame::AckFrame( uint8_t *data,  size_t len)
    : Frame(data, len)
{
    frameType = ACK;


    checksum = 0;  // TODO!!
};




// ***** NACK FRAME ******


NackFrame::NackFrame( uint8_t *data,  size_t len)
    : Frame(data, len)
{
    frameType = NACK;


    checksum = 0;  // TODO!!
}




// ***** PING FRAME ******
PingFrame::PingFrame( uint8_t *data, size_t len)
    : Frame(data, len)
{
    frameType = PING;


    checksum = 0;  // TODO!!
}
