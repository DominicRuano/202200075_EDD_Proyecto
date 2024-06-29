#include "../Objects/nodo.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

template <typename T>
class ArbolB {
private:
    int minDegree;
    struct BNode {
        vector<T> keys;
        vector<BNode*> children;
        bool isLeaf;

        BNode(int t, bool leaf) {
            isLeaf = leaf;
            keys.reserve(2 * t - 1);
            children.reserve(2 * t);
        }
    };

    BNode* root;

    void insertNonFull(BNode* node, const T& k) {
        int i = node->keys.size() - 1;
        if (node->isLeaf) {
            node->keys.push_back(k);
            while (i >= 0 && node->keys[i] > k) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = k;
        } else {
            while (i >= 0 && node->keys[i] > k)
                i--;
            if (node->children[i + 1]->keys.size() == 2 * minDegree - 1) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (node->keys[i + 1] < k)
                    i++;
            }
            insertNonFull(node->children[i + 1], k);
        }
    }

    void splitChild(BNode* parent, int i, BNode* child) {
        BNode* newChild = new BNode(minDegree, child->isLeaf);
        for (int j = 0; j < minDegree - 1; j++)
            newChild->keys.push_back(child->keys[j + minDegree]);
        if (!child->isLeaf) {
            for (int j = 0; j < minDegree; j++)
                newChild->children.push_back(child->children[j + minDegree]);
        }
        child->keys.resize(minDegree - 1);
        parent->children.insert(parent->children.begin() + i + 1, newChild);
        parent->keys.insert(parent->keys.begin() + i, child->keys[minDegree - 1]);
    }

    void generateDot(BNode* node, ofstream& out, int& count) const {
        int nodeId = count++;
        out << "node" << nodeId << " [label=\"";
        out << "<f0>|";
        for (int i = 0; i < node->keys.size(); i++) {
            out << "<f" << i << "> " << node->keys[i] << "| <f" << i + 1 << ">";
            if (i != node->keys.size() - 1) {
                out << "|";
            }
        }
        out << "\"];\n";
        int currentNodeId = nodeId;
        for (int i = 0; i < node->children.size(); i++) {
            out << "\"node" << currentNodeId << "\":f" << i << " -> \"node" << count << "\";\n";
            generateDot(node->children[i], out, count);
        }
    }

    void remove(BNode* node, const T& k) {
        int idx = findKey(node, k);

        if (idx < node->keys.size() && node->keys[idx] == k) {
            if (node->isLeaf)
                removeFromLeaf(node, idx);
            else
                removeFromNonLeaf(node, idx);
        } else {
            if (node->isLeaf) {
                cout << "The key " << k << " does not exist in the tree.\n";
                return;
            }

            bool flag = (idx == node->keys.size());

            if (node->children[idx]->keys.size() < minDegree)
                fill(node, idx);

            if (flag && idx > node->keys.size())
                remove(node->children[idx - 1], k);
            else
                remove(node->children[idx], k);
        }
    }

    int findKey(BNode* node, const T& k) {
        int idx = 0;
        while (idx < node->keys.size() && node->keys[idx] < k)
            ++idx;
        return idx;
    }

    void removeFromLeaf(BNode* node, int idx) {
        for (int i = idx + 1; i < node->keys.size() - 1; ++i)
            node->keys[i - 1] = node->keys[i];
        node->keys.resize(node->keys.size() - 1);
    }

    void removeFromNonLeaf(BNode* node, int idx) {
        T k = node->keys[idx];

        if (node->children[idx]->keys.size() >= minDegree) {
            T pred = getPred(node, idx);
            node->keys[idx] = pred;
            remove(node->children[idx], pred);
        } else if (node->children[idx + 1]->keys.size() >= minDegree) {
            T succ = getSucc(node, idx);
            node->keys[idx] = succ;
            remove(node->children[idx + 1], succ);
        } else {
            merge(node, idx);
            remove(node->children[idx], k);
        }
    }

    T getPred(BNode* node, int idx) {
        BNode* cur = node->children[idx];
        while (!cur->isLeaf)
            cur = cur->children[cur->keys.size()];
        return cur->keys[cur->keys.size() - 1];
    }

    T getSucc(BNode* node, int idx) {
        BNode* cur = node->children[idx + 1];
        while (!cur->isLeaf)
            cur = cur->children[0];
        return cur->keys[0];
    }

    void fill(BNode* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->keys.size() >= minDegree)
            borrowFromPrev(node, idx);
        else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= minDegree)
            borrowFromNext(node, idx);
        else {
            if (idx != node->keys.size())
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    void borrowFromPrev(BNode* node, int idx) {
        BNode* child = node->children[idx];
        BNode* sibling = node->children[idx - 1];

        for (int i = child->keys.size() - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];

        if (!child->isLeaf) {
            for (int i = child->children.size() - 1; i >= 0; --i)
                child->children[i + 1] = child->children[i];
        }

        child->keys[0] = node->keys[idx - 1];

        if (!node->isLeaf)
            child->children[0] = sibling->children[sibling->keys.size()];

        node->keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];

        child->keys.push_back(T());
        child->keys[0] = sibling->keys[sibling->keys.size() - 1];
        sibling->keys.resize(sibling->keys.size() - 1);
    }

    void borrowFromNext(BNode* node, int idx) {
        BNode* child = node->children[idx];
        BNode* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);

        if (!child->isLeaf)
            child->children[child->keys.size()] = sibling->children[0];

        node->keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->keys.size(); ++i)
            sibling->keys[i - 1] = sibling->keys[i];

        if (!sibling->isLeaf) {
            for (int i = 1; i <= sibling->keys.size(); ++i)
                sibling->children[i - 1] = sibling->children[i];
        }

        sibling->keys.resize(sibling->keys.size() - 1);
    }

    void merge(BNode* node, int idx) {
        BNode* child = node->children[idx];
        BNode* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);

        for (int i = 0; i < sibling->keys.size(); ++i)
            child->keys.push_back(sibling->keys[i]);

        if (!child->isLeaf) {
            for (int i = 0; i <= sibling->keys.size(); ++i)
                child->children.push_back(sibling->children[i]);
        }

        for (int i = idx + 1; i < node->keys.size(); ++i)
            node->keys[i - 1] = node->keys[i];

        for (int i = idx + 2; i <= node->keys.size(); ++i)
            node->children[i - 1] = node->children[i];

        child->keys.resize(child->keys.size() + sibling->keys.size());
        node->keys.resize(node->keys.size() - 1);
        node->children.resize(node->children.size() - 1);

        delete sibling;
    }

