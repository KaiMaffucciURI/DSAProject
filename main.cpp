/*
 * TODO:
 *  Modify insert and search methods - Asher
 *  Generate DOT file to visualize code - Sydney
 *  Create user friendly functions (like the last project) - Ryan
 *  Check again to make it all work/debug - it'll get done in the process, right?
 */

#include <fstream>
#include <iostream>
#include <string>
#include <exception>

#include "dictionary.hpp"

void writeTree(std::ofstream& ofs, LLRBTNode* root)
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
void writeDotFile(std::string file, const LLRBTree& tree)
{
	std::ofstream ofs(file, std::ofstream::trunc);
	if (!ofs.good())
	{
		throw new std::exception("Failed to open file");
	}

	ofs << "digraph G { ";

	writeTree(ofs, tree.getRoot());

	ofs << "}";
	ofs.close();

	return;
}
*/
int main()
{
	LLRBTree t;
	t.insert("BC");
    t.insert("BC");
	t.insert("A");
	t.insert("C");

    t.search("BC");

	//writeDotFile("test.gv", t);

	return 0;
}
