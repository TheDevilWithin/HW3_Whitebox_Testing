#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <stdio.h>

using namespace std;

struct MTGraph {
    string vertex[100];
    string edge[100][100];
    int vertex_num, edge_num;
};
typedef struct MTGraph MTGraph;

struct input {
    string val1;
    string val2;
    string type;
};
typedef struct input input;

int order[100] = {0};
bool visited[100] = {false};
int position[100] = {-1};
vector<string> now;
vector<int> tmpstr;
vector<string> result;

int findid(string a, string b[100]) {
    int i;
    for (i = 0; i < 100; i++) {
        if (a == b[i]) {
            break;
        }
    }
    if (i == 100)
        return -1;
    else
        return i;
}

int torf = 0;
int a[100][100];
int line = 0;
int linesize[100] = {0};

int b[100][100];
int line2 = 0;
int linesize2[100] = {0};
int test[100][100];

void deal(MTGraph G, int t) {
    for (vector<string>::size_type x = 0; x < now.size(); x++) {
        tmpstr.push_back(atoi(now[x].c_str()));
    }
    //    for (int p = 0; p < G.vertex_num; p++) {
    //        if (G.edge[t][p] != "0") {
    //            tmpstr.push_back(atoi(G.vertex[p].c_str()));
    //            break;
    //        }
    //    }
    if (t != -1) {
        tmpstr.push_back(atoi(G.vertex[t].c_str()));
    }
    for (vector<int>::size_type j = 0; j < tmpstr.size(); j++) {
        a[line][j] = tmpstr[j];
    }
    linesize[line] = tmpstr.size();
    tmpstr.clear();
    bool outjudge = false;
    for (int j = 0; j < linesize[line] - 1; j++) {
        if (test[a[line][j]][a[line][j + 1]] == 0) {
            test[a[line][j]][a[line][j + 1]] = 1;
            outjudge = true;
        }
    }
    if (outjudge)
        line++;
}
int judge;

void DFS(MTGraph G, int i) {
    int j;
    //cout << G.vertex[i]; //访问定点vi

    judge = 0;
    if (order[i] == 1 || order[i] == 0) {
        for (j = 0; j < G.vertex_num; j++) { //依次搜索vi的邻接点
            if ((G.edge[i][j] == "F" || G.edge[i][j] == "T" || G.edge[i][j] == "N")) { //若vj尚未访问
                judge = 1;
                if (visited[j] == false) {
                    now.push_back(G.vertex[j]);
                    visited[j] = 1;
                    DFS(G, j);
                    visited[j] = 0;
                    now.pop_back();
                } else {
                    deal(G, j);
                }
            }
        }
    }
    if (order[i] == 2) {
        for (j = G.vertex_num - 1; j >= 0; j--) { //依次搜索vi的邻接点
            if ((G.edge[i][j] == "F" || G.edge[i][j] == "T" || G.edge[i][j] == "N")) //若vj尚未访问
            {
                judge = 1;
                if (visited[j] == false) {
                    now.push_back(G.vertex[j]);
                    visited[j] = 1;
                    DFS(G, j);
                    visited[j] = 0;
                    now.pop_back();
                } else {
                    deal(G, j);
                }
            }
        }
    }
    if (!judge) {
        //cout << "*";
        deal(G, -1);
        judge = 1;
    }
}

void dfstravel(MTGraph G) {
    visited[0] = true;
    now.push_back(G.vertex[0]);
    DFS(G, 0);

}

bool compare(int n1, int n2) {
    if (linesize[n1] > linesize[n2])
        return true;
    else if (linesize[n1] < linesize[n2])
        return false;
    else {
        for (int q = 0; q < linesize[n1]; q++) {
            if (a[n1][q] > a[n2][q]) {
                return true;
            }
        }
    }
    return false;
}

void Swap(int i, int j) {
    int t = max(linesize[i], linesize[j]);
    for (int k = 0; k < t; k++)
        swap(a[i][k], a[j][k]);
    swap(linesize[i], linesize[j]);
}

