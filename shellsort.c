#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"

void print_array(long* intArray, int* size);
void free_list(Node* head);
static long get_size_list(Node** a_head);

static long get_size_list(Node** a_head) {
	long size_ctr = 0;
	Node* curr = *a_head;
	while(curr != NULL) {
		size_ctr++;
		curr = curr -> next;
	}
	return size_ctr;
}	
//Prints array
void print_array(long* intArray, int* size) {
	printf("\nSize:%d\n[", *size);
	int idx = 0;
	for(idx = 0; idx < *size; idx++) {
		printf("%ld,", intArray[idx]);
	}
	printf("]");
}


//Frees linked list
void free_list(Node* head) {
	Node* curr;
	for(curr = head; curr != NULL; curr = head) {
		head = head -> next;
		free(curr);
	}
}



//Main function to determine if we are sorting with linked list or array
//Maintains overall function and flow
int main(int argc, char* argv[]) {
	if (argc != 4){
		return EXIT_FAILURE;
	}
	if(*(argv[1]+1) =='a'){
		int size = 0;
		long n_comp = 0;
		long* intArray = Array_Load_From_File(argv[2], &size);
		if(intArray == NULL){
			return EXIT_FAILURE;
		}
		Array_Shellsort(intArray, size, &n_comp);
		printf("%ld\n", n_comp);
		int written = Array_Save_To_File(argv[3], intArray, size);
		if(intArray != NULL){
			free(intArray);
		}
		if(written != size){
			return EXIT_FAILURE;
		}
	}
	else if(*(argv[1]+1) =='l'){
		long n_comp = 0;
		Node* list = List_Load_From_File(argv[2]);
		list = List_Shellsort(list, &n_comp);
		printf("%ld\n", n_comp);
		int written = List_Save_To_File(argv[3], list);
		int size = get_size_list(&list);
		if(list != NULL){
			free_list(list);
		}
		if(written != size){
			return EXIT_FAILURE;
		}
		
		
	}
	else{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
