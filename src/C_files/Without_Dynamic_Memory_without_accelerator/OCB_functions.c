#include "OCB_functions.h"
#include "Decrypt_functions.h"
#include "Encrypt_functions.h"
#include "AES_defines.h"


/*________________________________Declarations________________________________________*/
int hex_to_int(char h);

void str_to_Uchar_array(char str[KEY_BLEN], unsigned char state[]);

enum OCB_status ntz(unsigned int number, int* rval);

void OCB_R_Shift(unsigned char state[], unsigned char result[]);

void OCB_L_Shift(unsigned char state[], unsigned char result[]);

enum OCB_status plainntext_to_blocks(char plaintext[MAX_LENGTH], unsigned char Blocks[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], int blocks_number, int reminder);

void Number_of_Blocks(char* str, int* Blocks_number, int* reminder);

void L_Array_Length(int blocks_number, int* mu);

enum OCB_status L_Array_init(unsigned char*** L_Array, int mu);

void  Array_1d_to_2d(unsigned char array[], unsigned char state[][STATE_COLUMNS_NUMBER]);

void  Array_2d_to_1d(unsigned char state[][STATE_COLUMNS_NUMBER], unsigned char array[]);

void xor_arrays(unsigned char array1[], unsigned char array2[], unsigned char result_array[], int m);

enum OCB_status zero_padding(char str[]);

enum OCB_status Tag_remover(char ciphertext[MAX_LENGTH], char plaintext[MAX_LENGTH], char Tag[TAG_BLEN]);

void ciphertext_blocks_to_str(unsigned char cipher_blocks[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], int blocks_number, int reminder, char chipertext[]);

char int_to_hex(int h);

void array_1d_to_str(unsigned char arr[], char str[]);

enum OCB_status OCB_init(int blocks_number, unsigned char round_keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char Z_Array[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], unsigned char L_inv_array[], char nonce[]);

void free_1D_array_memory(unsigned char** Array, int length);

/*________________________________Defines________________________________________*/


/*
* Input: this function takes as input unsined int number and a pointer.
* Output and functionality: the function finds the largest number that 2 int the power of it devides the input number.
*/
enum OCB_status ntz(unsigned int number, int* rval)
{
	*rval = 0;
	while ((number & 0x1) == 0)
	{
		if (number == 0)break;
		number >>= 1;
		*rval = *rval + 1;
	}
	if (rval != 0)return FOUND;
	return NOT_FOUND;
}

/*
* Input: this function takes as input a char.
* Output and functionality: the function sets the hex representation of the number into rval.
*/
int hex_to_int(char h)
{
	switch (h)
	{
	case('0'):return  0;
	case('1'):return 1;
	case('2'):return 2;
	case('3'):return 3;
	case('4'):return 4;
	case('5'):return 5;
	case('6'):return 6;
	case('7'):return 7;
	case('8'):return 8;
	case('9'):return 9;
	case('a'):return 10;
	case('b'):return 11;
	case('c'):return 12;
	case('d'):return 13;
	case('e'):return 14;
	case('f'):return 15;
	default:return -1;
	}
}

/*
* Input: this function takes as input string and an empty 2d array.
* Output and functionality: the function converts the 1d array anto 2d array.
*/
void  str_to_Uchar_array(char str[KEY_BLEN], unsigned char state[])
{
	state[0] = (hex_to_int(str[0]) << 4) + hex_to_int(str[1]);
	state[1] = (hex_to_int(str[2]) << 4) + hex_to_int(str[3]);
	state[2] = (hex_to_int(str[4]) << 4) + hex_to_int(str[5]);
	state[3] = (hex_to_int(str[6]) << 4) + hex_to_int(str[7]);
	state[4] = (hex_to_int(str[8]) << 4) + hex_to_int(str[9]);
	state[5] = (hex_to_int(str[10]) << 4) + hex_to_int(str[11]);
	state[6] = (hex_to_int(str[12]) << 4) + hex_to_int(str[13]);
	state[7] = (hex_to_int(str[14]) << 4) + hex_to_int(str[15]);
	state[8] = (hex_to_int(str[16]) << 4) + hex_to_int(str[17]);
	state[9] = (hex_to_int(str[18]) << 4) + hex_to_int(str[19]);
	state[10] = (hex_to_int(str[20]) << 4) + hex_to_int(str[21]);
	state[11] = (hex_to_int(str[22]) << 4) + hex_to_int(str[23]);
	state[12] = (hex_to_int(str[24]) << 4) + hex_to_int(str[25]);
	state[13] = (hex_to_int(str[26]) << 4) + hex_to_int(str[27]);
	state[14] = (hex_to_int(str[28]) << 4) + hex_to_int(str[29]);
	state[15] = (hex_to_int(str[30]) << 4) + hex_to_int(str[31]);
	// <<4 in is equivilent to multiplication by 16 in order to get the right value.
}

