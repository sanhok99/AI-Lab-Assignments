#include <iostream>
#include<queue>
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
		if(a[i]	==a[r])	//if the last placed number matches with the previous numbers, same line error
		{
			return false;
		}
		
		if((r-i)==abs(a[r]-a[i])) //checking diagonals
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
    queue<vector<int> > q;
    for(int i=0;i<n;i++)
    {
        vector<int> board;
        board.push_back(i);
        q.push(board);
    }

    //---------------placing the queens -----------------------------------------------
    while(!q.empty())
    {
        vector<int> front=q.front();
        q.pop();
        if(front.size()==n)	//solution reached
        {
            solutions++;
            //printBoard(front,front.size());
        }
        else
        {
            for(int i=0;i<n;i++)
            {
                front.push_back(i);
                int size=front.size();
                int a[size];
                for(int i=0;i<size;i++)
                {
                    a[i]=front[i];
                }
                
                
                if(isSafe(a,size-1))
                {
                    q.push(front);
                }
                front.pop_back();
                
            }
        }
    }
    cout<<"NUMBER OF SOLUTIONS IS : "<<solutions;
}

