/*

AUTHOR: Rebecca Yu
DATE MODIFIED: 16-10-2019
PURPOSE:

*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
	
	typedef struct{
		int turn;
		char player;
		int locationX;
		int locationY;
	}LogEntry;
	
	typedef struct ListNode{
		void* data;
		struct ListNode* next;
		struct ListNode* prev;
	}ListNode;
	
	typedef struct{
		ListNode* head;
		ListNode* tail;
		int count;
	}LinkedList;
	
	typedef void(*cast)(LinkedList*, void*);
	
	LinkedList* createLinkedList();
	void insertStart(LinkedList* list, void* inData);
	void* removeStart(LinkedList* list);
	void insertLast(LinkedList* list, void* inData);
	void* removeLast(LinkedList* list);
	void printLinkedList(LinkedList* list, cast funcPtr);
	void freeLinkedList(LinkedList* list, cast funcPtr);

#endif 
