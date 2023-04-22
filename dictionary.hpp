#pragma once

#include <iostream>
#include <ostream>
#include <string>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the LLRBTree class.
// I.E. LLRBTree is made up of LLRBTNode
struct LLRBTNode
{
    std::pair<std::string, int> data; //Word and then the number of times it appears
    bool red;
    LLRBTNode* left;
    LLRBTNode* right;

    LLRBTNode(std::string word);
    ~LLRBTNode();
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Private version: implement the functions recursively
class LLRBTree
{
private:
    LLRBTNode* _root;

    // helper methods
    LLRBTNode* rotate_left(LLRBTNode *node);
    LLRBTNode* rotate_right(LLRBTNode *node);
    bool is_red(LLRBTNode *node);
    void flip_colors(LLRBTNode *node1, LLRBTNode *node2);

    // tree methods
    LLRBTNode* insert(std::string word, LLRBTNode* root);
    LLRBTNode* remove(std::string word, LLRBTNode* root);
    LLRBTNode* find_ios(LLRBTNode* root, bool& disconnect);
    int height(LLRBTNode* root);

    void preorder(LLRBTNode* root, std::ostream& os);
    void inorder(LLRBTNode* root, std::ostream& os);
    void postorder(LLRBTNode* root, std::ostream& os);

    void destroy(LLRBTNode* root);
    LLRBTNode* search(const std::string&, LLRBTNode* root); // Called by other insert function. Returns node where word is located

public:
    LLRBTree();
    ~LLRBTree();

    void insert(std::string word);
    void remove(std::string word);
    int height();

    void preorder(std::ostream& os = std::cout);
    void inorder(std::ostream& os = std::cout);
    void postorder(std::ostream& os = std::cout);

    int search(const std::string& word); // takes in word, returns how many times it appears (0 if not found)

    LLRBTNode* const getRoot() const { return _root; }
};
