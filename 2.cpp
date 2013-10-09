/* 
 * File:   main.cpp
 * Author: ioootee
 *
 * Created on 2012年11月16日, 下午8:17
 */

#include <cstdlib>
#include <iostream>
using namespace std;
 struct a{
    int nodenum;
    int lchild;
    int rchild;
    int flag;
};
a nodes[300];//variables
a tmpnode1;
a tmpnode2;
a tmpnode[20];
int path[30][30];
//函数1新建 写num 左右指针为null,flage=0

 struct b{
     int nodenum;
    int index;

};
b nodeindex [50];

int isempty(int ij){
    if(nodes[i].nodenum==0){
        return 0;
    }
    else 
        return nodes[i].nodenum;
}


int lchild(int i){
    if(nodes[i].lchild!=0)
        return nodes[i].lchild;
    else
        return 0;
}

int rchild(int i){
    if(nodes[i].rchild!=0)
        return nodes[i].rchild;
    else 
        return 0;
}


bool isin(int num,int pathn,int len){
    for (int i=0;i<len;i++){
        if(path[pathn][i]==num)
            return true;
    }
    return false;
}
int pathnum=0;
int pathlen=0;


int array[30];   //栈，用于保存数据
int ding=-1;
int temp;



void pre(int i){
    if(!isempty(i)){   //记录一条新路径
        //sum[pathnum]=pathlen;
        pathnum++;
        pathlen=0;
    }
    else if(isin(nodes[i].nodenum,pathnum,pathlen)){
        path[pathnum][pathlen++]=nodes[i].nodenum;
        //sum[pathnum]=pathlen;
        pathnum++;
        pathlen=0;
    }
    else{
        path[pathnum][pathlen++]=nodes[i].nodenum;
        //cout<<nodes[i].nodenum;
    if(nodes[i].flag==0){
        pathnum++;
        pathlen=0;
    }

    if(nodes[i].flag==1){   //类型为N
        temp=lchild(i);
        pre(temp);
    }
    
    if(nodes[i].flag==2){
        for(int u=1;u<=pathlen;u++){   //有分支就在访问左结点之前压站
            array[ding+u]=path[pathnum][u-1];
        }
        ding+=pathlen;
        array[++ding]=pathlen;    //压入此次压站的数量
        //ding++;
        temp=lchild(i);
        pre(temp);

        int t=array[ding--];
        pathlen=t;
        for(t;t>0;t--){   //在访问右结点时把栈中的数据放入右结点的路线中
            path[pathnum][t-1]=array[ding--];
        }
        temp=rchild(i);
        pre(temp);
    }
}
}

//
/*
 * 
 */
