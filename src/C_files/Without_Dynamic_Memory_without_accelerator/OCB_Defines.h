#ifndef OCB_DEFINES_H
#define OCB_DEFINES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "xil_printf.h"
#include "platform.h"
#define KEY_BLEN 33
#define TAG_BLEN 33
#define BLOCK_BLEN 33
#define NONCE_BLEN 33
#define BYTE_TO_BIT  16
#define STR_TO_1D_ARRAY	16
#define MAX_LENGTH	5000
#define MAX_BLOCKS_NUM	156
#define MAX_L_ARRAY_LENGTH	7


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
