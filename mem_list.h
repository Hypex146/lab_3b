#ifndef MEM_LIST_H
#define MEM_LIST_H

typedef struct _Element{
	int offset;
	int size;
	struct _Element *next;
} Element;

typedef struct _List{
	struct _Element *head;
} List;

Element *_initElement(int offset, int size);
List *initList();
int _addInList(List *list, Element *element, int index);
int _delFromList(List *list, int index);
int _getLenList(List *list);
Element *_getElementList(List *list, int index);
int clearList(List *list);
int _popOffset(List *list, int size);

#endif
