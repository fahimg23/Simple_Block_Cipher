#include <stdint.h>

#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

/* Structure that can be used for dynamic allocation of a byte buffer */
typedef struct file_bytebuf {
  char* buf;
  size_t size_in_bytes;
} file_bytebuf;

/* Frees memory that was allocated using read_file_into_bytebuf() */
void free_file_buf(file_bytebuf* fbb);

/* Creates a file_bytebuf object and fills it using a file (the whole file). If not successful, returns NULL */
file_bytebuf* convert_file_to_bytebuf(const char* filename);

/* Writes the specified number of bytes of a byte array to a file. If file does not already exist it is created. */
void write_bytebuf_to_file(const char* filename, const char* buf, size_t buf_size_in_bytes);

#endif
