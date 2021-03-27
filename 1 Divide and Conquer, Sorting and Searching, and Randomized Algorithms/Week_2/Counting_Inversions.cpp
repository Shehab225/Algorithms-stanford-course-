/****************************************************************************************************************************************
 * The idea is similar to merge sort, divide the array into two equal or almost equal halves in each step until the base case is reached.

 * A function Merge that counts the number of inversions when two halves of the array are merged, while Merging if arr1[i] greater than
 * arr2[j], then there are ((size of first arr) - i) inversions. because left and right subarrays are sorted,

 * Time Complexity : O(n log n)
 * Space Complexity : O(n)
****************************************************************************************************************************************/
#include<iostream>
#include<fstream>
using namespace std;

long long inv_count {0};
void Merge(int arr[] , int start , int mid , int end);
void MergeSort(int arr[] , int start , int end);
void input_array(int arr[]);


int main(){
    int arr[100000];
    input_array(arr);
    MergeSort(arr,0,(sizeof(arr)/sizeof(arr[0])));
    cout << "Number of inversions are : " << inv_count << endl;
}

void Merge(int arr[] , int start , int mid , int end){
    int temp1[(mid-start)];
    int temp2[(end-mid)];
    for(int i1 = 0 , i2 = start ; i1 < (mid-start) ; i1++ , i2++) temp1[i1] = arr[i2];
    for(int j1 = 0 , j2 = mid; j1 < (end-mid) ; j1++ , j2++) temp2[j1] = arr[j2];
    for(int index = start , i3 = 0 , j3 = 0 ; index < end ; index++){
        if(i3 == (mid-start)) { arr[index] = temp2[j3++] ; continue; }
        if(j3 == (end-mid)) { arr[index] = temp1[i3++] ; continue; }
        if(temp2[j3] < temp1[i3]){
            arr[index] = temp2[j3++];
            inv_count += ( (mid-start) - i3); // count_inversions
        }else{
            arr[index] = temp1[i3++];
        }
    }
}


void MergeSort(int arr[] , int start , int end){
    if (end-start <= 1)   return;
    int mid = ((start+end) + 1) / 2;
    MergeSort(arr,start,mid);
    MergeSort(arr,mid,end);
    Merge(arr,start,mid,end);
}

void input_array(int arr[]){
    ifstream reader("file.txt");
    if(reader.is_open()){
        for(int i = 0 ; i < 100000 ; i++){
            reader >> arr[i];
        }
    }
    reader.close();
}

