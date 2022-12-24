#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "shell_list.h"
static long generate_k(long size, long k);
static bool append_list(long value, Node** a_head, Node** a_tail);
static long get_size_list(Node** a_head);
static Node* swap_nodes(Node** head, Node** node_1, Node** node_2, Node* pt_to_n1, Node* pt_to_n2);
static Node* move_k_nodes_away(Node* start, long k, long size);


//Loads a linked list from a filename, returns null if invalid open
Node *List_Load_From_File(char *filename){

	//error handle opening the file
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		return NULL;
	}
	//allocating proper size
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(long);
	fseek(fp, 0, SEEK_SET);
	Node* a_head = NULL;
	Node* a_tail = a_head;
	//reading file
	
	int idx = 0;
	long read;
	bool valid_read;
	//long i;
	for(idx = 0; idx < size; idx++){
		fread(&read, sizeof(read), 1, fp); 
		valid_read = append_list(read, &a_head, &a_tail);
		if(!valid_read){
			break;
		}
	}
	fclose(fp);
	return a_head;
}

//Saves a linked list to the filename
int List_Save_To_File(char *filename, Node *list){
	int size = 0;
	//error handle opening the file
	FILE* fp = fopen(filename, "w");
	if(fp == NULL) {
		return size;
	}
	if(list != NULL){
		Node* curr;
		for(curr = list; curr != NULL; curr = curr -> next){
			size += fwrite(&(curr -> value), sizeof(curr -> value), 1, fp);
		}
	}
	fclose(fp);
	return size;
}

//Function to Shell Sort with a linked list
Node *List_Shellsort(Node *List, long *n_comp){
	long k;
	long i;
	long size = get_size_list(&List);
	
	*n_comp = 0;
	if(List == NULL){
		return List;
	}
	Node* curr;
	Node* pt_to_curr;
	Node* compare;
	Node* pt_to_compare;
	bool is_not_sorted = true;
	long idx_track_last_swap = size;
	long idx_last_swap = size;
	for(k = generate_k(size, size); k > 0; k = (k - 1) / 3){ //iterates through all k values
		is_not_sorted = true;
		idx_last_swap = size;
		idx_track_last_swap = size;
		//setting up initial vals
		while(is_not_sorted){
			is_not_sorted = false;
			curr = List;
			pt_to_curr = NULL;
			//pt_to_compare = get_ith_node(k-2,&List );
			pt_to_compare = move_k_nodes_away(List, k-1, size );
			idx_last_swap = idx_track_last_swap;
			if(pt_to_compare != NULL){
				compare = pt_to_compare -> next;
			} else{
				compare = NULL;
			}
			for(i = 0; i < idx_last_swap; i++) {
				(*n_comp)++;
				if(compare != NULL && (curr -> value > compare -> value)){
					swap_nodes(&List, &curr, &compare, pt_to_curr, pt_to_compare);
					is_not_sorted = true;
					idx_track_last_swap = i;
				}
				pt_to_curr = curr;
				pt_to_compare = compare;
				if(curr != NULL) {
					curr  = pt_to_curr -> next;
				}
				if(compare != NULL) {
					compare = pt_to_compare -> next;
				}
			}
		}
	}
	return List;
}

//Function to swap nodes, including a head or tail
static Node* swap_nodes(Node** head, Node** node_1, Node** node_2, Node* pt_to_n1, Node* pt_to_n2){
	if (*head == NULL || (*node_1) == NULL || (*node_2) == NULL) { //no swap to be done
		return NULL;
	}
	Node* temp1;
	if(*head == *node_1){ 
		*head = *node_2;
	}
	else {
		pt_to_n1 -> next = *node_2;
	}
	pt_to_n2 -> next = *node_1;
	temp1 = (*node_1) -> next;
	(*node_1) -> next = (*node_2) -> next;
	(*node_2) -> next = temp1;
	Node* temp2 = *node_1;
	*node_1 = *node_2;
	*node_2 = temp2;
	return *node_2; //node_2 has now taken the place of node1
}

//Move a certain number (k) nodes away froma  starting node
static Node* move_k_nodes_away(Node* start, long k, long size){
	if(start == NULL || k < 0 || k >= size) {
		return NULL;
	}
	else {
		Node* curr = start;
		while(k > 0 && curr != NULL) {
			curr = curr -> next;
			k--;
		}
		return curr;
	}
}

//Append a node to a linked list
static bool  append_list(long value, Node** a_head, Node** a_tail) {
    Node* new_node = malloc(sizeof(*new_node));
	if (new_node == NULL){
		return false;
	}
    new_node -> value = value;
    new_node -> next = NULL;
    if(*a_head == NULL) { //empty list
        *a_head = new_node;
    }
    else {
        (*a_tail) -> next = new_node;
    }
    *a_tail = new_node;
	return true;
}

//Function to generate the "k's" needed for optimum shell sort
static long generate_k(long size, long k){
	long new_k;
	for(new_k = 0; new_k < size && new_k < k; new_k = 3 * new_k + 1){
		;
	}
	new_k = (new_k - 1) / 3;

	return new_k;
}
//get the size of the linked list
static long get_size_list(Node** a_head) {
	long size_ctr = 0;
	Node* curr = *a_head;
	while(curr != NULL) {
		size_ctr++;
		curr = curr -> next;
	}
	return size_ctr;
}	

