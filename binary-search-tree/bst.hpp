//
// Created by juheeSVT on 2019-11-04.
//

#include <iostream>
using namespace std;

#define MAX [](int (n), int (m)) -> int {     return n > m ? n : m;   }

class Node {
private:
    int data;
    Node * left;
    Node * right;
public:
    Node(int data = NULL, Node* left = NULL, Node* right = NULL) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    void setData(int data) {
        this->data = data;
    }
    void setLeft(Node* left) {
        this->left = left;
    }
    void setRight(Node* right) {
        this->right = right;
    }
    int getData() {
        return this->data;
    }
    Node * getLeft() {
        return this->left;
    }
    Node * getRight() {
        return this->right;
    }
};

class BinarySearchTree {
private:
    Node *root;
public:
    BinarySearchTree() {
        this->root = NULL;
    }

    Node *getRoot() {
        return this->root;
    }

    int isEmpty() {
        return root == NULL;
    }

    int search(int target) {
        if (isEmpty()) {
            cout << "Tree is Empty !!" << endl;
            return NULL;
        }
        Node *temp = root;
        for (; temp != NULL;) {
            if (temp->getData() == target)
                return target;
            else if (target < temp->getData()) {
                temp = temp->getLeft();
                continue;
            } else {
                temp = temp->getRight();
                continue;
            }
        }
        cout << "Not found" << endl;
    }

    Node *insert(Node *ptr, int data) {

        if (ptr == NULL) {
            ptr = getNode(data);
            if (isEmpty())
                root = ptr;
        } else if (data < ptr->getData())
            ptr->setLeft(insert(ptr->getLeft(), data));
        else
            ptr->setRight(insert(ptr->getRight(), data));
        return ptr;
    }

    Node *getNode(int data) {
        return new Node(data);
    }

    Node *minNode(Node *ptr) {
        if (ptr->getLeft() == NULL)
            return ptr;
        minNode(ptr->getLeft());
    }

    Node *maxNode(Node *ptr) {
        if (ptr->getRight() == NULL)
            return ptr;
        maxNode(ptr->getRight());
    }

    Node *del(Node *ptr, int data = 0) {
        if (!isEmpty()) {
            if (data < ptr->getData())                           // 탐색
                ptr->setLeft(del(ptr->getLeft(), data));
            else if (data > ptr->getData())
                ptr->setRight(del(ptr->getRight(), data));       // 탐색
            else if (ptr->getLeft() == NULL && ptr->getRight() == NULL) { // leaf node
                if (ptr == root)
                    root = NULL;
                ptr = NULL;
            } else if (ptr->getLeft() == NULL) {    // 왼쪽 자식X
                Node *temp = ptr;
                ptr = ptr->getRight();
                if (temp == root)
                    root = ptr;
                delete temp;
            } else if (ptr->getRight() == NULL) {     // 오른쪽자식 X
                Node *temp = ptr;
                ptr = ptr->getLeft();
                if (temp == root)
                    root = ptr;
                delete temp;
            } else { // 둘다 있음
                if (height(ptr->getLeft()) > height(ptr->getRight())) { // 왼쪽 노드의 개수 > 오른쪽 노드의 개수
                    Node *temp = maxNode(ptr->getLeft());
                    ptr->setData(temp->getData());
                    ptr->setLeft(del(ptr->getLeft(), ptr->getData()));
                }
                else if (height(ptr->getLeft()) < height(ptr->getRight())) {
                    Node *temp = minNode(ptr->getRight());
                    ptr->setData(temp->getData());
                    ptr->setRight(del(ptr->getRight(), ptr->getData()));
                }
                else {
                    if (noNodes(ptr->getLeft()) >= noNodes(ptr->getRight())) {
                        Node *temp = maxNode(ptr->getLeft());
                        ptr->setData(temp->getData());
                        ptr->setLeft(del(ptr->getLeft(), ptr->getData()));
                    } else {
                        Node *temp = minNode(ptr->getRight());
                        ptr->setData(temp->getData());
                        ptr->setRight(del(ptr->getRight(), ptr->getData()));
                    }
                }
            }
        } else
            cout << "not found" << endl;
        return ptr;
    }

    int height(Node *p) {
        if (p == NULL) return 0;
        return 1 + MAX( height(p->getLeft()), height(p->getRight()) );
    }

    int noNodes(Node *p) {
        if (p == NULL) {
            return 0;
        }
        int num = 1;
        num += noNodes(p->getLeft()) + noNodes(p->getRight());
        return num;
    }
    void inOrder(Node * ptr) {
        if (ptr) {
            inOrder(ptr->getLeft());
            cout << ptr->getData() << " ";
            inOrder(ptr->getRight());
        }
    }
};