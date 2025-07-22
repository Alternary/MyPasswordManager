#include <iostream>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <json.hpp> //I copy pasted the json.hpp header file from the nlohmann/json project's single_include folder into /usr/include

using namespace std;
using namespace std::filesystem;
using json = nlohmann::json;


// read a JSON file
ifstream inputSaveFile("/home/bruh/k/cpps/i/MyPasswordManager/passwordManager/saveFile.json");
json saveFileJson = json::parse(inputSaveFile);
void writeSaveFileJsonToFile() {
  ofstream outputSaveFile("/home/bruh/k/cpps/i/MyPasswordManager/passwordManager/saveFile.json");
  if (outputSaveFile.is_open()) {
//    outputSaveFile << setw(4) << saveFileJson << endl; // write prettified JSON to file
    outputSaveFile << "{ \"strang\": \"strang0\" }";
    outputSaveFile.close();
  }
  else {
    cout << "Failed to create json file" << endl;
  }
}


json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
float jPi = j["pi"];
//j["strang"] = "strang"; //can't set json values
//would need to convert a json into a dict and then a dict into a json

json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

json j2 = {
  {"pi", 3.141},
  {"happy", true},
};

class Password {
  public: string username;
  public: string password;
  public: string note;
};

Password defaultPassword = Password{"default_username", "default_password", "default_note"};

vector<Password> passwords = {defaultPassword};

// path saveDirectoryPath = ".";
// path saveFilePath = saveDirectoryPath / "password_save.txt";
path saveFilePath = "/home/bruh/Code/cpps/i/MyPasswordManager/passwordManager/password_save.txt";
string encryptedPasswords = "";
//got to use some encryption library to encrypt the password jsons
//perhaps could use a bash command execution command

void saveEncryptedPasswords() {
  ofstream file(saveFilePath);
  if (file.is_open()) {
    cout << "writing to file";
    file << encryptedPasswords;
    //file << "somethang";
    file.close();
  }
  else {
    cerr << "Failed to create file: " << saveFilePath << endl;
  }
}

void loadEncryptedPasswords() {
  ifstream inputFile(saveFilePath);
  encryptedPasswords.clear();
  string line;
  while (getline(inputFile, line)) {
    encryptedPasswords += line + "\n";
  }
}

void showPasswords() {
  for (const auto& password : passwords) {
    cout << "Username: " << password.username << "\nPassword: " << "*****" << "\nNote: " << password.note << endl;
  }
}

void echoInput() {
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag |= ECHO; // Enable echo
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void dontEchoInput() {
  termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

//system("fys running a shell command from c++");

int main() {
  //cout << saveFileJson["strang"];
  saveFileJson = "{ \"strang\": \"strang2\" }"_json;
  writeSaveFileJsonToFile();
  cout << jPi;
  while (true) {
    cout << endl;
    showPasswords();
    cout << "type a number to go to password" << endl;
    string menuInput;
    cin >> menuInput;
    if (isdigit(menuInput[0])) {
      int chosenPasswordIndex = stoi(menuInput);
      if (chosenPasswordIndex >= 0 && chosenPasswordIndex < passwords.size()) {
        string passwordFieldChoice;
        cout << "type 0 to edit username, type 1 to edit password, type 2 to edit note and type 3 to show password): ";
        cin >> passwordFieldChoice;
        if (passwordFieldChoice == "0") {
          cout << "Editing username at index " << chosenPasswordIndex << endl;
          cout << "Enter new username: ";
          string newUsername;
          cin >> newUsername;
          passwords[chosenPasswordIndex].username = newUsername;
        } else if (passwordFieldChoice == "1") {
          dontEchoInput();

          cout << "Editing password at index " << chosenPasswordIndex << endl;
          cout << "Enter new password: ";
          string newPassword;
          cin >> newPassword;
          passwords[chosenPasswordIndex].password = newPassword;

          echoInput();
        } else if (passwordFieldChoice == "2") {
          cout << "Editing note at index " << chosenPasswordIndex << endl;
          cout << "Enter new note: ";
          string newNote;
          cin.ignore(); // Clear the newline character from the input buffer
          getline(cin, newNote);  // Use getline to allow spaces in the note
          passwords[chosenPasswordIndex].note = newNote;
        } else if (passwordFieldChoice == "3") {
          cout << "Username: " << passwords[chosenPasswordIndex].username << endl;
          cout << "Password: " << passwords[chosenPasswordIndex].password << endl;
          cout << "Note: " << passwords[chosenPasswordIndex].note << endl;
        }
      }
    }
  }
  
  cout << "Type password" << endl;
  string strang;
  getline(cin,strang);
  cout << endl << strang << endl;


  encryptedPasswords = "asdh";
  saveEncryptedPasswords();
  encryptedPasswords.clear();
  cout << "Encrypted passwords cleared: " << encryptedPasswords << endl;
  loadEncryptedPasswords();
  cout << "Encrypted passwords loaded: " << encryptedPasswords << endl;
}
