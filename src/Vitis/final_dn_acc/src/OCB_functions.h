#ifndef OCB_FUNCTIONS_H
#define OCB_FUNCTIONS_H

#include "OCB_Defines.h"
#include "AES_defines.h"



enum OCB_status OCB_enc_dyc(char plain_or_cipher[], char key[], char nonce[], char ** cipher_or_plain,enum mode ENC_OR_DEC);

#endif // !OCB_FUNCTIONS_H
