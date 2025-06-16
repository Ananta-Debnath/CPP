#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    Node* getNode(Node* root, Key key) const
    {
        if (root == nullptr || root->key == key) return root;

        else if (key < root->key) return getNode(root->left, key);

        else return getNode(root->right, key);
    }

    void defaultPrint(Node* root) const
    {
        std::cout << "(";
        if (root != nullptr)
        {
            std::cout << root->key << ":" << root->value;

            if (root->left || root->right)
            {
                std::cout << " ";
                defaultPrint(root->left);
            }

            if (root->right)
            {
                std::cout << " ";
                defaultPrint(root->right);
            }
        }
        std::cout << ")";
    }

    void preOrderPrint(Node* root) const
    {
        if (root != nullptr)
        {
            std::cout << "(" << root->key << ":" << root->value << ") ";
            preOrderPrint(root->left);
            preOrderPrint(root->right);
        }
    }

    void inOrderPrint(Node* root) const
    {
        if (root != nullptr)
        {
            inOrderPrint(root->left);
            std::cout << "(" << root->key << ":" << root->value << ") ";
            inOrderPrint(root->right);
        }
    }

    void postOrderPrint(Node* root) const
    {
        if (root != nullptr)
        {
            postOrderPrint(root->left);
            postOrderPrint(root->right);
            std::cout << "(" << root->key << ":" << root->value << ") ";
        }
    }

    void freeNode(Node* root)
    {
        if (root == nullptr) return;

        freeNode(root->left);
        freeNode(root->right);
        delete root;
    }

    Node* removeNode(Node* root, Key key)
    {
        if (root == nullptr) return root;

        if (key < root->key) root->left = removeNode(root->left, key);

        else if (key > root->key) root->right = removeNode(root->right, key);

        else // key == root->key
        {
            Node* temp;
            if (!root->left && !root->right) // Leaf node
            {
                delete root;
                return nullptr;
            }
            else if (!root->left) // Only right child
            {
                temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) // Only left child
            {
                temp = root->left;
                delete root;
                return temp;
            }
            else // Both children
            {
                temp = root->right;

                if (temp->left)
                {
                    // Find in-order successor (kinda)
                    while (temp->left->left) temp = temp->left;
                    root->key = temp->left->key;
                    root->value = temp->left->value;
                    temp->left = removeNode(temp->left, temp->left->key);
                    return root;
                }
                else
                {
                    temp->left = root->left;
                    delete root;
                    return temp;
                }
            }
        }
        return root;
    }
    
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clear();
    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        bool success = true;

        if (root == nullptr) root = new Node(key, value);

        else
        {
            Node* cur = root;
            while (1)
            {
                if (key < cur->key)
                {
                    if (cur->left == nullptr) break;

                    else cur = cur->left;
                }
                else if (key > cur->key)
                {
                    if (cur->right == nullptr) break;

                    else cur = cur->right;
                }
                else // key == curr->key;
                {
                    success = false;
                    break;
                }
            }

            if (success)
            {
                if (key < cur->key) cur->left = new Node(key, value);

                else cur->right = new Node(key, value);
            }
        }

        if (success) node_count++;
        return success;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic

        if (!find(key)) return false;

        else
        {
            root = removeNode(root, key);
            node_count--;
            return true;
        }
    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override
    {
        // TODO: Implement find logic

        if (getNode(root, key) == nullptr) return false;

        else return true;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic

        Node* node = getNode(root, key);
        
        if (node != nullptr) return node->value;

        else throw std::runtime_error("Key not found");
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic

        Node* node = getNode(root, key);
        
        if (node != nullptr) node->value = value;

        else throw std::runtime_error("Key not found");
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic

        freeNode(root);
        root = nullptr;
        node_count = 0;
    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic

        return node_count;
    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic

        return node_count == 0;
    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic
        
        if (!empty())
        {
            Node* curr = root;
            while (curr->left) curr = curr->left;

            return curr->key;
        }
        else throw std::runtime_error("BST is empty");
    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic
        
        if (!empty())
        {
            Node* curr = root;
            while (curr->right) curr = curr->right;

            return curr->key;
        }
        else throw std::runtime_error("BST is empty");
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        // TODO: Implement print logic
        if (traversal_type == 'D' || traversal_type == 'd')
        {
            std::cout << "BST (Default): ";
            defaultPrint(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'I' || traversal_type == 'i')
        {
            std::cout << "BST (In-order): ";
            inOrderPrint(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'P' || traversal_type == 'p')
        {
            std::cout << "BST (Pre-order): ";
            preOrderPrint(root);
            std::cout << std::endl;
        }
        else if (traversal_type == 'O' || traversal_type == 'o')
        {
            std::cout << "BST (Post-order): ";
            postOrderPrint(root);
            std::cout << std::endl;
        }
        else throw std::runtime_error("Invalid traversal type");
    }
    
};

#endif // LISTBST_H