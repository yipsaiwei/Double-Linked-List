#include "unity.h"
#include "DoubleLinkedList.h"
//#include "MemAlloc.h"
#include "mock_MemAlloc.h"
#include  "mock_DummyFree.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void  test_createList_given(){
  DoubleLinkedList  *list = malloc(sizeof(DoubleLinkedList));
  memAlloc_ExpectAndReturn(sizeof(DoubleLinkedList), list);
  list = createList();
  free(list);
}

void  test_linkedListCreateListItem_given(){
  ListItem  *item = malloc(sizeof(DoubleLinkedList));
  memAlloc_ExpectAndReturn(sizeof(ListItem), item);
  item = linkedListCreateListItem(NULL);
  free(item);
}

void  test_linkedListFreeListItem_given(){
  ListItem  item = {NULL, NULL, (void*)1010};
  memFree_Expect(&item);
  linkedListFreeListItem(&item);
}

void  test_linkedListFreeList_given_dummy(){
  DoubleLinkedList  *list = malloc(sizeof(DoubleLinkedList));
  ListItem  item = {NULL, NULL, (void  *)0123};
  list->head = &item;
  list->tail = &item;
  dummyFree_Expect(list->head->data);
  memFree_Expect(list);
  memFree_Expect(&item);
  linkedListFreeList(list, dummyFree);
  free(list);
}
