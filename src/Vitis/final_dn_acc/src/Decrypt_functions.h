#ifndef DECRYPT_FUNCTIONS_H
#define DECRYPT_FUNCTIONS_H
#include "AES_defines.h"


enum status AESDecryption(unsigned char plainText[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char cipherText[][STATE_COLUMNS_NUMBER]);


#endif // !DECRYPT_FUNCTIONS_H

