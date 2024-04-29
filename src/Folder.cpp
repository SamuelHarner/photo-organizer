// Folder class
#include <cstring>
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <map>

#include "../include/Folder.h"
using namespace std; 
  
Folder::Folder() {
    string noName = "unnamed_folder";

    // Create directory in filesystem
    if (mkdir(noName.c_str(), 0777) == -1) {
        cerr << "Error :  " << strerror(errno) << endl; 
    }

    else {
        name = noName;
        path = "noPath";
        cout << "Folder created: " << name << endl; 
    }
}

Folder::Folder(string folderPath) {
    string folderName = findNameFromPath(folderPath);

        // Create directory in filesystem
        if (mkdir(folderPath.c_str(), 0777) == -1)
    {
        cerr << "Error :  " << strerror(errno) << endl;
    }

    else {
        this->name = folderName;
        this->path = folderPath;
        cout << "Folder created: " << name << endl; 
    }
}

Folder::Folder(string folderName, string parentFolderPath) {
    string folderPath = parentFolderPath + "/" + folderName;

        // Create directory in filesystem
        if (mkdir(folderPath.c_str(), 0777) == -1)
    {
        cerr << "Error :  " << strerror(errno) << endl;
    }

    else {
        this->name = folderName;
        this->path = folderPath;
        cout << "Folder created: " << name << endl; 
    }
}

// Constructor for creating virtual folder without creating actual directory (mainly for testing purposes)
Folder::Folder(string folderPath, int noOutputArg) {
    if (noOutputArg == 0) {
        this->path = folderPath; 
        this->name = this->findNameFromPath();

        cout << "Virtual folder created: " << name << endl;
    }

    else {
        cout << "Wrong use of this constructor" << endl; 
    }
    
}

// Find the name of an existing Folder from its folderpath
string Folder::findNameFromPath() {
    char sep = '/';
    cout << path.length() << endl;
   size_t i = path.rfind(sep, path.length());
   if (i != string::npos) {
      return(path.substr(i+1, path.length() - i));
   }

   return("");
}

string Folder::getType() {
    return "Folder";
}

string Folder::getName() {
    return name;
}

string Folder::getPath() {
    return path;
}

// Static helper function for determining name before a Folder is created
string Folder::findNameFromPath(string p) {
    char sep = '/';
    size_t i = p.rfind(sep, p.length());
    if (i != string::npos) {
        if ((p.substr(i+1, p.length() - i)).empty()) {
            size_t i = p.rfind(sep, p.length()-2);
            return (p.substr(i + 1, p.length() - i));
        }
        return(p.substr(i+1, p.length() - i));
    }

    return("");
}

string Folder::directoryRootString(string path) {
    string rootString = "";
    const size_t last_slash_idx = path.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        rootString = path.substr(0, last_slash_idx);
    }
    return rootString;
}