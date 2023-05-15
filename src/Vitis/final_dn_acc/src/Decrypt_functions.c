#include "Decrypt_functions.h"
#include "Rijndael_functions.h"

/*________________________________Declarations________________________________________*/

enum status inverseMixedColumn(unsigned char mixed[][STATE_ROWS_NUMBER], unsigned char invmixed[][STATE_COLUMNS_NUMBER]);
enum status inverseSubShiftRow(unsigned char state[][STATE_ROWS_NUMBER], unsigned char result[][STATE_COLUMNS_NUMBER]);

/*________________________________Defines________________________________________*/

/*
* Input: this function takes as input an unsigned char 2d array that represent the mixed state and another one that will be the result of the inverse mix columns operation.
* Output and functionality: the function inverse mixes the columns of the state and fills it into the original array.
*/
enum status inverseMixedColumn(unsigned char mixed[][STATE_ROWS_NUMBER], unsigned char invmixed[][STATE_COLUMNS_NUMBER])
{
    enum status status = PASS;
    int i;
    for (i = 0; i < STATE_COLUMNS_NUMBER; i++)
    {
        unsigned char temp_mul9 = 0x00, temp_mul11 = 0x00;
        unsigned char temp_mul13=0x00, temp_mul14=0x00;
        Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][0] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul14 );
		temp_mul14 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][1] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul11 );
		temp_mul11 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][2] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul13 );
		temp_mul13 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][3] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul9 );
		temp_mul9 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		/*status = R_Boxes(mixed[i][0], &temp_mul14, mul14);
		status = R_Boxes(mixed[i][1], &temp_mul11, mul11);
		status = R_Boxes(mixed[i][2], &temp_mul13, mul13);
		status = R_Boxes(mixed[i][3], &temp_mul9, mul9);*/
		invmixed[0][i] = temp_mul14 ^ temp_mul11 ^ temp_mul13 ^ temp_mul9;

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][0] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul9 );
		temp_mul9 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][1] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul14 );
		temp_mul14 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][2] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul11 );
		temp_mul11 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][3] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul13 );
		temp_mul13 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		/*status = R_Boxes(mixed[i][0], &temp_mul9, mul9);
		status = R_Boxes(mixed[i][1], &temp_mul14, mul14);
		status = R_Boxes(mixed[i][2], &temp_mul11, mul11);
		status = R_Boxes(mixed[i][3], &temp_mul13, mul13);*/
		invmixed[1][i] = temp_mul14 ^ temp_mul11 ^ temp_mul13 ^ temp_mul9;


		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][0] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul13 );
		temp_mul13 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][1] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul9 );
		temp_mul9 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][2] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul14 );
		temp_mul14 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][3] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul11 );
		temp_mul11 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);


		/*status = R_Boxes(mixed[i][0], &temp_mul13, mul13);
		status = R_Boxes(mixed[i][1], &temp_mul9, mul9);
		status = R_Boxes(mixed[i][2], &temp_mul14, mul14);
		status = R_Boxes(mixed[i][3], &temp_mul11, mul11);*/
		invmixed[2][i] = temp_mul14 ^ temp_mul11 ^ temp_mul13 ^ temp_mul9;


		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][0] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul11 );
		temp_mul11 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][1] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul13 );
		temp_mul13 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][2] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul9 );
		temp_mul9 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)mixed[i][3] );
		Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, mul14 );
		temp_mul14 = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

		/*status = R_Boxes(mixed[i][0], &temp_mul11, mul11);
		status = R_Boxes(mixed[i][1], &temp_mul13, mul13);
		status = R_Boxes(mixed[i][2], &temp_mul9, mul9);
		status = R_Boxes(mixed[i][3], &temp_mul14, mul14);*/
		invmixed[3][i] = temp_mul14 ^ temp_mul11 ^ temp_mul13 ^ temp_mul9;
    }
    return status;
}

/*
* Input: this function takes as input an unsigned char 2d array that represent the current state and another one that will be the result of the inverse sub and shift rows operation.
* Output and functionality: the function applies the Rijndael inverse sub operation of the current state and then applies the inverse shift rows operation and finally fills the result into the result array.
*/
enum status inverseSubShiftRow(unsigned char state[][STATE_ROWS_NUMBER], unsigned char result[][STATE_COLUMNS_NUMBER])
{
    enum status status = PASS;

    Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[0][0] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[0][0] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[0][1] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[0][1] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[0][2] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[0][2] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[0][3] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[0][3] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[1][0] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[1][1] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[1][1] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[1][2] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[1][2] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[1][3] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[1][3] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[1][0] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[2][0] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[2][2] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[2][1] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[2][3] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[2][2] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[2][0] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[2][3] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[2][1] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);


	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[3][0] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[3][3] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[3][1] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[3][0] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[3][2] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[3][1] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*0, (u32)state[3][3] );
	Xil_Out32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*1, isub );
	result[3][2] = Xil_In32(XPAR_R_BOXES_IP_V1_0_0_BASEADDR + 4*2);

	/*status = R_Boxes(state[0][0], &(result[0][0]), isub);
	status = R_Boxes(state[0][1], &(result[0][1]), isub);
	status = R_Boxes(state[0][2], &(result[0][2]), isub);
	status = R_Boxes(state[0][3], &(result[0][3]), isub);
	status = R_Boxes(state[1][0], &(result[1][1]), isub);
	status = R_Boxes(state[1][1], &(result[1][2]), isub);
	status = R_Boxes(state[1][2], &(result[1][3]), isub);
	status = R_Boxes(state[1][3], &(result[1][0]), isub);
	status = R_Boxes(state[2][0], &(result[2][2]), isub);
	status = R_Boxes(state[2][1], &(result[2][3]), isub);
	status = R_Boxes(state[2][2], &(result[2][0]), isub);
	status = R_Boxes(state[2][3], &(result[2][1]), isub);
	status = R_Boxes(state[3][0], &(result[3][3]), isub);
	status = R_Boxes(state[3][1], &(result[3][0]), isub);
	status = R_Boxes(state[3][2], &(result[3][1]), isub);
	status = R_Boxes(state[3][3], &(result[3][2]), isub);*/
    return status;

}

