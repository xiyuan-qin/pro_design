#include<iostream>
#include<vector>
#include<deque>

namespace test{
    std::vector<int> max;
    std::vector<int> min;
}

int main(){
    int n, k;
    std::cin >> n >> k;
     
    std::vector<int> a(n);
    for(int i = 0; i < n; i++){
        std::cin >> a[i];
    }

    std::deque<int> max_deque, min_deque; // 存储索引
    
    // 处理所有元素
    for(int i = 0; i < n; i++){
        // 移除不在当前窗口的元素
        while(!max_deque.empty() && max_deque.front() <= i - k){
            max_deque.pop_front();
        }
        while(!min_deque.empty() && min_deque.front() <= i - k){
            min_deque.pop_front();
        }
        
        // 维护单调队列：最大值队列从大到小，最小值队列从小到大
        while(!max_deque.empty() && a[i] >= a[max_deque.back()]){
            max_deque.pop_back();
        }
        max_deque.push_back(i);
        
        while(!min_deque.empty() && a[i] <= a[min_deque.back()]){
            min_deque.pop_back();
        }
        min_deque.push_back(i);
        
        // 当处理了至少k个元素后，记录当前窗口的最大值和最小值
        if(i >= k - 1){
            test::max.push_back(a[max_deque.front()]);
            test::min.push_back(a[min_deque.front()]);
        }
    }
    
    // 输出结果
    for(int i = 0; i < test::min.size(); i++){
        std::cout << test::min[i] << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < test::max.size(); i++){
        std::cout << test::max[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
