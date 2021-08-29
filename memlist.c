#include <stdio.h>
#include <stdlib.h>
#include "memlist.h"

MemElement *_initMemElement(int offset, int size){
	MemElement *element = (MemElement*)malloc(1*sizeof(MemElement));
	element->offset = offset;
	element->size = size;
	element->next = NULL;
	return element;
}


MemList *_initMemList(){
	MemList *list = (MemList*)malloc(1*sizeof(MemList));
	MemElement *head = _initMemElement(0, 0);
	list->head = head;
	return list;
}


int _addInMemList(MemList *list, MemElement *element, int index){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	MemElement *now = list->head;
	int i = 0;
	while(i<index && now->next){
		now = now->next;
		i++;
	}
	element->next = now->next;
	now->next = element;
	if (i==index) {return 0;}
	return 1;
}


int _delFromMemList(MemList *list, int index){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	MemElement *now = list->head;
	int i = 0;
	if (!now->next) {return 1;}
	while(i<index && now->next->next){
		now = now->next;
		i++;
	}
	MemElement *tmp = now->next;
	if (!tmp) {return 1;}
	now->next = now->next->next;
	free(tmp);
	if (i=index) {return 0;}
	return 1;
}


int _getLenMemList(MemList *list){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	MemElement *now = list->head;
	int len = 0;
	while(now->next){
		len++;
		now = now->next;
	}
	return len;
}


MemElement *_getElementMemList(MemList *list, int index){
	if (!list) {return NULL;}
	if (!list->head) {return NULL;}
	MemElement *now = list->head;
	int i = 0;
	while(i<=index && now->next){
		i++;
		now = now->next;
	}
	//if (i==index+1) {return now;}
	return now;
}


int clearMemList(MemList *list){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	MemElement *now = list->head;
	MemElement *next = NULL;
	while (now){
		next = now->next;
		free(now);
		now = next;
	}
	free(list);
	return 0;
}


int _popOffset(MemList *list, int size){
	int offset = -3;
	int index = -1;
	int counter = 0;
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	MemElement *now = list->head->next;
	if (!now) {return offset;}
	MemElement *possible = NULL;
	for (now; now; now=now->next){
		if (now->size>=size){
			if (!possible){
				possible = now;
				index = counter;
			} else if (possible->size>now->size){
				possible = now;
				index = counter;
			}
		}
		counter++;
	}
	if (possible){
		offset = possible->offset;
	}
	if (index>=0){
		_delFromMemList(list, index);
	}
	return offset;
}


int writeInFileMemList(MemList *list){
	FILE *file = fopen("memList.bin", "w+b");
	int len = _getLenMemList(list);
	if (len<=0) {
		len = 0;
		fwrite(&len, 1, sizeof(int), file);
		fclose(file);
		return -1;
	}
	fwrite(&len, 1, sizeof(int), file);
	MemElement *now = list->head->next;
	for (now; now; now=now->next){
		fwrite(&now->offset, 1, sizeof(int), file);
		fwrite(&now->size, 1, sizeof(int), file);
	}
	fclose(file);
	return 0;
}


int readFromFileMemList(MemList *list){
	FILE *file = fopen("memList.bin", "rb");
	if (!file) {return -1;}
	int len;
	fread(&len, 1, sizeof(int), file);
	if (len<=0) {
		fclose(file);
		return -2;
		}
	for (int i=0; i<len; i++){
		int offset, size;
		fread(&offset, 1, sizeof(int), file);
		fread(&size, 1, sizeof(int), file);
		MemElement *element = _initMemElement(offset, size);
		_addInMemList(list, element, 0);
	}
	fclose(file);
	return 0;
}
