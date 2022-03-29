/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include<stack>
#include<vector>

using namespace std;
unsigned int solutions=0;

void printBoard(vector<int> board,int n)
{
	cout<<"[ ";
	for(int i=0;i<n;i++)
	{
		cout<<board[i]<<" ";
	}
	cout<<" ]\n";
}

bool isSafe(int a[],int r)
{
    for(int i=0;i<r;i++)
	{
		if(a[i]	==a[r]) //if the last placed number matches with the previous numbers, same line error
		{
			return false;
		}
		
		if((r-i)==abs(a[r]-a[i]))//check for diagonals
		{
			return false;
		}
	}
    
    
    return true;
}

int main()
{
    int n;
    cout<<"Enter the value of n : ";
    cin>>n;
    //--------------Entering initial elements-----------------------------------------
    stack<vector<int> > stack;
    for(int i=0;i<n;i++)
    {
        vector<int> board;
        board.push_back(i);
        stack.push(board);
    }

    //---------------placing the queens -----------------------------------------------
    while(!stack.empty())
    {
        vector<int> top=stack.top();
        stack.pop();
        
        if(top.size()==n)   //reached the solution
        {
            solutions++;
            //printBoard(top,top.size());
        }
        else    //trying next level combinations
        {
            for(int i=0;i<n;i++)
            {
                top.push_back(i);
                
                //----convertiong the vector to a 1D array---
                int size=top.size();
                int a[size];
                for(int i=0;i<size;i++)
                {
                    a[i]=top[i];
                }
                //------------------
                
                if(isSafe(a,size-1))    //calling isSafe with the array
                {
                    stack.push(top);
                }
                top.pop_back(); //if not safe state, then remove the queen
                
            }
        }
    }
    cout<<"NUMBER OF SOLUTIONS IS : "<<solutions;
}

