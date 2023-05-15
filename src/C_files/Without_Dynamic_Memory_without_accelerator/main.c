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
        char plaintext[MAX_LENGTH] = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f2021";
        char key[KEY_BLEN] = "000102030405060708090a0b0c0d0e0f";
        char Nonce[NONCE_BLEN] = "00000000000000000000000000000001";
        char ciphertext[MAX_LENGTH] ="";
        char reversed[MAX_LENGTH] ="";
        error_Handler(OCB_enc_dyc(plaintext, key, Nonce, ciphertext, ENCRYPTION));
        error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, reversed, DECRYPTION));
        printf("The plaintext is:\n%s\n", plaintext);
        printf("The key is:\n%s\n", key);
        printf("The nonce is:\n%s\n", Nonce);
        printf("The encrypte text is:\n%s\n", ciphertext);
        printf("The decrypted text is:\n%s\n\n\n", reversed);

        /*
        print(plaintext);
        print(key);
        print( Nonce);
        print(ciphertext);
        print(reversed);
/*
        strcpy(plaintext,"000102");
        strcpy(key,"000102030405060708090a0b0c0d0e0f");
        strcpy(Nonce,"00000000000000000000000000000001");
        error_Handler(OCB_enc_dyc(plaintext, key, Nonce, &ciphertext, ENCRYPTION));
        error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, &reversed, DECRYPTION));
        print("The plaintext is:\n%s\n", plaintext);
        print("The key is:\n%s\n", key);
        print("The nonce is:\n%s\n", Nonce);
        print("The encrypte text is:\n%s\n", ciphertext);
        print("The decrypted text is:\n%s\n\n\n", reversed);

        strcpy(plaintext,"000102030405060708090a0b0c0d0e0f");
        strcpy(key,"000102030405060708090a0b0c0d0e0f");
        strcpy(Nonce,"00000000000000000000000000000001");
        error_Handler(OCB_enc_dyc(plaintext, key, Nonce, &ciphertext, ENCRYPTION));
        error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, &reversed, DECRYPTION));
        print("The plaintext is:\n%s\n", plaintext);
        print("The key is:\n%s\n", key);
        print("The nonce is:\n%s\n", Nonce);
        print("The encrypte text is:\n%s\n", ciphertext);
        print("The decrypted text is:\n%s\n\n\n", reversed);


        strcpy(plaintext,"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
        strcpy(key,"000102030405060708090a0b0c0d0e0f");
        strcpy(Nonce,"00000000000000000000000000000001");
        error_Handler(OCB_enc_dyc(plaintext, key, Nonce, &ciphertext, ENCRYPTION));
        error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, &reversed, DECRYPTION));
        print("The plaintext is:\n%s\n", plaintext);
        print("The key is:\n%s\n", key);
        print("The nonce is:\n%s\n", Nonce);
        print("The encrypte text is:\n%s\n", ciphertext);
        print("The decrypted text is:\n%s\n\n\n", reversed);
*/


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
        printf("An error has detected while copying a string..\nPlease try again later.\n");
        break;
    default:
        break;
    }
}

