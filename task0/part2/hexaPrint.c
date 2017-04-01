
#include <stdio.h>
#include <stdlib.h>

void PrintHex(char* buffer, int length){

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

		printf("%hhX ", byte[0]);
	}
	puts("");


	fclose(file);

	return 0;
}