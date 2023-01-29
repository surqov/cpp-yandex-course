#include <cassert>
#include <iostream>

template <typename T>
struct TreeNode {
    T value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

template <typename T>
void DeleteTree(TreeNode<T>* node) {
    if (!node) {
        return;
    }
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node) {
    T value = node->value;
    if (node->left && node ->right) {
        T left_value = node->left->value;
        T right_value = node->right->value;
        
        if ((left_value > value) || (value > right_value)) {
            return false;
        }
        
        return CheckTreeProperty(node->left) && CheckTreeProperty(node->right);
    } else if (node->left) {
        T left_value = node->left->value;
        if (left_value > value) {
            return false;
        }
        return CheckTreeProperty(node->left);
    } else if (node->right) {
        T right_value = node->right->value;
        if (value > right_value) {
            return false;
        }
        return CheckTreeProperty(node->right);
    }
    return true;
}

int main() {
    using T = TreeNode<int>;
    T* root1 = new T{6, 
        new T{4, new T{3}, new T{5}}, new T{7}};
    assert(CheckTreeProperty(root1));

    T* root2 = new T{6, 
        new T{4, new T{3}, new T{5}}, new T{7, new T{8}}};
    assert(!CheckTreeProperty(root2));

    DeleteTree(root1);
    DeleteTree(root2);
}