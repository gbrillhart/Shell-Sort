#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include "shell_array.h"

static long generate_ks(int size, long k);

//load the Array from a file
long *Array_Load_From_File(char *filename, int *size) {
	//error handle opening the file
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		*size = 0;
		return NULL;
	}
	//allocating proper size
	fseek(fp, 0, SEEK_END);
	*size = ftell(fp) / sizeof(long);
	fseek(fp, 0, SEEK_SET);
	long* intArray = malloc(sizeof(*intArray) * *size);
	if (intArray == NULL){
		return NULL;
	}
	//reading file
	fread(intArray, sizeof(*intArray), *size, fp);
	//closing and returning
	fclose(fp);
	return intArray;

}

//Save the Array to the file
int Array_Save_To_File(char *filename, long *array, int size) {
	//error handle opening the file
	FILE* fp = fopen(filename, "w");
	if(fp == NULL) {
		return 0;
	}
	if(!(size == 0 || array == NULL)){
		size = fwrite(array, sizeof(*array), size, fp);
	}
	fclose(fp);
	return size;
}

//Shell sort using an array
void Array_Shellsort(long *array, int size, long *n_comp) {
	long k;
	long j;
	long i;
	long temp_r;
	*n_comp = 0;
	if(array == NULL || size == 0){
		return;
	}

	for(k = generate_ks(size, size); k > 0; k = generate_ks(size, k)){ //iterates through all k values
		for(j = k; j < size; j++){
			temp_r = array[j];
			i = j;
			(*n_comp) += 1;
			while (i >= k && array[i-k] > temp_r) {
				array[i] = array[i-k];
				i = i-k;
			}
			array[i] = temp_r;
		}
	}

}

//function to generate k's
static long generate_ks(int size, long k){
	long new_k;
	for(new_k = 1; new_k < size && new_k < k; new_k = 3 * new_k + 1){
		;
	}
	new_k = (new_k - 1) / 3;

	return new_k;
}
