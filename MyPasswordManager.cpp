#include <iostream>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace std::filesystem;

class Password {
  private: string username;
  private: string password;
  private: string note;
};

vector<Password> passwords;

path saveDirectoryPath = ".";
path saveFilePath = saveDirectoryPath / "password_save.txt";
string encryptedPasswords = "";
//got to use some encryption library to encrypt the password jsons

void saveEncryptedPasswords() {
  ofstream file(saveFilePath);
  if (file.is_open()) {
    file << encryptedPasswords;
    file.close();

  }
  else {
    cerr << "Failed to create file: " << saveFilePath
              << endl;
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


int main() {

}