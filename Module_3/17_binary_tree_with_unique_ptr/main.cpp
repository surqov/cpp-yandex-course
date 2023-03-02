#include <cassert>
#include <iostream>
#include <memory>

using namespace std::literals;

template <typename T>
struct TreeNode;

template <typename T>
using TreeNodePtr = std::unique_ptr<TreeNode<T>>;

template <typename T>
struct TreeNode { 
    // Используйте TreeNodePtr<T> вместо сырых указателей
    // Примите умные указатели по rvalue-ссылке
    TreeNode(T val, TreeNodePtr<T>&& left, TreeNodePtr<T>&& right)
        : value(std::move(val))
        , left(std::move(left)) 
        , right(std::move(right)) {
    }
 
    T value;
    TreeNodePtr<T> left;  // Замените TreeNode* на TreeNodePtr<T>
    TreeNodePtr<T> right; // Замените TreeNode* на TreeNodePtr<T>
    TreeNode* parent = nullptr;
};

template <typename T>
bool CheckTreeProperty(const TreeNodePtr<T>& node, const T* min, const T* max) {
    if (node == nullptr) return true;
    const T value = node.get()->value;
    if ((min && value <= *min) || (max && value >= *max)) {
        return false;
    }
    return CheckTreeProperty(node.get()->left, min, &value) && CheckTreeProperty(node.get()->right, &value, max);
}

template <typename T>
bool CheckTreeProperty(const TreeNodePtr<T>& node) {
    return CheckTreeProperty<T>(node, nullptr, nullptr);
}

template <typename T>
bool CheckTreeProperty(const T* node) {
    return CheckTreeProperty(std::make_unique<TreeNode>(node, nullptr, nullptr));
}

TreeNodePtr<int> N(int val, TreeNodePtr<int>&& left = {}, TreeNodePtr<int>&& right = {}) {
    auto res = std::make_unique<TreeNode<int>>(val, std::move(left), std::move(right));
    if (left) {
        left->parent = res.get();
    }
    if (right) {
        right->parent = res.get();
    }

    return res;
}

template <class T>
TreeNodePtr<T> begin(TreeNodePtr<T> node) noexcept {
    return node->left ? begin(node->left) : node;
}

template <class T>
TreeNodePtr<T> next(TreeNodePtr<T> node) {
    if (node->right) {
        return begin(node->right);
    } else if (node->parent && node->parent->value > node->value) {
        return node->parent;
    } 
    TreeNodePtr<T> bigger_ = std::make_unique<T>(node);
    while (bigger_->parent) {
        bigger_ = bigger_->parent;
        if (bigger_->value > node->value) {
            return bigger_;
        }
    }
    return nullptr;    
}

int main() {
    using namespace std;
    using T = TreeNode<int>;
    auto root1 = N(6, N(4, N(3), N(5)), N(7));
    assert(CheckTreeProperty(root1));
    //assert(CheckTreeProperty(root1.get()));

    auto root2 = N(6, 
        N(4, 
        N(3), N(5) ), 
            N(7, N(8)));
    assert(!CheckTreeProperty(root2));
    //assert(!CheckTreeProperty(root2.get()));

    // Функция DeleteTree не нужна. Узлы дерева будут рекурсивно удалены
    // благодаря деструкторам unique_ptr
}