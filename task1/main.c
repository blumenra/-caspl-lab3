#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus virus;
typedef struct link link;

void PrintHex(char* buffer, int length);
void list_print(link *virus_list);
link* list_append(link* virus_list, virus* data);
void list_free(link *virus_list);
void detect_virus(char *buffer, link *virus_list, unsigned int size);
 
struct virus {
    unsigned short length;
    char name[16];
    char signature[];
};

struct link {
    virus *v;
    link *next;
};


int main(int argc, char** argv){
	
	FILE* file1;
	char* filename = argv[1];
	char* signatures = "signatures1";
	char endian[2] = {0, 0};
	int intEndian = 0;
	char sizeByte[2] = {0, 0};
	link* list = NULL;
	char buffer[10000];


	file1 = fopen(signatures, "r");
	if(file1 == NULL){

		perror("fopen");
		exit(1);
	}

	fread(endian, 1, 1, file1);
	intEndian = endian[0];
	
	while(fread(sizeByte, 1, 2, file1) == 2){


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

		virus* tempVirus = (virus*) malloc(sizeof(short)+sizeof(char)*(16+len));
		tempVirus->length = len;

		fread(tempVirus->name, 1, 16+tempVirus->length, file1);

		list = list_append(list, tempVirus);
	}

	FILE *file2 = fopen(filename, "r");
	fseek(file2, 0, SEEK_END);
	int fileSize = ftell(file2);
	fseek(file2, 0, SEEK_SET);  //same as rewind(f);

	fread(buffer, 1, fileSize, file2);

	detect_virus(buffer, list, fileSize);

	// list_print(list);
	list_free(list);

	fclose(file1);
	fclose(file2);

	return 0;
};


void PrintHex(char* buffer, int length){

	int i;
	for(i=0; i<length; i++){
		fprintf(stdout, "%02hhX ", buffer[i]);
	}
};

void list_print(link *virus_list){

	//****Add to the beginning
	// link* currLink = virus_list;
	// int size = 0;
	// while(currLink != NULL){
	// 	size++;
	// 	currLink = currLink->next;
	// }
	// virus* viruses[size];
	// currLink = virus_list;
	// int i = 0;
	// while(currLink != NULL){

	// 	viruses[i] = currLink->v;
	// 	i++;
	// 	currLink = currLink->next;
	// }

	// i = size-1;
	// while(i >= 0){

	// 	virus* virus = viruses[i];

	// 	fprintf(stdout, "%s", "Virus name: ");
	// 	fprintf(stdout, "%s\n", virus->name);
	// 	fprintf(stdout, "%s", "Virus size: ");
	// 	fprintf(stdout, "%d\n", virus->length);
	// 	fprintf(stdout, "%s\n", "Signature: ");
	// 	PrintHex(virus->signature, virus->length);
	// 	puts("\n");

	// 	i--;
	// }

	//****Add to the beginning


	//****Add to the end
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
	//****Add to the end
};

link* list_append(link* virus_list, virus* data){

	if(virus_list == NULL){

		link* new_list = (link*) malloc(sizeof(link));
		new_list->v = data;
		new_list->next = NULL;
		return new_list;
	}

	//****Add to the beginning
	// link* link1 = (link*) malloc(sizeof(link));
	// link1->v = data;
	// link1->next = virus_list;
	// return link1;
	//****Add to the beginning

	//****Add to the end
	link* currLink = virus_list;
	while(currLink->next != NULL){
		currLink = currLink->next;
	}

	link* link1 = (link*) malloc(sizeof(link));
	link1->v = data;
	link1->next = NULL;
	currLink->next = link1;
	return virus_list;
	//****Add to the end
};

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
};

void detect_virus(char *buffer, link *virus_list, unsigned int size){

	link* currLink = virus_list;
	virus* currVirus;
	while(currLink != NULL){

		currVirus = currLink->v;
		int i;
		int res;
		for(i=0; i<size; i++){
			
			res = memcmp(buffer+i, currVirus->signature, currVirus->length);

			if(res == 0){
				fprintf(stdout, "Starting byte location: %d\n", i);
				fprintf(stdout, "Virus name: %s\n", currVirus->name);
				fprintf(stdout, "Virus signature size: %d\n", currVirus->length);
			}
		}
		currLink = currLink->next;
	}
}