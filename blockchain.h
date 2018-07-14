#include <openssl/sha.h>

#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#define HASH_LENGTH SHA256_DIGEST_LENGTH * 2 + 1 // 65 bytes
#define OUTPUT_FILE "blockchain.dat"

typedef struct BlockStruct {
	unsigned int id;
	unsigned int nonce;
	char data[100];
	char timestamp[20];
	char hashPrev[HASH_LENGTH];
	char hash[HASH_LENGTH];
}Block;

char mdString[HASH_LENGTH];

void setBlock(char *);
void readOutputFile();
void hashSHA256(char *);

#endif /* BLOCKCHAIN_H_ */
