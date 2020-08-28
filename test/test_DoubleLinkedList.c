#include "unity.h"
#include "DoubleLinkedList.h"
#include  "IntegerListItem.h"
#include  "MemAlloc.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void  freeData(void *dataToFree){
  Data  *data = dataToFree;
  if(data)
    free(data);
}

void  test_createList_given_empty(){
  DoubleLinkedList  *list = createList();
  TEST_ASSERT_NULL(list->head);
  TEST_ASSERT_NULL(list->tail);
  TEST_ASSERT_EQUAL(0, list->count);
  free(list);
}

void  test_createList_given_data(){
  Data  data = {193, 0.333};
  DoubleLinkedList  *list = createList();
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(0, list->count);
  TEST_ASSERT_EQUAL_PTR(NULL, list->head);
  TEST_ASSERT_EQUAL_PTR(NULL, list->tail);
  ListItem  item = {NULL, NULL, (void *)&data};
  linkedListAddItemToHead(&item, list);
  TEST_ASSERT_EQUAL_PTR(&item, list->head);
  TEST_ASSERT_EQUAL_PTR(&item, list->tail);
  TEST_ASSERT_EQUAL(193, ((Data *)(list->head->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(0.333, ((Data *)(list->head->data))->val2);
  free(list);
}

void  test_linkedListCreateListItem_given_empty(){
  ListItem  *item = linkedListCreateListItem(0);
  TEST_ASSERT_NULL(item->next);
  TEST_ASSERT_NULL(item->prev);
  TEST_ASSERT_NULL(item->data);
  free(item);
}


void  test_linkedListCreateListItem_given_data(){
  Data  data = {1010, 23.333};
  ListItem  *item = linkedListCreateListItem((void  *)&data);
  TEST_ASSERT_NOT_NULL(item);
  TEST_ASSERT_EQUAL(1010, ((Data  *)(item->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(23.333, ((Data  *)(item->data))->val2);
  free(item);
}


void  test_linkedListFreeListItem(){
  Data  data = {0123, 32.1911};
  ListItem  *item = linkedListCreateListItem((void  *)&data);
  TEST_ASSERT_EQUAL(0123, ((Data  *)(item->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(32.1911, ((Data  *)(item->data))->val2);
  TEST_ASSERT_EQUAL_PTR(&data, item->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item->next);
  TEST_ASSERT_EQUAL_PTR(NULL, item->prev);
  linkedListFreeListItem(item);
}

/* Add item to head.
 Before			
~~~~~~~ 
  list						        			         		
  head--------->NULL		  
  tail--------->NULL		  	
  count=0					        		    

Scenario1   
~~~~~~~~~
list			      item1		                                                                         
head---------->	next-------->NULL 
tail---------->	prev-------->NULL	
count=1			      12		

Scenario2
~~~~~~~~~
                   item2            item1
head--------------->next----------->next----->NULL
tail-----------	   -prev<-----------prev
count=2        |  |24		    12
               |  |		     ^
               | NULL		     |		           
               -----------------------
*/

//Scenario1 : add 1 item(item1) into list from head
void test_DoubleLinkedList_add_item_to_head_given_item1_expect_head_and_tail_point_to_item1_item1_next_and_prev_are_both_NULL()
{
  int count;
  DoubleLinkedList	list={NULL, NULL, 0};
  IntegerListItem		item1={NULL, NULL, 12};
  count=linkedListAddItemToHead((ListItem  *)&item1, &list );
  TEST_ASSERT_EQUAL(1, list.count);
  TEST_ASSERT_EQUAL_PTR(12, list.head->data);
  TEST_ASSERT_EQUAL_PTR(12, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
}

//Scenario2 : add two items (item1 and item2) into list from head
void test_DoubleLinkedList_add_item_to_head_given_2_items_expect_head_points_to_item2_tail_points_to_item1_item2_prev_and_item1_next_point_to_NULL()
{
  int count;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={(ListItem  *)&item1, (ListItem  *)&item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  count=linkedListAddItemToHead((ListItem  *)&item2, &list );
  TEST_ASSERT_EQUAL(2, list.count);
  TEST_ASSERT_EQUAL(2, count);
  TEST_ASSERT_EQUAL_PTR(24, list.head->data);
  TEST_ASSERT_EQUAL_PTR(12, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
}
/* Add item to head.
Scenario3
~~~~~~~~~
list		   item3	item2		item1
head--------------->next-------->next----------->next------->NULL
tail-----------    -prev<--------prev<-----------prev
count=3	      |	  | 36		  24		  12
              |   |				  ^	 
              |  NULL		      		  |	
               -----------------------------------
*/

//Scenario3 : Add three items into list from head
void test_DoubleLinkedList_add_item_to_head_given_three_items_expect_head_points_to_item3_tail_points_to_item1__item3_prev_and_item1_next_point_to_NULL()
{
  int count;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={(ListItem *)&item2,(ListItem *) &item1, 2};
  item2.next=(ListItem *)&item1;
  item1.prev=(ListItem *)&item2;
  item2.prev=NULL;
  item1.next=NULL;
  count=linkedListAddItemToHead((ListItem  *)&item3, &list );
  TEST_ASSERT_EQUAL(3, list.count);
  TEST_ASSERT_EQUAL(3, count);
  TEST_ASSERT_EQUAL(36, list.head->data);
  TEST_ASSERT_EQUAL(12, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.prev);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.next);
	
}
/* Add item to tail.
 Before		
~~~~~~~ 
list					        				      
head--------->NULL	
tail--------->NULL	
count=0				      					        
          |
          v
Scenario1  
~~~~~~~~~                                                                   
list		    item1		
head------->next-------->NULL
tail------->prev-------->NULL		
count=1		  12	             
          |
          v
Scenario2
~~~~~~~~~
list		   item1         item2
head--------------->next-------->next----->NULL
tail-----------    -prev<--------prev
count=2	       |  | 12		  24
               |  |		   ^	
               |  NULL		   | 
               --------------------               
*/

//Scenario1 : Add an item to list from tail
void test_DoubleLinkedList_add_item_to_tail_given_item1_expect_head_and_tail_point_to_item_1_item1_prev_and_item_1_next_point_to_NULL()
{
  int count;
  IntegerListItem		item1={NULL, NULL, 12};
  DoubleLinkedList	list={NULL, NULL, 0};
  count=linkedListAddItemToTail((ListItem  *)&item1, &list);	
  TEST_ASSERT_EQUAL(1, list.count);
  TEST_ASSERT_EQUAL(1, count);
  TEST_ASSERT_EQUAL_PTR(&item1, list.head);
  TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
  TEST_ASSERT_EQUAL_PTR(12, list.head->data);
  TEST_ASSERT_EQUAL_PTR(12, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);  
}

//Scenario2 : Add two items (item1 and item2) to the list from tail
void test_DoubleLinkedList_add_item_to_tail_given_item2_expect_head_points_to_item_1_tail_point_to_item2_item1_prev_and_item_2_next_point_to_NULL()
{
  int count;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  count=linkedListAddItemToTail((ListItem  *)&item2, &list);				
  TEST_ASSERT_EQUAL(2, list.count);
  TEST_ASSERT_EQUAL(2, count);
  TEST_ASSERT_EQUAL_PTR(&item1, list.head);
  TEST_ASSERT_EQUAL_PTR(&item2, list.tail);
  TEST_ASSERT_EQUAL_PTR(12, list.head->data);
  TEST_ASSERT_EQUAL_PTR(24, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.next);
}
/* Add item to tail.
Scenario3
list	           item1         item2		   item3
head--------------->next-------->next-------------->next------->NULL
tail-----------    -prev<--------prev<--------------prev
count=3	      |	  | 12		 24	            36
              |   |			             ^	 
              |  NULL		      	             |	
              ----------------------------------------
*/

//Scenario3 : Add 3 items(item1, item2, item3) to the list from tail
void test_DoubleLinkedList_add_item_to_tail_given_item3_expect_head_points_to_item_1_tail_point_to_item3_item1_prev_and_item_2_next_point_to_NULL()
{
  int count;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={(ListItem  *)&item1, (ListItem  *)&item2, 2};
  item2.next=NULL;
  item2.prev=(ListItem  *)&item1;
  item1.next=(ListItem  *)&item2;
  item1.prev=NULL;
  count=linkedListAddItemToTail((ListItem  *)&item3, &list);
  TEST_ASSERT_EQUAL(3, list.count);
  TEST_ASSERT_EQUAL(3, count);
  TEST_ASSERT_EQUAL_PTR(12, list.head->data);
  TEST_ASSERT_EQUAL_PTR(36, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
}

/* Remove item from head.
Scenario1
~~~~~~~~~
Before                  After
list	
head--------->NULL      return NULL
tail--------->NULL
count=0		

Scenario2
~~~~~~~~~                 
Before                                After
list       item1	              list
head------->next-------->NULL         head----->NULL	
tail------->prev-------->NULL         tail----->NULL	
count=1     12			      count=0	

Scenario3
~~~~~~~~~ 
Before                                              After
list		item1	     item2                 head--------->next----->NULL
head------------>next-------->next----->NULL        tail--------->prev----->NULL
tail--------    -prev<--------prev                  count=1		  24
count=2	    |  | 12	      24
            |  |	       ^	
            | NULL	       |	
            --------------------
*/

//Scenario1 : remove item from head of the list and return it(No item inside the list)
void test_DoubleLinkedList_remove_item_from_head_list_empty_expect_NULL_returned()
{
  IntegerListItem		*returnedItem;
  DoubleLinkedList	list={NULL, NULL, 0};
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromHead(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, returnedItem);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
}

//Scenario2 : remove item from the head of the list and return it(Only 1 item inside the list)
void test_DoubleLinkedList_remove_item_from_head_only_1_item_inside_expect_list_head_and_list_NULL_equal_NULL_count_equals_0()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item1, 1};
	item1.next=NULL;
  item1.prev=NULL;  
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromHead(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL(0, list.count);
}

//Scenario3 : remove item from the head of the list and return it(There are 2 items inside the list)
void test_DoubleLinkedList_remove_item_from_head_2_items_inside_expect_item2_prev_item2_next_point_to_NULL_head_tail_point_to_item2_count_equals_1()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item2, 2};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=NULL;
  item2.prev=(ListItem *)&item1;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromHead(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, list.head);
  TEST_ASSERT_EQUAL_PTR(24, list.head->data);
  TEST_ASSERT_EQUAL_PTR(&item2, list.tail);
  TEST_ASSERT_EQUAL_PTR(24, list.tail->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.next);
  TEST_ASSERT_EQUAL(1, list.count);
}
/* Remove item from head.
Scenario4
~~~~~~~~~
Before
list	           item1        item2	    item3
head--------------->next-------->next------>next---->NULL
tail-----------    -prev<--------prev<------prev
count=3	      |	  |	12       24	    36
              |   |			     ^	
              |  NULL		             |	
               ------------------------------
               
After
list	     item2	item3
head--------->next------>next----->NULL
tail---      -prev<------prev
count=2|     | 24	 36
       |     |		 ^
       |   NULL          |
       |                 |
       -------------------
*/

//Scenario4 : remove item from the head of the list and return it(There are 3 items inside the list)
void test_DoubleLinkedList_remove_item_from_head_3_items_inside_expect_item2_prev_item3_next_point_to_NULL_head_point_to_item2_tail_point_to_item3_count_equals_2()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item3, 3};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=(ListItem *)&item3;
  item2.prev=(ListItem *)&item1;
  item3.next=NULL;
  item3.prev=(ListItem *)&item2;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromHead(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, list.head);
  TEST_ASSERT_EQUAL(24, list.head->data);
  TEST_ASSERT_EQUAL_PTR(&item3, list.tail);
  TEST_ASSERT_EQUAL(36, list.tail->data);
  TEST_ASSERT_EQUAL(2, list.count);
}

//Extra test
//Scenario Extra : Remove item from the head of list and return it (There are 4 items inside the list)
/* Remove item from head.
ScenarioEx
~~~~~~~~~
Before
list		   item1	item2	   item3    item4
head--------------->next-------->next------>next---->next---->NULL
tail-----------    -prev<--------prev<------prev<----prev
count=4	      |	  |  12		  24	    36        48
              |   |			              ^	
              |  NULL		      		      |	
               ---------------------------------------
               
After
list	     item2	item3     item4
head--------->next------>next----->next--->NULL
tail---      -prev<------prev<-----prev
count=3|     |24	 36        48
       |     |			    ^
       |   NULL                     |
       |                            |
       ------------------------------
*/
void test_DoubleLinkedList_remove_item_from_head_4_items_inside_expect_item2_prev_item4_next_point_to_NULL_head_point_to_item2_tail_point_to_item4_count_equals_3()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  IntegerListItem		item4={NULL, NULL, 48};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item4, 4};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=(ListItem *)&item3;
  item2.prev=(ListItem *)&item1;
  item3.next=(ListItem *)&item4;
  item3.prev=(ListItem *)&item2;
  item4.next=NULL;
  item4.prev=(ListItem *)&item3;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromHead(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item4, item3.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item4.next);
  TEST_ASSERT_EQUAL_PTR(&item3, item4.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, list.head);
  TEST_ASSERT_EQUAL_PTR(&item4, list.tail);
  TEST_ASSERT_EQUAL(3, list.count);
}

/* Remove item from tail.
Scenario1
~~~~~~~~~
Before                    After
list                      return NULL
head--------->NULL
tail--------->NULL
count=0	

Scenario2
~~~~~~~~~
Before                              After
list	      item1	                  list
head------->next-------->NULL       head----->NULL
tail------->prev-------->NULL       tail----->NULL
count=1		  12                      count-0
  
Scenario3
~~~~~~~~~
Before                                             After
list		   item1	 item2               list	 item1
head--------------->next-------->next----->NULL     head--------->next----->NULL
tail-----------    -prev<--------prev               tail--------->prev----->NULL
count=2	      |	  |	12	  24                count=1		  12
              |   |		  ^	                
              |  NULL		  |	              
              --------------------             
*/

//Scenario1 : Remove item from the tail of list and return it (No item inside the list)
void test_DoubleLinkedList_remove_item_from_tail_list_empty_expect_NULL_returned()
{
  IntegerListItem		*returnedItem;
  DoubleLinkedList	list={NULL, NULL, 0};
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromTail(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, returnedItem);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
}

//Scenario2 : Remove item from the tail of list and return it (Only 1 item inside the list)
void test_DoubleLinkedList_remove_item_from_tail_only_1_item_inside_expect_list_head_and_list_NULL_equal_NULL_count_equals_0()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  DoubleLinkedList	list={(ListItem *)&item1,(ListItem *) &item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromTail(&list); 
  TEST_ASSERT_EQUAL(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL(0, list.count);
}

//Scenario3 : Remove item from the tail of list and return it (There are 2 items inside the list)
void test_DoubleLinkedList_remove_item_from_tail_2_items_inside_expect_item1_prev_item1_next_point_to_NULL_head_tail_point_to_item1_count_equals_1()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item2, 2};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=NULL;
  item2.prev=(ListItem *)&item1;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromTail(&list); 
  TEST_ASSERT_EQUAL(24, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.next);
  TEST_ASSERT_EQUAL_PTR(&item1, list.head);
  TEST_ASSERT_EQUAL_PTR(&item1, list.tail);
  TEST_ASSERT_EQUAL(1, list.count);
}

/* Remove item from tail.
Scenario4
~~~~~~~~~
Before
list		   item1        item2	   item3
head--------------->next-------->next------>next---->NULL
tail-----------    -prev<--------prev<------prev
count=3	      |	  |	12	 24	    36
              |   |			    ^	
              |  NULL		      	    |	
               ------------------------------
After
list		  item1		 item2
head--------->next------>next----->NULL
tail---      -prev<------prev
count=2|     | 12	 24
       |     |		  ^
       |    NULL	  |
       |                  |
        -------------------
*/

//Scenario4 : Remove item from the tail of list and return it (There are 3 items inside the list)
void test_DoubleLinkedList_remove_item_from_tail_3_items_inside_expect_item1_prev_item2_next_point_to_NULL_head_point_to_item1_tail_point_to_item2_count_equals_2()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={(ListItem *)&item1, (ListItem *)&item3, 3};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=(ListItem *)&item3;
  item2.prev=(ListItem *)&item1;
  item3.next=NULL;
  item3.prev=(ListItem *)&item2;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromTail(&list); 
  TEST_ASSERT_EQUAL_PTR(36, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, list.head);
  TEST_ASSERT_EQUAL_PTR(&item2, list.tail);
  TEST_ASSERT_EQUAL(2, list.count);
}

//Extra test
//Scenario Extra : Remove item from the tail of list and return it (There are 4 items inside the list)
/* Remove item from tail.
ScenarioEx
~~~~~~~~~
Before
list		   item1	item2	   item3    item4
head--------------->next-------->next------>next---->next---->NULL
tail-----------    -prev<--------prev<------prev<----prev
count=4	      |	  |  12		 24	    36        48
              |   |				      ^	
              |  NULL		      		      |	
               ---------------------------------------
               
After
list	     item1      item2     item3
head--------->next------>next----->next--->NULL
tail---      -prev<------prev<-----prev
count=3|     |12	 24        36
       |     |			    ^
       |   NULL                     |
       |                            |
       ------------------------------
*/
void test_DoubleLinkedList_remove_item_from_tail_4_items_inside_expect_item1_prev_item3_next_point_to_NULL_head_point_to_item1_tail_point_to_item3_count_equals_3()
{
  IntegerListItem		*returnedItem;
  IntegerListItem		item1={NULL, NULL, 12};
  IntegerListItem		item2={NULL, NULL, 24};
  IntegerListItem		item3={NULL, NULL, 36};
  IntegerListItem		item4={NULL, NULL, 48};
  DoubleLinkedList	list={(ListItem *)&item1,(ListItem  *) &item4, 4};
  item1.next=(ListItem *)&item2;
  item1.prev=NULL;
  item2.next=(ListItem *)&item3;
  item2.prev=(ListItem *)&item1;
  item3.next=(ListItem *)&item4;
  item3.prev=(ListItem *)&item2;
  item4.next=NULL;
  item4.prev=(ListItem *)&item3;
  returnedItem = (IntegerListItem *)linkedListRemoveItemFromTail(&list); 
  TEST_ASSERT_EQUAL_PTR(48, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(&item2, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item1, list.head);
  TEST_ASSERT_EQUAL_PTR(&item3, list.tail);
  TEST_ASSERT_EQUAL(3, list.count);
}


void  test_linkedListCreateListItem_linkedListAddItemToHead_given_Data_struct(){
  Data  data1 = {10101, 293e-2};
  Data  data2 = {0x284, 12.456};
  Data  data3 = {0111, 5.6666};
  ListItem  *item1 = linkedListCreateListItem((Data *)&data1);
  ListItem  *item2 = linkedListCreateListItem((Data *)&data2);
  ListItem  *item3 = linkedListCreateListItem((Data *)&data3);
  DoubleLinkedList  list = {NULL, NULL, 0};
  linkedListAddItemToHead(item1, &list);
  TEST_ASSERT_EQUAL_PTR(item1, list.head);
  TEST_ASSERT_EQUAL_PTR(item1, list.tail);
  //Typecast list.head->data from void* to Data* type
  TEST_ASSERT_EQUAL(10101, ((Data  *)(list.head->data))->val1);   
  TEST_ASSERT_EQUAL(10101, ((Data  *)(list.tail->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(293e-2, ((Data  *)(list.head->data))->val2);
  TEST_ASSERT_EQUAL_FLOAT(293e-2, ((Data  *)(list.tail->data))->val2);
  linkedListAddItemToHead(item2, &list);
  TEST_ASSERT_EQUAL(0x284, ((Data  *)(list.head->data))->val1);
  TEST_ASSERT_EQUAL(10101, ((Data  *)(list.tail->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(293e-2, ((Data  *)(list.tail->data))->val2);
  TEST_ASSERT_EQUAL_FLOAT(12.456, ((Data  *)(list.head->data))->val2);
  linkedListAddItemToHead(item3, &list);
  TEST_ASSERT_EQUAL(0111, ((Data  *)(list.head->data))->val1);
  TEST_ASSERT_EQUAL(10101, ((Data  *)(list.tail->data))->val1);
  TEST_ASSERT_EQUAL(0x284, ((Data  *)(list.head->next->data))->val1);
  TEST_ASSERT_EQUAL(0x284, ((Data  *)(list.tail->prev->data))->val1);
  TEST_ASSERT_EQUAL_FLOAT(293e-2, ((Data  *)(list.tail->data))->val2);
  TEST_ASSERT_EQUAL_FLOAT(5.6666, ((Data  *)(list.head->data))->val2);
  TEST_ASSERT_EQUAL_FLOAT(12.456, ((Data  *)(list.head->next->data))->val2);
  TEST_ASSERT_EQUAL_FLOAT(12.456, ((Data  *)(list.tail->prev->data))->val2);
  if(item1)
    free(item1);
  if(item2)
    free(item2);
  if(item3)
    free(item3);
}


/*
struct  Data  {
  int val1;
  double  val2;
};
void  linkedListFreeList(DoubleLinkedList *list, void (*freeFunction)(void *) );
void  freeData(void *data){
  
}
void  test_linkedListFreeList(){
  linkedListFreeList(list, freeData);
}
*/

