#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string>
#include<cstring>
#include <string.h>
#define MAX_NUM 99

using namespace std;
int path[MAX_NUM];
int Path,i,j;
int graph[MAX_NUM][MAX_NUM]= {};
int judge[MAX_NUM]= {0};
char line[10];
int Outbasepath[MAX_NUM][MAX_NUM]= {};

bool is_end(string str)
{

     if(str == "END" || str == "end" || str == "EXT" || str == "ext")
            return true;
     return false;
}

void getinfo(char line[],int i,int j,int Path,int graph[99][99],int judge[])
{
    char end[] = "END";
    do
        {
            cin.getline(line,10);
            int pos_i;
            pos_i=0;
            i=0;j=0;

            while(line[pos_i]<=57 && line[pos_i]>=48)
            {
                i=i*10+line[pos_i]-48;
                pos_i++;
            }
            pos_i=pos_i+2;

            while(line[pos_i]<=57 && line[pos_i]>=48)
            {
                j=j*10+line[pos_i]-48;
                pos_i++;
            }
            pos_i=pos_i+1;

            if (line[pos_i]=='T')
            {
                graph[i][j]=2;
                judge[i]=1;
            }

            else if (line[pos_i]=='F')
            {
                graph[i][j]=1;
                judge[i]=1;
            }

            else if (line[pos_i]=='N')
                graph[i][j]=0;

        }while(strcmp(line, end) != 0);
}

int is_Nau(int graph[MAX_NUM][MAX_NUM],int Arcnode)
{

    int flag=-1;
    for (int i=0; i<MAX_NUM; i++)
        {
            if (graph[Arcnode][i]==0)
            flag=i;
        }
    return flag;
}

int is_False(int graph[MAX_NUM][MAX_NUM],int Arcnode)
{
    int flag=-1;
    for (int i=0; i<MAX_NUM; i++)
        {
            if (graph[Arcnode][i]==1)
            flag=i;
        }
    return flag;
}


int is_True(int graph[MAX_NUM][MAX_NUM],int Arcnode)
 {

   int flag=-1;
    for (int i=0; i<MAX_NUM; i++)
        {
            if (graph[Arcnode][i]==2)
            flag=i;
        }
    return flag;
}



void DFSTraverse(int graph[MAX_NUM][MAX_NUM],int path[MAX_NUM],int Path,int Outbasepath[MAX_NUM][MAX_NUM])
{
    int path_1=Path;
    int path_2=Path;

    int visit=0;
    for (int k=0; k<Path-1; k++)
        if (path[k]==path[Path-1])
            visit=1;
    if (visit!=0)
    {
        int TMP=0;

        while(Outbasepath[TMP][0]!=-1)
            TMP++;
        for (int j=0; j<Path; j++)
        {
            Outbasepath[TMP][j]=path[j];
        }

        return ;
    }
    else if (is_True(graph,path[Path-1])==-1 && is_False(graph,path[Path-1])==-1 && is_Nau(graph,path[Path-1])==-1)
    {
        int TMP=0;
        while(Outbasepath[TMP][0]!=-1)
            TMP++;

        for (int j=0; j<Path; j++)
        {
            Outbasepath[TMP][j]=path[j];
        }
        return ;
    }
    if (is_False(graph,path[Path-1])!=-1)
    {
        path[Path++]=is_False(graph,path[Path-1]);
        DFSTraverse(graph,path,Path,Outbasepath);
    }
    if (is_True(graph,path[path_1-1])!=-1)
    {
        path[path_1++]=is_True(graph,path[path_1-1]);
        graph[path[path_1-2]][path[path_1-1]]=-1;
        DFSTraverse(graph,path,path_1,Outbasepath);
    }
    else if (is_Nau(graph,path[path_2-1])!=-1)
    {
        path[path_2++]=is_Nau(graph,path[path_2-1]);
        DFSTraverse(graph,path,path_2,Outbasepath);
    }
}



void init(int Outbasepath[MAX_NUM][MAX_NUM],int judge[MAX_NUM],int graph[MAX_NUM][MAX_NUM],int i,int j)
{
    for (i=0; i<MAX_NUM; i++)
            judge[i]=0;
    for (i=0; i<MAX_NUM; i++)
        for (j=0; j<MAX_NUM; j++)
            graph[i][j]=-1;
    for (i=0; i<MAX_NUM; i++)
        for (j=0; j<MAX_NUM; j++)
            Outbasepath[i][j]=-1;
}

void DicSort(int Outbasepath[MAX_NUM][MAX_NUM])
{
    int length_i,length_j;
    int TMP[MAX_NUM]= {};
    int n;int m;
    for(m=0;m<=50;m++)
    {
    for (int i=0; i<MAX_NUM; i++)
        for (int j=i+1; j<MAX_NUM; j++)
        {
            length_i=0;
            length_j=0;

            while(Outbasepath[i][length_i++]!=-1);
            while(Outbasepath[j][length_j++]!=-1);

            if (length_i ==1 || length_j==1)
                break;

            else if (length_i<length_j)
                continue;

            else if (length_i>length_j)
            {
                for (n=0; n<MAX_NUM; n++)
                    TMP[n]=Outbasepath[i][n];
                for (n=0; n<MAX_NUM; n++)
                    Outbasepath[i][n]=Outbasepath[j][n];
                for (n=0; n<MAX_NUM; n++)
                    Outbasepath[j][n]=TMP[n];
            }

            else for (int k=0; k<MAX_NUM; k++)
                {
                    if( Outbasepath[j][k] < Outbasepath[i][k] )
                    {
                        for (n=0; n<MAX_NUM; n++)
                            TMP[n]=Outbasepath[i][n];
                        for (n=0; n<MAX_NUM; n++)
                            Outbasepath[i][n]=Outbasepath[j][n];
                        for (n=0; n<MAX_NUM; n++)
                            Outbasepath[j][n]=TMP[n];
                        break;
                    }
                }
        }
    }
}


void display(int judge[],int Outbasepath[99][99],int i,int j,int Path,int graph[99][99],int path[])
{

        i=0;
        int k=0;

        for(int i=0; i<MAX_NUM; i++)
        if (judge[i]!=0)
            k++;
        cout<<"CC="<<k+1<<endl;
        DFSTraverse(graph,path,Path,Outbasepath);
        DicSort(Outbasepath);
        do
        {
            j=0;
            if(Outbasepath[i][j]!=-1)
                cout<<Outbasepath[i][j++];
            while (Outbasepath[i][j]!=-1)
                cout<<","<<Outbasepath[i][j++];
            cout<<endl;
            i++;
        }while (Outbasepath[i][0]!=-1);
}


int main()
{
    int begin;
    while (cin>>begin)
    {
        Path=0;
        path[Path++]=begin;
        init(Outbasepath, judge, graph,i,j);
        getinfo(line, i, j, Path, graph, judge);
        display( judge, Outbasepath,i,j,Path, graph,path);
    }
    return 0;
}

