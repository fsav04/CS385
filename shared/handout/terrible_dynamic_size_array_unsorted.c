#include "terrible_dynamic_size_array_unsorted.h"


void init(struct int_array* arr) {
	arr->count 		= 	0;
	arr->capacity 	= 	DEFAULT_CAPACITY;
	arr->data 		= 	(int*)malloc(sizeof(int) * arr->capacity);
}

void clear(struct int_array* arr) {
	destr(arr);
	init(arr);
}

void destr(struct int_array* arr) {
	free(arr->data);
	arr->count = 0;
}

void print_array(struct int_array* arr) {
	for (unsigned int i = 0; i < arr->count; ++ i)
		printf("%d ", arr->data[i]);
	printf("\n");
}

int contains(struct int_array* arr, int target) {

	unsigned int i;

	for (i = 0; i < arr->count; ++i) //there was a semicolon there where there should not have been a semicolon (1)
	{
		if (arr->data[i] == target)
			return TRUE;
			//else statement stopped the loop from looping  (2)
	}
	return FALSE;
}

void resize(struct int_array* arr) {

	arr->capacity *= 2;
	int* new_data = (int*)malloc(sizeof(int) * arr->capacity);
	for (unsigned int i = 0; i < arr->count; ++i)
	{
		new_data[i] = arr->data[i];
	}

	free(arr->data); //free data had to go before you set a new data value (7)

	arr->data = new_data;
	


}

void add(struct int_array* arr,  int payload) {

	if ((arr->count == arr->capacity))

		resize(arr);

	arr->data[arr->count++] = payload; //the ++ count was skipping the first iteration because it adds and evaluates so the first iteration would get skipped (3)
}

int remove_elem(struct int_array* arr,  int target) {

	unsigned int i = 0;

	if ((arr->count == 0)) //there was a set operand instead of compare operand in the if statement (4)

		return FALSE;

	while (i < arr->count && arr->data[i] != target)  i++;


	if (i == arr->count){ //there was a semicolon there where there should not have been a semicolon (5)

		return FALSE;
	}

	if (arr->data[i] == target){ //needed an if statement because code would not check if the target was hit and it would constantly return false (6)

		arr->data[i] = arr->data[arr->count];

		arr->count--;
	
		return TRUE;
	}
	

}


