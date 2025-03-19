#include<iostream>
#include<deque>
#include<string>
using namespace std;
 
typedef long long ll;
class win {
public:
	win(int t) { this->u = t; this->lxcishu = 0; }//新建留言
	int u;//喜好度
	ll lxcishu;//留言次数
	bool up = 0;//判断当前窗口是否置顶
};

deque<win> windows;//所有窗口
deque<win> temp;//缓冲区
bool ADD(int u) {//add u操作 打开一个喜爱度为u的新窗口
	for (auto it = windows.begin(); it != windows.end(); it++) {//查看一下有没有好感度为u的
		if ((*it).u == u) {
			return 0;
		}
	}
	win New_win(u);
	windows.push_back(New_win);//尾插入新的窗口
	return 1;
}

void CLOSE(int u) {
	bool flag = 0;
	ll lxcishu;
	for (auto i = windows.begin(); i != windows.end(); i++) {//查看一下有没有好感度为u的
		if ((*i).u == u) {
			flag = 1;
			lxcishu = (*i).lxcishu;
			break;
		}
	}
	if (flag == 0) { cout << "invalid likeness."<<endl; return; }//如果没找到

	auto it = windows.begin();
	while ((*it).u!=u) {//把目标之前的都弹出，并存起来
		temp.push_front(*it);
		windows.pop_front();
		it = windows.begin();
	}
	windows.pop_front();//删除目标
	if (temp.empty()) {//如果要删的是第一个
		cout << "close " << u << " with " << lxcishu << "." << endl;
		return;
	}
	
	while(!temp.empty()){//把原先的再重新放回去
		auto iit = temp.begin();
		windows.push_front(*iit);
		temp.pop_front();
	}
	cout << "close " << u << " with " << lxcishu << "." << endl;
}

void Chat(ll w) {
	if (windows.empty()) {
		cout << "empty." << endl; return;
	}
		for (auto it = windows.begin(); it != windows.end(); it++) {
			if ((*it).up == 1) {
				(*it).lxcishu += w;
				cout << "success." << endl;
				return;
			}
		}
	windows.front().lxcishu += w;
	cout << "success." << endl;
}

void Rotate(int x) {
	if (x > windows.size() || x < 1) {
		cout << "out of range." << endl;
		return;
	}
	for (int i = 0; i < x; i++) {//把第x以及之前的都弹出，并存起来
		auto it = windows.begin();
		temp.push_front(*it);
		windows.pop_front();
	}
	win new_top = *(temp.begin());
	temp.pop_front();//把要新放入队首的拿出来
	for (int i = 1; i < x; i++) {//把原先的再重新放回去
		auto iit = temp.begin();
		windows.push_front(*iit);
		temp.pop_front();
	}
	windows.push_front(new_top);
	cout << "success." << endl;
}

void Prior() {
	if (windows.empty()) {
		cout << "empty." << endl;
		return;
	}
	ll Max_love = 0;
	for (auto it = windows.begin(); it != windows.end(); it++) {
		if ((*it).u > Max_love)Max_love = (*it).u;
	}
	auto it = windows.begin();
	while (!windows.empty()&&(*it).u<Max_love) {//把第Max_love之前的都弹出，并存起来
		temp.push_front(*it);
		windows.pop_front();
		it = windows.begin();
	}
	temp.push_front(*it);
	windows.pop_front();
	win new_top = *(temp.begin());
	temp.pop_front();//把要新放入队首的拿出来
	while(!temp.empty()) {//把原先的再重新放回去
		auto iit = temp.begin();
		windows.push_front(*iit);
		temp.pop_front();
	}
	windows.push_front(new_top);
	cout << "success." << endl;
}

