/***************************************************************************************************************************
 * Karastuba_Multiplication
***************************************************************************************************************************/

#include<iostream>
#include<cmath>
#include <utility>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std; 
using boost::multiprecision::cpp_int;

cpp_int power(int n)
{
    cpp_int back {10};
    n--;
    while(n)
    {
        back *=10;
        n--;
    }
    
    return  (back);
}

int getlength(cpp_int num)
{
    int count {};
    while(num)
    {
        count++;
        num /=10;
    }
    return count;
}

cpp_int multiply(cpp_int x, cpp_int y) {
  int xlength = getlength(x);
  int ylength = getlength(y);

  int n = (xlength > ylength) ? (xlength / 2) : (ylength / 2);

  if (n < 1)
    return x*y;
    
    

    cpp_int diver = power(n);

   cpp_int a = x / diver;
   cpp_int b = x - (a * diver );
   cpp_int c = y / diver;
   cpp_int d = y - (c * diver );
   
   cpp_int z0 = multiply(a,c);
   cpp_int z1 = multiply(a+b,c+d);
   cpp_int z2 = multiply(b,d);

    return (  ( power(n*2) * z0 ) +  ( diver * (z1-z0-z2) )  + z2     );
}

int main()
{
    cpp_int x {};
    cpp_int y {};

    cin >> x >> y ;
cout << x*y << endl;
    cout << multiply(x,y) << endl;

    return 0;
}
