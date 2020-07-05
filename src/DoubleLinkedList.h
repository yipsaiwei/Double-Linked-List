#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

typedef	struct	ListItem	ListItem;
struct ListItem{
	ListItem		*next;
	ListItem		*prev;
	int			data;
};

typedef	struct	DoubleLinkedList	DoubleLinkedList;
struct	DoubleLinkedList{
	ListItem		*head;
	ListItem		*tail;
	int			count;
};

int	addItemToHead(ListItem* , DoubleLinkedList* );
int addItemToTail(ListItem* , DoubleLinkedList* );	
ListItem *removeItemFromHead(DoubleLinkedList* );
ListItem *removeItemFromTail(DoubleLinkedList* );
#endif // DOUBLELINKEDLIST_H
