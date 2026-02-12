#include <vector>
#include <queue>

template <typename Key, typename Value>
class AVLTree
{
private:
    class Node
    {
    public:
        Key key;
        Value value;

        Node* left;
        Node* right;
        int height;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;


    Node* rightRotate(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    Node* leftRotate(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    void updateHeight(Node* node)
    {
        int leftHeight = (node->left) ? node->left->height : 0;
        int rightHeight = (node->right) ? node->right->height : 0;

        node->height = 1 + std::max(leftHeight, rightHeight);
    }

    int getBalanceFactor(Node* node)
    {
        int leftHeight = (node->left) ? node->left->height : 0;
        int rightHeight = (node->right) ? node->right->height : 0;
        return leftHeight - rightHeight;
    }

    Node* inOrderSuccessor(Node* node)
    {
        if (node->right)
        {
            node = node->right;
            while (node->left) node = node->left;
            return node;
        }
        return nullptr;
    }

    Node* balanceNode(Node* node)
    {
        updateHeight(node);
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) // Left heavy
        {
            if (getBalanceFactor(node->left) < 0) // Left Right heavy
            {
                node->left = leftRotate(node->left);
            }
            node = rightRotate(node);
        }
        else if (balanceFactor < -1) // Right heavy
        {
            if (getBalanceFactor(node->right) > 0) // Right Left heavy
            {
                node->right = rightRotate(node->right);
            }
            node = leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, const Key& key, const Value& value)
    {
        if (!node) return new Node(key, value);

        if (key < node->key) node->left = insert(node->left, key, value);
        
        else if (key > node->key) node->right = insert(node->right, key, value);
        
        else // key == node->key
        {
            // node->value = value;
            return node;
        }

        node = balanceNode(node);

        return node;
    }

    Node* remove(Node* node, const Key& key)
    {
        if (!node) return node; // node == nullptr

        if (key < node->key) node->left = remove(node->left, key);

        else if (key > node->key) node->right = remove(node->right, key);

        else // key == node->key
        {
            if (!node->left || !node->right)
            {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else
            {
                Node* temp = inOrderSuccessor(node);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }

        node = balanceNode(node);

        return node;
    }

    void freeNode(Node* node)
    {
        if (node)
        {
            freeNode(node->left);
            freeNode(node->right);
            delete node;
        }
    }

    void inOrderHelper(Node* node, std::vector<std::pair<Key, Value>>& result)
    {
        if (node)
        {
            inOrderHelper(node->left, result);
            result.emplace_back(node->key, node->value);
            inOrderHelper(node->right, result);
        }
    }

    void preOrderHelper(Node* node, std::vector<std::pair<Key, Value>>& result)
    {
        if (node)
        {
            result.emplace_back(node->key, node->value);
            preOrderHelper(node->left, result);
            preOrderHelper(node->right, result);
        }
    }

    void postOrderHelper(Node* node, std::vector<std::pair<Key, Value>>& result)
    {
        if (node)
        {
            postOrderHelper(node->left, result);
            postOrderHelper(node->right, result);
            result.emplace_back(node->key, node->value);
        }
    }

public:
    AVLTree()
    {
        root = nullptr;
    }

    ~AVLTree()
    {
        clear();
    }

    bool insert(const Key& key, const Value& value)
    {
        if (get(key)) return false; // Key already exists
        
        root = insert(root, key, value);
        return true;
    }

    bool remove(const Key& key)
    {
        if (!get(key)) return false; // Key does not exist
        
        root = remove(root, key);
        return true;
    }

    Value* get(const Key& key)
    {
        Node* current = root;
        while (current)
        {
            if (key < current->key) current = current->left;

            else if (key > current->key) current = current->right;

            else return &(current->value); // key == current->key
        }
        return nullptr; // Key not found
    }

    void clear()
    {
        freeNode(root);
        root = nullptr;
    }

    std::vector<std::pair<Key, Value>> inOrderTraversal()
    {
        std::vector<std::pair<Key, Value>> result;
        inOrderHelper(root, result);
        return result;
    }

    std::vector<std::pair<Key, Value>> preOrderTraversal()
    {
        std::vector<std::pair<Key, Value>> result;
        preOrderHelper(root, result);
        return result;
    }

    std::vector<std::pair<Key, Value>> postOrderTraversal()
    {
        std::vector<std::pair<Key, Value>> result;
        postOrderHelper(root, result);
        return result;
    }

    std::vector<std::pair<Key, Value>> levelOrderTraversal()
    {
        std::vector<std::pair<Key, Value>> result;
        if (!root)
            return result;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* current = q.front();
            q.pop();
            result.emplace_back(current->key, current->value);

            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
        return result;
    }
};