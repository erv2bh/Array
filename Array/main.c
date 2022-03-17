//main.c
#include "Array.h"
#include<stdlib.h>
#include<stdio.h>
#include<memory.h>

#pragma warning (disable:4996)

int Compare(void* one, void* other);


int main(int argc, char* argv[]) {
	Array array;
	Array one;
	Array other;
	Long index;
	Long count;
	Long(*indexes);
	Long i;
	int object;
	int ret;
	int key;

	Create(&array, 3, sizeof(int));

	object = 100;
	index = Store(&array, 0, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 80;
	index = Store(&array, 1, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 60;
	index = Store(&array, 2, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n",ret);
	
	printf("================================\n");

	object = 90;
	index = Insert(&array, 1, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);
	

	object = 80;
	index = AppendFromFront(&array, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 70;
	index = AppendFromRear(&array, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	index = Delete(&array, 1, sizeof(int));
	if (index == -1) {
		printf("지워졌습니다\n");
	}

	index = DeleteFromFront(&array, sizeof(int));
	if (index == -1) {
		printf("지워졌습니다\n");
	}

	index = DeleteFromRear(&array, sizeof(int));
	if (index == -1) {
		printf("지워졌습니다\n");
	}

	Clear(&array);

	printf("================================\n");

	object = 90;
	index = AppendFromFront(&array, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 80;
	index = AppendFromRear(&array, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 70;
	index = AppendFromRear(&array, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 100;
	index = Modify(&array, 1, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	printf("================================\n");

	key = 90;
	index = LinearSearchUnique(&array, &key, sizeof(int), Compare);
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 100;
	index = Modify(&array, 0, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	key = 100;
	LinearSearchDuplicate(&array, &key, &indexes, &count, sizeof(int), Compare);
	i = 0;
	while (i < count) {
		GetAt(&array, indexes[i], &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	object = 80;
	index = Modify(&array, 0, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	InsertionSort(&array, sizeof(int), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}

	key = 100;
	index = BinarySearchUnique(&array, &key, sizeof(int), Compare);
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 100;
	index = Modify(&array, 0, &object, sizeof(int));
	GetAt(&array, index, &ret, sizeof(int));
	printf("%d\n", ret);

	SelectionSort(&array, sizeof(int), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}

	key = 100;
	BinarySearchDuplicate(&array, &key, &indexes, &count, sizeof(int), Compare);
	i = 0;
	while (i < count) {
		GetAt(&array, indexes[i], &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	Create(&one, 2, sizeof(int));

	object = 100;
	index = Store(&one, 0, &object, sizeof(int));
	GetAt(&one, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 90;
	index = Store(&one, 1, &object, sizeof(int));
	GetAt(&one, index, &ret, sizeof(int));
	printf("%d\n", ret);
	printf("================================\n");
	
	BubbleSort(&one, sizeof(int), Compare);
	i = 0;
	while (i < one.length) {
		GetAt(&one, i, &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}

	Create(&other, 2, sizeof(int));

	object = 80;
	index = Store(&other, 0, &object, sizeof(int));
	GetAt(&other, index, &ret, sizeof(int));
	printf("%d\n", ret);

	object = 70;
	index = Store(&other, 1, &object, sizeof(int));
	GetAt(&other, index, &ret, sizeof(int));
	printf("%d\n", ret);

	printf("================================\n");

	SelectionSort(&other, sizeof(int), Compare);
	i = 0;
	while (i < other.length) {
		GetAt(&other, i, &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}

	printf("================================\n");

	Merge(&array, &one, &other, sizeof(int), Compare);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(int));
		printf("%d\n", ret);
		i++;
	}
	
	Destroy(&other);
	Destroy(&one);
	Destroy(&array);
	

	return 0;
}

int Compare(void* one, void* other) {
	int* one_ = (int*)one;
	int* other_ = (int*)other;
	int ret;
	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_ < *other_) {
		ret = -1;
	}
	return ret;
}
