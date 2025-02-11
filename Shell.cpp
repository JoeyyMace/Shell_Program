#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void parse_args(string line, vector<string> &cmds){
    stringstream liness(line);
 
    string token;
    while (getline(liness, token, ' ')) {
        cmds.push_back(token);
    }
}

void add_pid_history(vector<string>& history, size_t max_size = 5, int pid) {
    if (history.size() >= max_size) {
        history.erase(history.begin());
    }
    history.push_back(pid);
}

void print_history(vector<string>& history) {
    for (const auto& pid : history)
            std::cout << pid << endl;
        std::cout << std::endl;
}

int main(void)
{
    int argc = 0;
    vector<std::string> history;

    while (1)
    {
        // prompt
        cout << "JM9853s";

        string cmd;
        getline(cin, cmd);

        // ignore empty input
        if (cmd == "" || cmd.size() == 0) 
            continue;

        cout <<"Received user commands: ";
        cout << cmd << endl;
        
        // built-in: exit
        if (cmd == "help"){
            cout << "//*********************************************************
                     //
                     // <JOSEPH MACE>
                     // CSC360/660 Operating Systems
                     // Project #2: My Shell - Writing Your Own Shell
                     // This shell supports the following commands: help, exit, history
                     //
                     //*********************************************************\n";
                     continue;
        } else if (cmd == "exit"){
            exit(0);
        } else if (cmd == "history") {
            print_history(history)
        }

        vector<string> cmd_args;
        parse_args(cmd, cmd_args);

        // fork child and execute program
        int pid = fork();
        int status;
        if (pid == 0) //this is the child
        {
            add_pid_history(history, 5, getpid());
            char * argv[4] = {"ls", "-l", "-a", NULL};
            execvp(argv[0], argv);
            
        }
        else //this is the parent
        {
            // wait for program to finish and print exit status
            waitpid(pid, &status, 0);
        }
    }
}
