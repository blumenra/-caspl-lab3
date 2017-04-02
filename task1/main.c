#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintHex(char* buffer, int length){

	int i;
	for(i=0; i<length; i++){
		fprintf(stdout, "%hhX ", buffer[i]);
	}
}


typedef struct virus virus;
 
struct virus {
    unsigned short length;
    char name[16];
    char signature[];
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

	fread(endian, 1, 2, file);
	intEndian = endian[0];
	// printf("endian: %d\n", endian[0]);
	// printf("currByte: %hhX\n", currByte[0]);
	// printf("currByte: %d\n", currByte[1]);
	// fread(currByte, 1, 2, file);
	// printf("currByte: %x\n", currByte[0]);
	// printf("currByte: %x\n", currByte[1]);

	
	// while(fread(sizeByte, 1, 2, file) == 2){
	fread(sizeByte, 1, 2, file);
	

	virus* virus = malloc(sizeof(virus));

	short len =0;
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
	virus->length = len;

	printf("%d\n", virus->length);
	char sig[virus->length-2-16];
	fread(virus->name, 1, 16, file);
	fread(sig, 1, virus->length-2-16, file);
	strcpy(virus->signature, sig);
	printf("%s\n", virus->name);
	PrintHex(virus->signature, virus->length);



	// }


	
	puts("");


	fclose(file);

	return 0;
}