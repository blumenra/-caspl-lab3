#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus virus;
typedef struct link link;

void PrintHex(char* buffer, int length);
void list_print(link *virus_list);
link* list_append(link* virus_list, virus* data);
void list_free(link *virus_list);
 
struct virus {
    unsigned short length;
    char name[16];
    char* signature;
};

struct link {
    virus *v;
    link *next;
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

		virus* tempVirus = (virus*) malloc(sizeof(virus));

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
		tempVirus->length = len;
		char* sig = (char*) malloc(sizeof(char)*(tempVirus->length));

		fread(tempVirus->name, 1, 16, file);
		fread(sig, 1, tempVirus->length, file);
		tempVirus->signature = sig;

		fprintf(stdout, "%s", "Virus name: ");
		fprintf(stdout, "%s\n", tempVirus->name);
		fprintf(stdout, "%s", "Virus size: ");
		fprintf(stdout, "%d\n", tempVirus->length);
		fprintf(stdout, "%s\n", "Signature: ");
		PrintHex(tempVirus->signature, tempVirus->length);
		puts("\n");

		free(tempVirus->signature);
		free(tempVirus);
	}

	fclose(file);

	return 0;
}


void PrintHex(char* buffer, int length){

	int i;
	for(i=0; i<length; i++){
		fprintf(stdout, "%02hhX ", buffer[i]);
	}
}

void list_print(link *virus_list){

	link* currLink = virus_list;

	while(currLink != NULL){

		virus* virus = currLink->v;

		fprintf(stdout, "%s", "Virus name: ");
		fprintf(stdout, "%s\n", virus->name);
		fprintf(stdout, "%s", "Virus size: ");
		fprintf(stdout, "%d\n", virus->length);
		fprintf(stdout, "%s\n", "Signature: ");
		PrintHex(virus->signature, virus->length);
		puts("\n");

		currLink = currLink->next;
	}
}

link* list_append(link* virus_list, virus* data){

	if(virus_list == NULL){

		link* new_list = (link*) malloc(sizeof(link));
		return new_list;
	}

	//****Add to the beginning
	link* link1 = (link*) malloc(sizeof(link));
	link1->v = data;
	link1->next = virus_list;
	return link1;
	//****Add to the beginning

	//****Add to the end
	// link* currLink = virus_list;
	// while(currLink.next != NULL){
	// 	currLink = currLink.next;
	// }

	// link* link = (link*) malloc(sizeof(link));
	// link->v = data;
	// link->next = NULL;
	// currLink.next = link;
	// return virus_list;
	//****Add to the end
}

void list_free(link *virus_list){

	if(virus_list != NULL){

		link* currLink = virus_list;
		link* nextLink = virus_list->next;
		while(nextLink != NULL){
			free(currLink->v);
			free(currLink);
			currLink = nextLink;
			nextLink = nextLink->next;
		}
		free(currLink->v);
		free(currLink);
	}
}