#include<iostream>
#include<cstdio>
#include<vector>
#include<iterator>
#include<algorithm>
using std::cout;
using std::endl;
using std::scanf;
using std::printf;
using std::vector;
using std::iterator;
using std::sort;
class Node{
	public:
		Node(int, int, int, int);
		~Node(void);
		/*bool isFVisit();
		bool isTVisit();*/
		int nod_num;
		int f_num;//if condition is false, exec number
		int t_num;//if true, exec num
		int n_num;//none condition, exec this
		bool f_visit;//if f_num is visited , set true
		bool t_visit;//if t_num is visited , set true
};
Node::Node(int _nod_num = -1, int _f_num = -1, int _t_num = -1, int _n_num = -1):nod_num(_nod_num), f_num(_f_num), t_num(_t_num), n_num(_n_num),
																				 f_visit(false), t_visit(false){
}
Node::~Node(void){
}
void swap(vector<Node> &v1, vector<Node> &v2){
	vector<Node> v3;
	v3 = v1;
	v1 = v2;
	v2 = v3;
}
/*
class Edge{
	public:
		Edge(int, int, int);
		int nod_edge;
		int f_edge;
		int t_edge;
};
Edge::Edge(int _nod_edge = -1, int _f_edge = -1, int _t_edge = -1):nod_edge(_nod_edge), f_edge(_f_edge), t_edge(_t_edge){
}
*/
const int ARR_SIZE = 128;
bool isLoop(vector<Node> &vec){
	vector<Node>::iterator itr;
	for(itr = vec.begin(); itr != vec.end() - 1; itr++){
		if((*itr).nod_num == vec.back().nod_num)
			return true;
	}
	return false;
}
bool cmp(vector<Node> v1, vector<Node> v2){
		return v1.size() < v2.size();
}
/*
bool dictCmp(vector<Node> v1, vector<Node> v2){
	if(v1.size() == v2.size()){
		for(int i = 0; i < v1.size(); i++){
			if(v1[i].nod_num == v2[2].nod_num)
				continue;
			else
				return v1[i].nod_num < v2[i].nod_num;
		}
	}
	else
		return 
}
*/
int main(){
	int head,father, child;
	char condition;
	char str[8];
	Node *arr_nod = new Node[ARR_SIZE];
	//Edge *arr_edg = new Edge[ARR_SIZE];
	scanf("%d", &head);
	while(scanf("%d->%d,%c", &father, &child, &condition)){
		arr_nod[father].nod_num = father;
		arr_nod[child].nod_num = child;
		if(condition == 'N')
			arr_nod[father].n_num = child;
		else if(condition == 'F')
			arr_nod[father].f_num = child;
		else
			arr_nod[father].t_num = child;
	}

	/*test code
		
	for(int i = 0; i < 10; i++){
		if(arr_nod[i].nod_num != -1){
			cout << arr_nod[i].nod_num << "\t" << arr_nod[i].f_num <<"\t" << arr_nod[i].t_num << "\t"<< arr_nod[i].n_num<< endl;
		}
	}
	*/	

	scanf("%s", str);//deal with ext or end string
	//printf("%s\n", str);
	/*need some code to deal with ext case*/
	/*
	stack<Node> nod_stk;//stack of node pointer			
	nod_stk.push(arr_nod[head]);
	while(!nod_stk.empty()){
			
	}
	*/
	
	vector<Node> nod_vec;//work as a stack
	nod_vec.push_back(arr_nod[head]);
	Node n_tmp, put_tmp;
	vector<vector<Node> > vec_result;
	while(!nod_vec.empty()){
		n_tmp = nod_vec.back();
		//node has non condition
		if(n_tmp.n_num != -1){
			//check loop, may reuseful
			if(isLoop(nod_vec)){
				vec_result.push_back(nod_vec);
				nod_vec.pop_back();

				//back trace
				while(true){

					if(/*(nod_vec.back().n_num == -1 && nod_vec.back().f_num == -1 ) ||*/nod_vec.back().n_num =! -1/*non condition*/
					  || nod_vec.back().t_visit == true){
						nod_vec.pop_back();
						if(nod_vec.empty())
							break;	
					}
					else /*(nod_vec.back().t_visit == false)*/{
						put_tmp = arr_nod[nod_vec.back().t_num];
						nod_vec.push_back(put_tmp);
						break;
					}
				}

			}
			else{
				put_tmp = arr_nod[nod_vec.back().n_num];
				nod_vec.push_back(put_tmp);
			}
		}
		//node has true or false confition
		else if(n_tmp.f_num != -1){
			//check loop	
			//set visit
			//check new edge , may not to do this???

			//deal with
			if(!n_tmp.f_visit){
				/*test code
				nod_vec.back().f_num = 10;
				*/
				nod_vec.back().f_visit = true;
				arr_nod[nod_vec.back().nod_num].f_visit = true;
				put_tmp = arr_nod[nod_vec.back().f_num];
				nod_vec.push_back(put_tmp);
				/*arr_edg[n_tmp.nod_num].nod_edge = n_tmp.nod_num;
				arr_edg[n_tmp.nod_num].f_edge = n_tmp.f_edge;*/
			}
			else{
					
				if(isLoop(nod_vec)){
					vec_result.push_back(nod_vec);
					nod_vec.pop_back();

					//back trace
					while(true){
						if(/*(nod_vec.back().n_num == -1 && nod_vec.back().f_num == -1 ) ||*/nod_vec.back().n_num != -1/*non condition*/
						  || nod_vec.back().t_visit == true){
							nod_vec.pop_back();
							if(nod_vec.empty())
								break;	
						}
						else /*(nod_vec.back().t_visit == false)*/{
							nod_vec.back().t_visit = true;
							arr_nod[nod_vec.back().nod_num].t_visit = true;
							put_tmp = arr_nod[nod_vec.back().t_num];
							nod_vec.push_back(put_tmp);
							break;
						}
					}
				}
				else{
					put_tmp = arr_nod[nod_vec.back().f_num];
					nod_vec.push_back(put_tmp);
				}
			}
		}
		//node has no child
		else{
			//write down the trace
			vec_result.push_back(nod_vec);
			//back trace
			nod_vec.pop_back();//pop the end point
			while(true){
				if(nod_vec.back().n_num != -1 || nod_vec.back().t_visit == true){
					nod_vec.pop_back();
					if(nod_vec.empty())
						break;	
				}
				else /*(nod_vec.back().t_visit == false)*/{
					nod_vec.back().t_visit = true;
					arr_nod[nod_vec.back().nod_num].t_visit = true;
					put_tmp = arr_nod[nod_vec.back().t_num];
					nod_vec.push_back(put_tmp);
					break;
				}
			}
		}
	}
	vector<Node> loop_vec;
	cout << "CC=" << vec_result.size() <<endl;
	vector<Node>::iterator out_itr;
	sort(vec_result.begin(), vec_result.end(), cmp);

	for(int i = 0; i < vec_result.size(); i++)
		for(int j = 0; j < vec_result.size() - 1; j++){
			//if(vec_result[j].size() > vec_result[j+1].size())
		//			swap(vec_result[j], vec_result[j+1]);
			if(vec_result[j].size() == vec_result[j + 1].size())
				for(int k = 0; k < vec_result[j].size(); k++)
					if(vec_result[j][k].nod_num > vec_result[j +1][k].nod_num){
						swap(vec_result[j], vec_result[j+1]);
						break;
					}
		}

	int i, j;
	for(i = 0; i < vec_result.size(); i++){
		loop_vec = vec_result[i];
		for(j = 0; j < loop_vec.size() - 1; j++){
			cout << loop_vec[j].nod_num << ",";
		}
		cout << loop_vec[j].nod_num << endl;
		//for(j = 0; j < loop_vec.size() - 1; j++)
		//	cout << loop_vec[j].nod_num << ",";
		//cout << j << endl;
		//cout << loop_vec[j].nod_num << endl;
	}
	
	delete [] arr_nod;
	return 0;
}
