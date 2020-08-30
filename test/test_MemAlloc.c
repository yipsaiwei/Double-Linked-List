#include "unity.h"
#include "DoubleLinkedList.h"
#include  "Data.h"
#include "mock_MemAlloc.h"
#include  "mock_DummyFree.h"


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
  listptr = linkedListCreateList();
  TEST_ASSERT_EQUAL_PTR(NULL, listptr->head);
  TEST_ASSERT_EQUAL_PTR(NULL, listptr->tail);
  TEST_ASSERT_EQUAL(0, listptr->count);
  
}

void  test_linkedListCreateListItem_given_NULL(){
  ListItem  item = {NULL, NULL, (void *)1234};
  ListItem  *itemptr;
  memAlloc_ExpectAndReturn(sizeof(ListItem), &item);
  itemptr = linkedListCreateListItem(NULL);
  TEST_ASSERT_EQUAL(NULL, itemptr->next);
  TEST_ASSERT_EQUAL(NULL, itemptr->prev);
  TEST_ASSERT_EQUAL(0, itemptr->data);
}

void  test_linkedListCreateListItem_given_data(){
  ListItem  item = {NULL, NULL, (void *)1234};
  ListItem  *itemptr;
  Data  data = {1937, 91.283};
  memAlloc_ExpectAndReturn(sizeof(ListItem), &item);
  itemptr = linkedListCreateListItem(&data);
  TEST_ASSERT_EQUAL(NULL, itemptr->next);
  TEST_ASSERT_EQUAL(NULL, itemptr->prev);
  TEST_ASSERT_EQUAL(1937, ((Data  *)(itemptr->data))->val1);
  TEST_ASSERT_EQUAL(91.283, ((Data  *)(itemptr->data))->val2);
}

void  test_linkedListFreeListItem_given(){
  ListItem  item = {NULL, NULL, (void*)1010};
  memFree_Expect(&item);
  linkedListFreeListItem(&item);
}

void  test_linkedListFreeList_given_dummy(){
  DoubleLinkedList  list = {NULL, NULL, 0};
  DoubleLinkedList  *listptr = &list;
  Data  data = {193, 0.333};
  ListItem  item = {NULL, NULL, (void  *)&data};
  listptr->head = &item;
  listptr->tail = &item;
  dummyFree_Expect(listptr->head->data);
  memFree_Expect(listptr);
  memFree_Expect(&item);
  linkedListFreeList(listptr, dummyFree);
}

