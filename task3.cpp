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

node* inorderSuccessor(node* deletionNode){
    node* successor = deletionNode -> right;

    while (successor -> left != nullptr){
        successor = successor -> left;
    }

    return successor;
}

node* deleteBST( node* root, int value ){
    if (root == nullptr)
        return root;

    if (value < root -> data)
        root -> left = deleteBST(root -> left, value);
    else if (value > root -> data)
        root -> right = deleteBST(root -> right, value);
    else{
        if (root -> left == nullptr){
            if (root -> right == nullptr){
                delete root;
                return nullptr;
            }

            // reaching here means there is a child on the right
            node* child = root -> right;
            delete root;
            return child;
        }

        if (root -> right == nullptr){
            node* child = root -> left;
            delete root;
            return child;
        }

        // reaching here means two children
        node* successor = inorderSuccessor(root);

        root -> data = successor -> data;
        root -> right = deleteBST(root -> right, successor -> data);

        
    }

    //value not found
    return root;
}

node* deleteAVL(node* root, int value){
    if (root == nullptr)
        return root;

    if (value < root -> data)
        root -> left = deleteAVL(root -> left, value);
    else if (value > root -> data)
        root -> right = deleteAVL(root -> right, value);
    else{
        if (root -> left == nullptr){
            if (root -> right == nullptr){
                delete root;
                return nullptr;
            }

            // reaching here means there is a child on the right
            node* child = root -> right;
            delete root;
            return child;
        }

        if (root -> right == nullptr){
            node* child = root -> left;
            delete root;
            return child;
        }

        // reaching here means two children
        node* successor = inorderSuccessor(root);

        root -> data = successor -> data;
        root -> right = deleteAVL(root -> right, successor -> data);
    }
    root -> height = updateHeight(root);
    int balance = balanceFactor(root);

    if ( balance > 1 ){
        // LL Case
        if ( balanceFactor(root -> left) >= 0 )
            root = rightRotate(root);
        // LR Case
        else if ( balanceFactor(root -> left) < 0){
            root -> left = leftRotate(root -> left);
            root = rightRotate(root);
        }
    }
    else if ( balance < -1){
        // RR case
        if (balanceFactor(root -> right) <= 0)
            root = leftRotate(root);
        // RL case
        else if (balanceFactor(root -> right) > 0){
            root -> right = rightRotate(root-> right);
            root = leftRotate(root);
        }
    }

    return root;
}

void verifyBalance(node* root){
    if (root == nullptr)
        return;

    cout << "Key: " << root -> data
         << ", Height: " << getHeight(root)
         << ", BF: " << balanceFactor(root) << endl;
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
    node* root = nullptr;

    root = addNode(root, 30);
    root = addNode(root, 20);
    root = addNode(root, 40);
    root = addNode(root, 10);
    root = addNode(root, 25);
    root = addNode(root, 50);
    root = addNode(root, 5);

    cout << "After Inserting: 30, 20, 40, 10, 25, 50, 5\n";
    cout << "No unbalanced ancestor\nNo rotation needed\n";
    cout << "Tree:\n";
    cout << "        30\n";
    cout << "       /  \\\n";
    cout << "     20    40\n";
    cout << "    /  \\     \\\n";
    cout << "  10    25    50\n";
    cout << " /\n";
    cout << "5\n\n";
    cout << "Preorder:\n";
    preOrder(root);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(root);
    cout << endl;
    cout << "Key, Height, and Balance Factors:\n";
    verifyBalance(root);
    cout << endl;

    root = deleteAVL(root, 50);

    cout << "After Deleting: 50\n";
    cout << "Unbalanced ancestor at 30\nLL Imbalance -> Right Rotation will be done\n";
    cout << "Tree:\n";
    cout << "      20\n";
    cout << "     /  \\\n";
    cout << "   10    30\n";
    cout << "  /     /  \\\n";
    cout << " 5     25   40\n\n";
    cout << "Preorder:\n";
    preOrder(root);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(root);
    cout << endl;
    cout << "Key, Height, and Balance Factors:\n";
    verifyBalance(root);
    cout << endl;

    root = deleteAVL(root, 40);

    cout << "After Deleting: 40\n";
    cout << "No unbalanced ancestor\nNo rotation needed\n";
    cout << "Tree:\n";
    cout << "      20\n";
    cout << "     /  \\\n";
    cout << "   10    30\n";
    cout << "  /     /\n";
    cout << " 5     25\n\n";
    cout << "Preorder:\n";
    preOrder(root);
    cout << endl;
    cout << "InOrder:\n";
    inOrder(root);
    cout << endl;
    cout << "Key, Height, and Balance Factors:\n";
    verifyBalance(root);
    cout << endl;

    deleteTree(root);
    root = nullptr;
}

