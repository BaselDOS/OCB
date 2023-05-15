#ifndef AES_DEFINES_H
#define AES_DEFINES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"


#define RIJNDAEL_ARRAYS_LENGTH 256
#define RIJNDAEL_ROW_LENGTH 16
#define RIJNDAEL_RCON_LENGTH 10
#define AES_ROUND_NUMBER 10
#define ROUND_KEYS_NUMBER  11
#define STATE_ROWS_NUMBER 4
#define STATE_COLUMNS_NUMBER 4
enum status
{
	PASS,
	ERROR,
    R_S_BOX_ERROR,
    ALLOCATING_MEMORY_ERROR,
    KEYS_GENERATING_ERROR
};
enum Rijndael_Boxes
{
    sub,
    isub,
    mul2,
    mul3,
    mul9,
    mul11,
    mul13,
    mul14
};


#endif // !AES_DEFINES_H

