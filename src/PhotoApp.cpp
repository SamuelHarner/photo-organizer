#include <cstring>
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <string.h>
#include <vector>

#include "../include/exif.h"
#include "../include/exif_extraction.h"
#include "../include/Folder.h"
#include "../include/Sorter.h"
using namespace std; 
  

int main()   
{
    // Recieve input folder from user
    string inputFolderPath;
    cout << "Provide the path of the input folder:" << endl;
    getline (cin, inputFolderPath);

    // Define specifications for output folder
    string outputFolderName = "Sorted--" + Folder::findNameFromPath(inputFolderPath);

    // directoryRoot is used to create outputFolder in same directory as inputFolder (directoryRoot will be assigned as inputFolderPath without the name of the inputFolder)
    string directoryRoot = Folder::directoryRootString(inputFolderPath); 
    
    // Create output folder
    Folder outputFolder {outputFolderName, directoryRoot};

    //create vector to store all existing files and directories as nodes
    vector<Sorter::node> ans;
    
    bool lastSlash = false;

    //check the last slash if any to avoid redundant "/"
    if(inputFolderPath.c_str()[strlen(inputFolderPath.c_str())-1]=='/')
      lastSlash = true;

    //store all the files and subdirectories in vector
    Sorter::listdir(inputFolderPath.c_str(), ans, lastSlash);

    //go through all nodes and copy all files
    Sorter::copyFileIteration(ans, outputFolder.getPath(), directoryRoot, outputFolderName);

    cout << "\nFinished!" << endl;

    return 0;
}

