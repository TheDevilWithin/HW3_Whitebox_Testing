#include <iostream>
#include <stdio.h>

using namespace std;
void fuzhi(int temp,int i,int j,int num);
int judge(int temp,int i,int j);
int numOfNode(int *node,int n,int temp);

int m = 0;
typedef struct{
    int first;
    int second;
    char state;
    }ctj;
ctj s[200];
int l[200][200] ;

int main()
{
    int num = 0;
    int vertex;
    cin>>vertex;
    char ignore;
    int node[200];
    node[0] = vertex;
    int num_node = 1;
    //定义边的属性
    int edge[200][200];
    for(int num_edge1 = 0;num_edge1<200;num_edge1++)
    for(int num_edge2 = 0;num_edge2<200;num_edge2++)
    edge[num_edge1][num_edge2] = 0;
    //定义路径的属性
    int rote[200];
    for(int num_rote =0;num_rote<200;num_rote++)
    rote[num_rote] = 0;
    while(true){//读入数据
        cin>>s[num].first;
        if(cin.fail())
        break;
        if(numOfNode(node,num_node,s[num].first))
        node[num_node++] = s[num].first;
        cin>>ignore;
        cin>>ignore;
        cin>>s[num].second;
        if(numOfNode(node,num_node,s[num].second))
        node[num_node++] = s[num].second;
        cin>>ignore;
        cin>>s[num].state;
        edge[s[num].first][s[num].second] = 1;
        num++;
    }
    num--;
    l[0][0] = vertex;
    fuzhi(vertex,0,0,num+1);
    //数组数量
    int num_s[200];
    for(int number =0 ; number <= m ; number++)
    {
        int number2 = 0;
        while(l[number][number2] != 0)
        number2++;
        num_s[number] = number2-1;
    }
    //排序
    //cout<<num_s[0]<<num_s[1]<<num_s[2]<<num_s[3]<<endl;
    for(int t1 = 0 ; t1 < m ; t1++)
    {
        for(int t2 = t1+1 ; t2 <= m ; t2++)
        {
            if(num_s[t1] > num_s[t2])
            {
                int t3 = num_s[t1];
                while(t3 >=0)//排序
                {
                    int t4=0;
                    t4 = l[t2][t3];
                    l[t2][t3] = l[t1][t3];
                    l[t1][t3] = t4;
                    t3--;
                }
                t3 = num_s[t2];
                num_s[t2]=num_s[t1];
                num_s[t1]=t3;
            }
            if(num_s[t1] == num_s[t2])
            {
                int t5 = 0;
                while(t5<=num_s[t1])
                {
                    if(l[t1][t5]>l[t2][t5])
                    {
                        t5 = 0;
                        while(t5 <= num_s[t1])//交换
                        {
                            int t6 = 0;
                            t6 = l[t2][t5];
                            l[t2][t5] = l[t1][t5];
                            l[t1][t5] = t6;
                            t5++;
                        }
                        break;
                    }
                    t5++;
                }
            }
        }
    }
    //判读边是否都出现过
    for(int a=0;a<=m;a++)
    {
        for(int b=0;b<=num_s[a];b++)
        {
            if(edge[l[a][b]][l[a][b+1]] == 1)
            {
                rote[a] = 1;
                edge[l[a][b]][l[a][b+1]] = 0;
                while(b<=num_s[a])
                {
                    edge[l[a][b]][l[a][b+1]] = 0;
                    b++;
                }
                break;
            }
        }
    }
    //给出圈复杂度
    int m2 = 0;
    for(int a1 = 0;a1<200;a1++)
    if(rote[a1] == 1)
    m2++;
    cout<<"CC="<<m2<<endl;

    for(int i = 0;i<=m;i++)
    {
        if(rote[i] == 1)
        {
            int temp1 = l[i][0];
            int j = 1;
            if(temp1 != 0)
            {
                cout<<temp1;
                temp1 = l[i][1];
                while(temp1 != 0)
                {
                    cout<<","<<temp1;
                    j++;
                    temp1 = l[i][j];
                }
                cout<<endl;
            }
        }
    }
    return 0;
}

void fuzhi(int temp,int i,int j,int num){
    for(int k = 0;k<num;k++){
        if(s[k].first == temp){
            if(s[k].state == 'T'||s[k].state == 'N'){
                l[i][j+1] = s[k].second;
                if(judge(s[k].second,i,j+1))
                fuzhi(s[k].second,i,j+1,num);
            }
            if(s[k].state == 'F'){
                m++;
                for(int n = 0;n<=j;n++){
                    l[m][n] = l[i][n];
                }
                l[m][j+1] = s[k].second;
                if(judge(s[k].second,m,j+1))
                fuzhi(s[k].second,m,j+1,num);
            }

        }
    }
}

int judge(int temp,int i,int j)//判断是否已经存在
{
    for(int j_i = 0;j_i<j;j_i++)
    {
        if(l[i][j_i] == l[i][j])
        return 0;
    }
    return 1;
}

int numOfNode(int *node,int n,int temp)
{
    for(int i = 0;i<n;i++)
    {
        if(node[i] == temp)
        return 0;
    }
    return 1;
}