/*
* Input: this function takes as input unsigned 1d array that represent the current state and another one that represent the left shifted array.
* Output and functionality: the function shifts the state to the left by one bit.
*/
void OCB_R_Shift(unsigned char state[], unsigned char result[])
{
	int i;
	for (i = 0; i <= STR_TO_1D_ARRAY - 1; i++)
		result[i] = state[i];
	unsigned char last_bit = state[STR_TO_1D_ARRAY - 1] & 0x01;									//get the last bit of the number.
	for (i = STR_TO_1D_ARRAY - 1; i > 0; i--) {													//shift by one to the left.
		result[i] = (result[i] >> 1) | (((result[i - 1] & 0x01) == 0x01) ? 0x80 : 0);			
	}
	result[0] = (result[0] >> 1);
	if (last_bit == 0x01)																		//if the last bit is one xor the result with 10{0^120}1000011.
	{
		result[0] ^= 0x80;
		result[STR_TO_1D_ARRAY - 1] ^= 0x43;
	}
}

/*
* Input: this function takes as input unsigned 1d array that represent the current state and another one that represent the right shifted array.
* Output and functionality: the function shifts the state to the right by one bit.
*/
void OCB_L_Shift(unsigned char state[], unsigned char result[])
{
	int i;
	for (i = 0; i <= STR_TO_1D_ARRAY - 1; i++)
		result[i] = state[i];
	unsigned char first_bit = (int)result[0] & 0x80;											//get the first bit of the number.

	for (i = 0; i < STR_TO_1D_ARRAY - 1; i++) {													//shift by one to the right.
		result[i] = (result[i] << 1) | ((result[i + 1] & 0x80u) == 0x80 ? 1 : 0);
	}
	result[STR_TO_1D_ARRAY - 1] = (result[STR_TO_1D_ARRAY - 1] << 1);

	if (first_bit == 0x80)result[STR_TO_1D_ARRAY - 1] ^= 0x87;									//if the first bit is one xor the result with {0^120}10000111.
}

/*
* Input: this function takes as input pointer to a string, pointer to integer number which will
	represent the number of block needed and another pointer which will represent the reminder if we have such.
* Output and functionality: the function devides the length of the string by block length and calculates how much blocks we need
	and calculates the reminder of such division if there is any.
*/
void Number_of_Blocks(char* str, int* Blocks_number, int* reminder)
{
	int len = (int)strlen(str);
	*reminder = len % (BLOCK_BLEN-1);
	*Blocks_number = (*reminder == 0) ? (len / (BLOCK_BLEN-1)) : (len / (BLOCK_BLEN-1)+1);			// if there is reminder increase the blocks number by one.
}

/*
* Input: this function takes as input integer number which represent the blocks number and a pointer to integer that will
	represent the length of the L array.
* Output and functionality: the function fundes the log2(blocknumber) rounded up and sets mu to be this value.
*/
void L_Array_Length(int blocks_number, int* mu)
{
	*mu = 0;
	*mu = (int)ceil(log2((double)blocks_number));
}

