/***********************************************************************************************************************************
 * QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot.
 * There are many different versions of quickSort that pick pivot in different ways.
 * median of 3 pivot (implemented below)
************************************************************************************************************************************/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int num = 0;
void input_file(vector<int> &input);
int Partition(vector<int> &input ,int index, int first , int last);
void Sort(vector<int> &input ,int first , int last);
int ChoosePivot(vector<int> &arr, int l , int r);
int FindMedian(int a, int b, int c);

int main(){
    vector<int> input(10000);
    input_file(input);
    Sort(input,0,10000);
    cout << num << endl;
}

void Sort(vector<int> &input , int first , int last){
    if (last - first < 1) return;
    num += ((last - first) - 1);
    int Pindex = Partition(input , ChoosePivot(input,first,last) ,first ,last);
    Sort(input,first,Pindex);
    Sort(input,Pindex+1,last);
}

int Partition(vector<int> &input , int index,int first , int last){

    int temp = input.at(first);
    input.at(first) = input.at(index);
    input.at(index) = temp;

    int Pivot = input.at(first);
    int i,j;
    i = j = (first+1);

    for(; j < last ; j++){
        if(input.at(j) <= Pivot){
            temp = input[j];
            input.at(j) = input.at(i);
            input.at(i) = temp;
            i++;
        }
    }
        temp = input.at(i-1);
        input.at(i-1) = input.at(first);
        input.at(first) = temp;
        return (i-1);

}

void input_file(vector<int> &input)
{
    ifstream reader("file.txt");

   if(reader.is_open())
   {
   for(int i = 0 ; i < (10000 ) ; i++)
    {
      reader >> input.at(i);

    }
   }
  reader.close();
}

int FindMedian(int a, int b, int c){

    if(a>b && a>c ){
        if(b>c) { return 1; }
        else { return 2;} 
    }
    else if(b>c && b>a){
        if(c>a) { return 2;}
        else { return 0;}
    }
    else{
        if(a>b) { return 0; }
        else { return 1; }
    }
}

int ChoosePivot(vector<int> &input, int first , int last){
    int mid = ((last-1)+first)/2;
    int result = FindMedian(input.at(first), input.at(mid), input.at(last-1));
    if( result == 0) return first;
    else if (result == 1) return mid;
    else return last-1;
}
