#include "Encrypt_functions.h"
#include "Rijndael_functions.h"

/*________________________________Declarations________________________________________*/
enum status mixColumns(unsigned char state[][STATE_ROWS_NUMBER], unsigned char mixed[][STATE_COLUMNS_NUMBER]);
enum status SubShiftRow(unsigned char state[][STATE_ROWS_NUMBER], unsigned char result[][STATE_COLUMNS_NUMBER]);

/*________________________________Defines________________________________________*/

/*
* Input: this function takes as input an unsigned char 2d array that represent the current state and another one that will be the result of the mix columns operation.
* Output and functionality: the function mixes the columns of the state and fills it into the mixed array.
*/
enum status mixColumns(unsigned char state[][STATE_ROWS_NUMBER],unsigned char mixed[][STATE_COLUMNS_NUMBER])
{
    enum status status=PASS;
    int i;
    for (i = 0; i < STATE_COLUMNS_NUMBER; i++)
    {
        unsigned char temp_mul2, temp_mul3;        
        status = R_Boxes(state[0][i], &temp_mul2, mul2);
        status = R_Boxes(state[1][i], &temp_mul3, mul3);
        mixed[i][0] = temp_mul2 ^ temp_mul3 ^ state[2][i] ^ state[3][i];   

        status = R_Boxes(state[1][i], &temp_mul2, mul2);
        status = R_Boxes(state[2][i], &temp_mul3, mul3);

        mixed[i][1] = state[0][i] ^ temp_mul2 ^ temp_mul3 ^ state[3][i];      
        status = R_Boxes(state[2][i], &temp_mul2, mul2);
        status = R_Boxes(state[3][i], &temp_mul3, mul3);


        mixed[i][2] = state[0][i] ^ state[1][i] ^ temp_mul2 ^ temp_mul3;
        status = R_Boxes(state[3][i], &temp_mul2, mul2);
        status = R_Boxes(state[0][i], &temp_mul3, mul3);
        mixed[i][3] = temp_mul3 ^ state[1][i] ^ state[2][i] ^ temp_mul2;     
    }
    return status;
}

/*
* Input: this function takes as input an unsigned char 2d array that represent the current state and another one that will be the result of the sub and shift rows operation.
* Output and functionality: the function applies the Rijndael sub operation of the current state and then applies the shift rows operation and finally fills the result into the result array.
*/
enum status SubShiftRow(unsigned char state[][STATE_ROWS_NUMBER], unsigned char result[][STATE_COLUMNS_NUMBER])
{
    enum status status = PASS;


    status = R_Boxes(state[0][0], &(result[0][0]), sub);
    status = R_Boxes(state[0][1], &(result[0][1]), sub);
    status = R_Boxes(state[0][2], &(result[0][2]), sub);
    status = R_Boxes(state[0][3], &(result[0][3]), sub);
    status = R_Boxes(state[1][0], &(result[1][3]), sub);
    status = R_Boxes(state[1][1], &(result[1][0]), sub);
    status = R_Boxes(state[1][2], &(result[1][1]), sub);
    status = R_Boxes(state[1][3], &(result[1][2]), sub);
    status = R_Boxes(state[2][0], &(result[2][2]), sub);
    status = R_Boxes(state[2][1], &(result[2][3]), sub);
    status = R_Boxes(state[2][2], &(result[2][0]), sub);
    status = R_Boxes(state[2][3], &(result[2][1]), sub);
    status = R_Boxes(state[3][0], &(result[3][1]), sub);
    status = R_Boxes(state[3][1], &(result[3][2]), sub);
    status = R_Boxes(state[3][2], &(result[3][3]), sub);
    status = R_Boxes(state[3][3], &(result[3][0]), sub);
    return status;
    
}

