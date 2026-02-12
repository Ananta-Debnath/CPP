

template <typename Key, typename Value>
class RedBlackTree
{
private:
    class Node
    {
    public:
        Key key;
        Value value;

        Node* left;
        Node* right;
        Node* parent;
        bool isRed;

        int subtreeSize;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), isRed(true), subtreeSize(1) {}
    };

    Node* root;

    void updateSubtreeSize(Node* node)
    {
        if (node)
        {
            node->subtreeSize = 1;
            if (node->left) node->subtreeSize += node->left->subtreeSize;
            if (node->right) node->subtreeSize += node->right->subtreeSize;
        }
    }

    Node* rightRotate(Node* node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right) newRoot->right->parent = node;

        newRoot->right = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;

        if (newRoot->parent)
        {
            if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
            else newRoot->parent->right = newRoot;
        }
        else
        {
            root = newRoot;
        }
        updateSubtreeSize(node);
        updateSubtreeSize(newRoot);
        return newRoot;
    }

    Node* leftRotate(Node* node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        if (newRoot->left) newRoot->left->parent = node;

        newRoot->left = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;

        if (newRoot->parent)
        {
            if (newRoot->parent->left == node) newRoot->parent->left = newRoot;
            else newRoot->parent->right = newRoot;
        }
        else
        {
            root = newRoot;
        }
        updateSubtreeSize(node);
        updateSubtreeSize(newRoot);
        return newRoot;
    }

    Node* inOrderSuccessor(Node* node)
    {
        if (node->right)
        {
            node = node->right;
            while (node->left)
                node = node->left;
            return node;
        }
        return nullptr;
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

    void fixRedRed(Node* node)
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        Node* uncle = (grandparent->left == parent) ? grandparent->right : grandparent->left;

        if (uncle && uncle->isRed)
        {
            parent->isRed = false;
            uncle->isRed = false;
            grandparent->isRed = true;

            Node* gpp = grandparent->parent;
            if (gpp && gpp->isRed) fixRedRed(grandparent);
        }
        else
        {
            if (parent == grandparent->left)
            {
                if (node == parent->right)
                {
                    leftRotate(parent);
                    // std::swap(parent, node);
                    parent = node;
                }
                rightRotate(grandparent);
            }
            else
            {
                if (node == parent->left)
                {
                    rightRotate(parent);
                    // std::swap(parent, node);
                    parent = node;
                }
                leftRotate(grandparent);
            }
            parent->isRed = false;
            grandparent->isRed = true;
        }
    }

    void fixDoubleBlack(Node* x, Node* p)
    {
        Node* s = (p->left == x) ? p->right : p->left;

        if (s && s->isRed)
        {
            (s == p->right) ? leftRotate(p) : rightRotate(p);
            p->isRed = true;
            s->isRed = false;
            s = (p->left == x) ? p->right : p->left;
        }

        if (!s || (!s->left || !s->left->isRed) && (!s->right || !s->right->isRed)) // No red children
        {
            if (s) s->isRed = true;
            if (p->isRed) p->isRed = false;
            else if (p != root) fixDoubleBlack(p, p->parent);
        }

        else
        {
            Node* nc = (x == p->left) ? s->left : s->right;
            Node* fc = (x == p->left) ? s->right : s->left;
            if (nc && nc->isRed && (!fc || !fc->isRed))
            {
                (nc == s->left) ? rightRotate(s) : leftRotate(s);
                s->isRed = true;
                nc->isRed = false;
                s = nc;
                fc = (x == p->left) ? s->right : s->left;
            }

            (s == p->right) ? leftRotate(p) : rightRotate(p);
            s->isRed = p->isRed;
            p->isRed = false;
            if (fc) fc->isRed = false;
        }
    }


public:
    RedBlackTree()
    {
        root = nullptr;
    }

    ~RedBlackTree()
    {
        clear();
    }

    bool insert(const Key& key, const Value& value)
    {
        Node* newNode = new Node(key, value);

        if (!root)
        {
            root = newNode;
            root->isRed = false; // Root is always black
            return true;
        }

        Node* current = root;
        Node* parent = nullptr;
        while (current)
        {
            parent = current;
            if (key < current->key) current = current->left;
            else if (key > current->key) current = current->right;
            else // key == current->key
            {
                delete newNode;
                return false;
            }
        }
        newNode->parent = parent;
        if (key < parent->key) parent->left = newNode;
        else parent->right = newNode;

        Node* temp = newNode;
        while (temp)
        {
            updateSubtreeSize(temp);
            temp = temp->parent;
        }

        // Fix red-black tree properties
        if (parent->isRed) fixRedRed(newNode);
        root->isRed = false; // Root must always be black
        return true;
    }

    bool remove(const Key& key)
    {
        Node* node = root;
        while (node)
        {
            if (key < node->key) node = node->left;

            else if (key > node->key) node = node->right;

            else break; // key == node->key
        }
        if (!node) return false; // Key not found

        if (node->right && node->left)
        {
            Node* succ = inOrderSuccessor(node);
            node->key = succ->key;
            node->value = succ->value;
            node = succ;
        }

        bool nodeIsRed = node->isRed;
        Node* x = node->left ? node->left : node->right;
        Node* p = node->parent;
        if (x) x->parent = p;

        if (!p) root = x;
        else if (node == p->left) p->left = x;
        else p->right = x;

        delete node;

        Node* temp = p;
        while (temp)
        {
            updateSubtreeSize(temp);
            temp = temp->parent;
        }

        // Fix-up
        if (!nodeIsRed)
        {
            if (x && x->isRed) x->isRed = false;
            else if (x != root)
            {
                fixDoubleBlack(x, p);
            }
        }
        return true;
    }

    Value* get(const Key& key)
    {
        Node* node = root;
        while (node)
        {
            if (key < node->key) node = node->left;

            else if (key > node->key) node = node->right;

            else return &(node->value); // key == node->key
        }
        return nullptr; // Key not found
    }

    int getLowerCount(const Key& key)
    {
        Node* node = root;
        int count = 0;
        while (node)
        {
            if (key < node->key)
            {
                node = node->left;
            }
            else if (key > node->key)
            {
                count += (node->left ? node->left->subtreeSize : 0) + 1; // Count left subtree + current node
                node = node->right;
            }
            else
            {
                count += (node->left ? node->left->subtreeSize : 0); // Count left subtree only
                break;
            }
        }
        return count;
    }

    void clear()
    {
        freeNode(root);
        root = nullptr;
    }
};