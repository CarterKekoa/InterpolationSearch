//----------------------------------------------------------------------
// Name: Carter Mooring
// File: project_tests.cpp
// Date: Spring 2021
// Desc: Interpolation Search Algorithm with Merge Sort Support. This algorithm is tested on various 
//         gmake tests I implemented below.
//----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// Functions 
/////////////////////////////////////////////////////////////////////////////

int arraySortedOrNot(int A[], int n){
  // Array has one or no element or the rest are already checked and approved.
  if (n == 1 || n == 0)
      return 1;

  // Unsorted pair found (Equal values allowed)
  if (A[n - 1] < A[n - 2])
      return 0;

  // Last pair was sorted, keep checking
  return arraySortedOrNot(A, n - 1);
}

// Merge helper for mergesort
// Assumes A1 length is n1 and A2 length is n2
void merge(int A[], int start, int mid, int end)
{
  int n1 = mid - start + 1;
  int n2 = end - mid;

  // Temp arrays
  int A1[n1], A2[n2];

  // Copy Data to Temp Arrays
  for(int i = 0; i < n1; i++){
    A1[i] = A[start + i];
  }
  for(int j = 0; j < n2; j++){
    A2[j] = A[mid + 1 + j];
  }

  // Subarray indexes
  int i = 0;
  int j = 0;
  int k = start;

  // Merge the temp arrays back into A[]
  while(i < n1 && j < n2){
    if(A1[i] < A2[j]){
      A[k] = A1[i];
      i++;
    }else{
      A[k] = A2[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of A1[], if there are any
  while (i < n1) {
    A[k] = A1[i];
      i++;
      k++;
  }
  
  // Copy the remaining elements of A2[], if there are any
  while (j < n2) {
      A[k] = A2[j];
      j++;
      k++;
  }
}

// Basic array-based merge sort
// Assumes A is of length n
void merge_sort(int A[], int start, int end)
{
  if(start >= end){
    return;
  }
  
  int mid = (start + end) / 2;
  merge_sort(A, start, mid);
  merge_sort(A, mid + 1, end);
  merge(A, start, mid, end);
}

// Returns the index of the variable to be found (search_for) if found, else returns -1
int interpolationSearch(int A[], int n, int search_for){
  int low = 0;
  int high = n - 1;

  // check for empty array
  if(n == 0){
    return -1;
  }else if(arraySortedOrNot(A, n) == 0){
    // the array is unsorted
    merge_sort(A, low, high); // sort the array
  }

  // while the desired value is inbetween the current sub array range
  while (low <= high && search_for >= A[low] && search_for <= A[high]){
    // if the sub array is size 1
    if (low == high){
        if (A[low] == search_for){
          return low;
        }
        return -1;
    }

    // The idea of formula is to return higher value of "pos" when element to be searched is 
    // closer to A[high]. And smaller value when closer to A[low]
    // calculate a pos index of the subarray to determine values location with
    int pos = low + (((double)(high - low) / (A[high] - A[low])) * (search_for - A[low]));

    // current position is the desired value
    if (A[pos] == search_for){
      return pos;
    }else if (A[pos] < search_for){
      // search_for is larger so take the right subarray
      low = pos + 1;
    }else{
      // x is smaller so take the left subarray
      high = pos - 1;
    }
  }
  return -1;
}



/////////////////////////////////////////////////////////////////////////////
// TESTS 
/////////////////////////////////////////////////////////////////////////////

// Test 1 (Basic - Unsorted Array - value in middle)
TEST(MyInterpolationTest, Test1) {
  // Array of items on which search will
  // be conducted.
  int A[] = {14, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 18; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(4, index); // search_for found
}

// Test 2 (Basic - Sorted Array - Value at the end)
TEST(MyInterpolationTest, Test2) {
  // Array of items on which search will
  // be conducted.
  int A[] = {11, 12, 13, 14 ,16, 18, 20, 30, 40, 60, 70};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 70; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(10, index); // search_for found
}

// Test 3 (Empty Array)
TEST(MyInterpolationTest, Test3) {
  int A[] = {};
  int n = 0; 
  int x = 4;

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(-1, index); // x not found
}

// Test 4 (Basic - Search for value not in the array - unsorted)
TEST(MyInterpolationTest, Test4) {
  // Array of items on which search will
  // be conducted.
  int A[] = {14, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 2; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(-1, index); // search_for found
}

// Test 5 (Basic Array - multiple of desired value - sorted)
TEST(MyInterpolationTest, Test5) {
  int A[] = {1, 7, 7, 8, 9, 14};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 7; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(2, index); // search_for found
}

// Test 6 Basic Array - Single desired value)
TEST(MyInterpolationTest, Test6) {
  int A[] = {433};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 433; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(0, index); // search_for found
}

// Test 7 Basic Array - Single undesired value)
TEST(MyInterpolationTest, Test7) {
  int A[] = {433};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 432; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(-1, index); // search_for found
}

// Test 8 (Basic Array - multiple of undesired value - sorted)
TEST(MyInterpolationTest, Test8) {
  int A[] = {1, 7, 7, 8, 9, 9, 14};
  int n = sizeof(A)/sizeof(A[0]);
  int x = 1; // Element to be searched

  int index = interpolationSearch(A, n, x);
  ASSERT_EQ(0, index); // search_for found
}

// Test 1 if the list is sorted in the end
TEST(MergeSortTest, Test1){
  int A[] = {8, 4, 6, 1, 3, 7};   // 1, 3, 4, 6, 7, 8
  int n = 6;
  int end = n - 1;
  int start = 0;
  merge_sort(A, start, end);

  for (int i = 0; i < n - 1; ++i) {
    int v = A[i];
    ASSERT_LT(v, A[i + 1]);
  }
}

// Test 1 (100,000 size array - Unsorted Array)
TEST(MyInterpolationLargeTest, Test1) {
  // Array of items on which search will
  // be conducted.
  int Arr[100000];
  for(int i=0; i<100000; i++){
    Arr[i] = rand()%100000;  //Generate number between 0 to 99
  }
  Arr[450] = 80;

  int n = 100000;
  int x = 80; // Element to be searched
  int index = interpolationSearch(Arr, n, x);
  ASSERT_NE(-1, index); // search_for found
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

