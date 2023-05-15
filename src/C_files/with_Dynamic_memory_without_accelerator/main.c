#include "Decrypt_functions.h"
#include "Encrypt_functions.h"
#include "Rijndael_functions.h"
#include "OCB_Defines.h"
#include "OCB_functions.h"
/**
    File name: OCB 
    Author: Basel Mansour
    Date: 01/02/2023
    resource:
        (1) https://web.cs.ucdavis.edu/~rogaway/ocb/ocb-faq.htm#describe-ocb
        (2) https://en.wikipedia.org/wiki/Rijndael_MixColumns
        (3) https://en.wikipedia.org/wiki/Rijndael_S-box
        (4) https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
        (5) https://datatracker.ietf.org/doc/html/draft-moskowitz-aes128-ocb-00
    Program description:
    This program represent the OCB algorithim basel on the advances Encryption Standart,
    thie OCB functions work with 1d arrays and the AES algorithim in my case works with 
    2d arrays so we needed to right functions to converto from 1d to 2d and vice versa.
*/


void error_Handler(enum OCB_status status);

int main()
{
    while (1) {
        char* ciphertext = NULL;
        char* reversed = NULL;
        int rval = 0;
        char* key = (char*)malloc((KEY_BLEN + 1) * sizeof(char));
        if (key == NULL)printf("Memory allocation error.\n\a");
        char* Nonce = (char*)malloc((NONCE_BLEN + 1) * sizeof(char));
        if (Nonce == NULL)printf("Memory allocation error.\n\a");
        char* plaintext = (char*)malloc(MAX_LENGTH * sizeof(char));
        if (plaintext == NULL)printf("Memory allocation error.\n\a");
        printf("#######################################\n");
        printf("Please enter the plaintext:\n");
        rval = scanf("%[^\n]%*c", plaintext);
        if (rval == 0)printf("scaning error\n");
        printf("Please enter the key:\n");
        rval = scanf("%[^\n]%*c", key);
        if (rval == 0)printf("scaning error\n");
        printf("Please enter the Nonce:\n");
        rval = scanf("%[^\n]%*c", Nonce);
        if (rval == 0)printf("scaning error\n");
        error_Handler(OCB_enc_dyc(plaintext, key, Nonce, &ciphertext, ENCRYPTION));
        error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, &reversed, DECRYPTION));
        printf("The plaintext is:\n%s\n", plaintext);
        printf("The key is:\n%s\n", key);
        printf("The nonce is:\n%s\n", Nonce);
        printf("The encrypte text is:\n%s\n", ciphertext);
        printf("The decrypted text is:\n%s\n", reversed);
        free(key);
        free(plaintext);
        free(Nonce);
        free(ciphertext);
        free(reversed);
    }
}

/*
* Input: this function takes as input enum OCB_status that represent the status of the operations.
* Output and functionality: the function rights a message to the stdout respectly to the current
    status (handles the errors if there is any).
*/
void error_Handler(enum OCB_status status)
{
    switch (status)
    {
    case SUCESS:
        printf("Success.\n");
        break;
    case FAILED:
        printf("An error has accured.\nPlease try again later.\n");
        break;
    case FOUND:
        break;
    case NOT_FOUND:
        printf("ntz not found.\nPlease try again later.\n");
        break;
    case MEMORY_ALLOCATING_ERROR:
        printf("Memory allocation error.\nPlease try again later.\n");
        break;
    case ZERO_PADDING_ERROR:
        printf("An error has accured while zero padding.\nPlease try again later.\n");
        break;
    case ARRAY_INITIATING_ERROR:
        printf("Array Initiate error.\nPlease try again later.\n");
        break;
    case ENCRYPTION_ERROR:
        printf("Encryption error.\nPlease try again later.\n");
        break;
    case PLAINNTEXT_TO_BLOCKS_ERROR:
        printf("An error has accured while converting the plaintext to blocks.\nPlease try again later.\n");
        break;
    case OCB_INIT_ERROR:
        printf("An error has accured while initiating the OCB.\nPlease try again later.\n");
        break;
    case NTZ_ERROR:
        printf("ntz not found.\nPlease try again later.\n");
        break;
    case UNKNOWN_MODE:
        printf("Unknown mode.\nPlease try again later.\n");
        break;
    case INVALID:
        printf("T and T' doesn't match.\nPlease try again later.\n");
        break;
    case TAG_REMOVING_ERROR:
        printf("An error has detected while spliting the ciphertext for decryption.\nPlease try again later.\n");
        break;
    case STRING_COPY_ERROR:
        printf("An erro has detected while copying a string..\nPlease try again later.\n");
        break;
    default:
        break;
    }
}
