#include <iostream>
#include <stdint-gcc.h>
#include <unistd.h>
#include <stdint.h>
#include "libusb/libusb.h"

#define STEAM_CONTROLLER_MAGIC_PERIOD_RATIO 495483.0

using namespace std;

double midiFrequency[128]  = {8.1758, 8.66196, 9.17702, 9.72272, 10.3009, 10.9134, 11.5623, 12.2499, 12.9783, 13.75, 14.5676, 15.4339, 16.3516, 17.3239, 18.354, 19.4454, 20.6017, 21.8268, 23.1247, 24.4997, 25.9565, 27.5, 29.1352, 30.8677, 32.7032, 34.6478, 36.7081, 38.8909, 41.2034, 43.6535, 46.2493, 48.9994, 51.9131, 55, 58.2705, 61.7354, 65.4064, 69.2957, 73.4162, 77.7817, 82.4069, 87.3071, 92.4986, 97.9989, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.5, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760, 1864.66, 1975.53, 2093, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520, 3729.31, 3951.07, 4186.01, 4434.92, 4698.64, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040, 7458.62, 7902.13, 8372.02, 8869.84, 9397.27, 9956.06, 10548.1, 11175.3, 11839.8, 12543.9};

typedef struct {
    unsigned int delay;
    unsigned int note;
} noteStruct;

noteStruct noteArray0[] = {{3763,0},{250,67},{249,66},{250,64},{251,64},{249,66},{2496,0},{250,62},{247,67},{1,0},{251,66},{249,64},{251,64},{249,66},{748,0},{248,62},{270,0},{233,64},{382,57},{1613,0},{250,59},{498,64},{249,66},{252,67},{498,0},{250,64},{250,61},{250,0},{498,62},{748,64},{251,57},{250,57},{281,0},{499,66},{2247,0},{249,67},{248,66},{250,64},{249,64},{250,66},{2497,0},{251,62},{248,67},{250,66},{248,64},{253,64},{497,0},{250,66},{250,62},{501,0},{248,64},{250,57},{1995,0},{500,64},{248,66},{252,67},{498,0},{249,64},{251,61},{499,0},{249,62},{498,64},{250,57},{250,62},{251,64},{248,65},{250,64},{250,62},{248,60},{498,0},{253,57},{250,58},{499,60},{510,65},{238,64},{250,62},{284,62},{249,60},{251,62},{246,60},{1,0},{500,60},{498,60},{248,57},{249,58},{499,60},{503,65},{246,67},{251,65},{249,64},{1,0},{250,62},{271,62},{228,64},{498,65},{500,65},{249,67},{250,69},{250,70},{247,70},{500,69},{499,67},{253,65},{249,67},{248,69},{251,69},{500,67},{497,65},{249,62},{306,60},{207,62},{239,64},{246,65},{501,64},{250,65},{248,66},{252,66},{6766,0},{250,57},{254,67},{245,66},{252,64},{251,64},{498,66},{2497,0},{254,67},{245,66},{253,64},{247,64},{496,0},{250,66},{499,62},{501,64},{251,57},{1996,0},{498,64},{249,66},{251,67},{498,0},{249,64},{251,61},{498,0},{250,62},{749,64},{250,57},{249,57},{249,0},{752,66},{1744,0},{257,64},{244,71},{250,69},{248,67},{252,67},{247,69},{2527,0},{251,64},{250,71},{249,69},{260,67},{238,67},{500,0},{248,69},{254,66},{496,0},{250,67},{251,64},{1996,0},{498,64},{254,66},{768,67},{475,64},{500,61},{251,62},{497,64},{249,57},{250,62},{262,64},{257,65},{229,64},{251,62},{250,60},{499,0},{250,57},{250,58},{502,60},{497,65},{250,64},{250,62},{249,62},{250,60},{249,62},{250,60},{500,60},{499,60},{248,57},{250,58},{500,60},{498,65},{250,67},{249,65},{249,64},{1,0},{249,62},{249,62},{249,64},{503,65},{496,65},{280,67},{249,69},{253,70},{250,70},{500,69},{498,67},{248,65},{252,67},{250,69},{250,69},{248,67},{254,65},{496,65},{246,62},{254,60},{247,62},{248,64},{250,65},{501,64},{249,65},{250,66},{250,66},{6990,0},{247,67},{253,66},{246,64},{252,64},{497,66},{2246,0},{251,57},{247,67},{251,66},{250,64},{253,64},{495,0},{250,66},{251,62},{527,0},{251,64},{250,57},{1998,0},{499,64},{249,66},{749,67},{500,64},{498,61},{252,62},{745,64},{251,57},{251,57},{249,0},{749,66},{1996,0},{251,71},{248,69},{251,67},{251,67},{248,0},{749,69},{1998,0},{246,71},{253,69},{250,67},{249,67},{496,0},{256,69},{246,66},{498,0},{251,67},{248,64},{2019,0},{476,64},{280,66},{751,67},{501,64},{498,61},{250,62},{498,64},{250,57},{250,62},{250,64},{247,65},{251,64},{249,62},{252,60},{497,0},{249,57},{253,58},{498,60},{501,65},{247,64},{250,62},{254,62},{246,60},{249,62},{249,60},{500,60},{499,60},{250,57},{250,58},{496,60},{501,65},{253,67},{259,65},{249,64},{241,62},{246,62},{251,64},{500,65},{499,65},{248,67},{251,69},{246,70},{253,70},{247,69},{250,67},{501,67},{253,65},{247,67},{249,69},{250,69},{246,67},{254,65},{499,65},{247,62},{251,60},{249,62},{251,64},{247,65},{499,64},{250,65},{249,66},{253,66},{1527,0},{249,69},{251,69},{250,71},{248,69},{249,66},{499,62},{249,64},{250,66},{263,66},{1234,0},{251,69},{249,69},{249,69},{252,71},{249,69},{250,66},{501,62},{247,64},{249,66},{252,66},{1246,0},{250,69},{249,69},{249,69},{250,71},{250,69},{250,66},{500,62},{247,64},{250,66},{255,66},{1493,0},{249,69},{252,69},{248,71},{250,69},{250,66},{499,62},{249,64},{249,66},{253,66},{1245,0},{250,69},{250,69},{251,69},{248,71},{248,69},{251,66},{498,62},{275,64},{233,66},{244,66},{1276,0},{251,67},{251,69},{250,69},{1248,0},{247,67},{249,66},{251,66},{47,0}};


