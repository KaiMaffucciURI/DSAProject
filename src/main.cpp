#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <sstream>
#include <algorithm>

#include "dictionary.hpp"

int main()
{
    Dictionary t;

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
            std::cout<<"load [file] - inserts words from text file named [file]"<<std::endl;
            std::cout<<"print [file] - generates a DOT file named [file]"<<std::endl;
            std::cout<<"exit - exits the program and stops runtime"<<std::endl;
        }

        //Inserts words from a text file into the dictionary
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

                    //Ignores spaces and commas and separates words by whitespace
                    while(streamline >> entry){
                        char toremove[] = ",. ";

                        for (int i = 0; i < 3; i++)
                        {
                            entry.erase(std::remove(entry.begin(), entry.end(), toremove[i]), entry.end());
                        }

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
                    std::cout<< word << " was found "<<result<<" time(s)."<<std::endl;
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
                //Making a new file name for the DOT file
                int pos = f_name.find('.');
                std::string dot_name = f_name.substr(0,pos);
                std::string ending = f_name.substr(pos, f_name.length()-pos);
                dot_name += "_dot" + ending;
                t.writeDotFile(dot_name);
                std::cout<<"Dictionary successfully written to '"<<dot_name<<"'."<<std::endl;
                continue;
            }
        }
    }

    return 0;
}
