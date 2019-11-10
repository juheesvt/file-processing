//
// Created by juheeSVT on 2019-11-08.
//

#include <iostream>
using namespace std;

#define MAX [](int (n), int (m)) -> int {     return n > m ? n : m;       }
#define LL 1
#define LR 2
#define RR 3
#define RL 4
#define NO -1


class Node {
private:
    int data;
    int balanceFator;
    Node * left;
    Node * right;

public:
    Node(int data = NULL, int balanceFactor = NULL, Node* left = NULL, Node* right = NULL) {
        this->data = data;
        this->balanceFator = balanceFactor;
        this->left = left;
        this->right = right;
    }
    void setData(int data) {
        this->data = data;
    }
    void setBalancingFator(int balanceFactor){
        this->balanceFator = balanceFactor;
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
    int getBalancingFactor(){
        return this->balanceFator;
    }
    Node * getLeft() {
        return this->left;
    }
    Node * getRight() {
        return this->right;
    }
};

struct ReturnType{

    Node * target;
    Node * parent;
    int preNode;
    int rotationType;

    ReturnType(Node * target, Node * parent, int preNode, int rotationType){
        this-> target = target;
        this-> parent = parent;
        this-> preNode = preNode;
        this->rotationType = rotationType;
    }
};

class avlTree {
private:
    Node *root;
public:
    avlTree() {
        this->root = NULL;
    }

    Node *getRoot() {
        return this->root;
    }

    int isEmpty() {
        return root == NULL;
    }

    Node* search(Node * ptr, int target) {
        if (isEmpty()) {
            cout << "Tree is Empty !!" << endl;
            return NULL;
        }

        if(ptr != NULL) {
            if (ptr->getData() == target)
                return ptr;
            else if (target < ptr->getData()) {
                return search(ptr->getLeft(), target);
            }
            else {
                return search(ptr->getRight(), target);
            }
        }
        cout << "Not found" << endl;
        return NULL;
    }

    ReturnType * checkBalance(Node * ptr, int target, int rotationType) {

        if (isEmpty()) {
            cout << "Tree is Empty !!" << endl;
            return NULL;
        }

        if(ptr != NULL) {
            ReturnType * temp = NULL;
            if (ptr->getData() == target)
                return new ReturnType(NULL,NULL,NULL, NO);

            else if (target < ptr->getData()) {
                 temp = checkBalance(ptr->getLeft(), target, NULL);
                 ptr->setBalancingFator(height(ptr->getLeft()) - height(ptr->getRight()));

                 // 이전에 left에서 옴 ㅇㅇ
                if( (ptr->getBalancingFactor() != -1 || ptr->getBalancingFactor() != 0 || ptr->getBalancingFactor() != 1)
                    && temp != NULL && temp->target == NULL){
                    temp->target = ptr;
                    if( temp->preNode == -1)
                        temp->rotationType = LL;
                    else if(temp->preNode == 1)
                        temp->rotationType = RL;
                }

                if( temp != NULL ) {
                    if( temp->target != NULL)
                        temp->parent = ptr;
                    temp->preNode = -1; // 왼쪽
                }
                return temp;
            }
            else {
                temp = checkBalance(ptr->getRight(), target, NULL);
                ptr->setBalancingFator(height(ptr->getLeft()) - height(ptr->getRight()));

                // 이전에 right에서 옴 ㅇㅇ
                if( (ptr->getBalancingFactor() != -1 || ptr->getBalancingFactor() != 0 || ptr->getBalancingFactor() != 1)
                    && temp != NULL && temp->target != NULL){
                    temp->target = ptr;
                    if( temp->preNode == 1)
                        temp->rotationType = RR;
                    else if(temp->preNode == -1)
                        temp->rotationType = LR;
                }
                if( temp != NULL ) {
                    if( temp->target != NULL)
                        temp->parent = ptr;
                    temp->preNode = 1; // 오른쪽
                }
                return temp;
            }
        }
        return NULL;
    }

    void rotateTree(ReturnType * rt){
        switch(rt->rotationType){
            case LL :
                break;
            case LR :
                break;
            case RR :
                break;
            case RL :
                break;
        }
    }

    Node *insert(Node * ptr, int data) {

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

    void insertBST(Node * ptr, int data){

        // TODO : insert 호출 -> checkBalance 호출 -> 트리 회전

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