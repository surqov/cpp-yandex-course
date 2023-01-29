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
    const T* value = &node->value;
    const T* left_value = node->left ? &node->left->value : nullptr;
    const T* right_value = node->right ? &node->right->value : nullptr;
    
    if (left_value && right_value) {
        return (*left_value > *value || *value > *right_value) ? false : 
            CheckTreeProperty(node->left) && CheckTreeProperty(node->right);
    } else if (left_value) {
        return (*left_value > *value) ? false : CheckTreeProperty(node->left);
    } else if (right_value) {
        return (*value > *right_value) ? false : CheckTreeProperty(node->right);
    }
    return true;
}

int main() {
    using T = TreeNode<int>;
    T* root1 = new T{6, 
        new T{4, new T{3}, new T{5}}, new T{7}};
    assert(CheckTreeProperty(root1));
    CheckTreeProperty(root1);
    
    T* root2 = new T{6, 
        new T{4, new T{3}, new T{5}}, new T{7, new T{8}}};
    assert(!CheckTreeProperty(root2));
    CheckTreeProperty(root2);
    
    T* root3 = new T{3, 
        new T{2, new T{1}, new T{12}}, new T{8, new T{12}}};
    assert(!CheckTreeProperty(root3));
    CheckTreeProperty(root3);

    DeleteTree(root1);
    DeleteTree(root2);
}