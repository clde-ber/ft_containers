#ifndef PAIR_H
#define PAIR_H

#include <iostream>

static int end = 0;

namespace ft
{
    template< class Key, class T >
    struct Node
    {
        Key data; // holds the key
        T val;
        Node *parent; // pointer to the parent
        Node *left; // pointer to left child
        Node *right; // pointer to right child
        int color; // 1 -> Red, 0 -> Black
        Node() : data(0), val(0), parent(NULL), left(NULL), right(NULL), color(0) {}
        Node(Key key, T value) : data(key), val(value), parent(NULL), left(NULL), right(NULL), color(0) {}
        Node(Node const & rhs) : data(rhs.data), val(rhs.val), parent(rhs.parent), left(rhs.left), right(rhs.right), color(rhs.color) {}
        Node & operator=(Node const & rhs) { data = rhs.data; val = rhs.val; parent = rhs.parent; left = rhs.left; right = rhs.right; return *this; }
    };

    template< class Key, class T >
    class RBTree
    {
        private:
            Node< Key, T > *root = NULL;
            Node< Key, T > *last = NULL;

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Node< Key, T > *node)
            {
                node->data = 0;
                node->val = 0;
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
            void swap(Node< Key, T > **x, Node< Key, T > **y)
            {
                Node< Key, T > **tmp = x;
                x = y;
                y = tmp;
            }
        public:
            typedef Node< Key, T >* NodePtr;

            NodePtr find(Node<Key, T> const& toFind) const
            {
                NodePtr fromRoot = root;
                while (fromRoot)
                {
                    if (fromRoot == last)
                        return last;
                    if (toFind.val < fromRoot->val)
                        fromRoot = fromRoot->left;
                    else if (toFind.val > fromRoot->val)
                        fromRoot = fromRoot->right;
                    else
                        return fromRoot;
                }
                return last;
            }
            NodePtr findMinimum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->left && origin->left != last)
                    origin = origin->left;
                std::cout << "or val" << origin->val << std::endl;
                return origin;
            }
            NodePtr findMaximum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->right && origin->right != last)
                    origin = origin->right;
                std::cout << "or val" << origin->val << std::endl;
                return origin;
            }
            void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                x->right = leftY;
                y->left =  tmpX;
                x->parent = tmpY;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else
                    y->parent->right = y;    
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                //NodePtr leftX = x->left;
                NodePtr parentY = y->parent;

                x->right = tmpY;
                y->left =  rightX;
                x->parent = parentY;
                y->parent = tmpX;
               //x->parent->left = x;
                if (!parentY)
                    root = x;
                else
                  x->parent->left = x;    
                root->color = 0;
            }
            /*void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                if (leftY != last)
                    x->right = leftY;
                else
                    x->right = NULL;
                if (tmpX != last)
                    y->left =  tmpX;
                else
                    y->left = NULL;
                if (tmpY != last)
                    x->parent = tmpY;
                else
                    x->parent = NULL;
                if (parentX != last)
                    y->parent = parentX;
                else
                    y->parent = NULL;
                if (!parentX)
                {
                    root = y;
           //         root->parent = last;
           //         last->left = root;
                }
                else
                    y->parent->right = y; 
               NodePtr max = findMaximum(root);
                initializeNode(last);
                max->right = last;
                last->parent = max;
                prettyPrint();
                root->color = 0;
            }
            void rightRotate(NodePtr y)
            {
                NodePtr x = y->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                //NodePtr leftX = x->left;
                NodePtr parentY = y->parent;

                if (tmpY != last)
                x->right = tmpY;
                else
                x->right = NULL;
                if (rightX != last)
                y->left =  rightX;
                else
                y->left = NULL;
                if (parentY != last)
                x->parent = parentY;
                else
                x->parent = NULL;
                if (tmpX != last)
                y->parent = tmpX;
                else
                y->parent = NULL;
               //x->parent->left = x;
                if (!parentY)
                {
                    root = x;
          //          root->parent = last;
          //          last->left = root;
                }
                else
                  x->parent->left = x;    
                NodePtr max = findMaximum(root);
                initializeNode(last);
                max->right = last;
                last->parent = max;  
                prettyPrint();
                root->color = 0;
            }*/
            void insert(Node< Key, T > const &toInsert)
            {
                std::cout << "node" << toInsert.val << std::endl;
                prettyPrint();
                NodePtr node = new Node< Key, T >;
                initializeNode(node);
                node->val = toInsert.val;
                node->data = toInsert.data;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                if (root)
                std::cout << "node" << root->val << std::endl;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                while (fromRoot && fromRoot != last)
                {
                    parentNode = fromRoot;
                    if (node->val < fromRoot->val)
                        fromRoot = fromRoot->left;
                    else
                        fromRoot = fromRoot->right;
                    if (fromRoot)
                    {
                        child = fromRoot;
                        child->parent = parentNode;
                    }
                }
                node->parent = parentNode;
                if (!node->parent)
                {
                    root = node;
                    root->right = last;
                    last->parent = root;
                    node->color = 0;
                    return ;
                }
                if (node->val < root->val)
                {
                    if (node->val < parentNode->val)
                        parentNode->left = node;
                    else
                        parentNode->right = node;
                    rightRotate(root);
                }
                else
                {
                    if (node->val < parentNode->val)
                        parentNode->left = node;
                    else
                        parentNode->right = node;
                    leftRotate(root);
                }
                NodePtr max = findMaximum(root);
                max->right = last;
                last->parent = max;
                std::cout << "roooooot " << root->val << std::endl;
                if (node->parent)
                    recolor(root);
            }
            NodePtr getRoot()
            {
                return root;
            }
            NodePtr getLast() const
            {
                return last;
            }
            void setLast(NodePtr node)
            {
                last = node;
            }
            void recolor (NodePtr node)
            {
                if (node != NULL)
                {
                    if (node->left && node->left->color)
                    {
                        if (node->left->right)
                            node->left->right->color = 0;
                        if (node->left->left)
                            node->left->left->color = 0;
                    }
                    if (node->right && node->right->color)
                    {
                        if (node->right->right)
                            node->right->right->color = 0;
                        if (node->right->left)
                            node->right->left->color = 0;
                    }
                    recolor(node->left);
                    recolor(node->right);
                }
                if (root->right)
                    root->right->color = 0;
                if (root->left)
                    root->left->color = 0;
            }
            int isDeletable(NodePtr found)
            {
                std::cout << "la00 " << found->val << std::endl;
                std::cout << "FOUND" << found->val << std::endl;
                if (!found->parent && !found->left && found->right && found->right == last)
                {
                    std::cout << "la11 " << std::endl;
                    initializeNode(found);
                    initializeNode(last);
                    delete found;
                    found = NULL;
                    root = NULL;
                    end = 1;
                    return 1;
                }
                if (!found->parent && found->right && found->right == last && found->left)
                {
                    std::cout << "la22 " << std::endl;
                    root = found->left;
                    root->parent = NULL;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    NodePtr max = findMaximum(root);
                    max->right = last;
                    last->parent = max;
                    return 1;
                }
                if (!found->parent && !found->left && found->right && found->right != last)
                {
                    prettyPrint();
                    std::cout << "la33 " << found->val << std::endl;
                    found->right->parent = NULL;
                    root = found->right;
                    root->parent = NULL;
                    initializeNode(found);
                    delete found;
                    found = NULL;
                    prettyPrint();
                    NodePtr max = findMaximum(root);
                    max->right = last;
                    last->parent = max;
                    return 1;
                }
                if (found->left && found->right && found->right != last && !found->left->left && !found->left->right && !found->right->left && found->right->right == last)
                    {
                        std::cout << "la44 " << std::endl;
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->right;
                            found->right->parent = found->parent;
                            found->parent->right->left = found->left;
                            found->left->parent = found->parent->right;
                        }
                        else
                        {
                            found->parent->left = found->right;
                            found->right->parent = found->parent;
                            found->parent->left->left = found->left;
                            found->left->parent = found->parent->left;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->left && found->right && found->right == last)
                    {
                        std::cout << "la55 " << std::endl;
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->left;
                            found->left->parent = found->parent;
                        }
                        else
                        {
                            found->parent->left = found->left;
                            found->left->parent = found->parent;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->right && found->right != last && !found->left)
                    {
                        std::cout << "la66 " << std::endl;
                        if (found == found->parent->right)
                        {
                            found->parent->right = found->right;
                            found->right->parent = found->parent;
                        }
                        else
                        {
                            found->parent->left = found->right;
                            found->right->parent = found->parent;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    if (found->right && found->right == last && !found->left)
                    {
                        std::cout << "la77 " << std::endl;
                        if (found == found->parent->right)
                        {
                            found->parent->right = NULL;
                            found->parent = NULL;
                        }
                        else
                        {
                            found->parent->left = NULL;
                            found->parent = NULL;
                        }
                        initializeNode(found);
                        delete found;
                        found = NULL;
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        return 1;
                    }
                    return 0;
            }
            void deleteNode(T value)
            {
                std::cout << "valueeeeeeeeeeeeeee " << value << std::endl;
                NodePtr found = NULL;
                NodePtr node = getRoot();
                int i = 0;
                while (node)
                {
                    if (node->val == value)
                        found = node;
                    if (value <= node->val)
                        node = node->left;
                    else
                        node = node->right;
                }
                std::cout << "FOUND" << found->val << std::endl;
                if (!found || (found && !found->parent))
                {
                    if (!found)
                        return ;
                    else
                    {
                        i = isDeletable(found);
                        while (root && root->left && !i)
                        {
                            i = isDeletable(found);
                            if (i)
                                return ;
                            rightRotate(root);
                        }
                        while (root && root->right && !i)
                        {
                            i = isDeletable(found);
                            if (i)
                                return ;
                            leftRotate(root);
                        }
                    }
                    return ;
                }
                if (value < found->parent->val)
                {
                    while (found && found->left)
                    {
                        i = isDeletable(found);
                        if (i)
                        {
                            if (root && end == 0)
                                recolor(root);
                            break ;
                        }
                        rightRotate(found);
                    }
                }
                else
                {
                    while (found && found->right)
                    {
                        i = isDeletable(found);
                        if (i)
                        {
                            if (root && end == 0)
                                recolor(root);
                            break ;
                        }
                        leftRotate(found);
                    }
                }
              if (!i || found == root)
                isDeletable(found);
            }
            void printHelper(NodePtr root, std::string indent, bool last)
            {
                // print the tree structure on the screen
                if (root != NULL)
                {
                    std::cout<<indent;
                    if (last)
                    {
                        std::cout<<"R----";
                        indent += "     ";
                    }
                    else
                    {
                        std::cout<<"L----";
                        indent += "|    ";
                    }
                    std::string sColor = root->color?"RED":"BLACK";
                    std::cout<<root->val<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }
            void prettyPrint()
            {
                if (root)
                    printHelper(this->root, "", true);
	        }
            void freeNodes(NodePtr node)
            {
                if (node != NULL)
                {
                    freeNodes(node->left);
                    freeNodes(node->right);
                }
                delete node;
                node = NULL;
            }
            // If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
            // Every path from a root node to a NULL node has the same number of black nodes.
    };
}

//https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif