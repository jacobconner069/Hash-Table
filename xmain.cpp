#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "passserver.h"

using namespace std;

string getInput(){
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    string input;
    getline(cin, input);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    cout << endl;
    return input;
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main(){
    size_t size;
    cout << "Enter preferred hash table capacity: ";
    cin >> size;
    PassServer ps(size);
    char choice;
    do{
        Menu();
        cin >> choice;
        cin.ignore();
        switch(choice){
            case 'l':{
                string filename;
                cout << "Enter password file name to load from: ";
                cin >> filename;
                if(ps.load(filename.c_str())){
                    cout << "File loaded successfully!" << endl;
                } else {
                    cout << "Error loading file!" << endl;
                }
                break;
            }
            case 'a':{
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cin.ignore();
                cout << "Enter password: ";
                password = getInput();
                pair<string, string> kv(username, password);
                if(ps.addUser(kv)){
                    cout << "User added successfully!" << endl;
                } else {
                    cout << "Error adding user!" << endl;
                }
                break;
            }
            case 'r':{
                string username;
                cout << "Enter username to remove: ";
                cin >> username;
                if(ps.removeUser(username)){
                    cout << "User removed successfully!" << endl;
                } else {
                    cout << "Error removing user!" << endl;
                }
                break;
            }
            case 'c':{
                string username, oldPassword, newPassword;
                cout << "Enter username: ";
                cin >> username;
                cin.ignore();
                cout << "Enter old password: ";
                oldPassword = getInput();
                cout << "Enter new password: ";
                newPassword = getInput();
                pair<string, string> p(username, oldPassword);
                if(ps.changePassword(p, newPassword)){
                    cout << "Password changed successfully!" << endl;
                } else {
                    cout << "Error changing password!" << endl;
                }
                break;
            }
            case 'f':{
                string username;
                cout << "Enter username to find: ";
                cin >> username;
                if(ps.find(username)){
                    cout << "User found!" << endl;
                } else {
                    cout << "User not found!" << endl;
                }
                break;
            }
            case 'd':{
                ps.dump();
                break;
            }
            case 's':{
                cout << "HashTable size: " << ps.size() << endl;
                break;
            }
            case 'w':{
                string filename;
                cout << "Enter password file name to write to: ";
                cin >> filename;
                if(ps.write_to_file(filename.c_str())){
                    cout << "File written successfully!" << endl;
                } else {
                    cout << "Error writing to file!" << endl;
                }
                break;
            }
            default:{
                if(choice != 'x'){
                    cout << "Invalid choice! Please try again." << endl;
                }
                break;
            }
        }
    }
    while(choice != 'x');
        return 0;
}
