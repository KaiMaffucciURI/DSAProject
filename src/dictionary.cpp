#include "dictionary.h"

/*
 * Node Class Functions
*/

// TODO: account for the fact that 'data' is now a pair of a string and an int

LLRBTNode::LLRBTNode(std::string word){
    this->data.first = word;
    this->data.second = 1;
    this->red = true; // should always start as red
    this->left = nullptr;
    this->right = nullptr;
}

LLRBTNode::~LLRBTNode(){

}

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

// rotate counterclockwise
LLRBTNode* LLRBTree::rotate_left(LLRBTNode* node) {

    LLRBTNode* child = node->right;
    LLRBTNode* left_child = child->left;
    child->left = node;
    node->right = left_child;

    return child;
}

// rotate clockwise
LLRBTNode* LLRBTree::rotate_right(LLRBTNode* node) {

    LLRBTNode* child = node->left;
    LLRBTNode* right_child = child->right;
    child->right = node;
    node->left = right_child;

    return child;
}

// method that checks whether a given node is red or not
// we need this in case we check a node that doesn't exist
bool LLRBTree::is_red(LLRBTNode* node) {

    if (node == nullptr) {
        return false;
    }

    return node->red;
}

// method which swaps the colors of two given nodes
void LLRBTree::flip_colors(LLRBTNode* node1, LLRBTNode* node2) {

    bool temp = node1->red;
    node1->red = node2->red;
    node2->red = temp;
}

// TODO: fix this
LLRBTNode* LLRBTree::insert(std::string word, LLRBTNode* node){

    if (!node) {
        return new LLRBTNode(data);
    }

    // Go left if data < data at this Node
    if (data < node->data) {
        node->left = insert(data, node->left);
        // Go right otherwise
    } else if (data > node->data) {
        node->right = insert(data, node->right);
    } else {
        return node;
    }

    // case 1: right child is red but left child is black or doesn't exist
    if (is_red(node->right) && !is_red(node->left)) {

        // left rotate to make it stay valid
        node = rotate_left(node);

        // swap the colors, as child should be red
        flip_colors(node, node->left);
    }

    // case 2: left child as well as left grandchild is red
    if (is_red(node->left) && is_red(node->left->left)) {

        // right rotate to fix it
        node = rotate_right(node);
        flip_colors(node, node->right);
    }

    // case 3: when both left and right children are red
    if (is_red(node->left) && is_red(node->right)) {

        // flip the colors of the node
        node->red = !(node->red);
        // children must be black
        node->left->red = false;
        node->right->red = false;
    }

    return node;
}

// TODO: fix this (or just comment the whole thing out if we don't get around to implementing it)
LLRBTNode* LLRBTree::remove(std::string word, LLRBTNode* root){
    if(!root){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(data == root->data){
        LLRBTNode* temp;
        // This is a leaf node
        if(root->left == root->right){
            delete root;
            return nullptr;
        }

        // This node has 1 child
        if(!root->left != !root->right){
            // Set temp to whichever child exists
            root->left ? temp = root->left : temp = root->right;

            delete root;
            return temp;
        }

        // This node has 2 children
        // Find the in-order successor
        temp = root->right;

        while(temp->left){
            temp = temp->left;
        }

        // Copy the data to this node and delete the original
        root->data = temp->data;
        root->right = remove(temp->data, root->right);
        return root;
    }

    // This is not the Node we're looking for, recursively find the data we want to delete
    if(data < root->data){
        root->left = remove(data, root->left);
    }else{
        root->right = remove(data, root->right);
    }

    return root;
}

LLRBTNode* LLRBTree::find_ios(LLRBTNode* root, bool& disconnect){
    if(!root->left){
        disconnect = true;
        return root;
    }
    LLRBTNode* temp = find_ios(root->left, disconnect);

    if(disconnect){
        root->left = nullptr;
        disconnect = false;
    }

    return temp;
}

int LLRBTree::height(LLRBTNode* root){
    if(!root){
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

// TODO: fix traversal functions

void LLRBTree::preorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

// modified traversals that print in format value:color

void LLRBTree::inorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ":" << root->red << " ";

    return;
}

void LLRBTree::destroy(LLRBTNode* root){
    if(!root){
        return;
    }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

// TODO: fix this
int LLRBTree::search(std::string word, LLRBTNode* root){
    if(!root){
        return false;
    }

    if(data == root->data){
        return true;
    }

    if(data < root->data){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
    }
}

/*
 * Public Functions
*/

LLRBTree::LLRBTree(){
    this->_root = nullptr;
}

LLRBTree::~LLRBTree(){
    delete this->_root;
}

// TODO: fix public functions
void LLRBTree::insert(std::string word){
    this->_root = this->insert(word, this->_root);
    this->_root->red = false;
}

void LLRBTree::remove(std::string word){
    this->_root = this->remove(word, this->_root);
}

int LLRBTree::height(){
    return this->height(this->_root);
}

void LLRBTree::preorder(std::ostream& os){
    this->preorder(this->_root, os);
    os << "\n";
}

void LLRBTree::inorder(std::ostream& os){
    this->inorder(this->_root, os);
    os << "\n";
}

void LLRBTree::postorder(std::ostream& os){
    this->postorder(this->_root, os);
    os << "\n";
}

bool LLRBTree::search(std::string word){
    return this->search(word, this->_root);
}