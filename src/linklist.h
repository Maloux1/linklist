#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdlib.h>
#include <stdint.h>
#include <record.h>

typedef struct elem elem;
struct elem{
	void * data;
	elem * prev;
	elem * next;
};

typedef struct list list;
struct list{
	elem * first;
	elem * last;
	uint32_t size;
	void * (*init)(void *);
	void (*destroy)(void *);
};

list * createList(void * init(void *), void destroy(void *));
void freeList(list *);
int appendElement(list *, void *);
int prependElement(list *, void *);
uint32_t sizeofList(list *);
elem * removeElement(list *, elem *);

#endif /* LINKLIST_H */
