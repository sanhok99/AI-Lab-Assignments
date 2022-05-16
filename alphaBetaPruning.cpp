#include <iostream>
#include<stdlib.h>
#include <cmath>
#include <vector>
#include<bits/stdc++.h>



using namespace std;
typedef vector<int> rtype;
typedef vector<vector<int> > board;
static int count1=0;

typedef struct node          // Type of a node in the adjacency list.
{
    int vertex;
    int value;              // Vertex number.
    int depth;
    int alpha;
    int beta;
    struct node *next;      // Pointer to the next adjacent node.
} node;                     // Type name ’node’

typedef struct          // Type of a graph
{
    int vN;         // Number of vertices n: {0, 1, ..., n-1}
    node *vA;      // Pointer to the header array (n elements) of
} graph;            // node list

void makeTree(int b_factor,int depth,int n_nodes,graph g[])
{
    int flag=0;
    int f=flag;
    for(int i=0;i<n_nodes;i++)
    {
        g[i].vA=NULL;
        g[i].vN=i;

    }
    int kk=n_nodes-pow(b_factor,depth);
    int d=1,j=0;
    for(int i=1;i<=n_nodes-1;i++)
    {
        node* t=(node*)malloc(sizeof(node));
        t->next=NULL;
        t->vertex=++flag;
        t->depth=d;

        if(flag>=kk)
        {
            t->value=rand()%99;
        }

        node* y=g[j].vA;
        if(y==NULL)
            g[j].vA=t;
        else
        {
            node *x=NULL;
            while(y!=NULL)
            {
                x=y;
                y=y->next;
            }
            x->next=t;
        }
        if(flag==f+pow(b_factor,d))
        {
            d++;
            f=flag;
        }
        if(i%b_factor==0)
        {
            j++;
        }

    }
}

void show(graph g[],int n_nodes)
{

    for(int i=0;i<n_nodes;i++)
    {
        cout<<endl<<"from "<<i<<endl;
        node *y=g[i].vA;

        while(y!=NULL)
        {
            cout<<"Vertex:"<<y->vertex<<" Parent:"<<i;
            cout<<" depth :"<<y->depth<<" value:"<<y->value<<endl;
            y=y->next;
        }
    }
}


int minimax(node *n,graph g[])
{
    if(g[n->vertex].vA==NULL)
    {
        return n->value;
    }
    else
    {
        node *y=g[n->vertex].vA;
        int ret=minimax(y,g);
        y=y->next;

        while(y!=NULL)
        {
            int k=minimax(y,g);
            if(y->depth%2!=0 && ret<k)
            {
                ret=k;
            }
            else if(y->depth%2==0 && ret>k)
            {
                ret=k;
            }
            y=y->next;
        }
        n->value=ret;
        return ret;
    }
}

vector<int> prune(node *n,graph g[],int alpha,int beta)
{
    cout<<"call : "<<n->vertex<<endl<<endl;
    n->alpha=alpha;
    n->beta=beta;
    vector<int> r;
    if(g[n->vertex].vA==NULL)
    {

        r.push_back(n->value);
        r.push_back(n->value);
        cout<<"returning"<<endl;
        return r;
    }
    else
    {
        node *y=g[n->vertex].vA;

        //if(n->alpha<n->beta)
        //{
            vector<int> r=prune(y,g,n->alpha,n->beta);

            if(n->depth%2==0 && r[0]>n->alpha)
            {
                n->alpha=r[1];
            }
            else if(n->depth%2!=0 && r[0]<n->beta)
            {
                n->beta=r[1];
            }
        //}
        y=y->next;

        while(y!=NULL)
        {
            if(n->alpha<n->beta)
            {
                vector<int> k=prune(y,g,y->alpha,y->beta);
                if(y->depth%2!=0 && r[0]<k[0])
                {
                    r[0]=k[0];
                }
                else if(y->depth%2==0 && r[0]>k[0])
                {
                    r[0]=k[0];
                }

                if(n->depth%2==0 && r[1]>n->alpha)
                {
                    n->alpha=r[0];
                }
                else if(n->depth%2!=0 && r[1]<n->beta)
                {
                    n->beta=r[0];
                }
            }
            else
            {
                count1++;
                cout<<"pruned at depth "<<n->depth<<" node is "<<n->vertex <<" alpha:"<<n->alpha<<" beta:"<<n->beta<<endl ;
            }
            y=y->next;
        }
        if(n->depth%2!=0)
        {
            r[1]=(n->beta);
        }
        else
        {
            r[1]=(n->alpha);
        }
        n->value=r[0];
        return r;
    }
}

pair<int,int> min_and_max(int node_num,graph g[])
{
    node *n;
    n=g[node_num].vA;
    int minimum=n->value,maximumn=n->value,min_node=n->vertex,max_node=n->vertex,dep=n->depth;
    n=n->next;

    while(n!=NULL)
    {


        if(minimum>n->value)
        {
            minimum=n->value;
            min_node=n->vertex;
        }
        if(maximumn<n->value)
        {
            maximumn=n->value;
            max_node=n->vertex;
        }
        n=n->next;
    }
    pair<int,int> ret;
    pair<int,int> vertex;
    ret=make_pair(min_node,max_node);

    return ret;
}


void optimal_play(node *n,graph g[],int d)
{
    int call_node=n->vertex;
    pair<int,int> ret;
    for(int i=1;i<=d;i++)
    {
        ret=min_and_max(call_node,g);

        if(i%2!=0)
        {
            cout<<"MAX->"<<ret.second<<" ";

            if(g[ret.second].vA!=NULL)
            {
                call_node=ret.second;

            }
            else
            {
                break;
            }
        }
        else if(i%2==0)
        {
            cout<<"MIN->"<<ret.first<<" ";
            if(g[ret.first].vA!=NULL)
            {
                call_node=ret.first;

            }
            else
            {
                break;
            }

        }

    }


}

int main()
{
    int b_factor,m,n_nodes;
    cout<<"Enter branching factor :\n";
    cin>>b_factor;
    cout<<"Enter depth :\n";
    cin>>m;
    if(m<=2)
    {
        cout<<"this will not form a valid game sequence";
        exit(1);
    }
    m=m-1;
    n_nodes=b_factor*((pow(b_factor,m)-1)/(b_factor-1))+1;
    cout<<"total number of nodes : "<<n_nodes<<endl;
    graph g[n_nodes];

    makeTree(b_factor,m,n_nodes,g);
    node root;
    root.depth=0;
    root.vertex=0;
    int ret=minimax(&root,g);
    cout<<"root value "<<ret<<endl;
    //vector<int> r=prune(&root,g34,-999,999)     //this function needs some debugging.
    cout<<"PRINTING THE OPTIMAL PATH:"<<endl;
    optimal_play(&root,g,m);

    return 0;
}

