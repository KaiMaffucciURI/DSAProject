#pragma once

#include <iostream>
#include <fstream>
#include <string>

// Defines MAX
// When used, MAX(a,b) will be replaced with ((a > b) ? a : b)
#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

// Underlying class which will be used to implement the Dictionary class.
// I.E. Dictionary is made up of DictionaryNode
struct DictionaryNode
{
    std::pair<std::string, int> data;
    bool red;
    DictionaryNode* left;
    DictionaryNode* right;

    DictionaryNode(std::string word);
    ~DictionaryNode();
};

// Public versions: accept a single parameter so the usage of the class is neat.
// Only the public versions return anything to main
// Private version: implement the functions recursively
// Private versions returns the base case to the related public version
class Dictionary
{
private:
    DictionaryNode* _root;

    // helper methods
    DictionaryNode* rotate_left(DictionaryNode *node);
    DictionaryNode* rotate_right(DictionaryNode *node);
    bool is_red(DictionaryNode *node);
    void flip_colors(DictionaryNode *node1, DictionaryNode *node2);

    // tree methods
    DictionaryNode* insert(std::string word, DictionaryNode* root);
    DictionaryNode* remove(std::string word, DictionaryNode* root);
    DictionaryNode* find_ios(DictionaryNode* root, bool& disconnect);
    int height(DictionaryNode* root);

    void preorder(DictionaryNode* root, std::ostream& os);
    void inorder(DictionaryNode* root, std::ostream& os);
    void postorder(DictionaryNode* root, std::ostream& os);

    void destroy(DictionaryNode* root);
    DictionaryNode* search(const std::string&, DictionaryNode* root);
    void writeTree(std::ofstream& ofs, DictionaryNode* root);

public:
    Dictionary();
    ~Dictionary();

    void insert(std::string word);
    void remove(std::string word);
    int height();

    void preorder(std::ostream& os = std::cout);
    void inorder(std::ostream& os = std::cout);
    void postorder(std::ostream& os = std::cout);

    int search(const std::string& word);

    void writeDotFile(const std::string& file);
};