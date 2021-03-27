#include<iostream>
#include<vector>

using namespace std;

int Quick_Sort(vector<int> &input , int start , int end , int k);
int partition(vector<int> &input , int start , int end);

int main(){
    vector<int> input {1 , 0 , 3, 9 , 2 , 0 , 5};
    int k = (5-1); // (find thid element) take the input from user an increment it by 1 ... my algorithm i do find a place element(0,1,2,.....)
    cout << Quick_Sort(input,0,input.size()-1, k) << endl;
    return 0;
}

int Quick_Sort(vector<int> &input , int start , int end , int k){
    if(k >= 0 && k <= end){
    int p = partition(input,start,end);
    if(k == p){
        return input.at(p);
    }
    if(k < p){
        Quick_Sort(input,start,p - 1,k);
    }else{
        Quick_Sort(input,p+1,end,k);
    }
    }
}

int partition(vector<int> &input , int start , int end){
    int pivot = input.at(start);
    int temp ;
    int i  = start+1;
    int j = i;
    for(; j <= end ; j++){
        if(input.at(j) <= pivot){
            temp = input.at(j);
            input.at(j) = input.at(i);
            input.at(i++) = temp;
        }
    }
    temp = input.at(start);
    input.at(start) = input.at(i-1);
    input.at(i-1) = temp;
    return (i-1);

}
