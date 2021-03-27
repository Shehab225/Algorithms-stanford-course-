# Quickselect Algorithm
Quickselect is a selection algorithm to find the k-th smallest element in an unordered list. It is related to the quick sort sorting algorithm.
Examples: 

Input: arr[] = {7, 10, 4, 3, 20, 15}

           k = 3
Output: 7

Input: arr[] = {7, 10, 4, 3, 20, 15}

           k = 4
Output: 1

The algorithm is similar to QuickSort. The difference is, instead of recurring for both sides (after 

finding pivot), it recurs only for the part that contains the k-th smallest element. The logic is simple, if 

index of partitioned element is more than k, then we recur for left part. If index is same as k, we have 

found the k-th smallest element and we return. If index is less than k, then we recur for right part. This 

reduces the expected complexity from O(n) to O(n log n), with a worst case of O(n^2).
