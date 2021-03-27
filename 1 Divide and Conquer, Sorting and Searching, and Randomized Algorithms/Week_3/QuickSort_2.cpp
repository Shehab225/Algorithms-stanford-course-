/***********************************************************************************************************************************
 * QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot.
 * There are many different versions of quickSort that pick pivot in different ways.
 * Always pick last element as pivot (implemented below)
************************************************************************************************************************************/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int num = 0;
void input_file(vector<int> &input);
int Partition(vector<int> &input , int first , int last);
void Sort(vector<int> &input , int first , int last);

int main(){
    vector<int> input(10000);
    input_file(input);
    Sort(input,0,10000);
    cout << num << endl;
}

void Sort(vector<int> &input , int first , int last){
    if (last - first < 1) return;
    num += ((last - first) - 1);
    int Pindex = Partition(input ,first ,last);
    Sort(input,first,Pindex);
    Sort(input,Pindex+1,last);
}

int Partition(vector<int> &input , int first , int last){

    int temp = input.at(first);
    input.at(first) = input.at(last-1);
    input.at(last-1) = temp;

    int pivot = input.at(first);
    int j,i;
    i = j = first;

     for(; j < last ; j++){
        if(input.at(j) <= pivot){
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
