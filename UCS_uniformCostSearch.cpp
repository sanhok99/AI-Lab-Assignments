/*UNIFORM COST SEARCH
ROLL-2021SMCS002

Input file format:
Number of vertices
Number of edges
u v (each edge from u to v)
.
.
.
cost accordingly
.
.
.
*/


#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> p;
typedef queue<p> pq;
vector<vector<int> > graph;
static int cost[100][100];

//---------------------------------------SORTING---------------------------------------------------------------
int minIndex(pq &q, int sortedIndex)
{
    int min_index=-1;
    int minVal=INT_MAX;
    int n = q.size();
    for (int i=0;i<n;i++)
    {
        p curr=q.front();
        q.pop();
        if (curr.first<=minVal&& i<=sortedIndex)
        {
            min_index = i;
            minVal = curr.first;
        }
        q.push(make_pair(curr.first,curr.second));
    }
    return min_index;
}
void insertMinToRear(pq &q,int min_index)
{
    p min_val;
    int n=q.size();
    for (int i=0;i<n;i++)
    {
        p curr=q.front();
        q.pop();
        if (i!=min_index)
            q.push(curr);
        else
            min_val = curr;
    }
    q.push(min_val);
}
void sortQueue(pq &q)
{
    for (int i=1;i<=q.size();i++)
    {
        int min_index=minIndex(q, q.size() - i);
        insertMinToRear(q, min_index);
    }
}
//---------------------------------------------------------------------------------------------------------------
void updatecost(pq &q,int vertex,int c)
{
    for (int i=1;i<=q.size();i++)
    {
        p replace=q.front();
        q.pop();
        if(replace.second==vertex)
        {
            if(replace.first>c)
            {
                replace.first=c;
            }
        }
        q.push(replace);
    }
}
void showpq(pq &gq)
{
 pq g = gq;
 while(!g.empty())
 {
     p p1=g.front();
  cout << '\t' << p1.first<<'\t'<<p1.second;
  cout << '\n';
  g.pop();
 }

}
bool goalTest(vector<int> goal,int vertex)
{
    for(int i=0;i<goal.size();i++)
    {
        if(vertex==goal[i])
        {
            return true;
        }
    }
    return false;
}
pq UCS(vector<int> goal,int vertex,int initialV)
{
    int visited[vertex];
    pq answer;
    for(int i=0;i<vertex;i++)
    {
        visited[i]=0;
    }
    pq q;
    vector<int> initial=graph[initialV];
    for(int i=0;i<initial.size();i++)   //inserting the elements of the initial vertex
    {
        q.push(make_pair((cost[initialV][initial[i]]),initial[i]));
        visited[initial[i]]=1;
    }
    sortQueue(q);   //sorting with respect to cost
    visited[initialV]=2;
    while(!q.empty())
    {
        pair<int,int> front=q.front();
        if(goalTest(goal,front.second))
        {
            answer.push(front);
            sortQueue(answer);
        }
        q.pop();
        visited[front.second]=2;
        vector<int> frontier=graph[front.second];
        for(int i=0;i<frontier.size();i++)
        {
            if(visited[frontier[i]]==0) //first time the value is appearing
            {
                int new_cost=cost[front.second][frontier[i]]+front.first;
                q.push(make_pair(new_cost,frontier[i])); visited[frontier[i]]=1;

            }
            else if(visited[frontier[i]]==1) //if the vertex is already present in the queue
            {
                updatecost(q,frontier[i],(front.first+cost[front.second][frontier[i]])); //update only if the cost is lower.
            }
        }
        sortQueue(q);
    }

    return answer;
}
int main()
{
    ifstream ifile;
    ifile.open("in_UCS.txt");
    int vertex,edge;
    ifile>>vertex;
    ifile>>edge;
    graph.resize(edge);
    for(int i=0;i<edge;i++)
    {
        int a,b;
        ifile>>a;
        ifile>>b;
        graph[a].push_back(b);
    }
    for(int i=0;i<vertex;i++)
    {
        vector<int> vec;
        vec=graph[i];
        for(int j=0;j<vec.size();j++)
        {
            int c;
            ifile>>c;
            cost[i][vec[j]]=c;
            cost[vec[j]][i]=c;
        }
    }
    cout<<"GRAPH input part is over"<<endl;

    cout<<"Enter the number of goal states : ";
    int n;
    cin>>n;
    vector<int> goal;
    cout<<"Enter the goal states : "<<endl;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        goal.push_back(a);
    }
    cout<<"Enter the initial state : ";
    int initial;
    cin>>initial;
    for(int i=0;i<goal.size();i++)      //check if initial is present in the goal
    {
        if(goal[i]==initial)
        {
            cout<<"The cost of reaching "<<initial<<" from "<<initial<<" is 0";
            return 0;
        }
    }
    pq answer=UCS(goal,vertex,initial);
    cout<<"The cost of reaching "<<answer.front().second<<" is "<<answer.front().first;

    return 0;
}

//NOTE : passing a 2D array to a function was creating some issues, for which i used a 100x100 matrix.