/*
* Input: this function takes as input an unsigned char 2d array plaintext that represent the encrypted,a 3d array that represent the round keys and a 2d array that will represent the decrypted word.
* Output and functionality: the function applies the AES decryption method and fills the ciphertext array will the decrypted word.
*/
enum status AESDecryption(unsigned char plainText[][STATE_COLUMNS_NUMBER], unsigned char round_Keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char cipherText[][STATE_COLUMNS_NUMBER])
{
    enum status status = PASS;
    unsigned char state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
    unsigned char temp[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
    int round;
    //first round
    state[0][0] = plainText[0][0] ^ round_Keys[10][0][0];
    state[0][1] = plainText[0][1] ^ round_Keys[10][0][1];
    state[0][2] = plainText[0][2] ^ round_Keys[10][0][2];
    state[0][3] = plainText[0][3] ^ round_Keys[10][0][3];
    state[1][0] = plainText[1][0] ^ round_Keys[10][1][0];
    state[1][1] = plainText[1][1] ^ round_Keys[10][1][1];
    state[1][2] = plainText[1][2] ^ round_Keys[10][1][2];
    state[1][3] = plainText[1][3] ^ round_Keys[10][1][3];
    state[2][0] = plainText[2][0] ^ round_Keys[10][2][0];
    state[2][1] = plainText[2][1] ^ round_Keys[10][2][1];
    state[2][2] = plainText[2][2] ^ round_Keys[10][2][2];
    state[2][3] = plainText[2][3] ^ round_Keys[10][2][3];
    state[3][0] = plainText[3][0] ^ round_Keys[10][3][0];
    state[3][1] = plainText[3][1] ^ round_Keys[10][3][1];
    state[3][2] = plainText[3][2] ^ round_Keys[10][3][2];
    state[3][3] = plainText[3][3] ^ round_Keys[10][3][3];
    status = inverseSubShiftRow(state, temp);
    //now the 9 rounds begin
    for (round = AES_ROUND_NUMBER-1; round >0; round--)
    {
        state[0][0] = temp[0][0] ^ round_Keys[round][0][0];
        state[1][0] = temp[0][1] ^ round_Keys[round][0][1];
        state[2][0] = temp[0][2] ^ round_Keys[round][0][2];
        state[3][0] = temp[0][3] ^ round_Keys[round][0][3];
        state[0][1] = temp[1][0] ^ round_Keys[round][1][0];
        state[1][1] = temp[1][1] ^ round_Keys[round][1][1];
        state[2][1] = temp[1][2] ^ round_Keys[round][1][2];
        state[3][1] = temp[1][3] ^ round_Keys[round][1][3];
        state[0][2] = temp[2][0] ^ round_Keys[round][2][0];
        state[1][2] = temp[2][1] ^ round_Keys[round][2][1];
        state[2][2] = temp[2][2] ^ round_Keys[round][2][2];
        state[3][2] = temp[2][3] ^ round_Keys[round][2][3];
        state[0][3] = temp[3][0] ^ round_Keys[round][3][0];
        state[1][3] = temp[3][1] ^ round_Keys[round][3][1];
        state[2][3] = temp[3][2] ^ round_Keys[round][3][2];
        state[3][3] = temp[3][3] ^ round_Keys[round][3][3];       
        status = inverseMixedColumn(state, temp);
        status = inverseSubShiftRow(temp, state);
        temp[0][0] = state[0][0];
        temp[0][1] = state[0][1];
        temp[0][2] = state[0][2];
        temp[0][3] = state[0][3];
        temp[1][0] = state[1][0];
        temp[1][1] = state[1][1];
        temp[1][2] = state[1][2];
        temp[1][3] = state[1][3];
        temp[2][0] = state[2][0];
        temp[2][1] = state[2][1];
        temp[2][2] = state[2][2];
        temp[2][3] = state[2][3];
        temp[3][0] = state[3][0];
        temp[3][1] = state[3][1];
        temp[3][2] = state[3][2];
        temp[3][3] = state[3][3];
    }
    cipherText[0][0] = state[0][0] ^ round_Keys[0][0][0];
    cipherText[0][1] = state[0][1] ^ round_Keys[0][0][1];
    cipherText[0][2] = state[0][2] ^ round_Keys[0][0][2];
    cipherText[0][3] = state[0][3] ^ round_Keys[0][0][3];
    cipherText[1][0] = state[1][0] ^ round_Keys[0][1][0];
    cipherText[1][1] = state[1][1] ^ round_Keys[0][1][1];
    cipherText[1][2] = state[1][2] ^ round_Keys[0][1][2];
    cipherText[1][3] = state[1][3] ^ round_Keys[0][1][3];
    cipherText[2][0] = state[2][0] ^ round_Keys[0][2][0];
    cipherText[2][1] = state[2][1] ^ round_Keys[0][2][1];
    cipherText[2][2] = state[2][2] ^ round_Keys[0][2][2];
    cipherText[2][3] = state[2][3] ^ round_Keys[0][2][3];
    cipherText[3][0] = state[3][0] ^ round_Keys[0][3][0];
    cipherText[3][1] = state[3][1] ^ round_Keys[0][3][1];
    cipherText[3][2] = state[3][2] ^ round_Keys[0][3][2];
    cipherText[3][3] = state[3][3] ^ round_Keys[0][3][3];
    return status;
}

