/*****************************************************************************************************************************************
 * Merge Sort :  the overall idea is that you split a huge array dowm as much as possible and then over time build it back
 * The general idea of breaking up an array sorting all the parts of it and then building it back up again is called "Divide-and-Conquer"

 * Merge Sort consists of two recursive calls follwed by a merging procedure

 * One of the Merge_Sort's most attractive properties is that is sorts a file of N element in time proportional to N log N, no matter whatthe iput
 * The prime disadvantage of Merge_Sort is that EXTRA space proportional to N is needed in straightforward implementations
 * Merge_Sort is no more difficult to code than is Heab_Sort or Quick_Sort, so Merge_Sort is worth considerinmg if speed is of the essence

 * The running time of Merge_Sort depends primarily on only the number of input keys, and is vitually insensitive to thier order

 * Merge_Sort is a stable sort, and this feature tips the balance in its favor for the applications whever stability is important,
 * Competitive methods such as Qick_Sort and Heab_Sort are not stable, Various techniques to make such methods stable tend to require extra space

 * Another feature of Merge_Sort that is important in certain situations is that Merge_Sort is normally implemented such that it accesses the data
 * primairly sequentially (one item after the other), for example, Merge_Sort is the metho of choice for sorting a linked-list
*****************************************************************************************************************************************/

#include<iostream>
using namespace std;

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

int main()
{

    int arr[] ={8 , 1 , 2 , 1 , 7 , 9 , 10 , 5 ,3 , 1 , 0 , 3 , 7 , 0 , 11};
    MergeSort(arr,0,(sizeof(arr)/sizeof(arr[0])));

    for(auto &item : arr){
        cout << item << " " ;
    }
    cout << endl;
} // output : " 0 0 1 1 1 2 3 3 5 7 7 8 9 10 11 "

