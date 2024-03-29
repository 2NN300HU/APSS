/*문제

중세의 성과 요새들은 보안을 튼튼히 하면서도 더 넓은 영역을 보호하기 위해 여러 개의 성벽을 갖고 있었다고 하지요.
전세계에서 가장 편집증이 심한 영주가 지은 스트로고(Strawgoh) 요새는 이의 극치를 보여줍니다.
이 요새는 그림과 같이 커다란 원형 외벽 내에 여러 개의 원형 성벽이 겹겹이 지어진 형태로 구성되어 있는데, 어떤 성벽에도 문이 없어서 성벽을 지나가려면 사다리를 타고 성벽을 오르내려야 합니다.
요새 내에서도 한 곳에서 다른 곳으로 이동하는 데 시간이 너무 오래 걸린다는 원성이 자자해지자, 영주는 요새 내에서 왕래가 불편한 곳들을 연결하는 터널을 만들기로 했습니다.
계획을 세우기 위해 요새 내에서 서로 왕래하기 위해 가장 성벽을 많이 넘어야 하는 두 지점을 찾으려고 합니다.
예를 들어 위 그림의 경우, 별표로 표시된 두 지점 간을 이동하기 위해서는 다섯 번이나 성벽을 넘어야 하지요.
성벽들의 정보가 주어질 때 가장 성벽을 많이 넘어야 하는 두 지점 간을 이동하기 위해 몇 번이나 성벽을 넘어야 하는지 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 100) 가 주어집니다.
각 테스트 케이스의 첫 줄에는 성벽의 수 N (1 <= N <= 100) 이 주어집니다.
그 후 N 줄에는 각 3개의 정수로 각 성벽의 위치와 크기에 대한 정보 xi , yi , ri 가 주어집니다.
(0 <= xi, yi <= 1000,1 <= ri <= 1000,0 <= i<N) 이 때 i 번 성벽은 (xi, yi) 를 중심으로 하는 반지름 ri 인 원형으로 설치되어 있습니다.
편의상 모든 성벽의 두께는 0이라고 가정하며, 입력에 주어지는 성벽들은 서로 겹치거나 닿지 않습니다.
입력에 주어지는 첫 번째 성벽은 외벽이며, 외벽은 입력에 주어지는 모든 다른 성벽을 포함합니다.

출력

각 테스트 케이스마다 한 줄에 두 지점 간 이동을 위해 최대 몇 번이나 성벽을 넘어야 하는지를 출력하세요.

예제 입력
2
3
5 5 15
5 5 10
5 5 5
8 
21 15 20 
15 15 10 
13 12 5 
12 12 3 
19 19 2 
30 24 5 
32 10 7 
32 9 4

예제 출력
2
5
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int maxCount;

class Tree {
   private:
    bool isChild(Tree tree) {
        return (this->x - tree.x) * (this->x - tree.x) + (this->y - tree.y) * (this->y - tree.y) < this->r * this->r;
    }

   public:
    int x;
    int y;
    int r;
    vector<Tree> child;

    Tree(int x, int y, int r) {
        this->x = x;
        this->y = y;
        this->r = r;
    }

    void append(Tree tree) {
        vector<Tree>& child = this->child;
        for (int i = 0; i < child.size(); ++i) {
            if (child[i].isChild(tree)) {
                child[i].append(tree);
                return;
            } else if (tree.isChild(child[i])) {
                tree.append(child[i]);
                child.erase(child.begin() + i);
                return;
            }
        }
        this->child.push_back(tree);
    }
};

int fortress(Tree tree) {
    if (tree.child.empty()) {
        return 1;
    }
    int first = 0, second = 0;
    for (int i = 0; i < tree.child.size(); i++) {
        int temp = fortress(tree.child[i]);
        if (temp > second) {
            second = temp;
        }
        if (second > first) {
            temp = first;
            first = second;
            second = temp;
        }
    }
    maxCount = max(maxCount, first + second);
    return ++first;
}

int main() {
    int cases, n, x, y, r;
    cin >> cases;
    for (int c = 0; c < cases; c++) {
        maxCount = 0;
        cin >> n;
        cin >> x >> y >> r;
        Tree root(x, y, r);
        for (int i = 1; i < n; ++i) {
            cin >> x >> y >> r;
            root.append(Tree(x, y, r));
        }
        fortress(root);
        cout << maxCount << endl;
    }
    return 0;
}