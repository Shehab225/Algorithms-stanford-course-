/***************************************************************************************************************************************************
 * Problem : we are given an array of n points in the plane, and the output is to find the closest pair of points in array

 * We can calculate the samallest distance in O(n log(n)) time, using Divide-and-Conquer strategy
  1) Find the middle point in the sorted array,
  2) Divide the given array in two halves. 
  3) Recursively find the smallest distances in both subarray, and find the minimum of them
  4) From the above 3 steps, we have a minimum distance in two halves, we need to consider the pair is from the left half and the other from the right 
  5) Sort the array strip[] according to y coordinates.
  6) Find the smallest distance in strip[] 
  7) Finally return the the minimum distance

 * to know more about this visit : "https//www.google.com/amp/s/www.geeksforgeeks.org/closest-pai-ofpoints-onlogn-implementation/amp/"
***************************************************************************************************************************************************/

#include<bits/stdc++.h>
using namespace std;

struct point{
    float x;
    float y;
};

float dist(const point &p1 , const point &p2);
float min(float x , float y);
int compareY(const void *p1 , const void *p2);
int compareX(const void *p1 , const void *p2);
float brute_Force(point p[] , int size);
float closest_strip(point  p[] , int n , int d);
float closest(point px[] , point Py[] , int n);

int main(){
    point P[] = {{2,3},{11,30},{40,50},{5,1},{12,30},{3,4}};
    int n = sizeof(P) / sizeof(P[0]);
    point Py[n],Px[n];
    for(int i = 0 ; i < n ; i++){
        Px[i] = P[i];
        Py[i] = P[i];
    }
    qsort(Py,n,sizeof(point),compareY);
    qsort(Px,n,sizeof(point),compareX);
    cout << "the smallest distance is : " << closest(Px , Py ,n) << endl;
}

// find distance between two points
float dist(const point &p1 , const point &p2){
    return sqrt( ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y)) );
}

// find minimum of two float values
float min(float x , float y){
    return (x < y) ? x : y;
}

// sort array of points according to Y coordinate
int compareY(const void *p1 , const void *p2){
    return ( ((point*)p1)->y - ((point*)p2)->y );
}

// sort array of points according to X coordinate
int compareX(const void *p1 , const void *p2){
    return ( ((point*)p1)->x - ((point*)p2)->x );
}

// find smnallest distance between two points in p[]
float brute_Force(point p[] , int size){
    float min = FLT_MAX;
    for(int i = 0 ; i < size ; i++){
        for(int j = i+1 ; j < size ; j++){
            if(dist(p[i],p[j]) < min){
                min = dist(p[i],p[j]);
            }

        }
    }
    return min;
}

// find the smallest point in the strip[]
// it seems to be a (n*n) time, but it is actually O(n). we only need to check at most 7 points.
float closest_strip(point strip[] , int n , int d){
    float min = FLT_MAX;
    for(int i = 0 ; i < n ; i++){
        for(int j = i+1 ; j < n && ( (strip[j].y - strip[i].y) < d) ; j++){
            if(dist(strip[j],strip[i]) < d){
                min = dist(strip[j],strip[i]);
            }
        }
    }
    return min;
}

//the main function to find the smallest distance
float closest(point Px[] , point Py[] , int n){
    if(n<= 3 ){
        return brute_Force(Px , n);
    }
    int mid = n/2;
    point midpoint = Px[mid];
    point Pyl[mid];
    point Pyr[n-mid];
    int l = 0 , r = 0;
    // Assumption : All y coordinates are distincit
    for(int i = 0 ; i < n ; i++){
        if( Py[i].x < midpoint.x && l < mid){
            Pyl[l++] = Py[i];
        }else{
            Pyr[r++] = Py[i];
        }
    }
    float d1 = closest(Px, Pyr , mid);
    float d2 = closest(Px+mid, Pyl , n-mid);
    float d = min(d1,d2);
    point strip[n];
    int j= 0 ;
    for(int i = 0 ; i < n ; i++){
        if( abs(Py[i].x - midpoint.x) < d){
            strip[j] = Py[i];
            j++;
        }
    }
    return min(d,closest_strip(strip , j ,d));
}