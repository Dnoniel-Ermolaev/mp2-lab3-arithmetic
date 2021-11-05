// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TStack <int> v(5));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> v(-5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> v(MAX_STACK_SIZE + 1));
}

TEST(TStack, can_create_copied_stack)
{
	TStack <int> v(10);

	ASSERT_NO_THROW(TStack <int> v1(v));
}
TEST(TStack, can_include_new_element)
{
	TStack <int> v(2);
	v.Include(5);
	EXPECT_EQ(5, v.Get());
}

TEST(TStack, cant_include_element_when_stack_is_full)
{
	TStack <int> v(2);
	v.Include(5);
	v.Include(7);
	ASSERT_NO_THROW(v.Include(9));
}

TEST(TStack, can_exclude_element)
{
	TStack <int> v(2);
	v.Include(5);
	EXPECT_EQ(5, v.Exclude());
	EXPECT_EQ(-1, v.Top);
}

TEST(TStack, can_get_element)
{
	TStack <int> v(2);
	v.Include(5);
	EXPECT_EQ(5, v.Get());
	EXPECT_EQ(0, v.Top);
}

TEST(TStack, cant_get_element_when_stack_is_empty)
{
	TStack <int> v(2);
	ASSERT_ANY_THROW(v.Get());
}

TEST(TStack, cant_exclude_element_when_stack_is_empty)
{
	TStack <int> v(2);
	ASSERT_ANY_THROW(v.Exclude());
}

TEST(TStack, new_stack_is_empty)
{
	TStack<int> v(2);
	EXPECT_TRUE(v.CheckEmpty());
}

TEST(TStack, can_check_full_stack)
{
	TStack<int> v(2);
	v.Include(5);
	v.Include(7);
	EXPECT_TRUE(v.CheckFull());
}

TEST(TStack, can_count_elements_without_elements)
{
	TStack<int> v(5);
	EXPECT_EQ(0, v.Count());
}

TEST(TStack, can_count_elements_with_elements)
{
	TStack<int> v(5);
	v.Include(1);
	v.Include(2);
	EXPECT_EQ(2, v.Count());
}
TEST(TStack, can_count_elements_with_all_elemets)
{
	TStack<int> v(2);
	v.Include(1);
	v.Include(2);
	EXPECT_EQ(2, v.Count());
}

TEST(TStack, can_over_allocate_memory)
{
	TStack <int> v(3);
	v.Include(1);
	v.Include(2);
	v.Include(3);
	EXPECT_EQ(3, v.Size);
}