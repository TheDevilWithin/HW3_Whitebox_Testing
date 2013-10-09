#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
#define MAXNUM 500

typedef struct {
    char judge[MAXNUM][MAXNUM];
    int  e; //图的顶点数与边数
    int begin_vertex;
} MTGraph;

int one_path[MAXNUM];
int m = 1;
static int number = 0;
int numberOfpath[MAXNUM];

int path[MAXNUM][MAXNUM]; //访问标记数组是全局变量
bool visted[MAXNUM][MAXNUM];//用于标记该边是否访问过
bool Ispath[MAXNUM];
void CreateGraph(MTGraph *G) {
    int e = 0, i,j; //用于记录有多少顶点和边
    char none='s';
    for (i = 0; i < MAXNUM; i++) {
         for (j = 0; j < MAXNUM; j++){
            G->judge[i][j] = none;
         }
    }
    string str;
    string and_or;
    int tail1,tail2;
    int tail, head;
    char judge; //T or F or N
    getline(cin, str);
    for (i = 0; i < str.length(); i++) {
        G->begin_vertex = G->begin_vertex * 10 + str[i] - 48;
    }
    getline(cin, str); //输入命令，遇到换行符结束
    do {
        tail = 0;
        head = 0;
        for (i = 0; str[i] != '-'; i++) {
            tail = tail * 10 + str[i] - 48;
        }
        i = i + 2;
        for (; str[i] != ','; i++) {
            head = head * 10 + str[i] - 48;
        }
        i++;
        judge = str[i];
        G->judge[tail][head] = judge;
        e++;
        getline(cin, str); //输入命令，遇到换行符结束
    } while (str.compare(0, 3, "END") != 0 && str.compare(0, 3, "EXT")!=0);

    if(str.compare(0, 3, "EXT")==0){
        getline(cin, str);
        do{
            tail=0;
            for (i = 0; str[i] != ','; i++) {
                tail = tail * 10 + str[i] - 48;
            }
            i++;
            for (;i<str.length(); i++) 
                and_or+=str[i];
            if(tail==G->begin_vertex)
                    G->begin_vertex=tail*10+1;
            if(and_or.compare(0, 3, "AND") == 0 ){
                tail2 = tail*10+2;
                tail1 = tail*10+1;
                for(j=0;j<MAXNUM;j++){
                    if(G->judge[tail][j]=='T'){
                        G->judge[tail2][j]=G->judge[tail][j];
                        G->judge[tail][j]='s';
                    }
                    else if(G->judge[tail][j]=='F'){
                         G->judge[tail2][j]=G->judge[tail][j];
                         G->judge[tail][j]='s';
                         G->judge[tail1][j]='F';
                    }
                    if(G->judge[j][tail]!='s'){
                        G->judge[j][tail1]=G->judge[j][tail];
                        G->judge[j][tail]='s';
                    }
                }
                 G->judge[tail1][tail2]='T';
            }
            else if(and_or.compare(0, 2, "OR") == 0 ){
                tail2 = tail*10+2;
                tail1 = tail*10+1;
                for(j=0;j<MAXNUM;j++){
                    if(G->judge[tail][j]=='F'){
                        G->judge[tail2][j]=G->judge[tail][j];
                        G->judge[tail][j]='s';
                    }
                    else if(G->judge[tail][j]=='T'){
                         G->judge[tail2][j]=G->judge[tail][j];
                         G->judge[tail][j]='s';
                         G->judge[tail1][j]='T';
                    }
                    if(G->judge[j][tail]!='s'){
                        G->judge[j][tail1]=G->judge[j][tail];
                        G->judge[j][tail]='s';
                    }
                }
                 G->judge[tail1][tail2]='F';
            }
            getline(cin, str);
        }while(str.compare(0, 3, "END") != 0 );
    }
}