int main(int argc, char** argv) {

    string first;
    //int count=0;
    MTGraph graph;
    for (int p = 0; p < 100; p++) {
        graph.vertex[p] = "0";
    }
    for (int p = 0; p < 100; p++) {
        for (int q = 0; q < 100; q++)
            graph.edge[p][q] = "0";
    }
    graph.vertex_num = 0;
    graph.edge_num = 0;

    cin >> first;
    string inputtmp;
    string sstmp;
    input intmp;
    vector<input> inrecord;
    int label1, label2;
    while (cin >> inputtmp) {
        if (inputtmp != "END") {
            label1 = inputtmp.find("->");
            label2 = inputtmp.find(",");
            sstmp = inputtmp.substr(0, label1);
            intmp.val1 = sstmp;
            sstmp = inputtmp.substr(label1 + 2, label2 - label1 - 2);
            intmp.val2 = sstmp;
            sstmp = inputtmp.substr(label2 + 1, inputtmp.size() - label2);
            intmp.type = sstmp;
            inrecord.push_back(intmp);
        } else
            break;
    }

    //--------------------------------------------------------------------------建图
    int x, y;
    graph.vertex[0] = first;
    graph.vertex_num++;
    for (vector<input>::size_type i = 0; i != inrecord.size(); ++i) {
        x = findid(inrecord[i].val1, graph.vertex);
        y = findid(inrecord[i].val2, graph.vertex);
        if (x < 0) {
            graph.vertex[graph.vertex_num] = inrecord[i].val1;
            x = graph.vertex_num;
            (graph.vertex_num)++;
        }
        if (y < 0) {
            graph.vertex[graph.vertex_num] = inrecord[i].val2;
            y = graph.vertex_num;
            (graph.vertex_num)++;
        }
        graph.edge[x][y] = inrecord[i].type;
    }

    //输出图
    /*
    for (int k = 0; k < graph.vertex_num; k++) {
        cout << graph.vertex[k] << " ";
    }
    cout << endl << endl << endl;
    for (int k = 0; k < graph.vertex_num; k++) {
        for (int j = 0; j < graph.vertex_num; j++) {
            cout << graph.edge[k][j] << " ";
        }
        cout << endl;
    }

    bool flag = false;
    position[0] = 0;
    for (int k = 1; k < graph.vertex_num; k++) {
        flag = false;
        for (int j = 0; j < graph.vertex_num; j++) {
            if (graph.edge[k][j] == "F" || graph.edge[k][j] == "T") {
                position[k] = 1;
                flag = true;
                break;
            }
            if (graph.edge[k][j] == "N") {
                position[k] = 2;
                flag = true;
                break;
            }
        }
        if (!flag)
            position[k] = 3;
    }
    for (int k = 0; k < graph.vertex_num; k++) {
        cout << position[k] << " ";
    }
    cout << endl;
     */
    //遍历顺序

    int fid, tid;
    string str1 = "F";
    string str2 = "T";
    string tmp[100];
    for (int k = 0; k < graph.vertex_num; k++) {
        for (int t = 0; t < 100; t++) {
            tmp[t] = graph.edge[k][t];
        }
        fid = findid(str1, tmp);
        tid = findid(str2, tmp);
        //cout << fid << " " << tid << endl;
        if (fid < tid)
            order[k] = 1;
        if (tid < fid)
            order[k] = 2;
    }
    for (int p = 0; p < 100; p++) {
        for (int q = 0; q < 100; q++)
            test[p][q] = 0;
    }

    /*
       for (int k = 0; k < graph.vertex_num; k++) {
            cout << order[k] << " ";
        }
     */
    /*int count = 0;
    for (int i = 0; i < graph.vertex_num; i++) {
        if (position[i] == 1)
            count++;
    }
    count++;
    count++;
    cout << "CC=" << count << endl;*/
    dfstravel(graph);

    //cout<<endl<<endl;
    //cout<<result.size()<<endl;
    //for (vector<string>::size_type xx = 0; xx < result.size(); xx++) {
    //    cout << result[xx] << endl;
    //}

    int swapint[100];
    int swapsize;
    for (int nn = 0; nn < line; nn++) {
        for (int mm = nn + 1; mm < line; mm++) {
            if (compare(nn, mm)) {
                Swap(nn, mm);
            }
        }
    }




    cout << "CC=" << line << endl;
    //for(vector<string>::size_type z=0;z<result.size();z++){
    //   cout<<result[z]<<endl;
    //}
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < linesize[i] - 1; j++) {
            cout << a[i][j] << ",";
        }
        cout << a[i][linesize[i] - 1] << endl;
    }
    return 0;
}

