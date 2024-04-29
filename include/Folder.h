#ifndef FOLDER_H
#define FOLDER_H

#include <cstring>
#include <string> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <map>

using namespace std;

class Folder {
private:
    string name;
    string path;
    
public:    
    Folder();
    Folder(string folderPath);
    Folder(string folderName, string parentFolderPath);
    Folder(string folderPath, int noOutputArg);

    string getType();
    string getName();
    string getPath();
    string findNameFromPath();
    static string findNameFromPath(string p);
    static string directoryRootString(string path);

};

#endif // FOLDER_H