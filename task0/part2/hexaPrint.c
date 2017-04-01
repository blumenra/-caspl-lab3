
#include <stdio.h>
#include <stdlib.h>

void PrintHex(char* buffer, int length){

		int i;
		for(i=0; i<length; i++){

			printf("%02hhX ", buffer[i]);
		}
}

int main(int argc, char** argv){
	
	FILE* file;
	char* filename = argv[1];
	char byte[2] = {0, 0};

	file = fopen(filename, "r");
	if(file == NULL){

		perror("fopen");
		exit(1);
	}

	while((fread(byte, 1, 1, file)) == 1){

		PrintHex(byte, 1);
	}
	puts("");


	fclose(file);

	return 0;
}