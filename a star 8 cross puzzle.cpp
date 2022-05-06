/*

2 3 8
1 0 6
5 4 7

1 2 3
4 5 6
7 8 0


*/




#include<bits/stdc++.h>
using namespace std;


typedef vector<vector<int> > board;
typedef pair<board,char> vec;
board input,target;
vector<board> closedList;

priority_queue<pair<int,vec>,vector<pair<int,vec> >,greater<pair<int,vec> > > q;

int compare(board b1,board b2){ //returns 1 if matches
    for(int i=0;i<b1.size();i++)
    {
        for(int j=0;j<b1.size();j++)
        {
            if(b1[i][j]!=b2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;       //if same, then returning 1
}

int checkClosedList(board b,int n){   //checks the presence of a board configuration
    if(closedList.size()==0)
        return 0;
    else
    {
        for(int i=0;i<closedList.size();i++)
        {
            int k=compare(closedList[i],b);
            if(k==1)
            {
                return 1;       //if present then return 1
            }
        }
    }
    return 0;
}

int herustic(board b1,board b2){    //calculates the heurestic

    int flag=0;
    for(int i=0;i<b1.size();i++)
    {
        for(int j=0;j<b1.size();j++)
        {
            if(b1[i][j]!=b2[i][j]&&(b1[i][j]!=0||b2[i][j]!=0))
            {
                flag++;
            }
        }
    }
    return flag;
}
void print(board b,int n){
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
}

vector<vec> child(board in,int n){     //returns the possible children from a given board in form of vector of board,move
    vector<vec> next;
    int iPos,jPos;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(in[i][j]==0)
            {
                iPos=i;
                jPos=j;
                break;
            }
        }
    }
    if(iPos-1!=-1)
    {
        int k=in[iPos-1][jPos];
        in[iPos-1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'u'));

        k=in[iPos-1][jPos];
        in[iPos-1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(iPos+1!=n)
    {
        int k=in[iPos+1][jPos];
        in[iPos+1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'d'));

        k=in[iPos+1][jPos];
        in[iPos+1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(jPos-1!=-1)
    {
        int k=in[iPos][jPos-1];
        in[iPos][jPos-1]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'d'));

        k=in[iPos][jPos-1];
        in[iPos][jPos-1]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(jPos+1!=n)
    {
        int k=in[iPos][jPos+1];
        in[iPos][jPos+1]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'r'));

        k=in[iPos][jPos+1];
        in[iPos][jPos+1]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    return next;
}

void aStar(board inp, board tar,int n){

    int it=0;
    closedList.push_back(inp);
    if(compare(inp,tar))
    {
        cout<<"Initial condition is the final condition\n";
    }
    int gValue=0;
    q.push(make_pair(gValue+herustic(inp,tar),make_pair(inp,'s')));
    while(!compare(target,q.top().second.first))
    {
        gValue+=1;
        pair<int,vec> top=q.top();  //getting the top element
        q.pop();
        vector<vec> next=child(top.second.first,n); //vector of children along with associated move
        cout<<"GAVLUE= "<<gValue<<endl;

        for(int i=0;i<next.size();i++)
        {
            if(!checkClosedList(next[i].first,n))
            {
                int h=herustic(tar,next[i].first);
                q.push(make_pair(gValue+h,next[i]));
                closedList.push_back(next[i].first);
                print(next[i].first,n);
                cout<<"g+h= "<<gValue<<"+"<<h<<"="<<gValue+h<<endl;
                cout<<"size= "<<closedList.size()<<endl;
            }
        }
    }
    if(compare(tar,q.top().second.first))
    {
        cout<<"SUKKSES";
    }
}


int main()
{
    int n=3;
    input.resize(n);
    target.resize(n);
    cout<<"Enter the Current state of a 8 cross puzzle\n";
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int a;
            cin>>a;
            input[i].push_back(a);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int a;
            cin>>a;
            target[i].push_back(a);
        }
    }
    aStar(input,target,n);
    return 0;
}
