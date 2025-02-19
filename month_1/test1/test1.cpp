#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 判断牌型的函数
int determineHandType(vector<pair<int, int>>& hand) {
    // 提取大小和花色
    vector<int> ranks;
    vector<int> suits;
    for (auto& card : hand) {
        ranks.push_back(card.first);
        suits.push_back(card.second);
    }

    // 统计大小和花色的频率
    map<int, int> rankCount;
    map<int, int> suitCount;
    for (int rank : ranks) rankCount[rank]++;
    for (int suit : suits) suitCount[suit]++;

    bool isFlush = suitCount.size() == 1;
    bool isStraight = false;

    // 检查是否是顺子
    sort(ranks.begin(), ranks.end());
    bool isConsecutive = true;
    for (size_t i = 1; i < ranks.size(); ++i) {
        if (ranks[i] != ranks[i-1] + 1) {
            isConsecutive = false;
            break;
        }
    }
    isStraight = isConsecutive;

    // 检查是否是同花顺
    if (isFlush && isStraight) return 1;

    // 检查是否是炸弹
    for (auto& rc : rankCount) {
        if (rc.second == 4) return 2;
    }

    // 检查是否是三带二
    bool hasThree = false, hasTwo = false;
    for (auto& rc : rankCount) {
        if (rc.second == 3) hasThree = true;
        if (rc.second == 2) hasTwo = true;
    }
    if (hasThree && hasTwo) return 3;

    // 检查是否是同花
    if (isFlush) return 4;

    // 检查是否是顺子
    if (isStraight) return 5;

    // 检查是否是三条
    if (hasThree) return 6;

    // 检查是否是两对
    int pairCount = 0;
    for (auto& rc : rankCount) {
        if (rc.second == 2) pairCount++;
    }
    if (pairCount == 2) return 7;

    // 检查是否是一对
    if (pairCount == 1) return 8;

    // 否则是要不起
    return 9;
}

int main() {
    int A, B;
    cin >> A >> B;

    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    // 剩余的牌
    vector<pair<int, int>> remainingCards;
    for (int a = 0; a < A; ++a) {
        for (int b = 0; b < B; ++b) {
            if (!(a == a1 && b == b1) && !(a == a2 && b == b2)) {
                remainingCards.push_back({a, b});
            }
        }
    }

    // 初始化牌型计数
    vector<int> count(10, 0);

    // 遍历所有可能的3张牌的组合
    for (size_t i = 0; i < remainingCards.size(); ++i) {
        for (size_t j = i + 1; j < remainingCards.size(); ++j) {
            for (size_t k = j + 1; k < remainingCards.size(); ++k) {
                vector<pair<int, int>> hand = {{a1, b1}, {a2, b2}, remainingCards[i], remainingCards[j], remainingCards[k]};
                int type = determineHandType(hand);
                count[type]++;
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= 9; ++i) {
        cout << count[i] << " ";
    }
    cout << endl;

    return 0;
}