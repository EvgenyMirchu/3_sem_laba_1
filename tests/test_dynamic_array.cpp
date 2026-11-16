#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "dynamic_array.h"


TEST(DynamicArray, DefaultIsEmpty) 
{
    DynamicArray<int> array;
    EXPECT_EQ(array.GetSize(), 0);
}

TEST(DynamicArray, SizeConstructorZeroInitializes) 
{
    DynamicArray<int> array(3);
    ASSERT_EQ(array.GetSize(), 3);
    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(array.Get(i), 0);
}

TEST(DynamicArray, PointerCellsAreNull) 
{
    DynamicArray<int*> array(4);
    for (int i = 0; i < 4; ++i)
        EXPECT_EQ(array.Get(i), nullptr);
}

TEST(DynamicArray, ConstructFromArrayCopiesElements) 
{
    int items[] = {5, 6, 7};
    DynamicArray<int> array(items, 3);
    items[0] = 100;                              
    EXPECT_EQ(array.Get(0), 5);                      
    EXPECT_EQ(array.Get(2), 7);
}

TEST(DynamicArray, SetThenGet) 
{
    DynamicArray<std::string> array(2);
    array.Set(1, "tree");
    EXPECT_EQ(array.Get(1), "tree");
    EXPECT_EQ(array[0], "");                         
}

TEST(DynamicArray, OutOfRangeThrows) 
{
    DynamicArray<int> array(3);
    EXPECT_THROW(array.Get(-1), IndexOutOfRange);
    EXPECT_THROW(array.Get(3), IndexOutOfRange);
    EXPECT_THROW(array.Set(3, 1), IndexOutOfRange);
    EXPECT_THROW(array[3], IndexOutOfRange);
}

TEST(DynamicArray, InvalidArgumentsThrow) 
{
    EXPECT_THROW(DynamicArray<int>(-1), InvalidArgument);
    EXPECT_THROW(DynamicArray<int>(nullptr, 2), InvalidArgument);
    DynamicArray<int> array(2);
    EXPECT_THROW(array.Resize(-5), InvalidArgument);
}

TEST(DynamicArray, CopyIsIndependent) 
{
    int items[] = {1, 2, 3};
    DynamicArray<int> array_1(items, 3);
    DynamicArray<int> array_2 = array_1;                     
    array_2.Set(0, 99);
    EXPECT_EQ(array_1.Get(0), 1);                      
    EXPECT_EQ(array_2.Get(0), 99);
}

TEST(DynamicArray, AssignmentAndSelfAssignment) 
{
    int items[] = {1, 2, 3};
    DynamicArray<int> array_1(items, 3);
    DynamicArray<int> array_2(1);
    array_2 = array_1;
    EXPECT_EQ(array_2.GetSize(), 3);
    EXPECT_EQ(array_2.Get(2), 3);
    array_1 = array_1;                                       
    EXPECT_EQ(array_1.GetSize(), 3);
    EXPECT_EQ(array_1.Get(1), 2);
}

TEST(DynamicArray, ResizeUpKeepsOldAndZeroesNew) 
{
    int items[] = {1, 2};
    DynamicArray<int> array(items, 2);
    array.Resize(4);
    ASSERT_EQ(array.GetSize(), 4);
    EXPECT_EQ(array.Get(1), 2);
    EXPECT_EQ(array.Get(3), 0);
}

TEST(DynamicArray, ResizeDownAndToZero) 
{
    int items[] = {1, 2, 3};
    DynamicArray<int> array(items, 3);
    array.Resize(1);
    ASSERT_EQ(array.GetSize(), 1);
    EXPECT_EQ(array.Get(0), 1);
    EXPECT_THROW(array.Get(1), IndexOutOfRange);
    array.Resize(0);
    EXPECT_EQ(array.GetSize(), 0);
}

TEST(DynamicArray, MoveTakesDataAndLeavesSourceEmpty) 
{
    int items[] = {1, 2, 3};
    DynamicArray<int> array_1(items, 3);
    DynamicArray<int> array_2 = std::move(array_1);
    EXPECT_EQ(array_2.GetSize(), 3);
    EXPECT_EQ(array_2.Get(2), 3);
    EXPECT_EQ(array_1.GetSize(), 0);
}