#ifndef __MAP_H__
#define __MAP_H__

#include "pair.h"
#include <functional>
#include <memory>
#include <queue>
#include <stdexcept>

namespace MyStl {
    template<class _TpX, class _TpY>
    class map {
        using Key = _TpX;
        using Value = _TpY;
        using Pair = MyStl::pair<_TpX, _TpY>;
        using compare = std::function<bool(const Key&, const Key&)>;

    protected:
        /* Data Structure Declaration */        
        enum class _Color { RED, BLACK };

        struct _TreeNode {
            Pair data;
            _TreeNode* parent;
            _TreeNode* left;
            _TreeNode* right;
            _Color color;
            _TreeNode(const Pair& data, _TreeNode* nil = nullptr) : 
                data(data), parent(nil), left(nil), 
                right(nil), color(_Color::RED) {}
        };

        class _RedBlackTree {
        public:
            _TreeNode* root;
            _TreeNode* NIL; // 哨兵节点
            compare cmp;
            
            _RedBlackTree() : cmp(std::less<Key>()) {
                NIL = new _TreeNode(Pair(), NIL);
                NIL->color = _Color::BLACK;
                root = NIL;
            }

            _RedBlackTree(const compare& cmp) : cmp(cmp) {
                NIL = new _TreeNode(Pair(), NIL);
                NIL->color = _Color::BLACK;
                root = NIL;
            }

            ~_RedBlackTree() {
                destroyTree(root);
                delete NIL;
            }

            template<typename Func>
            void inorder(_TreeNode* node, Func func) const {
                if (node == NIL) return;
                inorder(node->left, func);
                func(node->data);
                inorder(node->right, func);
            }

            void insert(const Pair& data) {
                _TreeNode* newNode = new _TreeNode(data, NIL);

                _TreeNode* y = NIL;
                _TreeNode* x = root;

                while (x != NIL) {
                    y = x;
                    if (cmp(newNode->data.first, x->data.first)) {
                        x = x->left;
                    } else if (cmp(x->data.first, newNode->data.first)) {
                        x = x->right;
                    } else {
                        // 更新值
                        x->data.second = newNode->data.second;
                        delete newNode;
                        return;
                    }
                }

                newNode->parent = y;
                if (y == NIL) {
                    root = newNode;
                } else if (cmp(newNode->data.first, y->data.first)) {
                    y->left = newNode;
                } else {
                    y->right = newNode;
                }

                newNode->color = _Color::RED;
                insertFixup(newNode);
            }

            void deleteNode(const Key& key) {
                _TreeNode* node = findNode(root, key);
                if (node != NIL) {
                    deleteNodeHelper(node);
                }
            }

            _TreeNode* findNode(_TreeNode* node, const Key& key) const {
                while (node != NIL) {
                    if (cmp(key, node->data.first)) {
                        node = node->left;
                    } else if (cmp(node->data.first, key)) {
                        node = node->right;
                    } else {
                        return node;
                    }
                }
                return NIL;
            }

            void destroyTree(_TreeNode* node) {
                if (node == NIL) return;
                destroyTree(node->left);
                destroyTree(node->right);
                delete node;
            }

            void insertFixup(_TreeNode* node) {
                while (node->parent->color == _Color::RED) {
                    if (node->parent == node->parent->parent->left) {
                        _TreeNode* uncle = node->parent->parent->right;
                        if (uncle->color == _Color::RED) {
                            // Case 1
                            node->parent->color = _Color::BLACK;
                            uncle->color = _Color::BLACK;
                            node->parent->parent->color = _Color::RED;
                            node = node->parent->parent;
                        } else {
                            if (node == node->parent->right) {
                                // Case 2
                                node = node->parent;
                                rotateLeft(node);
                            }
                            // Case 3
                            node->parent->color = _Color::BLACK;
                            node->parent->parent->color = _Color::RED;
                            rotateRight(node->parent->parent);
                        }
                    } else {
                        // 对称情况
                        _TreeNode* uncle = node->parent->parent->left;
                        if (uncle->color == _Color::RED) {
                            // Case 1
                            node->parent->color = _Color::BLACK;
                            uncle->color = _Color::BLACK;
                            node->parent->parent->color = _Color::RED;
                            node = node->parent->parent;
                        } else {
                            if (node == node->parent->left) {
                                // Case 2
                                node = node->parent;
                                rotateRight(node);
                            }
                            // Case 3
                            node->parent->color = _Color::BLACK;
                            node->parent->parent->color = _Color::RED;
                            rotateLeft(node->parent->parent);
                        }
                    }
                }
                root->color = _Color::BLACK;
            }

