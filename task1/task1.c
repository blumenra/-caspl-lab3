#include <stdio.h>
#include <stdlib.h>

void PrintHex(char* buffer, int length){

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
	char byte[1] = {0};

	file = fopen(filename, "r");
	if(file == NULL){

		perror("fopen");
		exit(1);
	}

	fread(byte, 1, 1, file)

		
		// for(i=0; i < 10; i++){

		printf("%02x ", byte[0]);
		// }
	
	puts("");


	fclose(file);

	return 0;
}