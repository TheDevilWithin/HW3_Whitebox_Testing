#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
char middle[200][200];//保存输入边的性质（T,F,N）
int lastanswer[200][200];//保存路径
int middleint[200][2]={{0,0}};//用于遍历时保存数据
int middlenum=0;//遍历时控制变量
int n=0;//路径行数

//判断lastanswer数组第y行，0到z-1项中，有无与z项相等的情况，有返回false，无返回true，用于检测循环。
bool xunhuan(int y,int z){
               int tmp = 0;
               while ( tmp < z) {
                if (lastanswer[y][tmp] == lastanswer[y][z])
                    break;
                tmp++;
            }
      if(tmp == z)
      return true;
      else
      return false;
}

////计算lastanswer数组第2列等于-1的项数，并将项数累加到pointnumber中输出，返回pointnumber,用于打印基本路径数目
int  printcc(int pointnumber){
     int i = 0;
     while ( i < 200) {
        if (lastanswer[i][1] != -1)
            pointnumber++;
        i++;

    }
    cout << "CC=" << pointnumber << endl;
    return pointnumber;
}

//更加arraytemp数组指示的顺序，打印路径
void printway(int pointnumber,int arraytemp[]){
    int i = 0;
    while(i < pointnumber) {
        int ntemp = arraytemp[i];
        int j=0;
        while ( j < 200) {
            if (lastanswer[ntemp][j+1] == -1)
                break;
            else
                cout << lastanswer[ntemp][j] << ',';
            j++;
        }
        cout << lastanswer[ntemp][j] << endl;
         i++;
    }

}

//遍历middle数组，形成基本路径,start为middle数组行，ttemp，rtemp分别为lastanswer中的行和列
void recurse(int start, int ttemp, int rtemp) {
	int x;
    for (x = 0; x< 200; x++) {//先遍历N和F
        if ( middle[start][x] == 'N') {
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {//如果没有循环则迭代
                rtemp++;
                recurse(x, ttemp, rtemp);
            }
        } else if ( middle[start][x] == 'F') {
            middleint[middlenum][0]=ttemp;//保存判定节点的行列值
            middleint[middlenum][1]=rtemp;
            middlenum++;
            //int middlenumber=middlenum; 无用变量
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {//如果没有循环则迭代
                rtemp++;
               recurse(x, ttemp, rtemp);
            }
        }
    }
    for (x = 0; x < 200; x++) {
        if ( middle[start][x] == 'T') {
            for(int w=0;w<200;w++){//将所有为F的边换为N
                if( middle[start][w]=='F')
                     middle[start][w]='N';
            }
             middle[start][x]='0';//将本条为T的边置空
            middlenum--;
            int j1=middleint[middlenum][0];//取出判定节点的行列值
            rtemp=middleint[middlenum][1];
            ttemp=n;
            for (int q = 0; q < rtemp; q++) {//复制判定节点以前的路径
                lastanswer[ttemp + 1][q] = lastanswer[j1][q];
            }
            ttemp++;
            n=ttemp;//增加行数
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {//如果没有循环则迭代
                rtemp++;
                recurse(x,ttemp,rtemp);
            }
        }
    }
}

//处理and节点
void transAND(int position)
{
	int x;
	for (x = 0; x< 200; x++)
	{
		if(middle[position][x]=='F')
		{
			middle[position*10+1][x]='F';
			middle[position*10+2][x]='F';
			middle[position][x]=0;
		}
		else if(middle[position][x]=='T')
		{
			middle[position*10+1][position*10+2]='T';
			middle[position*10+2][x]='T';
			middle[position][x]=0;
		}
	}
	for(x=0;x<200;x++)
		if(middle[x][position]!=0)
		{
			middle[x][position*10+1]=middle[x][position];
			middle[x][position]=0;
		}
}

//处理OR节点
void transOR(int position)
{
	int x;
	for (x = 0; x< 200; x++)
	{
		if(middle[position][x]=='T')
		{
			middle[position*10+1][x]='T';
			middle[position*10+2][x]='T';
			middle[position][x]=0;
		}
		else if(middle[position][x]=='F')
		{
			middle[position*10+1][position*10+2]='F';
			middle[position*10+2][x]='F';
			middle[position][x]=0;
		}
	}
	for(x=0;x<200;x++)
		if(middle[x][position]!=0)
		{
			middle[x][position*10+1]=middle[x][position];
			middle[x][position]=0;
		}
}

int main(int argc, char** argv) {
    int arraynew[200] = {0};//保存每行路径的长度
    int arraynewtemp[200] = {0};//保存路径打印顺序(排序后的数组)
	int i;
    int point;//保存入口节点
    cin >> point;
    int a,b;//保存节点编号
	char r;//保存边属性(N,T,F)
	char command[10];//保存命令EXT,AND,OR
    /*char o,p,q,r;
    while (cin >> a >> o >> p >> b >> q >> r) {
        middle[a][b] = r;
    }*/
	while(scanf("%d->%d,%c", &a, &b, &r)>0)//循环扫描
	{
		middle[a][b]=r;
	}
	scanf("%s", command);
	if(strcmp(command, "EXT")==0)
		while(cin>>a>>r>>command)
		{
			if(a==point)//如果输入的是入口节点，则更改入口节点
				point=point*10+1;
			if(strcmp(command, "AND")==0)
				transAND(a);
			else if(strcmp(command, "OR")==0)
				transOR(a);
			else
				break;
		}
    for (i = 0; i < 200; i++) {//初始化lastanswer数组
        for (int j = 0; j < 200; j++) {
            lastanswer[i][j] = -1;
        }
         lastanswer[i][0] = point;
    }
    recurse(point, 0, 1);//遍历入口
    int cc=printcc(0);//打印基本路径数
    for (i = 0; i < cc; i++) {//计算每行基本路径的长度
        int j = 0;
        while (j < 200) {
            if (lastanswer[i][j] == -1)
                 break;
             else
                 arraynew[i] ++;
             j++;
        }
    }
    for (i = 0; i < cc; i++) {//对基本路径进行排序
        int ele=arraynew[i];
		arraynewtemp[i] = i;
        for (int j = 0; j < cc; j++) {
             if (arraynew[j] == ele&&arraynew[j] != 1000) {
                 int k = 0;
                while( k < 200) {
                    if (lastanswer[arraynewtemp[i]][k]>lastanswer[j][k]) {
                        ele = arraynew[j];
                        arraynewtemp[i] = j;
						break;
                        //k++;
                    }
					else if(lastanswer[arraynewtemp[i]][k]<lastanswer[j][k])
						break;
                    else
                        k++;
                }
            }
             else if (arraynew[j] < ele) {
                  ele= arraynew[j];
                  arraynewtemp[i] = j;
            }
        }
        arraynew[arraynewtemp[i]] = 1000;
    }
    printway(cc,arraynewtemp);//打印基本路径
    return 0;
}
