#include "unity.h"
#include "DoubleLinkedList.h"

void setUp(void)
{
}

void tearDown(void)
{
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
count=2		     |	|	24				      12
               |  |		               ^
               | NULL				         |		           
               -----------------------
*/

//Scenario1 : add 1 item(item1) into list from head
void test_DoubleLinkedList_add_item_to_head_given_item1_expect_head_and_tail_point_to_item1_item1_next_and_prev_are_both_NULL()
{
  int count;
  DoubleLinkedList	list={NULL, NULL, 0};
  ListItem		item1={NULL, NULL, 12};
  count=addItemToHead(&item1, &list );
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
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={&item1, &item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  count=addItemToHead(&item2, &list );
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
list				        item3		    item2			 	        item1
head--------------->next-------->next----------->next------->NULL
tail-----------    -prev<--------prev<-----------prev
count=3		    |	  |	36		        24					   12
              |   |				  					            ^	 
              |  NULL		      					          |	
               -----------------------------------
*/

//Scenario3 : Add three items into list from head
void test_DoubleLinkedList_add_item_to_head_given_three_items_expect_head_points_to_item3_tail_points_to_item1__item3_prev_and_item1_next_point_to_NULL()
{
  int count;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={&item2, &item1, 2};
  item2.next=&item1;
  item1.prev=&item2;
  item2.prev=NULL;
  item1.next=NULL;
  count=addItemToHead(&item3, &list );
  TEST_ASSERT_EQUAL(3, list.count);
  TEST_ASSERT_EQUAL(3, count);
  TEST_ASSERT_EQUAL_PTR(36, list.head->data);
  TEST_ASSERT_EQUAL_PTR(12, list.tail->data);
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
list				        item1		    item2
head--------------->next-------->next----->NULL
tail-----------    -prev<--------prev
count=2		     |	  |	12		     24
               |    |				      ^	
               |    NULL		      | 
               --------------------               
*/

//Scenario1 : Add an item to list from tail
void test_DoubleLinkedList_add_item_to_tail_given_item1_expect_head_and_tail_point_to_item_1_item1_prev_and_item_1_next_point_to_NULL()
{
  int count;
  ListItem		item1={NULL, NULL, 12};
  DoubleLinkedList	list={NULL, NULL, 0};
  count=addItemToTail(&item1, &list);	
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
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={&item1, &item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  count=addItemToTail(&item2, &list);				
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
list				        item1		    item2			 	        item3
head--------------->next-------->next-------------->next------->NULL
tail-----------    -prev<--------prev<--------------prev
count=3		    |	  |	12		       24					        36
              |   |				  					                ^	 
              |  NULL		      					              |	
               ----------------------------------------
*/

//Scenario3 : Add 3 items(item1, item2, item3) to the list from tail
void test_DoubleLinkedList_add_item_to_tail_given_item3_expect_head_points_to_item_1_tail_point_to_item3_item1_prev_and_item_2_next_point_to_NULL()
{
  int count;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={&item1, &item2, 2};
  item2.next=NULL;
  item2.prev=&item1;
  item1.next=&item2;
  item1.prev=NULL;
  count=addItemToTail(&item3, &list);
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
list		    item1	                    list
head------->next-------->NULL         head----->NULL	
tail------->prev-------->NULL         tail----->NULL	
count=1		   12						            count=0	

Scenario3
~~~~~~~~~ 
Before                                              After
list				     item1		    item2                 head--------->next----->NULL
head------------>next-------->next----->NULL        tail--------->prev----->NULL
tail--------    -prev<--------prev                  count=1		  24
count=2		  |	  |	12		       24
            |   |				        ^	
            |  NULL		          |	
            --------------------
*/

//Scenario1 : remove item from head of the list and return it(No item inside the list)
void test_DoubleLinkedList_remove_item_from_head_list_empty_expect_NULL_returned()
{
  ListItem		*returnedItem;
  DoubleLinkedList	list={NULL, NULL, 0};
  returnedItem = removeItemFromHead(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, returnedItem);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
}

//Scenario2 : remove item from the head of the list and return it(Only 1 item inside the list)
void test_DoubleLinkedList_remove_item_from_head_only_1_item_inside_expect_list_head_and_list_NULL_equal_NULL_count_equals_0()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={&item1, &item1, 1};
	item1.next=NULL;
  item1.prev=NULL;  
  returnedItem = removeItemFromHead(&list); 
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
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={&item1, &item2, 2};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=NULL;
  item2.prev=&item1;
  returnedItem = removeItemFromHead(&list); 
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
list				        item1		     item2		  item3
head--------------->next-------->next------>next---->NULL
tail-----------    -prev<--------prev<------prev
count=3		    |	  |	12		       24			    36
              |   |				  			          ^	
              |  NULL		      			        |	
               ------------------------------
               
After
list		  item2		 item3
head--------->next------>next----->NULL
tail---      -prev<------prev
count=2|	   |24		      36
       |     |			      ^
	     |	  NULL          |
	     |                  |
	     -------------------
*/

//Scenario4 : remove item from the head of the list and return it(There are 3 items inside the list)
void test_DoubleLinkedList_remove_item_from_head_3_items_inside_expect_item2_prev_item3_next_point_to_NULL_head_point_to_item2_tail_point_to_item3_count_equals_2()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={&item1, &item3, 3};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=&item3;
  item2.prev=&item1;
  item3.next=NULL;
  item3.prev=&item2;
  returnedItem = removeItemFromHead(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, item2.prev);
  TEST_ASSERT_EQUAL_PTR(&item3, item2.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item3.next);
  TEST_ASSERT_EQUAL_PTR(&item2, item3.prev);
  TEST_ASSERT_EQUAL_PTR(&item2, list.head);
  TEST_ASSERT_EQUAL_PTR(24, list.head->data);
  TEST_ASSERT_EQUAL_PTR(&item3, list.tail);
  TEST_ASSERT_EQUAL_PTR(36, list.tail->data);
  TEST_ASSERT_EQUAL(2, list.count);
}

//Extra test
//Scenario Extra : Remove item from the head of list and return it (There are 4 items inside the list)
/* Remove item from head.
ScenarioEx
~~~~~~~~~
Before
list				        item1		     item2		  item3    item4
head--------------->next-------->next------>next---->next---->NULL
tail-----------    -prev<--------prev<------prev<----prev
count=4		    |	  |	12		       24			    36        48
              |   |				  			                    ^	
              |  NULL		      			                  |	
               ---------------------------------------
               
After
list		  item2		 item3            item4
head--------->next------>next----->next--->NULL
tail---      -prev<------prev<-----prev
count=3|	   |24		      36        48
       |     |			                 ^
	     |	  NULL                     |
	     |                             |
	     ------------------------------
*/
void test_DoubleLinkedList_remove_item_from_head_4_items_inside_expect_item2_prev_item4_next_point_to_NULL_head_point_to_item2_tail_point_to_item4_count_equals_3()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  ListItem		item4={NULL, NULL, 48};
  DoubleLinkedList	list={&item1, &item4, 4};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=&item3;
  item2.prev=&item1;
  item3.next=&item4;
  item3.prev=&item2;
  item4.next=NULL;
  item4.prev=&item3;
  returnedItem = removeItemFromHead(&list); 
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
list				        item1		    item2               list		      item1
head--------------->next-------->next----->NULL     head--------->next----->NULL
tail-----------    -prev<--------prev               tail--------->prev----->NULL
count=2		    |	  |	12		        24                count=1		  12
              |   |				        ^	                
              |  NULL		          |	              
              --------------------             
*/

//Scenario1 : Remove item from the tail of list and return it (No item inside the list)
void test_DoubleLinkedList_remove_item_from_tail_list_empty_expect_NULL_returned()
{
  ListItem		*returnedItem;
  DoubleLinkedList	list={NULL, NULL, 0};
  returnedItem = removeItemFromTail(&list);
  TEST_ASSERT_EQUAL_PTR(NULL, returnedItem);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
}

//Scenario2 : Remove item from the tail of list and return it (Only 1 item inside the list)
void test_DoubleLinkedList_remove_item_from_tail_only_1_item_inside_expect_list_head_and_list_NULL_equal_NULL_count_equals_0()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  DoubleLinkedList	list={&item1, &item1, 1};
  item1.next=NULL;
  item1.prev=NULL;
  returnedItem = removeItemFromTail(&list); 
  TEST_ASSERT_EQUAL_PTR(12, returnedItem->data);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.next);
  TEST_ASSERT_EQUAL_PTR(NULL, item1.prev);
  TEST_ASSERT_EQUAL_PTR(NULL, list.head);
  TEST_ASSERT_EQUAL_PTR(NULL, list.tail);
  TEST_ASSERT_EQUAL(0, list.count);
}

//Scenario3 : Remove item from the tail of list and return it (There are 2 items inside the list)
void test_DoubleLinkedList_remove_item_from_tail_2_items_inside_expect_item1_prev_item1_next_point_to_NULL_head_tail_point_to_item1_count_equals_1()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  DoubleLinkedList	list={&item1, &item2, 2};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=NULL;
  item2.prev=&item1;
  returnedItem = removeItemFromTail(&list); 
  TEST_ASSERT_EQUAL_PTR(24, returnedItem->data);
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
list				        item1		     item2		  item3
head--------------->next-------->next------>next---->NULL
tail-----------    -prev<--------prev<------prev
count=3		    |	  |	12		        24			  36
              |   |				  			           ^	
              |  NULL		      			         |	
               ------------------------------
After
list		  item1		 item2
head--------->next------>next----->NULL
tail---      -prev<------prev
count=2|	  |12		       24
       |     |			     ^
       |	NULL		       |
	     |                 |
	     -------------------
*/

//Scenario4 : Remove item from the tail of list and return it (There are 3 items inside the list)
void test_DoubleLinkedList_remove_item_from_tail_3_items_inside_expect_item1_prev_item2_next_point_to_NULL_head_point_to_item1_tail_point_to_item2_count_equals_2()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  DoubleLinkedList	list={&item1, &item3, 3};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=&item3;
  item2.prev=&item1;
  item3.next=NULL;
  item3.prev=&item2;
  returnedItem = removeItemFromTail(&list); 
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
list				        item1		     item2		  item3    item4
head--------------->next-------->next------>next---->next---->NULL
tail-----------    -prev<--------prev<------prev<----prev
count=4		    |	  |	12		       24			    36        48
              |   |				  			                    ^	
              |  NULL		      			                  |	
               ---------------------------------------
               
After
list		      item1		 item2       item3
head--------->next------>next----->next--->NULL
tail---      -prev<------prev<-----prev
count=3|	   |12		      24        36
       |     |			                 ^
	     |	  NULL                     |
	     |                             |
	     ------------------------------
*/
void test_DoubleLinkedList_remove_item_from_tail_4_items_inside_expect_item1_prev_item3_next_point_to_NULL_head_point_to_item1_tail_point_to_item3_count_equals_3()
{
  ListItem		*returnedItem;
  ListItem		item1={NULL, NULL, 12};
  ListItem		item2={NULL, NULL, 24};
  ListItem		item3={NULL, NULL, 36};
  ListItem		item4={NULL, NULL, 48};
  DoubleLinkedList	list={&item1, &item4, 4};
  item1.next=&item2;
  item1.prev=NULL;
  item2.next=&item3;
  item2.prev=&item1;
  item3.next=&item4;
  item3.prev=&item2;
  item4.next=NULL;
  item4.prev=&item3;
  returnedItem = removeItemFromTail(&list); 
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