            void rotateLeft(_TreeNode* x) {
                _TreeNode* y = x->right;
                x->right = y->left;
                if (y->left != NIL) {
                    y->left->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == NIL) {
                    root = y;
                } else if (x == x->parent->left) {
                    x->parent->left = y;
                } else {
                    x->parent->right = y;
                }
                y->left = x;
                x->parent = y;
            }

            void rotateRight(_TreeNode* x) {
                _TreeNode* y = x->left;
                x->left = y->right;
                if (y->right != NIL) {
                    y->right->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == NIL) {
                    root = y;
                } else if (x == x->parent->right) {
                    x->parent->right = y;
                } else {
                    x->parent->left = y;
                }
                y->right = x;
                x->parent = y;
            }

            void deleteNodeHelper(_TreeNode* z) {
                _TreeNode* y = z;
                _TreeNode* x;
                _Color yOriginalColor = y->color;

                if (z->left == NIL) {
                    x = z->right;
                    transplant(z, z->right);
                } else if (z->right == NIL) {
                    x = z->left;
                    transplant(z, z->left);
                } else {
                    y = minimum(z->right);
                    yOriginalColor = y->color;
                    x = y->right;
                    if (y->parent == z) {
                        x->parent = y;
                    } else {
                        transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }
                delete z;
                if (yOriginalColor == _Color::BLACK) {
                    deleteFixup(x);
                }
            }

            void deleteFixup(_TreeNode* x) {
                while (x != root && x->color == _Color::BLACK) {
                    if (x == x->parent->left) {
                        _TreeNode* w = x->parent->right;
                        if (w->color == _Color::RED) {
                            w->color = _Color::BLACK;
                            x->parent->color = _Color::RED;
                            rotateLeft(x->parent);
                            w = x->parent->right;
                        }
                        if (w->left->color == _Color::BLACK && w->right->color == _Color::BLACK) {
                            w->color = _Color::RED;
                            x = x->parent;
                        } else {
                            if (w->right->color == _Color::BLACK) {
                                w->left->color = _Color::BLACK;
                                w->color = _Color::RED;
                                rotateRight(w);
                                w = x->parent->right;
                            }
                            w->color = x->parent->color;
                            x->parent->color = _Color::BLACK;
                            w->right->color = _Color::BLACK;
                            rotateLeft(x->parent);
                            x = root;
                        }
                    } else {
                        // 对称情况
                        _TreeNode* w = x->parent->left;
                        if (w->color == _Color::RED) {
                            w->color = _Color::BLACK;
                            x->parent->color = _Color::RED;
                            rotateRight(x->parent);
                            w = x->parent->left;
                        }
                        if (w->right->color == _Color::BLACK && w->left->color == _Color::BLACK) {
                            w->color = _Color::RED;
                            x = x->parent;
                        } else {
                            if (w->left->color == _Color::BLACK) {
                                w->right->color = _Color::BLACK;
                                w->color = _Color::RED;
                                rotateLeft(w);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            x->parent->color = _Color::BLACK;
                            w->left->color = _Color::BLACK;
                            rotateRight(x->parent);
                            x = root;
                        }
                    }
                }
                x->color = _Color::BLACK;
            }

            void transplant(_TreeNode* u, _TreeNode* v) {
                if (u->parent == NIL) {
                    root = v;
                } else if (u == u->parent->left) {
                    u->parent->left = v;
                } else {
                    u->parent->right = v;
                }
                v->parent = u->parent;
            }

            _TreeNode* minimum(_TreeNode* node) const {
                while (node->left != NIL) {
                    node = node->left;
                }
                return node;
            }

            // 深拷贝红黑树
            _TreeNode* cloneTree(_TreeNode* node, _TreeNode* parent, _TreeNode* otherNIL) {
                if (node == otherNIL) {
                    return NIL; // 返回当前树的 NIL 节点
                }
                _TreeNode* newNode = new _TreeNode(node->data);
                newNode->color = node->color;
                newNode->parent = parent;
                newNode->left = cloneTree(node->left, newNode, otherNIL);
                newNode->right = cloneTree(node->right, newNode, otherNIL);
                return newNode;
            }

            bool compareTrees(_TreeNode* node1, _TreeNode* node2) const {
                if (node1 == NIL && node2 == NIL) {
                    return true;
                }
                if (node1 == NIL || node2 == NIL) {
                    return false;
                }
                if (!(node1->data == node2->data) || node1->color != node2->color) {
                    return false;
                }
                return compareTrees(node1->left, node2->left) &&
                    compareTrees(node1->right, node2->right);
            }
        };
        
    public:
        using Ptr = std::unique_ptr<_RedBlackTree>;

        map();
        map(const compare& cmp);
        map(const map& other);
        map(map&& other) noexcept;

        template<class Iterator>
        map(Iterator first, Iterator last, const compare& cmp = std::less<Key>());

        ~map();

        void insert(const Pair& data);
        void erase(const Key& key);
        void clear();
        void swap(map& other);

        bool empty() const;
        size_t size() const;

        Value& at(const Key& key);
        Value& operator[](const Key& key);

        bool operator==(const map& other);
        map& operator=(const map& other);

        int count(const Key& key);

    private:
        Ptr tree;
    };

