/*
Shounak Saha
2021SMCS002

*/


#include<bits/stdc++.h>
using namespace std;

pair<string,string> input()
{
    pair<string,string> p;
    string str1,str2;

    cout<<"Enter String 1:"<<endl;
    cin>>str1;
    cout<<"Enter String 2:"<<endl;
    cin>>str2;

    p=make_pair(str1,str2);
    return p;
}

int get_min(int a,int b,int c)
{
    int m=a;
    if(b<m)
    {
        m=b;
    }
    if(c<m)
    {
        m=c;
    }
    return m+1;
}


void print(string s1, string s2,int len1,int len2,vector<vector<int>> &a)
{
    cout<<"     ";
    for(int j=0;j<=len1;j++)
    {
        cout<<s1[j]<<"  ";
    }
        cout<<"   "<<endl;
    for(int i=0;i<=len2;i++)
    {
        if(i>0)
            cout<<s2[i-1]<<" ";
        else
            cout<<"  ";
        for(int j=0;j<=len1;j++)
        {
            cout<<a[i][j]<<"  ";
        }
        cout<<endl;
    }

    cout<<endl<<"distance("<<s1<<","<<s2<<") = "<<a[len2][len1];

}

void dp(string str1, string str2,int len1,int len2,vector<vector<int>> &a)
{
    for(int i=0;i<=len1;i++)
    {
        a[0][i]=i;
    }
    for(int i=0;i<=len2;i++)
    {
        a[i][0]=i;
    }


    for(int i=1;i<=len2;i++)
    {
        for(int j=1;j<=len1;j++)
        {
            if(str2.at(i-1)==str1.at(j-1))
            {
                a[i][j]=a[i-1][j-1];
            }
            else
            {
                int n1,n2,n3,mini;
                n1=a[i-1][j];
                n2=a[i][j-1];
                n3=a[i-1][j-1];
                mini=get_min(n1,n2,n3);
                a[i][j]=mini;

            }
        }
    }
}

int main()
{
    string str1,str2;
    pair<string,string> r=input();    //taking input
    str1=r.first;
    str2=r.second;

    int len1,len2;
    len1=str1.size();
    len2=str2.size();


    vector <vector<int>> a;

    a.resize(len2+1);
    //a.resize(len2);

    for(int i=0;i<=len2;i++)    //Initializing the values with 0
        for(int j=0;j<=len1;j++)
            a[i].push_back(0);


    dp(str1,str2,len1,len2,a);
    print(str1,str2,len1,len2,a);


}
