//Array.c
#include "Array.h"
#include<stdlib.h>
#include<memory.h>

#pragma warning (disable:4996)

//Create
void Create(Array* array, Long capacity, size_t size) {
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}

//Store
Long Store(Array* array, Long index, void* object, size_t size) {
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	return index;	
}

//GetAt
void GetAt(Array* array, Long index, void* object, size_t size) {
	memcpy(object, ((char*)array->front) + (index * size), size);
}

//Insert
Long Insert(Array* array, Long index, void* object, size_t size) {
	void (*temp);
	int i;
	int j = 0;

	temp = calloc(array->capacity + 1, size);
	i = 0;
	while (i < index) {
		memcpy(((char*)temp)+(j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	j++;
	while (i < array->length) {
		memcpy(((char*)temp)+(j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	return index;
}

//AppendFromFront
Long AppendFromFront(Array* array, void* object, size_t size) {
	void(*temp);
	int i = 0;
	int index=0;

	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + ((i + 1) * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = temp;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	return index;
}

//AppendFromRear
Long AppendFromRear(Array* array, void* object, size_t size) {
	void(*temp);
	int index;
	int i = 0;

	temp = calloc(array->capacity + 1, size);
	while (i < array->length) {
		memcpy(((char*)temp) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = temp;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	return index;
}

//Delete
Long Delete(Array* array, Long index, size_t size) {
	void(*temp)=NULL;
	int i = 0;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < index) {
		memcpy(((char*)temp) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	i++;
	while (i < array->length) {
		memcpy(((char*)temp) + ((i - 1) * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;
	return index;
}

//DeleteFromFront
Long DeleteFromFront(Array* array, size_t size) {
	void(*temp) = NULL;
	int i = 1;
	Long index;
	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}
	while (i < array->length) {
		memcpy(((char*)temp) + ((i - 1) * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;
	return index;
}

//DeleteFromRear
Long DeleteFromRear(Array* array, size_t size) {
	void(*temp)=NULL;
	int i = 0;
	Long index;

	if (array->capacity > 1) {
		temp = calloc(array->capacity - 1, size);
	}

	while (i < array->capacity-1) {
		memcpy(((char*)temp) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		array->front = temp;
	}
	array->capacity--;
	array->length--;
	index = -1;
	return index;
}

//Clear
void Clear(Array* array) {
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}

//Modify
Long Modify(Array* array, int index, void* object, size_t size) {
	memcpy(((char*)array->front) + (index * size), object, size);
	return index;
}

//LinearSearchUnique
Long LinearSearchUnique(Array* array, void* key, size_t size, int(*compare)(void*, void*)) {
	int i = 0;
	Long index = -1;
	while (i < array->length && compare(((char*)array->front) + (i * size), key) != 0) {
		i++;
	}
	if (i < array->length) {
		index = i;
	}
	return index;
}

//LinearSearchDuplicate
void LinearSearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count, size_t size, int(*compare)(void*, void*)) {
	int i = 0;
	int j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	while(i < array->length) {
		if (compare(((char*)array->front) + (i * size), key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

//BinarySearchUnique
Long BinarySearchUnique(Array* array, void* key, size_t size, int(*compare)(void*, void*)) {
	Long first = 0;
	Long mid;
	Long last;
	Long index = -1;

	last = array->length - 1;
	mid = (first + last) / 2;
	while (first <= last && compare(((char*)array->front) + (mid * size), key) != 0) {
		if (compare(((char*)array->front) + (mid * size), key) < 0) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
		mid = (first + last) / 2;
	}
	if (first <= last) {
		index = mid;
	}
	return index;
}

//BinarySearchDuplicate
void BinarySearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count, size_t size, int(*compare)(void*, void*)) {
	int first = 0;
	int mid;
	int last;
	int i;
	int j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	last = array->length - 1;
	mid = (first + last) / 2;
	while (first <= last && compare(((char*)array->front) + (mid * size), key) != 0) {
		if (compare(((char*)array->front) + (mid * size), key) < 0) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
		mid = (first + last) / 2;
	}
	i = mid - 1;
	while (i >= first && compare(((char*)array->front) + (i * size), key) == 0) {
		i--;
	}
	i++;
	while (i <= last && compare(((char*)array->front) + (i * size), key) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
}

//InsertionSort
void InsertionSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	void* temp;
	Long i = 1;
	Long j;

	temp = malloc(size);

	while (i < array->length) {
		memcpy(temp, ((char*)array->front) + (i * size), size);
		j = i - 1;
		while (j >= 0 && compare(((char*)array->front) + (j * size), temp) > 0) {
			memcpy(((char*)array->front) + ((j + 1) * size), ((char*)array->front) + (j * size), size);
			j = j - 1;
		}
		memcpy(((char*)array->front) + ((j + 1) * size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}

//SelectionSort
void SelectionSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	void* temp;

	temp = malloc(size);

	while (i < array->length - 1) {
		j = i + 1;
		while (j < array->length) {
			if (compare(((char*)array->front) + (i * size), ((char*)array->front) + (j * size)) > 0) {
				memcpy(temp, ((char*)array->front) + (i * size), size);
				memcpy(((char*)array->front) + (i * size), ((char*)array->front) + (j * size), size);
				memcpy(((char*)array->front) + (j * size), temp, size);
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}

//BubboleSort
void BubbleSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	void* temp;
	Long i = 0;
	Long j;
	int flag = 1;

	temp = malloc(size);

	while (i < array->length -1 && flag == 1) {
		flag = 0;
		j = 0;
		while (j < array->length-i-1) {
			if (compare(((char*)array->front) + (j * size), ((char*)array->front) + ((j + 1) * size))>0) {
				memcpy(temp, ((char*)array->front) + (j * size), size);
				memcpy(((char*)array->front) + (j * size), ((char*)array->front) + ((j + 1) * size), size);
				memcpy(((char*)array->front) + ((j + 1) * size), temp, size);
				flag = 1;
			}
			j++;
		}
		i++;
	}
	if (temp != NULL) {
		free(temp);
	}
}

//Merge
void Merge(Array* array, Array* one, Array* other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}

	array->front = calloc(one->length + other->length,size);
	array->capacity = one->length + other->length;
	array->length = 0;
	while (i < one->length && j < other->length) {
		if (compare(((char*)one->front) + (i * size), ((char*)other->front) + (j * size)) < 0) {
			memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
			k++;
			array->length++;
			i++;
		}
		else {
			memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
			k++;
			array->length++;
			j++;
		}
	}
	while (i < one->length) {
		memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
		k++;
		array->length++;
		i++;
	}

	while (j < other->length) {
		memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
		k++;
		array->length++;
		j++;
	}	
}

//Destroy
void Destroy(Array* array) {
	if (array->front != NULL) {
		free(array->front);
	}
}
