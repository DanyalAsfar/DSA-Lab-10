// Danyal Asfar
// 552124
// BS-CS-15
// Section D

#include <iostream>
using namespace std;

struct node{
    int data;
    int height;
    node* left;
    node* right;
};

int updateHeight(node* root){
    if (root == nullptr)
        return 0;

    int leftHeight = updateHeight(root -> left);
    int rightHeight = updateHeight(root -> right);

    return 1 + max(leftHeight, rightHeight);
}

int getHeight(node* root){
    if (root == nullptr)
        return 0;
    
    return root -> height;
}

int balanceFactor(node* root){
    if ( root == nullptr )
        return 0;

    return getHeight(root -> left) - getHeight(root -> right);
}

node* rightRotate(node* root){
    node* newRoot = root -> left;
    node* middleSubtree = newRoot -> right;
    root -> left = middleSubtree;
    newRoot -> right = root;

    root -> height  = updateHeight(root);
    newRoot -> height = updateHeight(newRoot);
    return newRoot;
}

node* leftRotate(node* root){
    node* newRoot = root -> right;
    node* middleSubtree = newRoot -> left;
    root -> right = middleSubtree;
    newRoot -> left = root;
    
    root -> height  = updateHeight(root);
    newRoot -> height = updateHeight(newRoot);
    return newRoot;
}

node* addNode(node* root, int value){

    if ( root == nullptr )
        return new node{value, 1, nullptr, nullptr};
    if ( value < root -> data )
        root -> left = addNode(root -> left, value);
    else if ( value > root -> data )
        root -> right = addNode(root -> right, value);
    
    root -> height = updateHeight(root);
    int balance = balanceFactor(root);

    if (balance > 1){ 
        // LL case
        if ( value < root -> left -> data)
            root = rightRotate(root);
        // LR case
        else if ( value > root -> left -> data){
            root -> left = leftRotate(root -> left);
            root = rightRotate(root);
        }
    }

    else if (balance < -1){
        // RR case
        if ( value > root -> right -> data)
            root = leftRotate(root);
        // RL case
        else if ( value < root -> right -> data){
            root -> right = rightRotate(root -> right);
            root = leftRotate(root);
        }
    }
    return root;
}

void verifyBalance(node* root){
    if (root == nullptr)
        return;
    
    cout << root -> data << ": " << balanceFactor(root) << endl;
    verifyBalance(root -> left);
    verifyBalance(root -> right);
}

void inOrder(node* root){
    if (root != nullptr){
        inOrder(root -> left);
        cout << root -> data << endl;
        inOrder( root -> right );
    }
}

void preOrder(node* root){
    if (root != nullptr){
        cout << root -> data << endl;
        preOrder(root -> left);
        preOrder( root -> right );
    }
}

void deleteTree(node* root){
    if (root == nullptr)
        return;
    deleteTree(root -> left);
    deleteTree(root -> right);
    delete root;
}

int main(){
    node* treeA = nullptr;
    node* treeB = nullptr;
    node* treeC = nullptr;
    node* treeD = nullptr;

    treeA = addNode(treeA, 30);
    treeA = addNode(treeA, 20);
    treeA = addNode(treeA, 10);

    treeB = addNode(treeB, 10);
    treeB = addNode(treeB, 20);
    treeB = addNode(treeB, 30);

    treeC = addNode(treeC, 30);
    treeC = addNode(treeC, 10);
    treeC = addNode(treeC, 20);

    treeD = addNode(treeD, 10);
    treeD = addNode(treeD, 30);
    treeD= addNode(treeD, 20);

    cout << "Part a: 30, 20, 10\n";
    cout << "LL Imbalance at 30\nRight Rotation will be done\n";
    cout << "Preorder:\n";
    preOrder(treeA);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(treeA);
    cout << endl;
    cout << "Balance Factors:\n";
    verifyBalance(treeA);
    cout << endl;
    cout << "Final Tree:\n";
    cout << "    20\n";
    cout << "   /  \\\n";
    cout << "  10  30\n\n";
    
    cout << "Part b: 10, 20, 30\n";
    cout << "RR Imbalance at 10\nLeft Rotation will be done\n";
    cout << "Preorder:\n";
    preOrder(treeB);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(treeB);
    cout << endl;
    cout << "Balance Factors:\n";
    verifyBalance(treeB);
    cout << endl;
    cout << "Final Tree:\n";
    cout << "    20\n";
    cout << "   /  \\\n";
    cout << "  10  30\n\n";
    
    cout << "Part c: 30, 10, 20\n";
    cout << "LR Imbalance at 30\nLeft Right Rotation will be done\n";
    cout << "Preorder:\n";
    preOrder(treeC);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(treeC);
    cout << endl;
    cout << "Balance Factors:\n";
    verifyBalance(treeC);
    cout << endl;
    cout << "Final Tree:\n";
    cout << "    20\n";
    cout << "   /  \\\n";
    cout << "  10  30\n\n";

    cout << "Part d: 10, 30, 20\n";
    cout << "RL Imbalance at 10\nRight Left Rotation will be done\n";
    cout << "Preorder:\n";
    preOrder(treeD);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(treeD);
    cout << endl;
    cout << "Balance Factors:\n";
    verifyBalance(treeD);
    cout << endl;
    cout << "Final Tree:\n";
    cout << "    20\n";
    cout << "   /  \\\n";
    cout << "  10  30\n\n";

    deleteTree(treeA);
    deleteTree(treeB);
    deleteTree(treeC);
    deleteTree(treeD);
}

