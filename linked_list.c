/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 10-10-2019
PURPOSE: linked list data structure

*/

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "logs.h"

/* Create an empty linked list*/
LinkedList* createLinkedList()
{
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
	return list;
}

/* Insert element at the start */
void insertStart(LinkedList* list, void* inData)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	/*data must point to the value to be inserted*/
	newNode->data = inData;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	/*if list is empty...*/
	if(list->count == 0)
	{
		/*head and tail should point to newNode*/
		list->head = newNode;
		list->tail = newNode;
		list->count++;
	}
	else
	{
		/*point "next" of newNode to current head*/
		newNode->next = list->head;
		/*point "prev" of current head to the newNode*/
		list->head->prev = newNode;
		/*then, point head to newNode*/
		list->head = newNode;
		list->count++;
	}
}

/* Insert an element at the end*/
void insertLast(LinkedList* list, void* inData)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	/*data must point to the value to be inserted*/
	newNode->data = inData;
	newNode->next = NULL;
	newNode->prev = NULL;
	
	/*if list is empty...*/
	if(list->count == 0)
	{
		/*head and tail should point to newNode*/
		list->head = newNode;
		list->tail = newNode;
		list->count++;
	}
	else
	{
		/*point "prev" of newNode to current tail*/
		newNode->prev = list->tail;
		/*point "next" of current tail to newNode*/
		list->tail->next = newNode;
		/*then, point tail to newNode*/
		list->tail = newNode;
		list->count++;
	}
}

/* Remove an element at the start*/
void* removeStart(LinkedList* list)
{
	void* retValue;
	retValue = NULL;
	
	/*if list is NOT empty...*/
	if(list->count != 0)
	{
		/*delete current head*/
		retValue = list->head->data;
		free(list->head);
		/*if list has only ONE node...*/
		if(list->count == 1)
		{
			list->head = NULL;
			list->tail = NULL;
			list->count--;
		}
		else
		{
			list->head = list->head->next;
			list->head->prev = NULL;
			list->count--;
		}
	}
	else
	{
		printf("Error! List is Empty! Can't remove first node\n");
	}

	return retValue;
}

/* Removing element from the end*/
void* removeLast(LinkedList* list)
{
	void* retValue;
	retValue = NULL;
	
	/*if list is NOT empty...*/
	if(list->count != 0)
	{
		/*delete current tail*/
		retValue = list->tail->data;
		free(list->tail);
		/*if list has only ONE node...*/
		if(list->count == 1)
		{
			list->head = NULL;
			list->tail = NULL;
			list->count--;
		}
		else
		{
			list->tail = list->tail->prev;
			list->tail->next = NULL;
			list->count--;
		}
	}
	else
	{
		printf("Error! List is Empty! Can't remove last node\n");
	}
	return retValue;
}

/* Print contents of the list*/
void printLinkedList(LinkedList* list, cast funcPtr)
{
	ListNode *node, *nextNode;
	void* inData;
	
	node = list->head;
	while(node != NULL)
	{
		nextNode = node->next;
		inData = node->data;
		funcPtr(list, inData);
		node = nextNode;		
	}
}

/* Free the list*/
void freeLinkedList(LinkedList* list, cast funcPtr)
{
	ListNode *node, *nextNode;
	void* inData;
	node = list->head;
	while(node != NULL)
	{
		nextNode = node->next;
		inData = node->data;
		funcPtr(list, inData);
		free(node);
		node = nextNode;
	}
	free(list);
	list = NULL;
	/*printf("Process complete...List Freed!\n\n");*/
}