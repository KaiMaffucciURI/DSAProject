#include "dictionary.h"

// helper function to easily convert everything to lowercase
std::string to_lower(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

/*
 * Node Class Functions
*/

LLRBTNode::LLRBTNode(std::string word){
    this->data.first = word;
    this->data.second = 1;
    this->red = true; // should always start as red
    this->left = nullptr;
    this->right = nullptr;
}

LLRBTNode::~LLRBTNode()= default;

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


LLRBTNode* LLRBTree::insert(std::string word, LLRBTNode* node){

    if (!node) {
        return new LLRBTNode(word);
    }

    // Go left if data < data at this Node
    if (word < node->data.first) {
        node->left = insert(word, node->left);
        // Go right otherwise
    } else if (word > node->data.first) {
        node->right = insert(word, node->right);
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

LLRBTNode* LLRBTree::remove(std::string word, LLRBTNode* root){
    if(!root){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(word == root->data.first){
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
        root->right = remove(temp->data.first, root->right);
        return root;
    }

    // This is not the Node we're looking for, recursively find the data we want to delete
    if(word < root->data.first){
        root->left = remove(word, root->left);
    }else{
        root->right = remove(word, root->right);
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

// modified traversals that print in format value:color
// I made it so that it doesn't make any compiler errors,
// but these funcs aren't super useful to us right now,
// although they could be if the user wanted to print out all values in the tree,
// so I'll leave this here like this for now

void LLRBTree::preorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data.first << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void LLRBTree::inorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data.first << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void LLRBTree::postorder(LLRBTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data.first << ":" << root->red << " ";

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

int LLRBTree::search(const std::string& word, LLRBTNode* root){
    if(!root){
        return false;
    }

    if(word == root->data.first){
        return true;
    }

    if(word < root->data.first){
        return this->search(word, root->left);
    }else{
        return this->search(word, root->right);
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

void LLRBTree::insert(std::string word){
    this->_root = this->insert(to_lower(word), this->_root);
    this->_root->red = false;
}

void LLRBTree::remove(std::string word){
    this->_root = this->remove(to_lower(word), this->_root);
}

int LLRBTree::search(const std::string& word){
    return this->search(to_lower(word), this->_root);
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

