#include "unity.h"
#include  "mock_MemAlloc.h"
#include "Data.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createData_given_empty_data(){
    Data  data;
    Data  *dataptr;
    memAlloc_ExpectAndReturn(sizeof(Data), &data);
    dataptr = createData();
    TEST_ASSERT_EQUAL(0, dataptr->val1);
    TEST_ASSERT_EQUAL(0, dataptr->val2);
}


void test_createData_given_data_assign_values(){
  Data  data;
  memAlloc_ExpectAndReturn(sizeof(Data), &data);
    Data  *dataptr = createData();
    dataptr->val1 = 123;
    dataptr->val2 = 1.342;
    TEST_ASSERT_EQUAL(123, dataptr->val1);
    TEST_ASSERT_EQUAL(1.342, dataptr->val2);
}

void  test_freeData(){
  Data  data = {1023, 1.324};
  memFree_Expect(&data);
  freeData(&data);
  
}
