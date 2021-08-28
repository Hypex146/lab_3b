#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Element *_initElement(int offset, int size){
	Element *element = (Element*)malloc(1*sizeof(Element));
	element->offset = offset;
	element->size = size;
	element->next = NULL;
	return element;
}


List *initList(){
	List *list = (List*)malloc(1*sizeof(List));
	Element *head = _initElement(0, 0);
	list->head = head;
	return list;
}


int _addInList(List *list, Element *element, int index){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	Element *now = list->head;
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


int _delFromList(List *list, int index){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	Element *now = list->head;
	int i = 0;
	if (!now->next) {return 1;}
	while(i<index && now->next->next){
		now = now->next;
		i++;
	}
	Element *tmp = now->next;
	if (!tmp) {return 1;}
	now->next = now->next->next;
	free(tmp);
	if (i=index) {return 0;}
	return 1;
}


int _getLenList(List *list){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	Element *now = list->head;
	int len = 0;
	while(now->next){
		len++;
		now = now->next;
	}
	return len;
}


Element *_getElementList(List *list, int index){
	if (!list) {return NULL;}
	if (!list->head) {return NULL;}
	Element *now = list->head;
	int i = 0;
	while(i<=index && now->next){
		i++;
		now = now->next;
	}
	return now;
}


int clearList(List *list){
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	Element *now = list->head;
	Element *next = NULL;
	while (now){
		next = now->next;
		free(now);
		now = next;
	}
	free(list);
	return 0;
}


int _popOffset(List *list, int size){
	int offset = -3;
	int index = -1;
	int counter = 0;
	if (!list) {return -1;}
	if (!list->head) {return -2;}
	Element *now = list->head->next;
	if (!now) {return offset;}
	Element *possible = NULL;
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
		_delFromList(list, index);
	}
	return offset;
}