/*
* Input: this function takes as input an unsigned char 2d array that represent the plaintext,a 3d array that represent the round keys and a 2d array that will represent the encrypted word.
* Output and functionality: the function applies the AES encryption method and fills the ciphertext array will the encrypted word.
*/
enum status AESEncryption(unsigned char plainText[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char cipherText[][STATE_COLUMNS_NUMBER])
{
    enum status status = PASS;
    unsigned char state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
    unsigned char temp[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
    int round;
    //first round
    state[0][0] = plainText[0][0] ^ round_Keys[0][0][0];
    state[0][1] = plainText[0][1] ^ round_Keys[0][0][1];
    state[0][2] = plainText[0][2] ^ round_Keys[0][0][2];
    state[0][3] = plainText[0][3] ^ round_Keys[0][0][3];
    state[1][0] = plainText[1][0] ^ round_Keys[0][1][0];
    state[1][1] = plainText[1][1] ^ round_Keys[0][1][1];
    state[1][2] = plainText[1][2] ^ round_Keys[0][1][2];
    state[1][3] = plainText[1][3] ^ round_Keys[0][1][3];
    state[2][0] = plainText[2][0] ^ round_Keys[0][2][0];
    state[2][1] = plainText[2][1] ^ round_Keys[0][2][1];
    state[2][2] = plainText[2][2] ^ round_Keys[0][2][2];
    state[2][3] = plainText[2][3] ^ round_Keys[0][2][3];
    state[3][0] = plainText[3][0] ^ round_Keys[0][3][0];
    state[3][1] = plainText[3][1] ^ round_Keys[0][3][1];
    state[3][2] = plainText[3][2] ^ round_Keys[0][3][2];
    state[3][3] = plainText[3][3] ^ round_Keys[0][3][3];
    //now the 9 rounds begin
    for (round = 1; round < AES_ROUND_NUMBER; round++)
    {  
        status = SubShiftRow(state, temp);
        status = mixColumns(temp, state);
        temp[0][0] = state[0][0] ^ round_Keys[round][0][0];
        temp[1][0] = state[0][1] ^ round_Keys[round][1][0];
        temp[2][0] = state[0][2] ^ round_Keys[round][2][0];
        temp[3][0] = state[0][3] ^ round_Keys[round][3][0];
        temp[0][1] = state[1][0] ^ round_Keys[round][0][1];
        temp[1][1] = state[1][1] ^ round_Keys[round][1][1];
        temp[2][1] = state[1][2] ^ round_Keys[round][2][1];
        temp[3][1] = state[1][3] ^ round_Keys[round][3][1];
        temp[0][2] = state[2][0] ^ round_Keys[round][0][2];
        temp[1][2] = state[2][1] ^ round_Keys[round][1][2];
        temp[2][2] = state[2][2] ^ round_Keys[round][2][2];
        temp[3][2] = state[2][3] ^ round_Keys[round][3][2];
        temp[0][3] = state[3][0] ^ round_Keys[round][0][3];
        temp[1][3] = state[3][1] ^ round_Keys[round][1][3];
        temp[2][3] = state[3][2] ^ round_Keys[round][2][3];
        temp[3][3] = state[3][3] ^ round_Keys[round][3][3];
        state[0][0] = temp[0][0];
        state[0][1] = temp[0][1];
        state[0][2] = temp[0][2];
        state[0][3] = temp[0][3];
        state[1][0] = temp[1][0];
        state[1][1] = temp[1][1];
        state[1][2] = temp[1][2];
        state[1][3] = temp[1][3];
        state[2][0] = temp[2][0];
        state[2][1] = temp[2][1];
        state[2][2] = temp[2][2];
        state[2][3] = temp[2][3];
        state[3][0] = temp[3][0];
        state[3][1] = temp[3][1];
        state[3][2] = temp[3][2];
        state[3][3] = temp[3][3];
    }
    //last round
    status = SubShiftRow(state, temp);
    cipherText[0][0] = temp[0][0] ^ round_Keys[round][0][0];
    cipherText[0][1] = temp[0][1] ^ round_Keys[round][0][1];
    cipherText[0][2] = temp[0][2] ^ round_Keys[round][0][2];
    cipherText[0][3] = temp[0][3] ^ round_Keys[round][0][3];
    cipherText[1][0] = temp[1][0] ^ round_Keys[round][1][0];
    cipherText[1][1] = temp[1][1] ^ round_Keys[round][1][1];
    cipherText[1][2] = temp[1][2] ^ round_Keys[round][1][2];
    cipherText[1][3] = temp[1][3] ^ round_Keys[round][1][3];
    cipherText[2][0] = temp[2][0] ^ round_Keys[round][2][0];
    cipherText[2][1] = temp[2][1] ^ round_Keys[round][2][1];
    cipherText[2][2] = temp[2][2] ^ round_Keys[round][2][2];
    cipherText[2][3] = temp[2][3] ^ round_Keys[round][2][3];
    cipherText[3][0] = temp[3][0] ^ round_Keys[round][3][0];
    cipherText[3][1] = temp[3][1] ^ round_Keys[round][3][1];
    cipherText[3][2] = temp[3][2] ^ round_Keys[round][3][2];
    cipherText[3][3] = temp[3][3] ^ round_Keys[round][3][3];

    return status;
}