void delay_ms(unsigned int ms){
    for(; ms > 0 ; ms --)
        usleep(1000);
}

int playNoteOnSteamController(libusb_device_handle *dev_handle, unsigned int note,unsigned int delay ){
    unsigned char dataBlob[64] = {0x8f,
                                  0x07,
                                  0x00, //Trackpad select : 0x01 = left, 0x00 = right
                                  0xff, //LSB Pulse High Duration
                                  0xff, //MSB Pulse High Duration
                                  0xff, //LSB Pulse Low Duration
                                  0xff, //MSB Pulse Low Duration
                                  0xff, //LSB Pulse repeat count
                                  0x04, //MSB Pulse repeat count
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    double frequency = midiFrequency[note];
    double period = 1.0 / frequency;
    uint16_t periodCommand = period * STEAM_CONTROLLER_MAGIC_PERIOD_RATIO;

    double duration = delay / 1000.0;
    uint16_t repeatCount = duration / period;

    cout << "Frequency : " <<frequency << ", Period : "<<periodCommand << ", Repeat : "<< repeatCount <<"\n";

    dataBlob[3] = periodCommand % 0xff;
    dataBlob[4] = periodCommand / 0xff;
    dataBlob[5] = periodCommand % 0xff;
    dataBlob[6] = periodCommand / 0xff;
    dataBlob[7] = repeatCount % 0xff;
    dataBlob[8] = repeatCount / 0xff;

    int r;
    r = libusb_control_transfer(dev_handle,0x21,9,0x0300,2,dataBlob,64,1000);
    if(r < 0) {
        cout<<"Command Error "<<r<<endl;
        return 1;
    }

    dataBlob[2] = 0x01;
    r = libusb_control_transfer(dev_handle,0x21,9,0x0300,2,dataBlob,64,1000);
    if(r < 0) {
        cout<<"Command Error "<<r<<endl;
        return 1;
    }
    return 0;
}

int main()
{
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = NULL; //a libusb session
    int r; //for return values
    unsigned int i;

    r = libusb_init(&ctx); //initialize the library for the session we just declared
    if(r < 0) {
        cout<<"Init Error "<<r<<endl;
        return 1;
    }

    libusb_set_debug(ctx, 3);

    dev_handle = libusb_open_device_with_vid_pid(ctx, 0x28DE, 0x1102); // Wired Steam Controller VID & PID
    if(dev_handle == NULL){
        cout<<"Cannot open device"<<endl;
        return 1;
    }


    r = libusb_claim_interface(dev_handle,2);
    if(r < 0) {
        cout<<"Claim Error "<<r<<endl;
        return 1;
    }

    for(i = 0 ; i < (sizeof(noteArray0) / sizeof(noteStruct)) ; i++){
        unsigned int note = noteArray0[i].note;
        unsigned int delay = noteArray0[i].delay;

        if(note != 0){
            r = playNoteOnSteamController(dev_handle,note,delay);
            if(r != 0)
                return 1;
        }
        cout << "Playing : "<<note<<"\n";
        delay_ms(delay);
    }


    /*unsigned char data[64] = {0x8f,
                              0x07,
                              0x01, //Trackpad select : 0x01 = left, 0x00 = right
                              0xff, //LSB Pulse High Duration
                              0xff, //MSB Pulse High Duration
                              0xff, //LSB Pulse Low Duration
                              0xff, //MSB Pulse Low Duration
                              0xff, //LSB Pulse repeat count
                              0x04, //MSB Pulse repeat count
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    while(1){
        r = libusb_control_transfer(dev_handle,0x21,9,0x0300,2,data,64,1000);
        if(r < 0) {
            cout<<"Command Error "<<r<<endl;
            return 1;
        }
        else {
            cout<<"Command Success "<<r<<endl;
        }
        std::cin.ignore();
    }
    */
    return 0;
}
