//
// Created by pedrito on 06/03/19.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"

void setOpCode(packet_t *packet, int mask)
{
	packet->op_code[0] = 0;
	packet->op_code[1] = 0;
	packet->op_code[0] |= mask;
	packet->op_code[1] |= mask >> 8;
}

int getOpCode(unsigned char raw[2])
{
	int op_code = 0;
	op_code |= (raw[1] << 8 | raw[0]);
	return op_code;
}

void writeD(unsigned char *payload, int value, int *off)
{
	payload[(*off)++] |= value & 0xff;
	payload[(*off)++] |= value >> 8 & 0xff;
	payload[(*off)++] |= value >> 16 & 0xff;
	payload[(*off)++] |= value >> 24 & 0xff;
}

void writeC(unsigned char *payload, int value, int *off)
{
	payload[(*off)++] |= value & 0xff;
}

void writeS(unsigned char *payload, char *string, int *off)
{
	size_t len = strlen(string);
	memmove(&payload[(*off)], string, len);
	payload[*off + len] = 0;
	*off = *off + (int)len + 1;
}

int readC(unsigned char *payload, int *off)
{
	return payload[(*off)++] & 0xff;
}

int readD(unsigned char *payload, int *off)
{
	int result = payload[(*off)++] & 0xff;
	result |= payload[(*off)++] << 8 & 0xff00;
	result |= payload[(*off)++] << 0x10 & 0xff0000;
	result |= payload[(*off)++] << 0x18 & 0xff000000;
	return result;
}

char *readS(unsigned char *payload, int *off)
{
	size_t i;
	char *str;

	for (i = 0; payload[*off + i] != 0; i++);
	str = malloc(sizeof(char) * (i + 1));
	str = memmove(str, &payload[*off], i + 1);
	*off = *off + (int)i + 1;
	return str;
}