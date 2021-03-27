#include<iostream>
#include<vector>
using namespace std;


/********* Normal multiplication of two matrices. *******/

void multiply (	vector< vector<int> > &A, vector< vector<int> > &B, vector< vector<int> > &C, int d)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            for (int k = 0; k < d; k++)
            {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
}


/************** Functions for Strassen ****************/


// function to split a matrix
void split(vector<vector<int>> &A , vector<vector<int>> &B , int row , int col , int d){
        for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
             for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
            B[i1][j1] = A[i2][j2];
        }
    }
}


// function to add two martrices
void add(vector<vector<int>> &A , vector<vector<int>> &B , vector<vector<int>> &c , int d){
    for(int i = 0 ; i < d ; i++){
        for(int j = 0 ; j < d ; j++){
            c[i][j] = A[i][j] + B[i][j];
        }
    }
}



// function to subtract two matrices.
void subtract(vector<vector<int>> &A , vector<vector<int>> &B , vector<vector<int>> &c , int d){
    for(int i = 0 ; i < d ; i++){
         for(int j = 0 ; j < d ; j++){
            c[i][j] = A[i][j] - B[i][j];
        }
    }
}




// join the 4 matrices in a resulting matrix
void join (	std::vector< std::vector<int> > &A, std::vector< std::vector<int> > &B, int row, int col, int d) {
    for (int i1 = 0, i2 = row; i1 < d; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < d; j1++, j2++){
        	B[i2][j2] = A[i1][j1];
        }
    }
}



/*********************** Strassen Algorithm **************************/


void strassen(vector<vector<int>> &A , vector<vector<int>> &B , vector<vector<int>> &C , int d){

    // if we are at the matrices (1*1), call the normal multiplication
    if(d <= 1){
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else{

    int new_d = d/2;

    vector<int> inside (new_d);

    // initialize the submatices	
    vector<vector<int>> A11 (new_d, inside);
    vector<vector<int>> A12 (new_d, inside);
    vector<vector<int>> A21 (new_d, inside);
    vector<vector<int>> A22 (new_d, inside);
    vector<vector<int>> B11 (new_d, inside);
    vector<vector<int>> B12 (new_d, inside);
    vector<vector<int>> B21 (new_d, inside);
    vector<vector<int>> B22 (new_d, inside);
    vector<vector<int>> C11 (new_d, inside);
    vector<vector<int>> C12 (new_d, inside);
    vector<vector<int>> C21 (new_d, inside);
    vector<vector<int>> C22 (new_d, inside);


    // split matrices A and B in 4 submatrices
    split(A,A11,0,0,new_d);
    split(A,A12,0,new_d,new_d);
    split(A,A21,new_d,0,new_d);
    split(A,A22,new_d,new_d,new_d);
    split(B,B11,0,0,new_d);
    split(B,B12,0,new_d,new_d);
    split(B,B21,new_d,0,new_d);
    split(B,B22,new_d,new_d,new_d);


    // matrices to store results from arithmetic operations
	std::vector< std::vector<int> > result1 (new_d, inside);
	std::vector< std::vector<int> > result2 (new_d, inside);


    /************************************************
    *** 	M1 = (A11 + A22)(B11 + B22)
    *** 	M2 = (A21 + A22) B11
    *** 	M3 = A11 (B12 - B22)
    *** 	M4 = A22 (B21 - B11)
    *** 	M5 = (A11 + A12) B22
    *** 	M6 = (A21 - A11) (B11 + B12)
    *** 	M7 = (A12 - A22) (B21 + B22)
    ************************************************/

    // calculate M1
   std::vector< std::vector<int> > M1 (new_d, inside);
   add(A11,A22,result1,new_d);
   add(B11,B22,result2,new_d);
   strassen(result1,result2,M1,new_d);


   // calculate M2
   std::vector< std::vector<int> > M2 (new_d, inside);
   add(A21,A22,result1,new_d);
   strassen(result1,B11,M2,new_d);


   // calculate M3
    std::vector< std::vector<int> > M3 (new_d, inside);
    subtract(B12,B22,result2,new_d);
    strassen(result2,A11,M3,new_d);

   // calculate M4 
    std::vector< std::vector<int> > M4 (new_d, inside);
    subtract(B21,B11,result1,new_d);
    strassen(result1,A22,M4,new_d);


    // calculate M5   (A11 + A12) B22
    std::vector< std::vector<int> > M5 (new_d, inside);
    add(A11,A12,result2,new_d);
    strassen(result2,B22,M5,new_d);


    // calculate M6
    std::vector< std::vector<int> > M6 (new_d, inside);
    add(B11,B12,result1,new_d);
    subtract(A21,A11,result2,new_d);
    strassen(result2,result1,M6,new_d);


    // calculate M7
    std::vector< std::vector<int> > M7 (new_d, inside);
    add(B21,B22,result1,new_d);
    subtract(A12,A22,result2,new_d);
    strassen(result1,result2,M7,new_d);

    /**********************************************
    ***      C11 = M1 + M4 - M5 + M7
    ***      C12 = M3 + M5
    ***      C21 = M2 + M4
    ***      C22 = M1 - M2 + M3 + M6
    **********************************************/

    // calculating C11
    add(M1,M4,result1,new_d);
    add(result1,M7,result2,new_d);
    subtract(result2, M5, C11, new_d);

    // calculating C12
    add(M3,M5,C12,new_d);

    // calculating C21
    add(M2,M4,C21,new_d);


    // calculating C22
    subtract(M1, M2, result1, new_d);
    add(M3, M6, result2, new_d);
    add(result1, result2, C22, new_d);



    // add the resulting matrices in one matrix
    join(C11, C, 0 , 0, new_d);
    join(C12, C, 0 , new_d, new_d);
    join(C21, C, new_d, 0, new_d);
    join(C22, C, new_d, new_d, new_d);

}
}


int main(){

  // 1th Matrix 
  vector< vector<int> > A{
        {3,2,3,1},
        {3,2,3,1},
        {3,2,3,1},
        {3,2,3,1}
    };

  // 2end Matrix
  vector< vector<int> > B{
        {3,2,3,1},
        {3,2,3,1},
        {3,2,3,1},
        {3,2,3,1}
    };

  // Resultant of Multiplication two matrices
  vector< vector<int> > C{
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

  // call strassen func.
    strassen(A,B,C,4);


  // print Resultant Matrix
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 4 ; j++){
            cout << C[i][j] << " ";

        }
        cout << endl;
    }
    return 0;
}
/* output : 27 18 27 9 
            27 18 27 9 
            27 18 27 9 
            27 18 27 9 */