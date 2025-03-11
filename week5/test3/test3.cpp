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

    // 最小值
    std::deque<int> min_deque;
    // 最大值
    std::deque<int> max_deque;

    for(int i = 0; i < k; i++){
        // 维护最小值的单调递增队列
        while(!min_deque.empty() && a[i] < a[min_deque.back()]){
            min_deque.pop_back();
        }
        min_deque.push_back(i);

        // 维护最大值的单调递减队列
        while(!max_deque.empty() && a[i] > a[max_deque.back()]){
            max_deque.pop_back();
        }
        max_deque.push_back(i);
    }

    // 保存第一个窗口的结果
    test::min.push_back(a[min_deque.front()]);
    test::max.push_back(a[max_deque.front()]);

    // 处理剩余窗口
    for(int i = k; i < n; i++){
        // 移除不在当前窗口的元素
        if(!min_deque.empty() && min_deque.front() <= i - k){
            min_deque.pop_front();
        }
        if(!max_deque.empty() && max_deque.front() <= i - k){
            max_deque.pop_front();
        }

        // 维护最小值的单调递增队列
        while(!min_deque.empty() && a[i] < a[min_deque.back()]){
            min_deque.pop_back();
        }
        min_deque.push_back(i);

        // 维护最大值的单调递减队列
        while(!max_deque.empty() && a[i] > a[max_deque.back()]){
            max_deque.pop_back();
        }
        max_deque.push_back(i);

        // 保存当前窗口的结果
        test::min.push_back(a[min_deque.front()]);
        test::max.push_back(a[max_deque.front()]);
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

