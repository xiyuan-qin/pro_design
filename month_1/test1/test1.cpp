#include <iostream>
#include <algorithm>

using namespace std;


struct Card {
    int rank;// 牌面
    int suit;// 花色
};

Card remainingCards[10000];// 剩余牌
int count[10] = {0};

// 判断牌型的函数
int determineHandType(int ranks[], int suits[]) {
    // 是否是同花
    bool isFlush = true;
    int firstSuit = suits[0];
    for (int i = 1; i < 5; ++i) {
        if (suits[i] != firstSuit) {//如果跟第一个花色不一样
            isFlush = false;
            break;
        }
    }

    // 是否是顺子
    int sortedRanks[5];
    for (int i = 0; i < 5; ++i) sortedRanks[i] = ranks[i];
    sort(sortedRanks, sortedRanks + 5);// 先排序
    
    bool isStraight = true;
    for (int i = 1; i < 5; ++i) {
        if (sortedRanks[i] != sortedRanks[i-1] + 1) {
            isStraight = false;
            break;
        }
    }

    // 统计牌型
    bool checked[5] = {false};
    int four = 0, three = 0, two = 0;// 分别表示四张、三张、两张的相同牌的数量
    for (int i = 0; i < 5; ++i) {// 对于每一张牌都要分别统计是否有符合的牌型
        if (checked[i]) continue;// 如果已经统计过某张牌，就跳过
        int cnt = 1;//保底高牌
        for (int j = i+1; j < 5; ++j) {//从这一张牌的下一张开始统计
            if (sortedRanks[j] == sortedRanks[i]) {
                cnt++;
                checked[j] = true;
            }
        }
        if (cnt == 4) four++;
        else if (cnt == 3) three++;
        else if (cnt == 2) two++;
    }

    // 判断牌型
    if (isFlush && isStraight) return 1;//同花顺
    if (four) return 2;//四条
    if (three && two) return 3;//葫芦
    if (isFlush) return 4;//同花
    if (isStraight) return 5;//顺子
    if (three) return 6;//三条
    if (two >= 2) return 7;//两对
    if (two) return 8;//一对
    return 9;//高牌
}

int main() {
    int A, B;
    cin >> A >> B;

    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    // 生成剩余牌
    int remainingCount = 0;
    for (int a = 0; a < A; ++a) {
        for (int b = 0; b < B; ++b) {
            if (!(a == a1 && b == b1) && !(a == a2 && b == b2)) {//如果不是已经发出去的牌
                remainingCards[remainingCount].rank = a;
                remainingCards[remainingCount].suit = b;
                remainingCount++;
            }
        }
    }

    // 遍历所有三张牌组合
    for (int i = 0; i < remainingCount; ++i) {
        for (int j = i+1; j < remainingCount; ++j) {
            for (int k = j+1; k < remainingCount; ++k) {
                int /*排面*/ranks[5] = {a1, a2, remainingCards[i].rank, remainingCards[j].rank, remainingCards[k].rank};
                int /*花色*/suits[5] = {b1, b2, remainingCards[i].suit, remainingCards[j].suit, remainingCards[k].suit};
                int type = determineHandType(ranks, suits);
                ::count[type]++;
            }
        }
    }

    // 输出结果
    for (int i = 1; i <= 9; ++i) {
        cout << ::count[i] << " ";
    }
    cout << endl;

    return 0;
}
