#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

// Baudrate settings are defined in <asm/termbits.h>, which is
// included by <termios.h>
#define _POSIX_SOURCE 1 // POSIX compliant source

#define BUF_SIZE 5
#define FLAG 0x7E
#define ADDR_SEND 0x03
#define ADDR_RECV 0X01
#define CONTROL_SET 0x03
#define CONTROL_UA 0x07
#define CONTROL_I0 0x00
#define CONTROL_I1 0x40 
#define CONTROL_REJ0 0x01
#define CONTROL_REJ1 0x81
#define CONTROL_RR0 0x05
#define CONTROL_RR1 0x85
#define CONTROL_DISC 0x0B
#define ESCAPE_CHAR 0x7d
#define ESCAPE_FLAG 0x5e
#define ESCAPE_ESCAPE 0x5d

extern bool alarm_enabled;
extern int alarm_count;
extern bool information_toggle;


typedef enum {
    PACKET_BEGIN = 0,
    ADDR,
    CONTROL,
    BCC,
    DATA,
    BCC2,
    PACKET_END,
    SUCCESS
} packet_status_t;

typedef struct packet_t {
    unsigned char addr;
    unsigned char control;
    unsigned char bcc;
    unsigned char * data;
    unsigned char bcc2;
    int data_size;
    int alloc_size;
    packet_status_t status;
} packet_t;


void init_packet(packet_t * packet);
int write_command(int fd, bool tx, char command);
int write_data(int fd, unsigned char * buf, int size);

void read_packet(int fd, packet_t * packet, bool tx);

bool validate_packet(packet_t * packet);
void alarm_handler(int signal);

unsigned char * stuff_packet(unsigned char * buf, int * size);
void destuff_packet(packet_t * packet);
#endif
