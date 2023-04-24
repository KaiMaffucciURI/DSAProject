#include "dictionary.hpp"

#include <exception>

// Helper function to easily convert everything to lowercase
// Makes sure words are not repeated in the tree
std::string to_lower(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        str.at(i) = std::tolower(str.at(i));
    }

    return str;
}

/*
 * Node Class Functions
*/

DictionaryNode::DictionaryNode(std::string word){
    this->data.first = word;
    this->data.second = 1;
    this->red = true; // should always start as red
    this->left = nullptr;
    this->right = nullptr;
}

DictionaryNode::~DictionaryNode()= default;

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

// rotate counterclockwise
DictionaryNode* Dictionary::rotate_left(DictionaryNode* node) {

    DictionaryNode* child = node->right;
    DictionaryNode* left_child = child->left;
    child->left = node;
    node->right = left_child;

    return child;
}

// rotate clockwise
DictionaryNode* Dictionary::rotate_right(DictionaryNode* node) {

    DictionaryNode* child = node->left;
    DictionaryNode* right_child = child->right;
    child->right = node;
    node->left = right_child;

    return child;
}

// method that checks whether a given node is red or not
// we need this in case we check a node that doesn't exist
bool Dictionary::is_red(DictionaryNode* node) {

    if (node == nullptr) {
        return false;
    }

    return node->red;
}

// method which swaps the colors of two given nodes
void Dictionary::flip_colors(DictionaryNode* node1, DictionaryNode* node2) {

    bool temp = node1->red;
    node1->red = node2->red;
    node2->red = temp;
}


DictionaryNode* Dictionary::insert(std::string word, DictionaryNode* node){

    if (!node) {
        return new DictionaryNode(word);
    }

    // Go left if data < data at this Node
    if (word < node->data.first) {
        node->left = insert(word, node->left);
        // Go right otherwise
    } else if (word > node->data.first) {
        node->right = insert(word, node->right);
        //If the node already exists, "insert" it as a duplicate
    } else if(word == node->data.first) {
        node->data.second += 1;
        return node;
    }else {
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

DictionaryNode* Dictionary::remove(std::string word, DictionaryNode* root){
    if(!root){
        return nullptr;
    }

    // We found what we're looking for, delete it.
    if(word == root->data.first){
        DictionaryNode* temp;
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

DictionaryNode* Dictionary::find_ios(DictionaryNode* root, bool& disconnect){
    if(!root->left){
        disconnect = true;
        return root;
    }
    DictionaryNode* temp = find_ios(root->left, disconnect);

    if(disconnect){
        root->left = nullptr;
        disconnect = false;
    }

    return temp;
}

int Dictionary::height(DictionaryNode* root){
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

void Dictionary::preorder(DictionaryNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data.first << ":" << root->red << " ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void Dictionary::inorder(DictionaryNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data.first << ":" << root->red << " ";
    this->inorder(root->right, os);

    return;
}

void Dictionary::postorder(DictionaryNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data.first << ":" << root->red << " ";

    return;
}

void Dictionary::destroy(DictionaryNode* root){
    if(!root){
        return;
    }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

DictionaryNode* Dictionary::search(const std::string& word, DictionaryNode* root){
    if(!root){ //If not in the tree at all
        return nullptr;
    }

    if(word == root->data.first){ //If we found the word
        return root; //Returns the root for the other insert function
    }

    if(word < root->data.first){
        return this->search(word, root->left);
    }else{
        return this->search(word, root->right);
    }
}

void Dictionary::writeTree(std::ofstream& ofs, DictionaryNode* root)
{
    if (root == nullptr)
    {
        return;
    }

    ofs << root->data.first << "[label=\"" << root->data.first << ", " << root->data.second << "\"]; ";

    if (root->left != nullptr)
    {
        ofs << root->data.first << " -> " << root->left->data.first << "; ";
    }

    if (root->right != nullptr)
    {
        ofs << root->data.first << " -> " << root->right->data.first << "; ";
    }

    writeTree(ofs, root->left);
    writeTree(ofs, root->right);

    return;
}

/*
 * Public Functions
 * Each calls the related private recursive function
*/

Dictionary::Dictionary(){
    this->_root = nullptr;
}

Dictionary::~Dictionary(){
    delete this->_root;
}

void Dictionary::insert(std::string word){
    this->_root = this->insert(to_lower(word), this->_root);
    this->_root->red = false;
}

void Dictionary::remove(std::string word){
    this->_root = this->remove(to_lower(word), this->_root);
}

int Dictionary::search(const std::string& word){
    DictionaryNode* foundnode = search(to_lower(word), this->_root);
    if (foundnode == nullptr){
        return 0; //Word is not found so it returns 0
    } else {
        return foundnode->data.second; //Returns the count of the found word
    }

}

int Dictionary::height(){
    return this->height(this->_root);
}

void Dictionary::preorder(std::ostream& os){
    this->preorder(this->_root, os);
    os << "\n";
}

void Dictionary::inorder(std::ostream& os){
    this->inorder(this->_root, os);
    os << "\n";
}

void Dictionary::postorder(std::ostream& os){
    this->postorder(this->_root, os);
    os << "\n";
}

void Dictionary::writeDotFile(const std::string& file)
{
    std::ofstream ofs(file, std::ofstream::trunc);
    if (!ofs.good())
    {
        throw;
    }

    ofs << "digraph G { ";

    writeTree(ofs, _root);

    ofs << "}";
    ofs.close();

    return;
}