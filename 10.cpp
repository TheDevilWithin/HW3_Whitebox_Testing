#include <cstdlib>
#include <iostream>

using namespace std;
char middle[100][100];
int lastanswer[100][100];
int middleint[100][2]={0};
int middlenum=0;
int n=0;

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

int  printcc(int pointnumber){
     int i = 0;
     while ( i < 100) {
        if (lastanswer[i][1] != -1)
            pointnumber++;
        i++;

    }
    cout << "CC=" << pointnumber << endl;
    return pointnumber;
}

void printway(int pointnumber,int arraytemp[]){
    int i = 0;
    while(i < pointnumber) {
        int ntemp = arraytemp[i];
        int j=0;
        while ( j < 100) {
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


void recurse(int start, int ttemp, int rtemp) {

    for (int x = 0; x< 100; x++) {
        if ( middle[start][x] == 'N') {
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {
                rtemp++;
                recurse(x, ttemp, rtemp);
            }
        } else if ( middle[start][x] == 'F') {
            middleint[middlenum][0]=ttemp;
            middleint[middlenum][1]=rtemp;
            middlenum++;
            int middlenumber=middlenum;
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {
                rtemp++;
               recurse(x, ttemp, rtemp);
            }
        }
    }
    for (int x = 0; x < 100; x++) {
        if ( middle[start][x] == 'T') {
            for(int w=0;w<100;w++){
                if( middle[start][w]=='F')
                     middle[start][w]='N';
            }
             middle[start][x]='0';
            middlenum--;
            int j1=middleint[middlenum][0];
            rtemp=middleint[middlenum][1];
            ttemp=n;
            for (int q = 0; q < rtemp; q++) {
                lastanswer[ttemp + 1][q] = lastanswer[j1][q];
            }
            ttemp++;
            n=ttemp;
            lastanswer[ttemp][rtemp] = x;
            if (xunhuan(ttemp,rtemp)) {
                rtemp++;
                recurse(x,ttemp,rtemp);
            }
        }
    }
}

int main(int argc, char** argv) {
    int arraynew[100] = {0};
    int arraynewtemp[100] = {0};

    int point;
    cin >> point;
    int a,b;
    char o,p,q,r;
    while (cin >> a >> o >> p >> b >> q >> r) {
        middle[a][b] = r;
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            lastanswer[i][j] = -1;
        }
         lastanswer[i][0] = point;
    }
    recurse(point, 0, 1);
    int cc=printcc(0);
    for (int i = 0; i < cc; i++) {
        int j = 0;
        while (j < 100) {
            if (lastanswer[i][j] == -1)
                 break;
             else
                 arraynew[i] ++;
             j++;
        }
    }
    for (int i = 0; i < cc; i++) {
        int ele = arraynew[i];
        arraynewtemp[i] = i;
        for (int j = 0; j < cc; j++) {
             if (arraynew[j] != 1000&&arraynew[j] == ele) {
                 int k = 0;
                while( k < 100) {
                    if (lastanswer[arraynewtemp[i]][k]>lastanswer[j][k]) {
                        ele = arraynew[j];
                        arraynewtemp[i] = j;
                        k++;
                    }
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
    printway(cc,arraynewtemp);
    return 0;
}

