//#define _CRT_SECURE_NO_WARNINGS
#ifndef OCB_DEFINES_H
#define OCB_DEFINES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "platform.h"
#include "xil_printf.h"
#define KEY_BLEN 32
#define BLOCK_BLEN 32
#define NONCE_BLEN 32
#define BYTE_TO_BIT  16
#define STR_TO_1D_ARRAY	16
#define MAX_LENGTH	1000


enum OCB_status
{
	SUCESS,
	FAILED,
	FOUND,
	NOT_FOUND,
	MEMORY_ALLOCATING_ERROR,
	ZERO_PADDING_ERROR,
	ARRAY_INITIATING_ERROR,
	ENCRYPTION_ERROR,
	PLAINNTEXT_TO_BLOCKS_ERROR,
	OCB_INIT_ERROR,
	NTZ_ERROR,
	UNKNOWN_MODE,
	INVALID,
	TAG_REMOVING_ERROR,
	STRING_COPY_ERROR,
	EMPTY_STRING
};
enum mode
{
	ENCRYPTION,
	DECRYPTION
};





#endif // !OCB_DEFINES_H
