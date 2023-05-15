#ifndef ENCRYPT_FUNCTIONS_H
#define ENCRYPT_FUNCTIONS_H
#include "AES_defines.h"


enum status round_keys_generator(unsigned char key[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER]);
enum status AESEncryption(unsigned char plainText[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char cipherText[][STATE_COLUMNS_NUMBER]);
#endif // !ENCRYPT_FUNCTIONS_H

