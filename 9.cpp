#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * 
 */

int graph[200][6];
int circomplex = 0;
int step = 0;
int newroute = 0;
int basicroute[100][100];

/* column 5 --- newroute
 * column 4 --- judgement node
 * column 3 --- extended node
 * column 2 --- AND(1) or OR(0)
 * column 1 --- true node
 * column 0 --- false node or normal node
 */

void route(int node)
{
    int local;
    if (node < 100) //normal node, judgement node and first extend node
    {
        if (graph[node][3] == -1) //non-extend node
            local = node;
        else if (graph[node][3] == 1) //first extend node
            local = node * 10 + 1;
    }
    else //second extend node
        local = (node - 100) * 10 + 2;
    basicroute[circomplex][step] = local;
    step++;

    if (graph[node][0] < 0)
    {
        if (graph[node][5] == -1)
        {
            graph[node][5] = 0;
            newroute = 1;
        }
        return; //end node
    }

    for (int i = 0; i < (step - 1); i++)
        if (basicroute[circomplex][i] == local)
            return; //repeated node

    if (graph[node][5] == 1) //new route
    {
        newroute = 1;
        graph[node][5] = 0;
    }

    if (graph[node][4] == -1) //normal node
    {
        //cout << local << "->" << graph[node][0] << ",N" << endl;
        route(graph[node][0]);
    }

    if (graph[node][4] == 1) //judgement node
    {
        int tmpstep = step;
        if (graph[node][3] == -1)//non-extended node
        {
            //cout << local << "->" << graph[node][0] << ",F" << endl;
            route(graph[node][0]);
            if (newroute == 0) //old route
            {
                //cout << "old route" << endl;
                for (int i = tmpstep; i < 100; i++)
                    basicroute[circomplex][i] = -1;
                step = tmpstep;
            }
            else //new route
            {
                //cout << "new route" << endl;
                basicroute[circomplex][99] = step;
                circomplex++;
                step = tmpstep;
                for (int i = 0; i < step; i++)
                    basicroute[circomplex][i] = basicroute[circomplex - 1][i];
            }
            //cout << local << "->" << graph[node][1] << ",T" << endl;
            newroute = 0;
            route(graph[node][1]);
        }
        if (graph[node][3] == 1)//extended node
        {
            if (node < 100) //first node
            {
                if (graph[node][2] == 1) //AND
                {
                    route(graph[node][0]);
                    if (newroute == 0)
                    {
                        for (int i = tmpstep; i < 100; i++)
                            basicroute[circomplex][i] = -1;
                        step = tmpstep;
                    }
                    else
                    {
                        basicroute[circomplex][99] = step;
                        circomplex++;
                        step = tmpstep;
                        for (int i = 0; i < step; i++)
                            basicroute[circomplex][i] = basicroute[circomplex - 1][i];
                    }
                    newroute = 0;
                    route(node + 100);
                }
                else if (graph[node][2] == 0) //OR
                {
                    route(node + 100);
                    if (newroute == 0)
                    {
                        for (int i = tmpstep; i < 100; i++)
                            basicroute[circomplex][i] = -1;
                        step = tmpstep;
                    }
                    else
                    {
                        basicroute[circomplex][99] = step;
                        circomplex++;
                        step = tmpstep;
                        for (int i = 0; i < step; i++)
                            basicroute[circomplex][i] = basicroute[circomplex - 1][i];
                    }
                    newroute = 0;
                    route(graph[node][1]);
                }
            }
            else //second node
            {
                if (graph[node][2] == 1) //AND
                {
                    route(graph[node][0]);
                    if (newroute == 0)
                    {
                        for (int i = tmpstep; i < 100; i++)
                            basicroute[circomplex][i] = -1;
                        step = tmpstep;
                    }
                    else
                    {
                        basicroute[circomplex][99] = step;
                        circomplex++;
                        step = tmpstep;
                        for (int i = 0; i < step; i++)
                            basicroute[circomplex][i] = basicroute[circomplex - 1][i];
                    }
                    newroute = 0;
                    route(graph[node][1]);
                }
                else if (graph[node][2] == 0) //OR
                {
                    route(graph[node][0]);
                    if (newroute == 0)
                    {
                        for (int i = tmpstep; i < 100; i++)
                            basicroute[circomplex][i] = -1;
                        step = tmpstep;
                    }
                    else
                    {
                        basicroute[circomplex][99] = step;
                        circomplex++;
                        step = tmpstep;
                        for (int i = 0; i < step; i++)
                            basicroute[circomplex][i] = basicroute[circomplex - 1][i];
                    }
                    newroute = 0;
                    route(graph[node][1]);
                }
            }
        }
    }
}

