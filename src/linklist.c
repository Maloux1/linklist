#include "linklist.h"

list * createList(void * init(void *), void destroy(void *)){
	list * head = malloc(sizeof(list));
	if (head == NULL){
		record(RECORD_LOG_ERROR, "LinkList", "malloc error", RECORD_CHECK_ERRNO, __FILE__, __LINE__);
		return NULL;
	}
	head->first = NULL;
	head->last = NULL;
	head->size = 0;
	head->init = init;
	head->destroy = destroy;
	return head;
}

void freeList(list * head){
	elem * element = head->first, *next=NULL;
	if (head->destroy){ // if is outside while for efficiency
		while (element){
			next = element->next;
			head->destroy(element->data);
			free(element);
			element = next;
		}
	}
	else {
		while (element){
			next = element->next;
			free(element);
			element = next;
		}
	}
	free(head);
	return;
}

int appendElement(list * head, void * dataOrArg){
	elem * element = malloc(sizeof(elem));
	if (element == NULL){
		record(RECORD_LOG_ERROR, "LinkList", "malloc error", RECORD_CHECK_ERRNO, __FILE__, __LINE__);
		return 1;
	}
	void * data;
	if (head->init){
		if ((data = head->init(dataOrArg)) == NULL){
			record(RECORD_LOG_ERROR, "LinkList", "user defined function init error", RECORD_CHECK_ERRNO, __FILE__, __LINE__);
			free(element);
			return 1;
		}
	}
	else {
		data = dataOrArg;
	}
	element->next = NULL;
	element->prev = NULL;
	element->data = data;
	if (head->first == NULL){
		head->first = element;
		head->last = element;
		head->size = 1;
	}
	else {
		head->last->next = element;
		element->prev = head->last;
		head->last = element;
		head->size++;
	}
	return 0;
}

int prependElement(list * head, void * dataOrArg){
	elem * element = malloc(sizeof(elem));
	if (element == NULL){
		record(RECORD_LOG_ERROR, "LinkList", "malloc error", RECORD_CHECK_ERRNO, __FILE__, __LINE__);
		return 1;
	}
	void * data;
	if (head->init){
		if ((data = head->init(dataOrArg)) == NULL){
			record(RECORD_LOG_ERROR, "LinkList", "user defined function init error", RECORD_CHECK_ERRNO, __FILE__, __LINE__);
			free(element);
			return 1;
		}
	}
	else {
		data = dataOrArg;
	}
	element->next = NULL;
	element->prev = NULL;
	element->data = data;
	if (head->first == NULL){
		head->first = element;
		head->last = element;
		head->size = 1;
	}
	else {
		element->next = head->first;
		element->next->prev = element;
		head->first = element;
		head->size++;
	}
	return 0;
}

uint32_t sizeofList(list * head){
	return head->size;
}

elem * removeElement(list * head, elem * element){
	elem * ret = element->next;
	if (head->destroy){
		head->destroy(element->data);
	}
	if (element->prev == NULL){
		head->first = element->next;
	}
	else {
		element->prev->next = element->next;
	}
	if (element->next == NULL){
		head->last = element->prev;
	}
	else {
		element->next->prev = element->prev;
	}
	head->size--;
	free(element);
	return ret;
}
