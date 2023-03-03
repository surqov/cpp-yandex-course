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
    TreeNode(const TreeNode<T>& other) = default;

    // Используйте TreeNodePtr<T> вместо сырых указателей
    // Примите умные указатели по rvalue-ссылке
    TreeNode(T val, TreeNodePtr<T>&& left, TreeNodePtr<T>&& right)
        : value(val)
        , left(std::move(left))
        , right(std::move(right)) {
    }
 
    T value;
    TreeNodePtr<T> left;  // Замените TreeNode* на TreeNodePtr<T>
    TreeNodePtr<T> right; // Замените TreeNode* на TreeNodePtr<T>
    TreeNode* parent = nullptr;
};

template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node, const T* min, const T* max) {
    if (node == nullptr) return true;
    const T value = node->value;
    if ((min && value <= *min) || (max && value >= *max)) {
        return false;
    }
    return CheckTreeProperty(node->left.get(), min, &value) && CheckTreeProperty(node->right.get(), &value, max);
}

template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node) noexcept {
    return CheckTreeProperty<T>(node, nullptr, nullptr);
}

TreeNodePtr<int> N(int val, TreeNodePtr<int>&& left = {}, TreeNodePtr<int>&& right = {}) {
    bool left_ = left != nullptr;
    bool right_ = right != nullptr;
    auto res = std::make_unique<TreeNode<int>>(val, std::move(left), std::move(right));
    if (left_) {
        res->left->parent = res.get();
    }
    if (right_) {
        res->right->parent = res.get();
    }

    return res;
}

template <class T>
TreeNode<T>* begin(TreeNode<T>* node) noexcept {
    return node->left ? begin(node->left.get()) : node;
}

template <class T>
TreeNode<T>* next(TreeNode<T>* node) {
    if (node->right) {
        return begin(node->right.get());
    } else if (node->parent && node->parent->value > node->value) {
        return node->parent;
    } 
    TreeNode<T>* bigger_ = node;
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
    assert(CheckTreeProperty(root1.get()));

    T* iter = begin(root1.get());
    while (iter) {
        std::cout << iter->value << " "s;
        iter = next(iter);
    }
    std::cout << endl;

    auto root2 = N(6, N(4, N(3), N(5)), N(7, N(8)));
    assert(!CheckTreeProperty(root2.get()));
}