int main(int argc, char** argv) {
    cin>>nodes[1].nodenum;
    nodeindex[1].index=1;
    nodeindex[1].nodenum=nodes[1].nodenum;
    int count=1;

    char type;
    int from=0;         //将信息记录在from和to中
    int to=0;
    char tmpchars[30];
    cin>>tmpchars[0];
    int ini=0;


    while (tmpchars[0]!='E'){
        from=0;
        to=0;
        ini=0;
    while (tmpchars[ini]!='-'){
        from=from*10+tmpchars[ini]-'0';
        ini++;
        cin>>tmpchars[ini];
    }

    ini=0;
    cin>>tmpchars[ini];
     cin>>tmpchars[ini];
    while (tmpchars[ini]!=','){
        to=to*10+tmpchars[ini]-'0';
         ini++;
        cin>>tmpchars[ini];
    }
     cin>>type;

     bool tofront=false;
     //bool in=false;
     int tmpindex;

     for(int i=1;i<=count;i++){          //遍历记录结点下表信息的nodeindex数组；
         if(nodeindex[i].nodenum==from){
             tofront=false;
             if (type=='F'){
                
                 for (int u=1;u<=count;u++){        //to结点是前面记录过的结点
                     if(nodeindex[u].nodenum==to){
                         tofront=true;

                         nodes[nodeindex[i].index].lchild=nodeindex[u].index;
                         nodes[nodeindex[i].index].flag=2;
                         break;
                     }
                 }
                 if(!tofront){              //to结点没出现过
             nodes[nodeindex[i].index*2].nodenum=to;
             nodes[nodeindex[i].index].lchild=nodeindex[i].index*2;
             tmpindex=nodeindex[i].index*2;
             nodes[nodeindex[i].index].flag=2;
                 }
             }
             else if (type=='T'){
                 // bool tofront=false;
                 for (int u=1;u<=count;u++){        //to结点是前面记录过的结点
                     if(nodeindex[u].nodenum==to){
                         tofront=true;
                         nodes[nodeindex[i].index].rchild=nodeindex[u].index;
                         nodes[nodeindex[i].index].flag=2;
                         break;
                     }
                 }
                  if(!tofront){
             nodes[nodeindex[i].index*2+1].nodenum=to;
             nodes[nodeindex[i].index].rchild=nodeindex[i].index*2+1;
              tmpindex=nodeindex[i].index*2+1;
             nodes[nodeindex[i].index].flag=2;
                        }
             }
             else if(type=='N'){

                // bool tofront=false;
                 for (int u=1;u<=count;u++){        //to结点是前面记录过的结点
                     if(nodeindex[u].nodenum==to){
                         tofront=true;
                         nodes[nodeindex[i].index].lchild=nodeindex[u].index;
                         nodes[nodeindex[i].index].flag=1;
                         break;
                     }
                 }
                 if(!tofront){
                 nodes[nodeindex[i].index*2].nodenum=to;
                 nodes[nodeindex[i].index].lchild=nodeindex[i].index*2;
                 tmpindex=nodeindex[i].index*2;
                 nodes[nodeindex[i].index].flag=1;
                 }
             }
             break;
         }
     }



         if(!tofront){            //若to结点是否在nodeindex数组中，不在就将其加入
             count++;
             nodeindex[count].nodenum=to;
             nodeindex[count].index=tmpindex;
         }
     cin>>tmpchars[0];
     
    }


    cin>>tmpchars[0];
    cin>>tmpchars[0];
    if(tmpchars[0]=='T'){
         ini=0;
    
     cin>>tmpchars[ini];
     while (tmpchars[ini]!=','){
        to=to*10+tmpchars[ini]-'0';
         ini++;
        cin>>tmpchars[ini];
    }
     cin>>type;
     int noden=0;
     int tmp=0;
     if(type=='A'){
         cin>>type;
         cin>>type;
         for(int i=1;i<=count;i++){
             if(nodeindex[i].nodenum==to){
                 nodes[nodeindex[i].index].nodenum=nodes[nodeindex[i].index].nodenum*10+1;
                 tmp=lchild(i);
                 if(tmp){
                     tmpnode[noden].nodenum=nodes[temp].nodenum;
                     tmpnode[noden].lchild=nodes[temp].lchild;
                     tmpnode[noden].rchild=nodes[temp].rchild;
                     tmpnode[noden].flag=nodes[temp].flag;
                 }
                 int nnow=0;
                 while(tmpnode[noden].flag!=0){
                     if(tmpnode[noden].flag!=1){
                         tmpnode[++noden].nodenum=nodes[nnow].nodenum;
                         tmpnode[++noden].lchild=nodes[nnow].lchild;
                         tmpnode[++noden].rchild=nodes[nnow].rchild;
                         tmpnode[++noden].flag=nodes[nnow].flag;
                     }
                 }

             }
         }
     }
      else if(type=='O'){
         cin>>type;

      }
    }
    
    pre(1);
   // int shunxun[30];
   // int shu[30]={0};
   
   // int min=100;
   // for(int t=0;t<pathnum;t++){
     //   int u=0;
      //  while(path[t][u]!=0){
        //    shu[t]++;
         //   u++;
      //  }
       // cout<<shu[t]<<endl;
        //if(min>shu[t]){
        //    min=shu[t];
      //  }
      //  cout<<endl;
 //   }

  //  int outcount=0;
  //  for(int t=0;t<pathnum;t++){
     //   while(outcount!=pathnum){
       //    if()
       // }
    //}
    int min=100;
    int outcount=0;
     int len[30]={0};
    int outarray[30]={0};
    int outarr[30]={0};
    //int pionts[30]={0};
    int bian[100][2]={0};
    int biancount=0;
   // pionts[0]=nodes[1].nodenum;
    //int piontsnum=1;
 //   bian[0][0]=path[0][0];
 //   bian[0][1]=path[0][1];
    int oldnum=0;
    for(int t=0;t<pathnum;t++){
        int u=0;
        while(path[t][u+1]!=0){
            bool nohave=true;
            if(biancount!=0){
            for(int x=0;x<biancount;x++){
                if(path[t][u]==bian[x][0]&&path[t][u+1]==bian[x][1]){
                    nohave=false;
                    break;
                }
            }
            }
                if(nohave){
                    biancount++;
                    bian[biancount-1][0]=path[t][u];
                    bian[biancount-1][1]=path[t][u+1];
                    
                }
                u++;
        }
        if(oldnum==biancount)
            continue;
        else{
            oldnum=biancount;
            outarray[outcount]=t;
            len[outcount++]=u;
            if(u<min)
                min=u;
         
        }
    }



//按长度排序，相同的按字典序
    int ocount=0;
    int tmpfrom=0;
    int tmpto=0;
    while(ocount<outcount){
    for(int j=0;j<outcount;j++){
        if(len[j]==min){
             tmpto=ocount;
            outarr[ocount++]=outarray[j];
            len[j]=100;
        }
      }

    bool change=true;
    int i=tmpfrom;
    while(change){
        change=false;
        int u=0;
    for(i;i+u<tmpto;u++){
        int t=0;
      while(path[outarr[i+u]][t]!=0){
         if( path[outarr[i+u]][t]-path[outarr[i+u+1]][t]>0){
         int tmp=outarr[i+u+1];
         outarr[i+u+1]=outarr[i+u];
         outarr[i+u]=tmp;
         change=true;
          break;
         }
         else if( path[outarr[tmpfrom]][t]-path[outarr[tmpfrom+1]][t]<0){

             change=false;
             break;
             
         }
         t++;
      }
    }
    }
    tmpfrom=tmpto+1;
    min++;
    }

    for(int q=0;q<outcount;q++){
        if(outarr[q]==outarr[q+1]){
      int t=0;
      while(path[outarr[q]][t]!=0){
         if( path[outarr[q]][t]-path[outarr[q+1]][t]>0){
         int tmp=outarr[q+1];
         outarr[q+1]=outarr[q];
         outarr[q]=tmp;
          break;
         }
         t++;
      }
        }
    }
  cout<<"CC="<<outcount<<endl;
  for(int o=0;o<outcount;o++){
      int t=0;
      while(path[outarr[o]][t+1]!=0){
          cout<<path[outarr[o]][t];
          cout<<",";
          t++;
      }
      cout<<path[outarr[o]][t];
      cout<<endl;
  }
    return 0;
}