/*
* Input: this function takes as input 3d pointer that represent an adress of 2d array
	and integer mu that represent the needed length.
* Output and functionality: the function allocate memory for the array and initiate it by zeros.
*/
enum OCB_status L_Array_init(unsigned char*** L_Array, int mu)
{
	int len = 0;
	if (mu == 0)len = 1;
	else len = mu;
	unsigned char** L_tmp_Array = (unsigned char**)malloc(len * sizeof(unsigned char*));
	if (L_tmp_Array == NULL)return MEMORY_ALLOCATING_ERROR;
	else {
		int i = 0;
		for (i = 0; i < len; i++)
		{
			L_tmp_Array[i] = (unsigned char*)malloc(BYTE_TO_BIT * sizeof(unsigned char));				//initiating by zeros
			if (L_tmp_Array[i] == NULL)return MEMORY_ALLOCATING_ERROR;
			else {
				for (int j = 0; j < STR_TO_1D_ARRAY; j++)
				{
					L_tmp_Array[i][j] = 0x00;
				}
			}
		}
		*L_Array = L_tmp_Array;
		L_tmp_Array = NULL;
		free(L_tmp_Array);
		return SUCESS;
	}
}

/*
* Input: this function takes as input 2d pointer that represent an adress of 2d array
	and integer length that represent the needed length.
* Output and functionality: the function free's the allocate memory for the array .
*/
void free_1D_array_memory(unsigned char** Array, int length)
{
	if (length == 0)return;
	if(length>1)
		for (int i = 0; i<length; i++)
			free(Array[i]);
	free(Array);
	return ;
}

/*
* Input: this function takes as input 3d pointer that represent an adress of 2d array
	and integer mu that represent the needed length.
* Output and functionality: the function allocate memory for the array and initiate it by zeros.
*/
void  Array_1d_to_2d(unsigned char array[], unsigned char state[][STATE_COLUMNS_NUMBER])
{
	state[0][0] = array[0];
	state[1][0] = array[1];
	state[2][0] = array[2];
	state[3][0] = array[3];
	state[0][1] = array[4];
	state[1][1] = array[5];
	state[2][1] = array[6];
	state[3][1] = array[7];
	state[0][2] = array[8];
	state[1][2] = array[9];
	state[2][2] = array[10];
	state[3][2] = array[11];
	state[0][3] = array[12];
	state[1][3] = array[13];
	state[2][3] = array[14];
	state[3][3] = array[15];
}

/*
* Input: this function takes as input string and a 2d array.
* Output and functionality: the function converts the 2d array anto 1d array.
*/
void  Array_2d_to_1d(unsigned char state[][STATE_COLUMNS_NUMBER], unsigned char array[])
{
	array[0] = state[0][0];
	array[1] = state[1][0];
	array[2] = state[2][0];
	array[3] = state[3][0];
	array[4] = state[0][1];
	array[5] = state[1][1];
	array[6] = state[2][1];
	array[7] = state[3][1];
	array[8] = state[0][2];
	array[9] = state[1][2];
	array[10] = state[2][2];
	array[11] = state[3][2];
	array[12] = state[0][3];
	array[13] = state[1][3];
	array[14] = state[2][3];
	array[15] = state[3][3];
}

/*
* Input: this function takes as input three unsigne char arrays and there length.
* Output and functionality: the function apllies bitwise xor to the first two arrays
	and fills the result in the right index of the third one.
*/
void xor_arrays(unsigned char array1[], unsigned char array2[], unsigned char result_array[], int m)
{
	for (int i = 0; i < m; i++)
	{
		result_array[i] = array1[i] ^ array2[i];
	}
}

/*
* Input: this function takes as input 2d pinter that represent an address of string.
* Output and functionality: the function padds the string with zeros from the right
	if it's length is smaller that the block length.
*/
enum OCB_status zero_padding(char str[])
{
	int source_len = (int)strlen(str);
	char tmp_str[BLOCK_BLEN]="";
	for (int i = 0; i < BLOCK_BLEN ; i++)
	{
		if (i < source_len) tmp_str[i] = str[i];						//copy the source array to the tmp array.
		else tmp_str[i] = '0';											//if the length is smaller than the block length padd with zero.
	}
	tmp_str[BLOCK_BLEN-1] = '\0';
	strcpy(str , tmp_str);
	return SUCESS;

}

