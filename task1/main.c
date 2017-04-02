#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintHex(char* buffer, int length){

	int i;
	for(i=0; i<length; i++){
		fprintf(stdout, "%02hhX ", buffer[i]);
	}
}


typedef struct virus virus;
 
struct virus {
    unsigned short length;
    char name[16];
    char* signature;
};

int main(int argc, char** argv){
	
	FILE* file;
	char* filename = argv[1];
	char endian[2] = {0, 0};
	int intEndian = 0;
	char sizeByte[2] = {0, 0};


	file = fopen(filename, "r");
	if(file == NULL){

		perror("fopen");
		exit(1);
	}

	fread(endian, 1, 1, file);
	intEndian = endian[0];
	
	while(fread(sizeByte, 1, 2, file) == 2){

		virus virus;

		short len = 0;
		if(intEndian == 0){

			len = sizeByte[0]-18;
		}
		else if(intEndian == 1){

			len = sizeByte[1]-18;
		}
		else{
			perror("Invalid endian!");
			exit(1);
		}
		virus.length = len;
		char* sig = (char*) malloc(sizeof(char)*(virus.length));

		fread(virus.name, 1, 16, file);
		fread(sig, 1, virus.length, file);
		virus.signature = sig;

		fprintf(stdout, "%s", "Virus name: ");
		fprintf(stdout, "%s\n", virus.name);
		fprintf(stdout, "%s", "Virus size: ");
		fprintf(stdout, "%d\n", virus.length);
		fprintf(stdout, "%s\n", "Signature: ");
		PrintHex(virus.signature, virus.length);
		puts("\n");

		free(virus.signature);
	}

	fclose(file);

	return 0;
}