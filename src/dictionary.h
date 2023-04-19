#pragma once

#include <iostream>
#include <ostream>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the LLRBTree class.
// I.E. LLRBTree is made up of LLRBTNode
class LLRBTNode
{
private:
    std::pair<std::string, int> data;
    bool red;
    LLRBTNode* left;
    LLRBTNode* right;

public:
    LLRBTNode(std::string word);
    ~LLRBTNode();

    friend class LLRBTree;
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
    int search(const std::string&, LLRBTNode* root); // takes in word, returns how many times it appears (0 if not found)

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
};