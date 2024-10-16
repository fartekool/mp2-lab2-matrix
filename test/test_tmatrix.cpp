#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			A[i][j] = i * 5 + j + 1;
	}
	TDynamicMatrix<int> B(A);

	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> A(5), B(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			A[i][j] = i * 5 + j + 1;
			B[i][j] = i * 5 + j + 1;
		}
	}
	TDynamicMatrix<int> C(A);
	C *= 5;
	TDynamicMatrix<int> D(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			D[i][j] = (i * 5 + j + 1) * 5;
	}
	EXPECT_EQ(A, B);
	EXPECT_EQ(C, D);
	EXPECT_NE(A, C);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> A(5);

	EXPECT_EQ(A.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> A(5);
	int arr[5] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> a(arr, 5);
	A[0] = a;

	EXPECT_EQ(A[0], a);
	EXPECT_EQ(A[0][1], 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> A(5);
	int arr[5] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> a(arr, 5);

	ASSERT_ANY_THROW(A.at(-1) = a);
	ASSERT_ANY_THROW(A.at(0).at(-1) = 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{	
	TDynamicMatrix<int> A(5);
	int arr[5] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> a(arr, 5);

	ASSERT_ANY_THROW(A.at(MAX_MATRIX_SIZE) = a);
	ASSERT_ANY_THROW(A.at(5) = a);
	ASSERT_ANY_THROW(A.at(6) = a);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> A(2);
	int arr1[2] = { 1, 2 };
	TDynamicVector<int> a(arr1, 2);
	int arr2[2] = { 3, 4 };
	TDynamicVector<int> b(arr2, 2);
	A[0] = a;
	A[1] = b;
	A = A;

	EXPECT_EQ(A[0], a);
	EXPECT_EQ(A[1], b);

}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			A[i][j] = i * 5 + j + 1;
	}
	TDynamicMatrix<int> B(5);
	B = A;

	EXPECT_EQ(A, B);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> A(5), B(6);
	A = B;

	EXPECT_EQ(A.size(), 6);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			A[i][j] = i * 5 + j + 1;
	}
	TDynamicMatrix<int> B(2);
	int arr1[2] = { 1, 2 };
	TDynamicVector<int> a(arr1, 2);
	int arr2[2] = { 3, 4 };
	TDynamicVector<int> b(arr2, 2);
	B[0] = a;
	B[1] = b;
	A = B;

	EXPECT_EQ(A.size(), 2);
	EXPECT_EQ(A[0], a);
	EXPECT_EQ(A[1], b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> A(5), B(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			A[i][j] = i * 5 + j + 1;
			B[i][j] = i * 5 + j + 1;
		}
	}

	EXPECT_TRUE(A == B);
	EXPECT_FALSE(A != B);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			A[i][j] = i * 5 + j + 1;
		}
	}

	EXPECT_TRUE(A == A);
	EXPECT_FALSE(A != A);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> A(5), B(6);

	EXPECT_TRUE(A != B);
	EXPECT_FALSE(A == B);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix) // added
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			A[i][j] = i * 5 + j + 1;
		}
	}
	TDynamicMatrix<int> B(A * 2);
	TDynamicMatrix<int> C(A);
	C *= 2;

	TDynamicMatrix<int> RESULT(5);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			RESULT[i][j] = (i * 5 + j + 1) * 2;
		}
	}

	EXPECT_NE(A, RESULT);
	EXPECT_EQ(B, RESULT);
	EXPECT_EQ(C, RESULT);

}

TEST(TDynamicMatrix, can_mult_matrix_and_vector) // added
{
	TDynamicMatrix<int> A(5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			A[i][j] = i * 5 + j + 1;
		}
	}
	int arr[5] = { 1, 1, 1, 1, 1 };
	TDynamicVector<int> a(arr, 5);
	TDynamicVector<int> b(5);
	b = A * a;

	int arr1[5] = { 15, 40, 65, 90, 115 };
	TDynamicVector<int> result(arr1, 5);

	EXPECT_EQ(b, result);
}

TEST(TDynamicMatrix, cant_mult_matrix_and_vector_with_diff_sizes) // added
{
	TDynamicMatrix<int> A(5);
	TDynamicVector<int> a(3);

	ASSERT_ANY_THROW(A * a);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> A(3), B(3), C(3), D(3);
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			A[i][j] = i * 3 + j + 1;
			B[i][j] = 1;
			C[i][j] = i * 3 + j + 2;
		}
	}
	D = A;
	D += B;
	EXPECT_EQ(A + B, C);
	EXPECT_EQ(D, C);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> A(3), B(5);

	ASSERT_ANY_THROW(A + B);
	ASSERT_ANY_THROW(A += B);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> A(3), B(3), C(3), D(3);
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			A[i][j] = i * 3 + j + 1;
			B[i][j] = 1;
			C[i][j] = i * 3 + j;
		}
	}
	D = A;
	D -= B;

	EXPECT_EQ(A - B, C);
	EXPECT_EQ(D, C);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> A(3), B(5);

	ASSERT_ANY_THROW(A - B);
	ASSERT_ANY_THROW(A -= B);
}

TEST(TDynamicMatrix, can_mult_matrices_with_equal_size) // added
{
	TDynamicMatrix<int> A(3), B(3), C(3);
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
			A[i][j] = i * 3 + j + 1;
	}
	B[0][0] = -1; B[0][1] = 4; B[0][2] = 7;
	B[1][0] = B[1][1] = 0; B[1][2] = 3;
	B[2][0] = 1; B[2][1] = 2; B[2][2] = 0;

	C[0][0] = C[1][0] = C[2][0] = 2;
	C[0][1] = 10; C[1][1] = 28; C[2][1] = 46;
	C[0][2] = 13; C[1][2] = 43; C[2][2] = 73;

	EXPECT_EQ(A * B, C);
}

TEST(TDynamicMatrix, cant_mult_matrixes_with_not_equal_size) // added
{
	TDynamicMatrix<int> A(3), B(5);

	ASSERT_ANY_THROW(A * B);
}


