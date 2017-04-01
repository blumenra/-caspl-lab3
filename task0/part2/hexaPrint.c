
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

	int i;
	while(!feof(file)){

		fread(byte, sizeof(char), sizeof(char), file);	
		// for(i=0; i < 10; i++){

		printf("%02x ", byte[0]);
		// }
	}
	puts("");


	fclose(file);

	return 0;
}