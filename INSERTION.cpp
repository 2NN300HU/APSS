/*문제

유명한 정렬 알고리즘인 삽입 정렬은 정렬된 부분 배열을 유지하며 이 배열에 새 원소를 삽입해 나가는 식으로 동작합니다.
주어진 정수 배열 A를 정렬하는 삽입 정렬의 구현은 다음과 같습니다.
void insertionSort(vector<int>& A) {
  for(int i = 0; i < A.size(); ++i) {
    // A[0..i-1] 에 A[i] 를 끼워넣는다
    int j = i;
    while(j > 0 && A[j-1] > A[j]) {
      // 불변식 a: A[j+1..i] 의 모든 원소는 A[j] 보다 크다.
      // 불변식 b: A[0..i] 구간은 A[j] 를 제외하면 정렬되어 있다.
      swap(A[j-1], A[j]);
      --j;
    }
  }
}

삽입 정렬은 A[0..i-1] 이 정렬된 배열일 때, A[i] 를 적절한 위치를 만날 때까지 왼쪽으로 한칸씩 움직입니다.
예를 들어 A={5,1,4,3,2} 의 삽입 정렬은 다음과 같이 이루어집니다.

A
비고

5 1 4 3 2
초기 상태

1 5 4 3 2
1을 왼쪽으로 1칸 옮김

1 4 5 3 2
4를 왼쪽으로 1칸 옮김

1 3 4 5 2
3을 왼쪽으로 2칸 옮김

1 2 3 4 5
2를 왼쪽으로 3칸 옮김

1부터 N까지의 자연수가 한 번씩 포함된 길이 N 인 수열 A[] 를 삽입 정렬했습니다.
원래 수열은 알 수 없지만, 그 과정에서 각 원소가 왼쪽으로 몇 칸이나 이동했는지를 알고 있습니다.
예를 들어, 위 예제에서 각 위치에 있는 값들이 움직인 칸수를 표현하면 {0,1,1,2,3}  이 됩니다.
이 때 원래 수열을 찾아내는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C  (1 <= C <= 50) 가 주어집니다.
각 테스트 케이스의 첫 줄에는 원 배열의 길이 N  (1 <= N <= 50000) 이 주어집니다.
그 다음 줄에 N 개의 정수로 A의 각 위치에 있던 값들이 움직인 칸수가 주어집니다.
A 는 1부터 N 까지의 정수를 한 번씩 포함합니다.
입력의 양이 많으므로 가능한 빠른 입력 함수를 사용하는 것이 좋습니다.

출력

각 테스트 케이스마다 재구성한 A[] 를 한 줄에 출력합니다.

예제 입력
2
5
0 1 1 2 3
4
0 1 2 3

예제 출력
5 1 4 3 2
4 3 2 1
*/

#include <iostream>
#include <random>
#include <utility>

using namespace std;

typedef int KeyType;

struct Node {
    KeyType key;
    int priority, size;
    Node *left, *right;

    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

    void setLeft(Node* newLeft) {
        left = newLeft;
        calcSize();
    }
    void setRight(Node* newRight) {
        right = newRight;
        calcSize();
    }
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, KeyType key) {
    if (!root) return NodePair(NULL, NULL);
    if (root->key > key) {
        NodePair res = split(root->left, key);
        root->setLeft(res.second);
        return NodePair(res.first, root);
    }
    NodePair res = split(root->right, key);
    root->setRight(res.first);
    return NodePair(root, res.second);
}

Node* insert(Node* root, Node* node) {
    if (!root) return node;
    if (node->priority > root->priority) {
        NodePair res = split(root, node->key);
        node->setRight(res.second);
        node->setLeft(res.first);
        return node;
    } else if (root->key > node->key) {
        root->setLeft(insert(root->left, node));
    } else {
        root->setRight(insert(root->right, node));
    }
    return root;
}

Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->priority > b->priority) {
        a->setRight(merge(a->right, b));
        return a;
    }
    b->setLeft(merge(a, b->left));
    return b;
}

Node* erase(Node* root, KeyType key) {
    if (!root) return root;
    if (root->key == key) {
        Node* res = merge(root->left, root->right);
        delete root;
        return res;
    }
    if (root->key < key) {
        root->setRight(erase(root->right, key));
    } else {
        root->setLeft(erase(root->left, key));
    }
    return root;
}

Node* kth(Node* root, int k) {
    int leftSize = 0;
    if (root->left) leftSize = root->left->size;
    if (leftSize + 1 == k) return root;
    if (leftSize >= k) return kth(root->left, k);
    return kth(root->right, k - leftSize - 1);
}

int n;

void insertion(int* arr) {
    auto res = new int[n];
    auto root = new Node(1);
    for (int i = 2; i < n+1; ++i) {
        root = insert(root, new Node(i));
    }
    for (int i = n - 1; i >= 0; --i) {
        auto temp = kth(root, i + 1 - arr[i])->key;
        res[i] = temp;
        root = erase(root, temp);
    }
    for (int i = 0; i < n; ++i) {
        cout << res[i] << ' ';
    }
    cout << endl;
    delete[] res;
}

int main() {
    int cases;
    cin >> cases;
    for (int c = 0; c < cases; ++c) {
        cin >> n;
        auto arr = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        insertion(arr);
        delete arr;
    }
    return 0;
}   