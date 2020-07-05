#include "DoubleLinkedList.h"
#include <stdio.h>
#include <stdlib.h>


int	addItemToHead(ListItem* Item, DoubleLinkedList* accList){
	int count;
	if(accList->head==NULL)
	{
		accList->head=Item;
		accList->tail=Item;
		accList->count=1;
		count=accList->count;
		return count;
	}
	else
	{
		Item->next=accList->head;
		accList->head->prev=Item;
		accList->head=Item;
		Item->prev=NULL;
		accList->count++;
		count=accList->count;
		return count;		
	}
}

int addItemToTail(ListItem* Item , DoubleLinkedList* accList){
	int count;
	if(accList->head==NULL)
	{
		accList->head=Item;
		accList->tail=Item;
		accList->count=1;
		count=accList->count;
		return count;
	}
	else
	{
		Item->prev=accList->tail;
		accList->tail->next=Item;
		Item->next=NULL;
		accList->tail=Item;
		accList->count++;
		count=accList->count;
		return count;	
	}
}

ListItem* removeItemFromHead(DoubleLinkedList* accList)
{
	ListItem	*returnedItem={NULL, NULL, 0};
	if(accList->head==NULL)
		return NULL;
	else if (accList->head==accList->tail)
	{
		returnedItem=accList->head;
		accList->head=NULL;
		accList->tail=NULL;
		accList->count--;
		return returnedItem;
	}
	else
	{
		returnedItem=accList->head;
		accList->head->next->prev=NULL;
		accList->head=accList->head->next;
		returnedItem->next=NULL;
		returnedItem->prev=NULL;
		accList->count--;
		return	returnedItem;
	}
}

ListItem* removeItemFromTail(DoubleLinkedList* accList)
{
	ListItem	*returnedItem={NULL, NULL, 0};
	if(accList->head==NULL)
		return NULL;
	else if (accList->head==accList->tail)
	{
		returnedItem=accList->tail;
		accList->head=NULL;
		accList->tail=NULL;
		accList->count--;
		return returnedItem;
	}
	else
	{
		returnedItem=accList->tail;
		accList->tail->prev->next=NULL;
		accList->tail=accList->tail->prev;
		returnedItem->next=NULL;
		returnedItem->prev=NULL;
		accList->count--;
		return	returnedItem;
	}
}