#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{	
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3);
	TDynamicVector<int> b(a);
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int arr1[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(arr1, 3);
	TDynamicVector<int> c(a);

	c[0] = -1;
	int arr2[3] = { -1, 2, 3 };
	TDynamicVector<int> d(arr2, 3);

	EXPECT_EQ(a, b);
	EXPECT_EQ(c, d);
	EXPECT_NE(a, c);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> a(4);
	a[0] = 4;

	EXPECT_EQ(4, a[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{	
	TDynamicVector<int> a(2);

	ASSERT_ANY_THROW(a.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> a(2);

	ASSERT_ANY_THROW(a.at(3) = 1);
	ASSERT_ANY_THROW(a.at(MAX_VECTOR_SIZE) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3);
	a = a;

	EXPECT_EQ(a[0], 1);
	EXPECT_EQ(a[1], 2);
	EXPECT_EQ(a[2], 3);

}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3);
	TDynamicVector<int> b(3);
	b = a;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> a(3);
	TDynamicVector<int> b(4);
	a = b;

	EXPECT_EQ(a.size(), 4);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int arr1[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	int arr2[4] = { -1, -2, -3, -4 };
	TDynamicVector<int> b(arr2, 4);
	a = b;
	EXPECT_EQ(a.size(), 4);
	EXPECT_EQ(a[0], -1);
	EXPECT_EQ(a[1], -2);
	EXPECT_EQ(a[2], -3);
	EXPECT_EQ(a[3], -4);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3);
	TDynamicVector<int> b(arr, 3);
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3);

	EXPECT_TRUE(a == a);
	EXPECT_FALSE(a != a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> a(3), b(4);

	EXPECT_TRUE(a != b);
	EXPECT_FALSE(a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int arr1[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(a + 1);
	TDynamicVector<int> c(a);
	c += 1;

	int arr2[3] = { 2, 3, 4 };
	TDynamicVector<int> result(arr2, 3);

	EXPECT_NE(a, result);
	EXPECT_EQ(b, result);
	EXPECT_EQ(c, result);
}

TEST(TDynamicVector, can_increment_vector) // added
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3), b(arr, 3), c(3), d(3);
	c = ++a;
	d = b++;
	int arr1[3] = { 2, 3, 4 };
	TDynamicVector<int> result(arr1, 3);

	EXPECT_EQ(a, result);
	EXPECT_EQ(a, b);
	EXPECT_EQ(c, a);
	EXPECT_NE(b, d);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int arr1[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(a - 1);
	TDynamicVector<int> c(a);
	c -= 1;

	int arr2[3] = { 0, 1, 2 };
	TDynamicVector<int> result(arr2, 3);

	EXPECT_NE(a, result);
	EXPECT_EQ(b, result);
	EXPECT_EQ(c, result);
}

TEST(TDynamicVector, can_decrement_vector) // added
{
	int arr[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr, 3), b(arr, 3), c(3), d(3);
	c = --a;
	d = b--;
	int arr1[3] = { 0, 1, 2 };
	TDynamicVector<int> result(arr1, 3);

	EXPECT_EQ(a, result);
	EXPECT_EQ(a, b);
	EXPECT_EQ(c, a);
	EXPECT_NE(b, d);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int arr1[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(a * 2);
	TDynamicVector<int> c(a);
	c *= 2;

	int arr2[3] = { 2, 4, 6 };
	TDynamicVector<int> result(arr2, 3);

	EXPECT_NE(a, result);
	EXPECT_EQ(b, result);
	EXPECT_EQ(c, result);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int arr1[3] = { 1, 2, 3 };
	int arr2[3] = { 100, 200, 300 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(arr2, 3);
	TDynamicVector<int> c(a + b);
	TDynamicVector<int> d(a);
	d += b;

	int arr3[3] = { 101, 202, 303 };
	TDynamicVector<int> result(arr3, 3);

	EXPECT_NE(a, result);
	EXPECT_NE(b, result);
	EXPECT_EQ(c, result);
	EXPECT_EQ(d, result);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(3);
	TDynamicVector<int> b(4);

	ASSERT_ANY_THROW(a + b);
	ASSERT_ANY_THROW(a += b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int arr1[3] = { 100, 200, 300 };
	int arr2[3] = { 1, 2, 3 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(arr2, 3);
	TDynamicVector<int> c(a - b);
	TDynamicVector<int> d(a);
	d -= b;

	int arr3[3] = { 99, 198, 297 };
	TDynamicVector<int> result(arr3, 3);

	EXPECT_NE(a, result);
	EXPECT_NE(b, result);
	EXPECT_EQ(c, result);
	EXPECT_EQ(d, result);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(3);
	TDynamicVector<int> b(4);

	ASSERT_ANY_THROW(a - b);
	ASSERT_ANY_THROW(a -= b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int arr1[3] = { 1, 2, 3 };
	int arr2[3] = { 100, 200, 300 };
	TDynamicVector<int> a(arr1, 3);
	TDynamicVector<int> b(arr2, 3);
	int c = a * b;


	EXPECT_EQ(c, 1400);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(3);
	TDynamicVector<int> b(4);

	ASSERT_ANY_THROW(a * b);
}

