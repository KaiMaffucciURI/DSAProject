# DSAProject
Left-Leaning Red-Black Binary Search Trees as a Dictionary

# Compilation
The primary version of C++ that this program was compiled and tested on was C++ 11, so for stable results, also compile using C++ 11. Other versions of C++ may work, but their safety and stability is not guarenteed. Open the terminal and enter the follwing command to generate executable ```./dictionary``` with g++:

```g++ src/main.cpp src/dictionary.cpp -o dictionary -std=c++11```

This of course requires g++ to be installed on your machine: if you would like to use another compiler with the same parameters feel free, but understand that you may have to do tweaking to make it fit what you choose. 

In the same directory as the ```./dictionary``` executable, include any text files containing words that the user wishes to include in their dictionary. The words in the text files are separated by whitespace only. Characters ',' and '.' will be ignored during runtime.

# Runtime
During runtime, the user will be greeted with a message and prompt to type ```help``` in the event that they do not already know the commands of the program. The following commands are as listed below:

```help``` - prints all possible commands

```insert [word]``` - inserts ```[word]``` into the dictionary

```search [word]``` - searches how many times ```[word]``` is found

```load [file]``` - inserts words from text file named ```[file]```

```print [file]``` - generates a DOT file named ```[file]```

```exit``` - exits the program and stops runtime

Incorrect usage of any commands will prompt the user with the correct format on how to properly use the attempted command.

# Demonstration

Given a dataset of words "sample.txt" as displayed:

![sampletxt](https://user-images.githubusercontent.com/114709842/233872110-6f828b4e-f071-4756-8bd6-9c740c9a0cde.PNG)

Compling and executing the program will look like the following:
![output1](https://user-images.githubusercontent.com/114709842/233872154-52d9f03e-c908-4ba0-a092-5be7a3b438f6.PNG)

With a resulting .DOT file that when put into a visualizer, will look as such:
![dot1](https://user-images.githubusercontent.com/114709842/233872216-3565fbb3-0e9f-4bd0-82ea-477e1c6638e1.PNG)

Invoking the ```insert``` and ```search``` commands on the prior "sample.txt" will produce results as dictated, creating a new node for new words, adding to an pre-existing word's copy count, and returning the copy count of a word in the dictionary.
![output2](https://user-images.githubusercontent.com/114709842/234020859-1a12d308-d8e5-43be-969b-b190b6345cf4.PNG)

Of course, the resulting .DOT output will correspond to changes made to the dictionary through ```insert``` calls:
![dot2](https://user-images.githubusercontent.com/114709842/234021760-9c922059-ab59-4217-bcfa-36a8f830dc5c.PNG)


