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

int countLessThan(Node* root, KeyType key) {
    if (!root) return 0;
    if (root->key >= key) return countLessThan(root->left, key);
    int res = !root->left ? 0 : root->left->size;
    return res + 1 + countLessThan(root->right, key);
}