/*
* Input: this function takes as input string and an empty 3d array that will represent the plaintext
	divided to blocks the number of blocks needed and the reminder if there is any.
* Output and functionality: the function allocate memory for the array and splits the plaintext into
	blocks of BLOCK_LEN arrays.
*/
enum OCB_status plainntext_to_blocks(char plaintext[MAX_LENGTH], unsigned char Blocks[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], int blocks_number, int reminder)
{
	if (blocks_number == 0)return EMPTY_STRING;
	enum OCB_status status = SUCESS;
	char tmp_rem[BLOCK_BLEN] = "";
	int rounds = (reminder == 0) ? blocks_number : blocks_number - 1;
	for (int i = 0; i < rounds; i++)
	{
			for (int j = 0; j < BLOCK_BLEN-1; j += 2)
			{
				Blocks[i][j / 2] = (hex_to_int(plaintext[((BLOCK_BLEN-1) * i) + j]) << 4) + hex_to_int(plaintext[((BLOCK_BLEN-1) * i) + j + 1]);
			}


	}
	if (reminder != 0)
	{
		for (int i = 0; i < reminder; i++)
		{
			tmp_rem[i] = plaintext[(BLOCK_BLEN-1) * (blocks_number - 1) + i];
		}
		status = zero_padding(tmp_rem);
		if (status != SUCESS)return ZERO_PADDING_ERROR;
		for (int i = 0; i < BLOCK_BLEN-1; i += 2)
		{
			Blocks[blocks_number - 1][i / 2] = (hex_to_int(tmp_rem[i]) << 4) + hex_to_int(tmp_rem[i + 1]);
		}
	}
	
	return SUCESS;

}

/*
* Input: this function takes as input string and two numbers that represent the number of the blocks
	and the reminder if there is any and a ciphertext string.
* Output and functionality: the function the cipher blocks into the array.
*/
void ciphertext_blocks_to_str(unsigned char cipher_blocks[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], int blocks_number, int reminder, char ciphertext[])
{
	int i = 0, k = 0;
	int rounds = (reminder == 0) ? blocks_number : blocks_number - 1;
	for (; i < rounds; i++)
	{
		for (int j = 0; j < BYTE_TO_BIT; j++)
		{

			ciphertext[k] = int_to_hex((int)(cipher_blocks[i][j] & 0xf0) >> 4);				//take the left byte.
			ciphertext[k + 1] = int_to_hex((int)(cipher_blocks[i][j] & 0x0f));				//take the right byte.
			k += 2;

		}
	}
	if (reminder != 0)
	{
		for (int j = 0; j < (int)(reminder / 2); j++)
		{
			ciphertext[k] = int_to_hex((int)(cipher_blocks[i][j] & 0xf0) >> 4);
			ciphertext[k + 1] = int_to_hex((int)(cipher_blocks[i][j] & 0x0f));
			k += 2;
		}
	}
	ciphertext[k] = '\0';

}

/*
* Input: this function takes as input a integer.
* Output and functionality: the function return the dec representation of the number.
*/
char int_to_hex(int h)
{
	switch (h)
	{
	case(0):return '0';
	case(1):return '1';
	case(2):return '2';
	case(3):return '3';
	case(4):return '4';
	case(5):return '5';
	case(6):return '6';
	case(7):return '7';
	case(8):return '8';
	case(9):return '9';
	case(10):return 'a';
	case(11):return 'b';
	case(12):return 'c';
	case(13):return 'd';
	case(14):return 'e';
	case(15):return 'f';
	default:return 'x';
	}
}

/*
* Input: this function takes as input string and an unsigned char 1d array.
* Output and functionality: the function converts the 1d array to string.
*/
void array_1d_to_str(unsigned char arr[], char str[])
{
	int k = 0;
	for (int j = 0; j < BYTE_TO_BIT; j++)
	{
		str[k] = int_to_hex((int)(arr[j] & 0xf0) >> 4);			//take the left byte.
		str[k + 1] = int_to_hex((int)(arr[j] & 0x0f));			//take the right byte.
		k += 2;
	}
	str[k] = '\0';
}

