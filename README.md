# Simple_Block_Cipher

Implementation of a simplified 64-bit block cipher (ECB) which adds a randomly generated 64-bit key to the input data (padded) each 64-bit block at a time to encrypt, and subtracts the key in the same fashion to decrypt.

"hello_world.txt" input file provided as a sample (even though the program prompts you for the name of the input file) for convenience.

main.c tests the encryption/decryption (read comment at top of main.c for brief overview of the functionality and "modes of operation")
