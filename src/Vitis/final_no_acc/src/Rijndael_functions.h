#ifndef RIJNDAEL_FUNCTIONS
#define RIJNDAEL_FUNCTIONS
#include "AES_defines.h"

enum status R_Boxes(unsigned char number, unsigned char* index, enum Rijndael_Boxes R_Box);
enum status round_keys_generator(unsigned char key[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER]);

#endif // !RIJNDAEL_FUNCTIONS

