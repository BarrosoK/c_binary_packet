#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "packet.h"

const unsigned char option0 = 0x1; // 0000 0001 
const unsigned char option1 = 0x2; // 0000 0010
const unsigned char option2 = 0x4; // 0000 0100
const unsigned char option3 = 0x8; // 0000 1000
const unsigned char option4 = 0x10; // 0001 0000
const unsigned char option5 = 0x20; // 0010 0000
const unsigned char option6 = 0x40; // 0100 0000
const unsigned char option7 = 0x80; // 1000 0000

void login(packet_t *packet)
{
	int offset = 0;
	char *username = readS(packet->payload, &offset);
	char *password = readS(packet->payload, &offset);
	int age = readD(packet->payload, &offset);

	printf("%s %s (%d)\n", username, password, age);
}

int main()
{
	packet_t packet;

	setOpCode(&packet, OP_HELLO);
	printf("%d\n", getOpCode(packet.op_code));

	packet.payload = malloc(sizeof(char) * 50);

	int offset = 0;

	writeC(packet.payload, 'P', &offset);
	writeD(packet.payload, 42, &offset);
	writeS(packet.payload, "fdp", &offset);
	writeS(packet.payload, "oh non", &offset);
	writeD(packet.payload, 13, &offset);
	writeS(packet.payload, "dernier test !", &offset);

	offset = 0;

	printf("%c\n",readC(packet.payload, &offset));
	printf("%d\n",readD(packet.payload, &offset));
	printf("%s\n",readS(packet.payload, &offset));
	printf("%s\n",readS(packet.payload, &offset));
	printf("%d\n",readD(packet.payload, &offset));
	printf("%s\n",readS(packet.payload, &offset));

	return 0;
}