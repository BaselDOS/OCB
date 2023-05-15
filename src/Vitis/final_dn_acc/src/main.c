//#define _CRT_SECURE_NO_WARNINGS

#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "Decrypt_functions.h"
#include "Encrypt_functions.h"
#include "Rijndael_functions.h"
#include "OCB_Defines.h"
#include "OCB_functions.h"
#include "xtmrctr.h"

#define TIMER_DEVICE_ID  XPAR_AXI_TIMER_0_DEVICE_ID

XTmrCtr tI;
XTmrCtr_Config *tC;
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
void tmrInit();

int main()
{

	init_platform();
	tmrInit();
	XTmrCtr_Stop(&tI,0);
	XTmrCtr_SetResetValue(&tI,0,0);
	//XtmrCtr_SetOpsions(&tI,0,XTC_DOWN_COUNT_OPTION);
	XTmrCtr_Start(&tI,0);

	char* ciphertext = NULL;
	char* reversed = NULL;
	char* key = (char*)malloc((KEY_BLEN + 1) * sizeof(char));
	if (key == NULL)printf("Memory allocation error.\n\a");
	char* plaintext = (char*)malloc(MAX_LENGTH * sizeof(char));
	if (plaintext == NULL)printf("Memory allocation error.\n\a");
	char* Nonce = (char*)malloc((NONCE_BLEN + 1) * sizeof(char));
	if (Nonce == NULL)printf("Memory allocation error.\n\a");

	/*
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
	*/

	//strcpy(plaintext,"\0");
	//strcpy(plaintext,"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f2021\0");
	//strcpy(plaintext,"000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f\0");
	//strcpy(plaintext,"000102\0");
	//strcpy(plaintext,"000102030405060708090a0b0c0d0e0f\0");
	//strcpy(plaintext,"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\0");
	strcpy(plaintext,"000102030405060708090a0b0c0d0e0f10111213\0");

	strcpy(key,"000102030405060708090a0b0c0d0e0f\0");
	strcpy(Nonce,"00000000000000000000000000000001\0");

	error_Handler(OCB_enc_dyc(plaintext, key, Nonce, &ciphertext, ENCRYPTION));
	error_Handler(OCB_enc_dyc(ciphertext, key, Nonce, &reversed, DECRYPTION));

	print("The plaintext is: ");
	print (plaintext);
	print("\n");
	print("The key is: ");
	print(key);
	print("\n");
	print("The nonce is: ");
	print(Nonce);
	print("\n");
	print("The encrypte text is: ");
	print(ciphertext);
	print("\n");
	print("The decrypted text is: ");
	print(reversed);
	print("\n\n");


	free(key);
	free(plaintext);
	free(Nonce);
	free(ciphertext);
	free(reversed);

	u32 count =XTmrCtr_GetValue(&tI,0);
    xil_printf("The number of cycles required is %0d\n",count);
    cleanup_platform();
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
        print("Success.\n");
        break;
    case FAILED:
        print("An error has accured.\nPlease try again later.\n");
        break;
    case FOUND:
        break;
    case NOT_FOUND:
        print("ntz not found.\nPlease try again later.\n");
        break;
    case MEMORY_ALLOCATING_ERROR:
        print("Memory allocation error.\nPlease try again later.\n");
        break;
    case ZERO_PADDING_ERROR:
        print("An error has accured while zero padding.\nPlease try again later.\n");
        break;
    case ARRAY_INITIATING_ERROR:
        print("Array Initiate error.\nPlease try again later.\n");
        break;
    case ENCRYPTION_ERROR:
        print("Encryption error.\nPlease try again later.\n");
        break;
    case PLAINNTEXT_TO_BLOCKS_ERROR:
        print("An error has accured while converting the plaintext to blocks.\nPlease try again later.\n");
        break;
    case OCB_INIT_ERROR:
        print("An error has accured while initiating the OCB.\nPlease try again later.\n");
        break;
    case NTZ_ERROR:
        print("ntz not found.\nPlease try again later.\n");
        break;
    case UNKNOWN_MODE:
        print("Unknown mode.\nPlease try again later.\n");
        break;
    case INVALID:
        print("T and T' doesn't match.\nPlease try again later.\n");
        break;
    case TAG_REMOVING_ERROR:
        print("An error has detected while spliting the ciphertext for decryption.\nPlease try again later.\n");
        break;
    case STRING_COPY_ERROR:
        print("An erro has detected while copying a string..\nPlease try again later.\n");
        break;
    default:
        break;
    }
}

void tmrInit()
{
	tC=XTmrCtr_LookupConfig(XPAR_TMRCTR_0_DEVICE_ID);
	XTmrCtr_CfgInitialize(&tI,tC,XPAR_TMRCTR_0_BASEADDR);

}
