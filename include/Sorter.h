#ifndef SORTER_H
#define SORTER_H

#include <string>

class Sorter {

public:    
    /************************************************************************************ 
    Name:        node
    Type:        Structure
    Description: A structure to store files or directory information
    Fields:      name: name of the file or directory
                    type: "F" for file and "D" for directory
                    size: size of the file, 0 for directory
                    time: last modified time in unix format               
    ************************************************************************************/
    struct node
    {
        string name;   
        string type; 
        unsigned long long size;
        unsigned long long time;
    };
    
    static bool compareNode(const node &a, const node &b);
    static void listdir(const char *name, vector<node> &ans, bool lastSlash);
    static void copyFile(const char *inputFilePath, const char *outputFilePath);
    static string getNewFilePath(const string& oldFilePath, const string& outputFolderPath);
    static void copyFileIteration(vector<node> &dirList, const string& outputFolder, string inputFolderPath, string outputFolderName);

};


#endif // SORTER_H