/*
* Input: this function takes as input blocks number, 3d array that represent the round keys, 3d pointer which represent
	the address of the Z array, a pointer to unsigned char which represent the L_* and a string which represent the nonce.
* Output and functionality: the function initiate the OCB by calculating the L_*, the L array and the Z array.
*/
enum OCB_status OCB_init(int blocks_number, unsigned char round_keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER], unsigned char Z_Array[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY], unsigned char L_inv_array[], char nonce[])
{
	enum OCB_status status = SUCESS;
	enum status AES_status = PASS;
	unsigned char L_Array[MAX_L_ARRAY_LENGTH][STR_TO_1D_ARRAY] = {0x00};
	unsigned char L_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char zeros_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char R_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char nonce_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char R_array[STR_TO_1D_ARRAY] = { 0x00 };
	int mu, ntz_i = 0;
	unsigned char tmp_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char tmp_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };

	L_Array_Length(blocks_number, &mu);
	if (status != SUCESS)return ARRAY_INITIATING_ERROR;
	if (status != SUCESS)return ARRAY_INITIATING_ERROR;
	AES_status = AESEncryption(zeros_state, round_keys, L_state);							//L=L(0)=Ek({0^n})
	if (AES_status != PASS)return ENCRYPTION_ERROR;
	Array_2d_to_1d(L_state, L_Array[0]);
	OCB_R_Shift(L_Array[0], L_inv_array);													//L_inv=L_*=L{x^-1}
	for (int i = 1; i < mu + 1; i++)
	{
		OCB_L_Shift(L_Array[i - 1], L_Array[i]);											//L(i)=L(i-1)x
	}
	str_to_Uchar_array(nonce, nonce_array);
	xor_arrays(nonce_array, L_Array[0], tmp_array, STR_TO_1D_ARRAY);						// calculate the N xor L
	Array_1d_to_2d(tmp_array, tmp_state);
	AES_status = AESEncryption(tmp_state, round_keys, R_state);								//R=Ek(N xor L)
	if (AES_status != PASS)return ENCRYPTION_ERROR;
	Array_2d_to_1d(R_state, R_array);
	xor_arrays(L_Array[0], R_array, Z_Array[1], STR_TO_1D_ARRAY);						//Z(1)=L xor R
	for (int i = 2; i < blocks_number + 1; i++)
	{
		status = ntz(i, &ntz_i);
		if (status != FOUND)return NTZ_ERROR;
		xor_arrays(Z_Array[i - 1], L_Array[ntz_i], Z_Array[i], STR_TO_1D_ARRAY);	//Z(i)=Z(i-1) xor L(ntz(i))
	}

	return SUCESS;
}

/*
* Input: this function takes as input string and an empty 2d pinter which represent
	the address of the plaintext and apointer to string that represent the tag.
* Output and functionality: the function splits the ciphertext into two string
	the first one represent the cipher text and the other represent the tag..
*/
enum OCB_status Tag_remover(char ciphertext[MAX_LENGTH], char plaintext[MAX_LENGTH], char Tag[TAG_BLEN])
{
	char* rval;
	char Tag_Tag[TAG_BLEN]="";
	char temp_plain[MAX_LENGTH]="";
	rval = strncpy(plaintext, ciphertext, (int)strlen(ciphertext) - (BLOCK_BLEN-1));						//copying from the begining to the last tau bits.
	if (rval == NULL)return STRING_COPY_ERROR;
	rval = strncpy(Tag, ciphertext + ((int)strlen(ciphertext) - (BLOCK_BLEN-1)), (BLOCK_BLEN-1));			//copying the last tau bits.
	if (rval == NULL)return STRING_COPY_ERROR;															//check for copying error.
	return SUCESS;
}

