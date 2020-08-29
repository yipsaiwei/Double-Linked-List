#include "unity.h"
#include "DoubleLinkedList.h"
//#include "MemAlloc.h"
#include "mock_MemAlloc.h"
#include  "mock_DummyFree.h"
#include  "IntegerListItem.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void  test_createList_given(){
  DoubleLinkedList  list = {NULL, NULL, 0};
  DoubleLinkedList  *listptr;
  memAlloc_ExpectAndReturn(sizeof(DoubleLinkedList), &list);
  listptr = createList();
  
}

void  test_linkedListCreateListItem_given(){
  ListItem  item = {NULL, NULL, (void *)1234};
  ListItem  *itemptr;
  memAlloc_ExpectAndReturn(sizeof(ListItem), &item);
  itemptr = linkedListCreateListItem(NULL);
}

void  test_linkedListFreeListItem_given(){
  ListItem  item = {NULL, NULL, (void*)1010};
  memFree_Expect(&item);
  linkedListFreeListItem(&item);
}

void  test_linkedListFreeList_given_dummy(){
  DoubleLinkedList  list = {NULL, NULL, 0};
  DoubleLinkedList  *listptr = &list;
  ListItem  item = {NULL, NULL, (void  *)&data};
  listptr->head = &item;
  listptr->tail = &item;
  dummyFree_Expect(listptr->head->data);
  memFree_Expect(listptr);
  memFree_Expect(&item);
  linkedListFreeList(listptr, dummyFree);
}

