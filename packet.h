//
// Created by pedrito on 06/03/19.
//

#ifndef BITMASK_PACKET_H
#define BITMASK_PACKET_H

// OP CODE MAX (65535)

#define OP_LOGIN 0x01
#define OP_REGISTER 0x0A
#define OP_HELLO 0xFFFF


typedef struct packet_s packet_t;

struct packet_s {
	unsigned char op_code[2];
	unsigned char *payload;
};

void setOpCode(packet_t *packet, int mask);
int getOpCode(unsigned char op_code[2]);

void writeD(unsigned char *payload, int value, int *offset);
void writeC(unsigned char *payload, int value, int *offset);
void writeS(unsigned char *payload, char *string, int *offset);

int readD(unsigned char *payload, int *offset);
int readC(unsigned char *payload, int *offset);
char *readS(unsigned char *payload, int *offset);

#endif //BITMASK_PACKET_H
