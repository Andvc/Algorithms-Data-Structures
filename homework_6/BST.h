#include <iostream>
#include <algorithm> // 用于 std::max

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height;          ///< 子树的高度

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ theElement }, left{ lt }, right{ rt }, height{ 0 } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ 0 } {}
    };

    BinaryNode *root;

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void insert(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
        balance(t);
    }

    void insert(Comparable &&x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }
        balance(t);
    }

    void remove(const Comparable &x, BinaryNode *& t) {
        if (t == nullptr) return; 

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {
            BinaryNode *minNode = detachMin(t->right);
            t->element = minNode->element;
            delete minNode;
        } else {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    BinaryNode *detachMin(BinaryNode *&t) {
        if (t == nullptr) return nullptr;
        if (t->left != nullptr) {
            return detachMin(t->left);
        } else {
            BinaryNode *minNode = t;
            t = t->right;
            return minNode;
        }
    }

    void balance(BinaryNode *& t) {
        if (t == nullptr) return;

        int leftHeight = (t->left) ? t->left->height : -1;
        int rightHeight = (t->right) ? t->right->height : -1;
        t->height = std::max(leftHeight, rightHeight) + 1;

        int balanceFactor = leftHeight - rightHeight;

        if (balanceFactor > 1) {
            if ((t->left->left ? t->left->left->height : -1) >= (t->left->right ? t->left->right->height : -1)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (balanceFactor < -1) {
            if ((t->right->right ? t->right->right->height : -1) >= (t->right->left ? t->right->left->height : -1)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }
    }

    void rotateWithLeftChild(BinaryNode *& k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max((k2->left ? k2->left->height : -1), (k2->right ? k2->right->height : -1)) + 1;
        k1->height = std::max((k1->left ? k1->left->height : -1), (k2->height)) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *& k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max((k1->left ? k1->left->height : -1), (k1->right ? k1->right->height : -1)) + 1;
        k2->height = std::max((k2->right ? k2->right->height : -1), (k1->height)) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(BinaryNode *& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(BinaryNode *& k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }
};
