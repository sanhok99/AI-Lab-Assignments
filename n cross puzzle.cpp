/*

2 3 8
1 0 6
5 4 7

1 2 3
4 5 6
7 8 0

1 2 3
4 5 6
0 7 8

1 2 3
4 5 6
7 8 0


*/

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
vector<vec> closedList;
vec success;

priority_queue<pair<int,vec>,vector<pair<int,vec> >,greater<pair<int,vec> > > q;

int compare(board &b1,board &b2){ //returns 1 if matches
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

int checkClosedList(board &b,int n){   //checks the presence of a board configuration
    if(closedList.size()==0)
        return 0;
    else
    {
        for(int i=0;i<closedList.size();i++)
        {
            int k=compare(closedList[i].first,b);
            if(k==1)
            {
                return 1;       //if present then return 1
            }
        }
    }
    return 0;
}

int herustic(board &b1,board &b2){    //calculates the heurestic

    int flag=0;
    for(int i=0;i<b1.size();i++)
    {
        for(int j=0;j<b1.size();j++)
        {
            if((b1[i][j]!=b2[i][j])&&(b1[i][j]!=0||b2[i][j]!=0))
            {
                flag++;
            }
        }
    }
    return flag;
}

vector<int> pos_i_j(board in,int x,int n)
{
    vector<int> ret;
    int iPos,jPos;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(in[i][j]==x)
            {
                iPos=i;
                jPos=j;
                break;
            }
        }
    }
    ret.push_back(iPos);
    ret.push_back(jPos);
    return ret;
}

int herustic_manhattern(board b1,board b2,int n)
{
    int dist=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            vector<int> r=pos_i_j(b2,b1[i][j],n);
            dist+=abs(i-r[0])+(j-r[1]);
        }
    }
    return dist;
}

void print(board &b,int n){
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
}

vector<vec> child(board &in,int n){     //returns the possible children from a given board in form of vector of board,move
    vector<vec> next;

    int iPos,jPos;
    vector <int> r=pos_i_j(in,0,n);
    iPos=r[0];
    jPos=r[1];
    if(iPos-1>-1)
    {
        int k=in[iPos-1][jPos];
        in[iPos-1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'u'));

        k=in[iPos-1][jPos];
        in[iPos-1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(iPos+1<n)
    {
        int k=in[iPos+1][jPos];
        in[iPos+1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'d'));

        k=in[iPos+1][jPos];
        in[iPos+1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(jPos-1>-1)
    {
        int k=in[iPos][jPos-1];
        in[iPos][jPos-1]=in[iPos][jPos];
        in[iPos][jPos]=k;

        next.push_back(make_pair(in,'l'));

        k=in[iPos][jPos-1];
        in[iPos][jPos-1]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    if(jPos+1<n)
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

void aStar(board &inp, board &tar,int n){
    int gValue=0;

    q.push(make_pair(herustic_manhattern(inp,tar,n),make_pair(inp,'s')));

   while(!q.empty())
    {
        gValue+=1;
        pair<int,vec> top=q.top();  //getting the top element
        closedList.push_back(top.second);
        q.pop();

        if(compare(tar,top.second.first))
        {
            cout<<"REACHED TO THE SOLUTION."<<endl;
            success=top.second;
            break;
        }

        vector<vec> next1=child(top.second.first,n); //vector of children along with associated move

        for(int i=0;i<next1.size();i++)
        {
            if(!checkClosedList(next1[i].first,n))
            {
                int h=herustic_manhattern(tar,next1[i].first,n);
                int fValue=gValue+h;
                q.push(make_pair(fValue,next1[i]));
            }
        }
    }

}


vec parent(board in,char mov,int n)
{
    int iPos,jPos;
    vector <int> r=pos_i_j(in,0,n);
    iPos=r[0];
    jPos=r[1];
    if(mov=='d')
    {
        int k=in[iPos-1][jPos];
        in[iPos-1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    else if(mov=='u')
    {
        int k=in[iPos+1][jPos];
        in[iPos+1][jPos]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    else if(mov=='l')
    {
        int k=in[iPos][jPos-1];
        in[iPos][jPos-1]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }

    else if(mov=='r')
    {

        int k=in[iPos][jPos+1];
        in[iPos][jPos+1]=in[iPos][jPos];
        in[iPos][jPos]=k;
    }


    for(int i=0;i<closedList.size();i++)
    {
        int k=compare(closedList[i].first,in);
        if(k==1)
        {
            return closedList[i];       //if present then return the board along with move
        }
    }
}

//vector<char>
void get_moves(int n)
{
    //cout<<"called"<<endl;
    //vector<char> ret;
    while(1)
    {
        char m=success.second;
        cout<<m<<" ";
        if(m=='u')
        {
            success=parent(success.first,'d',n);
        }
        else if(m=='d')
        {
            success=parent(success.first,'u',n);
        }
        else if(m=='l')
        {
            success=parent(success.first,'r',n);
        }
        else if(m=='r')
        {
            success=parent(success.first,'l',n);
        }

        if(success.second=='s')
        {
            break;
        }
        //ret.push_back(success.second);
        //exit(1);
    }
    //return ret;
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


    //vector<char> ret_moves=
    get_moves(n);

    return 0;
}