public:
    ArbolB(int t) : minDegree(t) {
        root = new BNode(t, true);
    }

    void insert(const T& k) {
        if (root->keys.size() == 2 * minDegree - 1) {
            BNode* newNode = new BNode(minDegree, false);
            newNode->children.push_back(root);
            splitChild(newNode, 0, root);
            root = newNode;
        }
        insertNonFull(root, k);
    }

    void traverse() {
        if (root != nullptr)
            traverse(root);
    }

    void traverse(BNode* node) {
        int i;
        for (i = 0; i < node->keys.size(); i++) {
            if (!node->isLeaf)
                traverse(node->children[i]);
            cout << " " << node->keys[i];
        }
        if (!node->isLeaf)
            traverse(node->children[i]);
    }

    void remove(const T& k) {
        if (!root) {
            cout << "The tree is empty\n";
            return;
        }

        remove(root, k);

        if (root->keys.size() == 0) {
            BNode* tmp = root;
            if (root->isLeaf)
                root = nullptr;
            else
                root = root->children[0];

            delete tmp;
        }
    }

    void generateDot(const string& filename) const {
        ofstream out(filename);
        if (!out.is_open()) {
            cerr << "Error opening file for writing\n";
            return;
        }
        out << "digraph BTree {\n";
        out << "node [shape=record];\n";
        int count = 0;
        generateDot(root, out, count);
        out << "}\n";
        out.close();
    }
};