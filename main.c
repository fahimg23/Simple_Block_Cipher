#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "file_buffer.h"
#include "encrypt.h"

/*
* Modes of Operation:
* 
* Mode 1: Asks for the input filename, reads input data into a buffer, encrypts
* the buffer using a randomly generated key, and writes the buffer to a file
* named "encrypted_data.txt" and the key to "key.txt"
*
*
* Mode 2: Reads in the data in "encrypted_data.txt" into a buffer, and also
* reads in the key from "key.txt", decrypts the buffer using the key, and writes
* the decrypted data to "decrypted_data.txt"
*/

int select_mode(void){
	char mode;
	printf("Please select mode of operation (enter 1 or 2): ");
	mode = getchar();

	/* When pressing enter for the getchar above, a newline character gets placed in stdin, need to remove */
	getchar();

	return atoi(&mode);
}

void mode1(void) {

	file_bytebuf* fbb;
	uint64_t key;
	plain_text* ptx_file;
	cipher_text* ctx;
	char filename[100];

	printf("Please enter the file that contains the data to encrypt: ");
	fgets(filename, 100, stdin);

	/* When entering the filename through command line, a new line character gets appended after hitting enter. This must be removed */
	filename[strlen(filename)-1] = '\0';

	fbb = convert_file_to_bytebuf(filename);

	ptx_file = (plain_text*)malloc(sizeof(plain_text));
	ptx_file->ptx_buf = (char*)malloc(fbb->size_in_bytes-1);
	ptx_file->size_in_bytes = fbb->size_in_bytes-1;

	memcpy(ptx_file->ptx_buf, fbb->buf, ptx_file->size_in_bytes);

	key = generate_rand_key64();

	ctx = encrypt(ptx_file, key);

	write_bytebuf_to_file("encrypted_data.txt", ctx->ctx_buf, ctx->size_in_bytes);
	write_bytebuf_to_file("key.txt", (const char*)(&key), BLOCK_SIZE_IN_BYTES);

	free_file_buf(fbb);
	free_file_buf((file_bytebuf*)ptx_file);
	free_file_buf((file_bytebuf*)ctx);
}

void mode2(void){

	file_bytebuf* fbb_to_dec;
	file_bytebuf* key_buf;
	uint64_t* key_read;
	cipher_text* ctx_dec;
	plain_text* ptx_dec;

	fbb_to_dec = convert_file_to_bytebuf("encrypted_data.txt");
	key_buf = convert_file_to_bytebuf("key.txt");
	key_read = (uint64_t*)key_buf->buf;

	ctx_dec = (cipher_text*)malloc(sizeof(plain_text));
	ctx_dec->ctx_buf = (char*)malloc(fbb_to_dec->size_in_bytes-1);
	ctx_dec->size_in_bytes = fbb_to_dec->size_in_bytes-1;

	memcpy(ctx_dec->ctx_buf, fbb_to_dec->buf, ctx_dec->size_in_bytes);

	ptx_dec = decrypt(ctx_dec, *key_read);

	write_bytebuf_to_file("decrypted_data.txt", ptx_dec->ptx_buf, ptx_dec->size_in_bytes);

	free_file_buf(fbb_to_dec);
	free_file_buf(key_buf);
	free_file_buf((file_bytebuf*)ctx_dec);
	free_file_buf((file_bytebuf*)ptx_dec);
}

int main(int argc, char* argv[]){

	int mode;

	mode = select_mode();

	if (mode == 1)
		mode1();
	else
		mode2();

	return 0;
}
