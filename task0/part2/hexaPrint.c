
#include <stdio.h>

void PrintHex(buffer, length){

}

int main(int argc, char** argv){
	
	FILE* file;
	char* filename = argv[1];
	char byte[1] = {0};

	file = fopen(filename, "r");
	if(file == NULL){

		perror("fopen");
		exit(1);
	}

	fread(byte, 1, 1, file);
	printf("%s\n", byte);


	fclose(file);

	return 0;
}