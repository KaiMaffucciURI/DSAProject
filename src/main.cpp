/*
 * TODO:
 *  Modify insert and search methods - Ashy (note from Kai: I toyed with them a bit, but I'm not sure if everything's done, check)
 *  Generate DOT file to visualize code - Sydney
 *  Create user friendly functions (like the last project) - Ryan
 *  Check again to make it all work/debug - it'll get done in the process, right?
 */

#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <sstream>
#include <algorithm>

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

//Not sure how to handle exceptions; commented it out to debug UI
void writeDotFile(std::string file, const LLRBTree& tree)
{
	std::ofstream ofs(file, std::ofstream::trunc);
	if (!ofs.good())
	{
		//throw new std::exception("Failed to open file");
	}

	ofs << "digraph G { ";

	writeTree(ofs, tree.getRoot());

	ofs << "}";
	ofs.close();

	return;
}

int main()
{
	LLRBTree t;

    std::cout<<"Welcome to the virtual dictionary, please type 'help' for commands."<<std::endl;

    //Loops the program until 'exit' is called
    bool running = true;
    while(running){
        std::cout<<'>';

        //Tokenizes user inputs to read commands
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token){
            tokens.push_back(token);
        }

        if (tokens.size() == 0){
            continue;
        }

        std::transform(tokens.at(0).begin(), tokens.at(0).end(), tokens.at(0).begin(),
                       [](char a) { return std::tolower(a); });

        //Exits the program
        if(tokens[0] == "exit"){
            std::cout<<"Exiting program, goodbye."<<std::endl;
            running = false;
            continue;
        }

        //Prints a full list of all commands and how to use them
        if(tokens[0] == "help"){
            std::cout<<"The following commands are available"<<std::endl;
            std::cout<<"help - prints all possible commands"<<std::endl;
            std::cout<<"insert [word] - inserts [word] into the dictionary"<<std::endl;
            std::cout<<"search [word] - searches how many times [word] is found"<<std::endl;
            std::cout<<"load [file] - inserts words from CSV file named [file]"<<std::endl;
            std::cout<<"print [file] - generates a DOT file named [file]"<<std::endl;
            std::cout<<"exit - exits the program and stops runtime"<<std::endl;
        }

        //Inserts words from a CSV file into the dictionary
        if(tokens[0] == "load"){
            if(tokens.size() != 2){
                std::cout<<"Usage - load [file]"<<std::endl;
                continue;
            }
            else{
                std::string f_name = tokens[1];
                std::string entry;
                std::ifstream table;

                table.open(f_name);

                if(table.fail()){
                    std::cout<<"File cannot be found..."<<std::endl;
                    continue;
                }

                while(std::getline(table, line)){
                    std::stringstream streamline(line);
                    std::string key;

                    while(std::getline(streamline, entry, ',')){
                        t.insert(entry);
                    }
                }
                std::cout<<"Words from '"<<f_name<<"' were successfully inserted into dictionary."<<std::endl;
                table.close();
                continue;
            }
        }

        //Inserts words directly into the dictionary
        if(tokens[0] == "insert"){
            if(tokens.size() != 2){
                std::cout<<"Usage - insert [word]"<<std::endl;
                continue;
            }
            else{
                std::string word = tokens[1];
                t.insert(word);
                std::cout<<"'"<<word<<"' was successfully inserted into dictionary."<<std::endl;
                continue;
            }
        }

        //Searches for a word in the dictionary and prints how many times it was found
        if(tokens[0] == "search"){
            if(tokens.size() != 2){
                std::cout<<"Usage - search [word]"<<std::endl;
                continue;
            }
            else{
                std::string word = tokens[1];
                int result = t.search(word);
                if(result == 0){
                    std::cout<<"Word not found..."<<std::endl;
                    continue;
                }
                else{
                    std::cout<<"Word was found "<<result<<" times."<<std::endl;
                    continue;
                }
            }
        }

        //Prints the dictionary to a file named [file] as a .DOT file
        if(tokens[0] == "print"){
            if(tokens.size() != 2){
                std::cout<<"Usage - print [file]"<<std::endl;
                continue;
            }
            else{
                std::string f_name = tokens[1];
                writeDotFile(f_name, t);
                continue;
            }
        }
    }


	return 0;
}
