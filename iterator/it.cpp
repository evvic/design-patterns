#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
using namespace std;

template <typename T> struct BinaryTree;

// todo: refactor to refer to parent instead of entire tree
template <typename T> struct Node
{
    T value = T();
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    explicit Node(const T& value) : value(value) {}

    Node(const T& value, Node<T>* const left, Node<T>* const right)
        : value(value),
        left(left),
        right(right)
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;
    }
};

template <typename T> struct BinaryTree
{
    Node<T>* root = nullptr;

    explicit BinaryTree(Node<T>* const root)
        : root{ root }, pre_order{ *this }
    {
        root->set_tree(this);
    }

    ~BinaryTree() { if (root) delete root; }
  
    template <typename U>
    struct LevelOrderIterator
    {
        Node<U>* current;
        queue<Node<U>*> next;

        explicit LevelOrderIterator(Node<U>* current)
            : current(current), next({current})
        {}

        bool operator!=(const LevelOrderIterator<U>& other)
        {
            return current != other.current;
        }

        // no continuations in C++ (unlike C#)
        LevelOrderIterator<U>& operator++() 
        {
            if (!next.empty()) {           
                // Print front of queue and remove it from queue
                current = next.front();
                next.pop();

                // Enqueue left child
                if (current->left != NULL)
                    next.push(current->left);

                // Enqueue right child
                if (current->right != NULL)
                    next.push(current->right);
            } 
            else current = nullptr;
            
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };

    typedef LevelOrderIterator<T> iterator;

    iterator end()
    {
        return iterator{ nullptr };
    }

    iterator begin()
    {
        return iterator{ root };
    }
};


// in order traversal
int main()
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f

    BinaryTree<string> family{
        new Node<string>{"me", 
        new Node<string>{"mother",
            new Node<string>{"mother's mother"},
            new Node<string>{"mother's father"}
        },
        new Node<string>{"father"}
        }
    };

    // pre order traversal
    for (auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << "\n";
    }

    cout << "=== and now, through a dedicated object:\n";

    // use iterator name
    // for (const auto& it: family.pre_order)
    // {
    //     cout << it.value << "\n";
    // }

    return 0;
}
