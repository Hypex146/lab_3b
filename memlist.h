#ifndef LIST_H
#define LIST_H

typedef struct _MemElement{
	int offset;
	int size;
	struct _MemElement *next;
} MemElement;

typedef struct _MemList{
	struct _MemElement *head;
} MemList;

MemElement *_initMemElement(int offset, int size);
MemList *_initMemList();
int _addInMemList(MemList *list, MemElement *element, int index);
int _delFromMemList(MemList *list, int index);
int _getLenMemList(MemList *list);
MemElement *_getElementMemList(MemList *list, int index);
int clearMemList(MemList *list);
int _popOffset(MemList *list, int size);
int writeInFileMemList(MemList *list);
int readFromFileMemList(MemList *list);

#endif