void displayrou()
{
    int tmparray[100] = {-1};
    int index, min;

    //order by step
    for (int i = 0; i < 100; i++)
    {
        if (basicroute[i][99] == -1)
            break;
        index = i;
        min = basicroute[i][99];
        for (int j = i + 1; j < 100; j++)
        {
            if (basicroute[j][99] == -1)
                break;
            if (basicroute[j][99] < min)
            {
                min = basicroute[j][99];
                index = j;
            }
        }

        if (index != i)
        {
            for (int k = 0; k < 100; k++)
                tmparray[k] = basicroute[i][k];
            for (int k = 0; k < 100; k++)
            {
                basicroute[i][k] = basicroute[index][k];
                basicroute[index][k] = tmparray[k];
            }
        }
    }

    int index1, index2;

    //order by dictionary
    for (int i = 0; i < 99; i++)
    {
        index1 = i;
        index2 = i + 1;
        if (basicroute[index2][99] < 0)
            break;

        if (basicroute[index1][99] == basicroute[index2][99])
        {
            for (int j = 0; j < 100; j++)
            {
                if (basicroute[index1][j] < basicroute[index2][j])
                    break;
                if (basicroute[index2][j] < basicroute[index1][j])
                {
                    for (int k = 0; k < 100; k++)
                        tmparray[k] = basicroute[index1][k];
                    for (int k = 0; k < 100; k++)
                    {
                        basicroute[index1][k] = basicroute[index2][k];
                        basicroute[index2][k] = tmparray[k];
                    }
                    break;
                }
            }
        }
    }

    //test
    /*
    cout << "basicroute:" << endl;
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 20; j++)
            cout << basicroute[i][j] << " ";
        cout << endl;
    }
    cout << endl;
     */

    for (int i = 0; i < 100; i++)
    {
        if (basicroute[i][99] < 0)
            break;

        for (int j = 0; j < 99; j++)
        {
            if (basicroute[i][j] < 0)
                break;

            cout << basicroute[i][j];
            if (basicroute[i][j + 1] >= 0)
                cout << ",";
        }
        cout << endl;
    }
}

int main(int argc, char** argv)
{
    for (int i = 0; i < 200; i++)
        for (int j = 0; j < 6; j++)
            graph[i][j] = -1;
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            basicroute[i][j] = -1;

    char input[10];
    int count = 0, extend = 0;
    int node1, node2, startnode;
    int pos;

    /*
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 6; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
     */

    while (1)
    {
        for (int i = 0; i < 10; i++)
            input[i] = '\0';

        cin >> input;
        pos = 9;
        while (input[pos] == '\0')
            pos--;

        if (input[0] == 'E' && input[1] == 'N')
            break;
        if (input[0] == 'E' && input[1] == 'X')
        {
            extend = 1;
            continue;
        }

        if (count == 0)
        {
            if (pos == 0)
                startnode = input[0] - 0x30;
            else
                startnode = (input[0] - '0') * 10 + (input[1] - '0');
            //cout << "start node is: " << startnode << endl;
            count++;
            continue;
        }

        if (extend == 0) //none extended
        {
            switch (pos)
            {
            case 5:
                node1 = input[0] - 0x30;
                node2 = input[3] - 0x30;
                break;
            case 6:
                if (input[1] < 0x30 || input[1] > 0x39)
                {
                    node1 = input[0] - 0x30;
                    node2 = (input[3] - 0x30)*10 + (input[4] - 0x30);
                }
                else
                {
                    node1 = (input[0] - 0x30)*10 + (input[1] - 0x30);
                    node2 = input[4] - 0x30;
                }
                break;
            case 7:
                node1 = (input[0] - 0x30)*10 + (input[1] - 0x30);
                node2 = (input[4] - 0x30)*10 + (input[5] - 0x30);
                break;
            }
            if (input[pos] == 'T' || input[pos] == 'F')
            {
                graph[node1][4] = 1; //column 4 is 1 if it's a judgement node
                graph[node1][5] = 1; //column 5 is 1 if not visited
                if (input[pos] == 'T')
                    graph[node1][1] = node2; //column 1 is True bit
                if (input[pos] == 'F')
                    graph[node1][0] = node2; //column 0 is False bit
            }
            else if (input[pos] == 'N') //normal node
            {
                //cout << "node " << input[0] << "is normal node" << endl;
                graph[node1][0] = node2;
                graph[node1][5] = 1;
            }
            //cout << "node " << input[0] << " links node " << input[3] << endl;
            count++;
        }

        if (extend == 1) //extended node
        {
            if (input[1] >= 0x30 && input[1] <= 0x39)
                node1 = (input[0] - 0x30)*10 + (input[1] - 0x30);
            else
                node1 = input[0] - 0x30;

            graph[node1][3] = 1; //column 3 is 1 if it's extended
            graph[node1][5] = 1;
            if (input[pos] == 'D')
                graph[node1][2] = 1; //if it's AND node, column 2 is 1
            if (input[pos] == 'R')
                graph[node1][2] = 0; //if OR, column 2 is 0

            //copy info
            for (int i = 0; i < 6; i++)
                graph[node1 + 100][i] = graph[node1][i];

            count++;
        }
    }

    //test
    /*
    cout << "graph:" << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 6; j++)
            cout << graph[i][j] << " ";
        cout << '\n';
    }
    cout << endl;
     */

    route(startnode);
    if (newroute == 1)
    {
        basicroute[circomplex][99] = step;
        circomplex++;
    }
    else
        for (int i = 0; i < 100; i++)
            basicroute[circomplex][i] = -1;

    //test
    /*
    cout << "basicroute: " << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 100; j++)
            cout << basicroute[i][j] << " ";
        cout << endl;
    }
    cout << endl;
     */

    cout << "CC=" << circomplex << endl;
    displayrou();

    return 0;
}

