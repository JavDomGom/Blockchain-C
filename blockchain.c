#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "blockchain.h"

void setBlock(char *string) {
	FILE *fichero;
	fichero = fopen(OUTPUT_FILE, "ab+");

	if (fichero == NULL) {
		printf("Error: No se ha podido crear el fichero \"%s\".\n", OUTPUT_FILE);
	} else {
		Block block;

		// Posicionamiento en el ultimo bloque
		fseek(fichero, sizeof(block) * -1, SEEK_END);
		// Leo el ultimo bloque
		fread(&block, sizeof(block), 1, fichero);

		// Set id
		if(ftell(fichero) != 0) {
			block.id++;
		} else {
			block.id = 0;
		}
		char idToString[12];
		sprintf(idToString, "%d", block.id);

		// Set data
		strcpy(block.data, string);

		// Set timestamp
		time_t now = time(0);
		strftime(block.timestamp, 100, "%Y/%m/%d %H:%M:%S", localtime(&now));

		// Set hashPrev
		if(ftell(fichero) == 0) {
			strcpy(block.hashPrev, "0");
		} else {
			strcpy(block.hashPrev, block.hash);
		}

		// Variable temporal para juntar todos los datos
		char tmp[256];

		// Se inserta id como string en tmp
		strcpy(tmp, idToString);

		// Se concatena data
		strcat(tmp, block.data);

		// Se concatena timestamp
		strcat(tmp, block.timestamp);

		// Y finalmente se concatena hashPrev
		strcat(tmp, block.hashPrev);

		// Set hash
		hashSHA256(tmp);
		strcpy(block.hash, mdString);

		fwrite(&block, sizeof(block), 1, fichero);
		fclose(fichero);
	}
}

void readOutputFile() {
	FILE *fichero;
	fichero = fopen(OUTPUT_FILE, "rb");
	Block block;

	if (fichero == NULL) {
		printf("Error: No se ha podido leer el fichero \"%s\".\n", OUTPUT_FILE);
	} else {
		fread(&block, sizeof(block), 1, fichero);

		while (!feof(fichero)) {
			printf("block.id:\t\t%d\n", block.id);
			printf("block.data:\t\t%s\n", block.data);
			printf("block.timestamp:\t%s\n", block.timestamp);
			printf("block.hashPrev:\t\t%s\n", block.hashPrev);
			printf("block.hash:\t\t%s\n\n", block.hash);

			fread(&block, sizeof(block), 1, fichero);
		}

		fclose(fichero);
	}
}

void hashSHA256(char *string) {
	int i;
	unsigned char digest[SHA256_DIGEST_LENGTH]; // 32 bytes
	SHA256((unsigned char*) string, strlen(string), (unsigned char*) &digest);
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(&mdString[i * 2], "%02x", (unsigned int ) digest[i]);
	}
}
