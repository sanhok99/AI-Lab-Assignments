/*
Shounak Saha
2021SMCS002
program to implement
1. build tree
2. minmax tree
3. alpha beta pruning
4. optimal path
*/



#include<bits/stdc++.h>
using namespace std;
typedef vector<int> rtype;
typedef vector<vector<int> > board;
static int count_flag=0;

typedef struct node          // Type of a node in the adjacency list.
{
    int vertex;
    int value;
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
    int kk=n_nodes-pow(b_factor,depth);     //flag set to track the start vertex of the leaf node
    int d=1,j=0;
    for(int i=1;i<=n_nodes-1;i++)   //creating a full binary tree
    {
        node* t=(node*)malloc(sizeof(node));
        t->next=NULL;
        t->vertex=++flag;
        t->depth=d;

        if(flag>=kk)
        {
            t->value=rand()%99; //inserting random number in leaf nodes
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
            if(n->depth%2==0 && ret<k)
            {
                ret=k;
            }
            else if(n->depth%2!=0 && ret>k)
            {
                ret=k;
            }
            y=y->next;
        }
        n->value=ret;
        return ret;
    }
}

void pruned(int n,int m,int b_factor)
{
    n=m-n;
    //cout<<"from node "<<n <<"graph is pruned"<<endl;
    int k=b_factor*((pow(b_factor,m-n)-1)/(b_factor-1))+1;
    //cout<<"Number of nodes pruned is :"<<k<<endl<<endl;
    count_flag+=k;
}

int alpha_beta_prune(node *n,graph g[],int alpha,int beta,int m,int b_factor)
{
    cout<<endl<<endl<<"call : "<<n->vertex<<endl;


    int r;
    if(g[n->vertex].vA==NULL)
    {
        //cout<<"returning"<<endl;
        return n->value;
    }
    else
    {

        node * y=g[n->vertex].vA;

        y->alpha=alpha;
        y->beta=beta;
        //cout<< "assigning alpha beta to node"<<y->vertex<<" alpha:"<<alpha<<" beta:"<<beta<<endl;

        int r=alpha_beta_prune(y,g,y->alpha,y->beta,m,b_factor);  //recursive call 1
        //cout<<"recived value"<<r<<endl;

        if((n->depth%2==0 || n->depth==0)&& r>n->alpha)
        {
            //cout<<"-changing alpha value of node "<<n->vertex <<" from "<<n->alpha<<" to "<<r<<" beta"<<n->beta<<endl;
            n->alpha=r;

        }
        else if(n->depth%2!=0 && r<n->beta)
        {
            //cout<<"-changing beta value of node "<<n->vertex <<" from "<<n->beta<<"to "<<r<<" alpha"<<n->alpha<<endl;
            n->beta=r;

        }

        y=y->next;
        if(y!=NULL)
        {
            y->alpha=n->alpha;
            y->beta=n->beta;
            //cout<< "assigning alpha beta to node"<<y->vertex<<" alpha:"<<n->alpha<<" beta:"<<n->beta<<endl;

        }

        while(y!=NULL)
        {
            if(n->alpha<n->beta)
            {
                int k=alpha_beta_prune(y,g,n->alpha,n->beta,m,b_factor);  //recursive call 2

                if(n->depth%2==0 && r<k)
                    r=k;

                else if(n->depth%2!=0 && r>k)
                    r=k;

                if(n->depth%2==0 && r>n->alpha)
                {
                    //cout<<"changing alpha value of node "<<n->vertex <<" from "<<n->alpha<<"to "<<r<<" beta"<<n->beta<<endl;
                    n->alpha=r;

                }
                else if(n->depth%2!=0 && r<n->beta)
                {
                    //cout<<"changing beta value of node "<<n->vertex <<" from "<<n->beta<<"to "<<r<<" alpha"<<n->alpha<<endl;
                    n->beta=r;

                }
            }
            else
            {
                //cout<<"pruned at depth "<<n->depth<<" node is "<<n->vertex<<endl ;
                pruned(n->depth,m,b_factor);
            }
            y=y->next;
            if(y!=NULL)
            {
                y->alpha=n->alpha;
                y->beta=n->beta;
                //cout<< "assigning alpha beta to node"<<y->vertex<<" alpha:"<<n->alpha<<" beta:"<<n->beta<<endl;
            }
        }

        n->value=r;
        return r;
    }
}

pair<int,int> min_and_max(int node_num,graph g[])   //returns the pair of int with vertex number of minimum and maximum from all the child nodes from a given node
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
            if(g[ret.second].vA!=NULL){
                call_node=ret.second;}
            else
                break;
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
    cout<<"Total number of nodes : "<<n_nodes<<endl;
    graph g[n_nodes];

    makeTree(b_factor,m,n_nodes,g);
    node root;
    root.depth=0;
    root.vertex=0;
    root.alpha=-999;
    root.beta=999;


    //show(g,n_nodes);

    int v=alpha_beta_prune(&root,g,-999,999,m,b_factor);

    int ret=minimax(&root,g);
    cout<<"root value "<<ret<<endl;

    cout<<endl<<"OPTIMAL PATH:"<<endl;
    optimal_play(&root,g,m);

    cout<<endl<<endl<<"NUMBER OF PRUNED NODES IS: "<<count_flag<<endl;

    return 0;
}