void Choose(int u) {
	bool flag = 0;
	
	for (auto it = windows.begin(); it != windows.end(); it++) {//查看一下有没有好感度为u的
		if ((*it).u == u) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) { cout << "invalid likeness."<<endl; return; }//如果没找到

	auto it = windows.begin();
	while((*it).u!=u) {//把好感u之前的都弹出，并存起来
		temp.push_front(*it);
		windows.pop_front();
		it = windows.begin();
	}
	temp.push_front(*it);
	windows.pop_front();
	it = windows.begin();
	if (temp.empty()) { cout << "success." << endl; return; }//如果一开始就是队首
	win new_top = *(temp.begin());
	temp.pop_front();//把要新放入队首的拿出来
	while(!temp.empty()) {//把原先的再重新放回去
		auto iit = temp.begin();
		windows.push_front(*iit);
		temp.pop_front();
	}
	windows.push_front(new_top);
	cout << "success." << endl;
}

void Top(int u) {
	bool flag = 0;
	for (auto it = windows.begin(); it != windows.end(); it++) {//查看一下有没有好感度为u的
		if ((*it).u == u) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) { cout << "invalid likeness."<<endl; return; }//如果没找到
	for (auto it = windows.begin(); it != windows.end(); it++) {//将好感度为u的置顶，并且把之前置顶的删了
		if ((*it).u != u && (*it).up == 1) { (*it).up = 0; }
		if ((*it).u == u) {
			(*it).up = 1;//标记置顶
		}
	}
	cout << "success." << endl;
}

void Untop() {
	bool flag = 0;
	for (auto it = windows.begin(); it != windows.end(); it++) {//查看一下有没有置顶的
		if ((*it).up == 1) {
			flag = 1;
			(*it).up = 0;
		}
	}
	if (flag == 0) { cout << "no such person." << endl; return; }//如果没找到
	cout << "success." << endl;
}

void Bye(int j) {

		//如果有置顶的
		for (auto it = windows.begin(); it != windows.end(); it++) {
			if ((*it).up == 1)
			{
				if ((*it).lxcishu != 0) {
					cout << "OpId #" << j << ": ";
					j++;
					cout << "Bye " << (*it).u << ": " << (*it).lxcishu << "." << endl;
				}
					
				break;
			}
		}
	
	while (!windows.empty()) {
		
		auto it = windows.begin();
		if ((*it).up != 1 && (*it).lxcishu != 0) {//聊过天但没有置顶的同学
			cout << "OpId #" << j << ": ";
			j++;
			cout << "Bye " << (*it).u << ": " << (*it).lxcishu << "." << endl;
		}
		windows.pop_front();
	}
}


int main() {
	//FILE* s1;
	//freopen_s(&s1, "input_1.txt", "r", stdin);
	//freopen_s(&s1, "out_1.txt", "w", stdout);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int n;
		cin >> n;
		int j = 1;
		for (; j <= n; j++) {//n+1次操作，最后一次操作为bye
			string op;
			cin >> op;
			//Add操作
			if (op == "Add") {//Add u操作
				int num;
				cin >> num;
				if (ADD(num) == 1)cout << "OpId #" << j << ": success." << endl;
				else cout << "OpId #" << j << ": same likeness." << endl;
			}
			//Close操作
			else if (op == "Close") {
				int u;
				cin >> u;
				cout << "OpId #" << j << ": ";
				CLOSE(u);
			}
			//Chat操作
			else if (op == "Chat") {
				ll w;
				cin >> w;
				cout << "OpId #" << j << ": ";
				Chat(w);
			}
			//Rotate操作
			else if (op == "Rotate") {
				int x;
				cin >> x;
				cout << "OpId #" << j << ": ";
				Rotate(x);
			}
			//Piror操作
			else if (op == "Prior") {
				cout << "OpId #" << j << ": ";
				Prior();
			}
			//Choose操作
			else if (op == "Choose") {
				int u;
				cin >> u;
				cout << "OpId #" << j << ": ";
				Choose(u);
			}
			//Top操作
			else if (op == "Top") {
				int u;
				cin >> u;
				cout << "OpId #" << j << ": ";
				Top(u);
			}
			//Untop操作
			else if (op == "Untop") {
				cout << "OpId #" << j << ": ";
				Untop();
			}
		}
		//bye操作
		
		Bye(j);
		windows.clear();//清空
		temp.clear();
	}
}

