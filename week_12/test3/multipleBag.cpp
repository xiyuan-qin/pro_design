#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n_items; 
    int capacity_v; 
    cin >> n_items >> capacity_v;

    vector<long long> dp(capacity_v + 1, 0);

    for (int i = 0; i < n_items; ++i) {
        int w, c, k; 
        cin >> w >> c >> k;

        if (w == 0) {
            continue; 
        }
        
        vector<long long> dp_current_item_iter = dp; 

        for (int remainder = 0; remainder < w; ++remainder) {
            deque<pair<long long, int>> mono_deque;

            for (int q_block_idx = 0; ; ++q_block_idx) {
                long long current_j_capacity = (long long)q_block_idx * w + remainder;
                if (current_j_capacity > capacity_v) {
                    break;
                }

                while (!mono_deque.empty() && mono_deque.front().second < q_block_idx - k) {
                    mono_deque.pop_front();
                }

                if (!mono_deque.empty()) {
                    long long val_from_deque = mono_deque.front().first; 
                    long long new_value_option = val_from_deque + (long long)q_block_idx * c;
                    dp_current_item_iter[current_j_capacity] = max(dp_current_item_iter[current_j_capacity], new_value_option);
                }

                long long value_for_candidate_in_deque = dp[current_j_capacity] - (long long)q_block_idx * c;
                
                while (!mono_deque.empty() && mono_deque.back().first <= value_for_candidate_in_deque) {
                    mono_deque.pop_back();
                }
                mono_deque.push_back({value_for_candidate_in_deque, q_block_idx});
            }
        }
        dp = dp_current_item_iter;
    }

    cout << dp[capacity_v] << endl;

    return 0;
}