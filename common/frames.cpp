#include "PLATFORM_HAL.h"
#include "frames.h"

#include "uart.h"

#ifdef __ZEPHYR__
#endif

#define HEADER_SIZE 4
#define TAIL_SIZE 2

void frame_id_init() {
    int frameCounter = 0;
    //hal_print("int frameCounter = 0;\n");//!!
    return;
}



// ***** BASE FRAME ******

Frame::Frame( uint8_t *data, size_t payload_len) {

    static int frameCounter = 0;

    payload_payload_length = payload_len;

    if(frameCounter > 255) {
	frameCounter = 0;
    }
    id = frameCounter++;
    printf("id = frameCounter = %x \t testing: %x\n", frameCounter, id);
    checksum = 5;
}

void Frame::structToBitstream(uint8_t* tx_buffer) {
    tx_buffer[0] = STX;
    tx_buffer[1] = frameType;
    tx_buffer[2] = id;
    tx_buffer[3] = payload_payload_length;
    //		   <---- additional members go here
    tx_buffer[4] = checksum;//TODO implement!!
    tx_buffer[5] = ETX;
    printf("first we make a base bitstream");
    for(uint8_t i = 0; i < 10; i++) {
	printf("tx_buffer[%d] = %x\n", i, tx_buffer[i]);
    }
}

void Frame::bitstreamToStruct(uint8_t* rx_buffer) {
    frameType = rx_buffer[1];
    id = rx_buffer[2];
    payload_payload_length = rx_buffer[3];
    checksum = rx_buffer[4];//TODO:implement!!
}

void Frame::readFrame(uint8_t *rx_buffer) { //!!


    //BootFrame bootFrame(buffer, payload_len);
    //ReqFrame reqFrame(buffer, payload_len);
    //DataFrame dataFrame(buffer, payload_len);
    //AckFrame ackFrame(buffer, payload_len);
    //NackFrame nackFrame(buffer, payload_len);
    //PingFrame pingFrame(buffer, payload_len);

    uint8_t *in_frame = rx_buffer;
    uint8_t in_frame_type = rx_buffer[1];
    uint8_t in_frame_id = rx_buffer[2];

    switch (rx_buffer[1]) {
	case BOOTMESSAGE: {
	    BootFrame bootFrame(rx_buffer,0);
	    bootFrame.bitstreamToStruct(rx_buffer);
	    //send ACK
	    printf("%x",bootFrame.message);
	    break;
	}

	case REQUEST: {
	    ReqFrame reqFrame(rx_buffer,0);
	    reqFrame.bitstreamToStruct(rx_buffer);
	    //send ACK?
	    //sensor measurements
            DataFrame dataFrame(tx_buffer,0);
	    dataFrame.id = reqFrame.id;
	    dataFrame.payload = reqFrame.requests;
	    break;
	}

	case DATA: {
	    DataFrame dataFrame(rx_buffer,0);
	    dataFrame.bitstreamToStruct(rx_buffer);
	    AckFrame ackFrame(tx_buffer,0);
            ackFrame.id = dataFrame.id;
	    uart_transmit(tx_buffer,ackFrame.payload_payload_length); // send ACK
	    break;
	}

	case ACK: {
	    AckFrame ackFrame(rx_buffer,0);
	    ackFrame.bitstreamToStruct(rx_buffer);
	    //TODO!!
	    break;
	}

	case NACK: {//TODO:implement!!
	    NackFrame nackFrame(tx_buffer,0);
	    nackFrame.bitstreamToStruct(tx_buffer);
	    break;
	}

	case PING: {
	    PingFrame pingFrame(rx_buffer,0);
	    pingFrame.bitstreamToStruct(rx_buffer);
            AckFrame ackFrame(tx_buffer,0);
            ackFrame.id = pingFrame.id;
            uart_transmit(tx_buffer,ackFrame.payload_payload_length); // send ACK
	    break;
	}
    }
}

// ***** DATA PACKET FRAME ******

DataFrame::DataFrame( uint8_t *data, size_t payload_len)
    : Frame(data,payload_len)
{
    frameType = DATA;


    payload = data;
    payload_payload_length = payload_len;
}

void DataFrame::structToBitstream(uint8_t* tx_buffer) {
    for (size_t i = 0; i < payload_payload_length; i++) {
        tx_buffer[HEADER_SIZE+i] = payload[i];
    }
    tx_buffer[HEADER_SIZE+payload_payload_length] = checksum;
    tx_buffer[HEADER_SIZE+payload_payload_length+1] = ETX;
}

void DataFrame::bitstreamToStruct(uint8_t* rx_buffer) {
    for (size_t i = 0; i < payload_payload_length; i++) {
        payload[i] = rx_buffer[HEADER_SIZE+i];
    }
}




// ***** BOOT MSG FRAME ******

BootFrame::BootFrame( uint8_t *data,  size_t payload_len)
    : Frame(data, payload_len)
{
    frameType = BOOTMESSAGE;

    message = data;

    printf("Bootframe made:\n");
    //hal_print((message));
    payload_payload_length = payload_len;

}

void BootFrame::structToBitstream(uint8_t* tx_buffer)
{
    Frame::structToBitstream(tx_buffer);
    for (size_t i = 0; i < payload_payload_length; i++) {
        tx_buffer[HEADER_SIZE+i] = message[i];
    }
    tx_buffer[HEADER_SIZE+payload_payload_length] = checksum;
    tx_buffer[HEADER_SIZE+payload_payload_length+1] = ETX;
    printf("boot bitstream made:\n");
    for(int i = 0; i < 10; i++) {
        printf("tx_buffer[%d] = %x\n", i, tx_buffer[i]);
    }

    //Serial.println(sizeof(msg));
    //uart_transmit(buffer, HEADER_SIZE+payload_payload_length);

}

void BootFrame::bitstreamToStruct(uint8_t* rx_buffer) {
    for (size_t i = 0; i < payload_payload_length; i++) {
        message[i] = rx_buffer[HEADER_SIZE+i];
    }
}




// ***** REQUEST FRAME ******

ReqFrame::ReqFrame( uint8_t *data,  size_t payload_len)
    : Frame(data, payload_len)
{
    frameType = REQUEST;

    requests = data;
    payload_payload_length = payload_len;
}

void ReqFrame::structToBitstream(uint8_t* tx_buffer) {
    for (size_t i = 0; i < payload_payload_length; i++) {
        tx_buffer[HEADER_SIZE+i] = requests[i];
    }
    tx_buffer[HEADER_SIZE+payload_payload_length] = checksum;
    tx_buffer[HEADER_SIZE+payload_payload_length+1] = ETX;
}

void ReqFrame::bitstreamToStruct(uint8_t* rx_buffer) {
    for (size_t i = 0; i < payload_payload_length; i++) {
        requests[i] = rx_buffer[HEADER_SIZE+i];
    }
}




// ***** ACK FRAME ******

AckFrame::AckFrame( uint8_t *data,  size_t payload_len)
    : Frame(data, payload_len)
{
    frameType = ACK;

};




// ***** NACK FRAME ******


NackFrame::NackFrame( uint8_t *data,  size_t payload_len)
    : Frame(data, payload_len)
{
    frameType = NACK;

}




// ***** PING FRAME ******
PingFrame::PingFrame( uint8_t *data, size_t payload_len)
    : Frame(data, payload_len)
{
    frameType = PING;

}





// ************ TROUBLESHOOT ***************

//
