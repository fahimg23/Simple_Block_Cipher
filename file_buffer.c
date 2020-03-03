#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file_buffer.h"

void free_file_buf(file_bytebuf* fbb) {
	free(fbb->buf);
	free(fbb);
}

file_bytebuf* convert_file_to_bytebuf(const char* filename) {

	file_bytebuf* fbb;
	long file_size_in_bytes;
	FILE* fp;

	fp = fopen(filename, (const char*)"rb");

	if (!fp) {
		printf("Could not open file named %s!\n", filename);
		return NULL;
	}

	// Move file stream to the end of the file so that the number of bytes in the file can be determined
	fseek(fp, 0L, SEEK_END);

	file_size_in_bytes = ftell(fp);

	// Allocate memory for the buffer object
	fbb = (file_bytebuf*)malloc(sizeof(file_bytebuf));
	fbb->buf = (char*)malloc(sizeof(char) * (file_size_in_bytes + 1));
	fbb->size_in_bytes = file_size_in_bytes+1;

	// Move file stream back to the beginning of the file
	fseek(fp, 0L, SEEK_SET);

	// Read the whole file into the buffer
	fread(fbb->buf, sizeof(char), file_size_in_bytes, fp);

	fclose(fp);

	// Null terminate in case buffer will be used as string
	fbb->buf[file_size_in_bytes] = '\0';

	return fbb;
}

void write_bytebuf_to_file(const char* filename, const char* buf, size_t buf_size_in_bytes) {
	FILE* fp;

	fp = fopen(filename, (const char*)"wb+");

	// Write the whole buffer into the file
	fwrite(buf, sizeof(char), buf_size_in_bytes, fp);

	fclose(fp);
}