void DFS(MTGraph *G, int i)//以vi为出发点对邻接矩阵表示的图G进行深度优先搜索
{
    int j,k,l,n;
    for (j = 0; j < MAXNUM; j++) {//依次搜索vi的邻接点
        if (G->judge[i][j] == 'N'||G->judge[i][j] == 'F'){
            if(visted[i][j]==false){//若ij边尚未访问
                visted[i][j]=true;
                Ispath[number]=true;
            }
            for(n=0;n<m;n++) {//循环访问
                if(one_path[n]==j){//路径中有此边
                     numberOfpath[number]=m;
                     if(Ispath[number]==true){
                        for(l=0;l<m;l++){
                            path[number][l]=one_path[l];
                        }
                        path[number][m]=j;
                        number++;
                     }
                     return;
                }
            }
            for(k=0;k<MAXNUM;k++){//判断j是否有出度
                if(G->judge[j][k]!='s'){
                    break;
                }
            }
            if(k==MAXNUM){//j为出口，因没有出度
                numberOfpath[number]=m;
                if(Ispath[number]==true){
                        for(l=0;l<m;l++){
                            path[number][l]=one_path[l];
                        }
                        path[number][m]=j;
                        number++;
                }
            }
            else if(G->judge[i][j]=='N'){
                one_path[m]=j;
                m++;
                DFS(G, j);
                m--;
            }
            else if(G->judge[i][j]=='F'){
                one_path[m]=j;
                m++;
                DFS(G, j);
                m--;
            }
        }
    }
    for (j = 0; j < MAXNUM; j++) {//依次搜索vi的邻接点
        if (G->judge[i][j] == 'T'){
            if(visted[i][j]==false){//若vj尚未访问
                visted[i][j]=true;
                Ispath[number]=true;
            }
            for(n=0;n<m;n++) {//循环访问
                if(one_path[n]==j){//路径中有此边
                     numberOfpath[number]=m;
                     if(Ispath[number]==true){
                        for(l=0;l<m;l++){
                            path[number][l]=one_path[l];
                        }
                        path[number][m]=j;
                        number++;
                     }
                     return;
                }
            }
            for(k=0;k<MAXNUM;k++){//判断j是否有出度
                if(G->judge[j][k]!='s'){
                    break;
                }
            }
            if(k==MAXNUM){//j为出口，因没有出度
                numberOfpath[number]=m;
                if(Ispath[number]==true){
                        for(l=0;l<m;l++){
                            path[number][l]=one_path[l];
                        }
                        path[number][m]=j;
                        number++;
                }
            }
             else if(G->judge[i][j]=='T'){
                one_path[m]=j;
                m++;
                DFS(G, j);
                m--;
            }
        }
    }
}//DFS

void DFSTraverse(MTGraph *G) //主算法/* 先深搜索一邻接表表示的图G；而以邻接矩阵表示G时，算法完全相同*/
{
    int i,j,k,l;
    for(i=0;i<MAXNUM;i++){
        for(j=0;j<MAXNUM;j++)
            visted[i][j]=false;
        Ispath[i]=false;
    }
    int tmp;
    int tmp_path[MAXNUM];
    one_path[0] = G->begin_vertex;
    DFS(G, G->begin_vertex); //从起始顶点出发的一次搜索，BFS(G, G->begin_vertex)
    cout<<"CC="<<number<<endl;
    for(i=0;i<number;i++){//排序输出
        for(j=i+1;j<number;j++){
            if(numberOfpath[i]>numberOfpath[j]){
                tmp=numberOfpath[j];
                for(k=0;k<=numberOfpath[j];k++){
                    tmp_path[k]=path[j][k];
                }
                for(k=0;k<=numberOfpath[i];k++){
                    path[j][k]=path[i][k];
                }
                numberOfpath[j]=numberOfpath[i];
                for(k=0;k<=tmp;k++){
                    path[i][k]=tmp_path[k];
                }
                numberOfpath[i]=tmp;
            }
            else if(numberOfpath[i]==numberOfpath[j]){
                 for(k=0;k<=numberOfpath[j];k++){
                     if(path[i][k]<path[j][k])  break;
                     else if(path[i][k]>path[j][k]){
                        tmp=numberOfpath[j];
                        for(l=k;l<=numberOfpath[j];l++){
                            tmp_path[l]=path[j][l];
                        }
                        for(l=k;l<=numberOfpath[i];l++){
                            path[j][l]=path[i][l];
                        }
                        numberOfpath[j]=numberOfpath[i];
                        for(l=k;l<=tmp;l++){
                            path[i][l]=tmp_path[l];
                        }
                        numberOfpath[i]=tmp;
                        break;
                     }
                }
            }

        }
    }
     for(i=0;i<number;i++){
        for(j=0;j<numberOfpath[i];j++){
            cout<<path[i][j]<<",";
        }
        cout<<path[i][j]<<endl;
    }
}
/*
 *
 */
int main(int argc, char** argv) {
    MTGraph *G;
    G = new  MTGraph;
    CreateGraph(G);
    DFSTraverse(G);
    return 0;
}