    template<class Key, class Value>
    map<Key, Value>::map() : tree(std::make_unique<_RedBlackTree>()) {}

    template<class Key, class Value>
    map<Key, Value>::map(const compare& cmp) 
        : tree(std::make_unique<_RedBlackTree>(cmp)) {}

    template<class Key, class Value>
    map<Key, Value>::map(const map& other) {
        tree = std::make_unique<_RedBlackTree>();
        tree->cmp = other.tree->cmp;
        tree->root = tree->cloneTree(other.tree->root, tree->NIL, other.tree->NIL);
    }

    template<class Key, class Value>
    map<Key, Value>::map(map&& other) noexcept {
        tree = std::move(other.tree);
    }

    template<class Key, class Value>
    template<class Iterator>
    map<Key, Value>::map(Iterator first, Iterator last, const compare& cmp) {
        for (auto it = first; it != last; ++it) {
            tree->insert(*it);
        }
        tree->cmp = cmp;
    }

    template<class Key, class Value>
    map<Key, Value>::~map() {}

    template<class Key, class Value>
    void map<Key, Value>::insert(const Pair& data) {
        tree->insert(data);
    }

    template<class Key, class Value>
    void map<Key, Value>::erase(const Key& key) {
        tree->deleteNode(key);
    }

    template<class Key, class Value>
    void map<Key, Value>::clear() {
        tree->destroyTree();
        tree->root = tree->NIL;
    }

    template<class Key, class Value>
    void map<Key, Value>::swap(map& other) {
        if (other.tree == tree)
            return;

        Ptr tmp = std::move(other.tree);
        other.tree = std::move(tree);
        tree = std::move(tmp);
    }

    template<class Key, class Value>
    bool map<Key, Value>::empty() const {
        return tree->root == tree->NIL;
    }

    template<class Key, class Value>
    size_t map<Key, Value>::size() const {
        size_t count = 0;
        tree->inorder(tree->root, [&count](const Pair&) {
            ++count;
        });
        return count;
    }

    template<class Key, class Value>
    Value& map<Key, Value>::at(const Key& key) {
        auto node = tree->findNode(tree->root, key);
        if (node == tree->NIL) {
            throw std::out_of_range("Key not found!");
        }
        return node->data.second;
    }

    template<class Key, class Value>
    Value& map<Key, Value>::operator[](const Key& key) {
        auto node = tree->findNode(tree->root, key);
        if (node == tree->NIL) {
            Value val{};
            tree->insert(Pair(key, val));
            node = tree->findNode(tree->root, key);
        }
        return node->data.second;
    }

    template<class Key, class Value>
    bool map<Key, Value>::operator==(const map& other) {
        if (this == &other)
            return true;

        if (this->size() != other.size())
            return false;

        return tree->compareTrees(tree->root, other.tree->root);
    }

    template<class Key, class Value>
    map<Key, Value>& map<Key, Value>::operator=(const map& other) {
        if (this == &other)
            return *this;

        tree->destroyTree(tree->root);
        tree->root = tree->NIL;

        tree->cmp = other.tree->cmp;
        tree->root = tree->cloneTree(other.tree->root, tree->NIL, other.tree->NIL);

        return *this;
    }

    template<class Key, class Value>
    int map<Key, Value>::count(const Key& key) {
        auto node = tree->findNode(tree->root, key);
        return (node != tree->NIL) ? 1 : 0;
    }
};

#endif
