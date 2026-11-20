// Danyal Asfar
// 552124
// BS-CS-15
// Section D

#include <iostream>
using namespace std;

struct node{
    int data;
    node* left;
    node* right;
};

node* addNode(node* root, int value){

    if ( root == nullptr )
        return new node{value, nullptr, nullptr};
    if ( value < root -> data )
        root -> left = addNode(root -> left, value);
    else if ( value > root -> data )
        root -> right = addNode(root -> right, value);
            
    return root;
}

void traverse(node* root){
    if (root != nullptr){
        traverse(root -> left);
        cout << root -> data << endl;
        traverse( root -> right );
    }
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

void deleteTree(node* root){
    if (root == nullptr)
        return;
    deleteTree(root -> left);
    deleteTree(root -> right);
    delete root;
}

int main(){
    node* root = nullptr;
    cout << "Deleting from Empty Tree\n";
    root = deleteBST(root, 20);

    root = addNode(root, 50);
    cout << "Deleting the Only Node\n";
    cout << "Tree:\n";
    traverse(root);
    root = deleteBST(root, 50);

    cout << "After Deletion:\n";
    traverse(root);
    cout << (root == nullptr ? "Returned nullptr\n" : "Did not return nullptr\n");

    root = addNode(root, 50);
    root = addNode(root, 30);
    root = addNode(root, 70);
    root = addNode(root, 20);
    root = addNode(root, 40);
    root = addNode(root, 60);
    root = addNode(root, 80);
    root = addNode(root, 65);
    cout << "Initial Tree:\n";
    traverse(root);


    cout << "Deleting 20\nCase: Leaf Node Deletion\nNode Will Be Deleted Directly\n";
    root = deleteBST(root, 20);
    traverse(root);
    cout << endl;
    
    cout << "Deleting 60\nCase: One Child Node\nNode Will Be Replaced by That Child (65)\n";
    root = deleteBST(root, 60);
    traverse(root);
    cout << endl;

    cout << "Deleting 50\nCase: Two Child Nodes\nNode Will Be Replaced by Inorder Successor (65)\n";
    root = deleteBST(root, 50);
    traverse(root);
    cout << endl;
    

    cout << "Deleting 100\nCase: Missing Key\nNo Change\n";
    root = deleteBST(root, 100);
    traverse(root);
    cout << endl;

    deleteTree(root);
}