/*
* Input: this function takes as input string that represent the plaintext if we want to encrypt and the
	ciphertext if we want to decrypt, astring that represent the key to use ,a string that represent a
	string that represent the nonce that we will use, a pointer to a string that represent the cipher
	text if we are encrypting and the plaintext if we are encrypting and the mode encrypt or decrypt.
* Output and functionality: the function applies the OCB algorithim to encrypt or decrypt and returns
	the status if we have succeeded or not.
*/
enum OCB_status OCB_enc_dyc(char plain_or_cipher[], char key[], char nonce[], char cipher_or_plain[MAX_LENGTH], enum mode ENC_OR_DEC)
{
	char Tag[TAG_BLEN]="";
	enum OCB_status status = SUCESS;
	enum status AES_status = PASS;
	int blocks_number = 0, reminder = 0;
	unsigned char Blocks[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY] ={0x00};
	unsigned char Z_Array[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char C_Array[MAX_BLOCKS_NUM][STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char Key_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char Key_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char L_inv_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char round_keys[ROUND_KEYS_NUMBER][STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char tmp_array[16] = { 0x00 };
	unsigned char tmp_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char tmp2_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char Y_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char X_state[STATE_COLUMNS_NUMBER][STATE_COLUMNS_NUMBER] = { 0x00 };
	unsigned char Y_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char X_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char Checksum_array[STR_TO_1D_ARRAY] = { 0x00 };
	unsigned char Tag_array[STR_TO_1D_ARRAY] = { 0x00 };
	char* rval = NULL;
	char Tag_Tag[TAG_BLEN]="";
	char tmp_cipher_or_plain[MAX_LENGTH]= "";
	int rv = 0;
	char text_IN[MAX_LENGTH]="";
	if (ENC_OR_DEC == ENCRYPTION)
	{
		if ((int)strlen(plain_or_cipher) == 0)
		{
			rval = strcpy(text_IN, "00000000000000000000000000000000");					//if the plaintext is empty replace it whith a block of zeros.
			if (rval == NULL)return STRING_COPY_ERROR;
			text_IN[BLOCK_BLEN] = '\0';
		}
		else
		{
			rval = strcpy(text_IN, plain_or_cipher);									//copy the plaintext to text_IN to start.
			if (rval == NULL)return STRING_COPY_ERROR;
		}
		
	}
	else
	{
		if (ENC_OR_DEC == DECRYPTION)
		{
			status = Tag_remover(plain_or_cipher, text_IN, Tag_Tag);					//split the cipher text to plaintext and tag.
			if (status != SUCESS)return TAG_REMOVING_ERROR;
		}
		else
		{
			return UNKNOWN_MODE;
		}
	}
	str_to_Uchar_array(key, Key_array);																//convert the input string to unsigned char array.
	Array_1d_to_2d(Key_array, Key_state);															//convert the 1d array to 2d array (state).
	AES_status = round_keys_generator(Key_state, round_keys);										//generate the round keys (3d array).
	if (AES_status != PASS)return KEYS_GENERATING_ERROR;
	Number_of_Blocks(text_IN, &blocks_number, &reminder);											//calculate the number of blocks and the reminder.
	status = plainntext_to_blocks(text_IN, Blocks, blocks_number, reminder);						//split the plaintext to blocks (zero padded if needed).
	if (status != SUCESS)return PLAINNTEXT_TO_BLOCKS_ERROR;
	status = OCB_init(blocks_number, round_keys, Z_Array, L_inv_array, nonce);						//generate the Z array and L_*
	if (status != SUCESS)return OCB_INIT_ERROR;
	for (int i = 0; i < blocks_number - 1; i++)														//C(i)=Ek(M(i) xor Z(i)) xor X(i).
	{
		xor_arrays(Blocks[i], Z_Array[i + 1], tmp_array, STR_TO_1D_ARRAY);							//calculate M(i) xor Z(i).
		Array_1d_to_2d(tmp_array, tmp_state);														//convert the result array to 2d array.
		if (ENC_OR_DEC == ENCRYPTION)
		{
			AES_status = AESEncryption(tmp_state, round_keys, tmp2_state);							//if we are encrypting calculate Ek(M(i) xor Z(i)).
			if (AES_status != PASS)return ENCRYPTION_ERROR;
		}
		else
		{
			AES_status = AESDecryption(tmp_state, round_keys, tmp2_state);							//if we are decrypting calculate Ek^-1(M(i) xor Z(i))
			if (AES_status != PASS)return ENCRYPTION_ERROR;
		}
		Array_2d_to_1d(tmp2_state, C_Array[i]);														//convert the result back to 1d array.
		xor_arrays(C_Array[i], Z_Array[i + 1], C_Array[i], STR_TO_1D_ARRAY);						//claculate Ek(M(i) xor Z(i)) xor X(i)
	}
	X_array[STR_TO_1D_ARRAY - 1] = (reminder != 0) ? (int)(reminder * 4) : BLOCK_BLEN * 4;			//X(i)=len(M(m)).
	xor_arrays(X_array, L_inv_array, X_array, STR_TO_1D_ARRAY);										//X(i)=X(i) xor L_*.
	xor_arrays(X_array, Z_Array[blocks_number], X_array, STR_TO_1D_ARRAY);							//X(i)=X(m) xor Z(m).
	Array_1d_to_2d(X_array, X_state);																//convert the result to 2d array.
	AES_status = AESEncryption(X_state, round_keys, Y_state);										//Y(m)=Ek(X(m)).
	if (AES_status != PASS)return ENCRYPTION_ERROR;
	Array_2d_to_1d(Y_state, Y_array);																//convert back to 1d array.
	xor_arrays(Y_array, Blocks[blocks_number - 1], C_Array[blocks_number - 1], STR_TO_1D_ARRAY);	//C(m)=Y(m) xor M(m).
	ciphertext_blocks_to_str(C_Array, blocks_number, reminder, tmp_cipher_or_plain);				//convert the result to string.
	if (reminder != 0)
		for (int i = STR_TO_1D_ARRAY - (reminder / 2); i > 0; i--)									//if there is a reminder remove the previous zero padded bytes.
			C_Array[blocks_number - 1][BYTE_TO_BIT - i] = 0x00;
	if (ENC_OR_DEC == ENCRYPTION)
	{
		for (int i = 0; i < blocks_number - 1; i++)
			xor_arrays(Checksum_array, Blocks[i], Checksum_array, STR_TO_1D_ARRAY);					//checksum=M(1) xorM(2) xor ...xor M(m-1) xor C(m)0^*.
		xor_arrays(Checksum_array, C_Array[blocks_number - 1], Checksum_array, STR_TO_1D_ARRAY);
	}
	else
	{
		for (int i = 0; i < blocks_number - 1; i++)
			xor_arrays(Checksum_array, C_Array[i], Checksum_array, STR_TO_1D_ARRAY);
		xor_arrays(Checksum_array, Blocks[blocks_number - 1], Checksum_array, STR_TO_1D_ARRAY);		//checksum=M(1) xorM(2) xor ...xor M(m-1) xor C(m)0^*.
	}
	xor_arrays(Checksum_array, Y_array, Checksum_array, STR_TO_1D_ARRAY);							//checksum=checksum xor Y(m).
	xor_arrays(Checksum_array, Z_Array[blocks_number], tmp_array, STR_TO_1D_ARRAY);					//calculate checksum xor Z(m).
	Array_1d_to_2d(tmp_array, tmp_state);															//convert to 2d array.
	AES_status = AESEncryption(tmp_state, round_keys, tmp2_state);									//T = Ek(checksum xor Z(m)).
	if (AES_status != PASS)return ENCRYPTION_ERROR;
	Array_2d_to_1d(tmp2_state, Tag_array);															//convert back to 1d array.
	array_1d_to_str(Tag_array, Tag);
	if (ENC_OR_DEC == ENCRYPTION)
	{
		strcpy(cipher_or_plain, tmp_cipher_or_plain);												//Cc = C.
		strcat(cipher_or_plain, Tag);																//Cc = C || T.
	}
	else
	{
		rv = strcmp(Tag, Tag_Tag);																	// check if T' equals T.
		if (rv != 0)return INVALID;																	// return invelid if T' != T
		strcpy(cipher_or_plain, tmp_cipher_or_plain);												// copy the final result to the output.
	}
	return SUCESS;
}

