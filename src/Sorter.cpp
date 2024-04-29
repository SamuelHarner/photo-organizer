// Sorter class (possibly to be used sorting operations such as copying files, iterating through folders, etc.)
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <vector>
#include <algorithm>

#include "../include/exif.h"
#include "../include/exif_extraction.h"
#include "../include/Folder.h"
#include "../include/Sorter.h"

using namespace std;

/************************************************************************************
 * THIS BLOCK CONTAINS METHODS FOR ITERATING ON A DIRECTORY (from https://github.com/gautamkmr/lsCpp)
************************************************************************************/

/************************************************************************************

   Name:        compareNode
   Type:        Method
   Description: A method to compare two node objects based on their name
   Return Type: Bool
   Argument:    a: Reference to constant objects of node type
                b: Reference to constant objects of node type
************************************************************************************/
bool Sorter::compareNode(const node &a, const node &b)
{
   int res = a.name.compare(b.name);
   if(res < 0)
     return true;
   else
     return false;
}

/************************************************************************************

  Name:        listDir
  Type:        Method
  Description: A method to list all the subdirectories and files under a 
               given directory 
  Return Type: void
  Argument:    name:      Path to the directory 
               ans:       vector of node objects to store details of files or dir. 
               lastSlash: To avoid redundant '/' in path

************************************************************************************/
void Sorter::listdir(const char *name, vector<node> &ans, bool lastSlash)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    struct tm      *tm;
    time_t rawtime;
 
    if (!(dir = opendir(name))) 
    {   
        cout<<"Couldn't open the file or dir "<<name<<"\n";
        return;
    }
    if (!(entry = readdir(dir)))
    {
        cout<<"Couldn't read the file or dir "<<name<<"\n";
        return;
    }

    do 
    {
        string slash="";
        if(!lastSlash)
          slash = "/";
      
        string parent(name);
        string file(entry->d_name);
        string final = parent + slash + file;
        if(stat(final.c_str(), &statbuf)==-1)
        {
            cout<<"Couldn't get the stat info of file or dir: "<<final<<"\n";
            return;
        }
        tm = localtime(&statbuf.st_mtime);
        unsigned long long time = mktime(tm);

        if (entry->d_type == DT_DIR) //its a directoru
        {
            //skip the . and .. directory
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            struct node tmp;
            tmp.name = final;
            tmp.type = "D";
            tmp.size = 0;
            tmp.time = time;
            ans.push_back(tmp);
            listdir(final.c_str(), ans, false);
        } 
        else //its a file  
        {
            struct node tmp;
            tmp.name = final;
            tmp.type = "F";
            tmp.size = statbuf.st_size;
            tmp.time = time;
            ans.push_back(tmp);
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

/************************************************************************************
 * THIS BLOCK CONTAINS ADAPTED FILECOPYING FUNCTIONS (from "Copier.cpp") [copytest2 branch]
************************************************************************************/
void Sorter::copyFile(const char *inputFilePath, const char *outputFilePath)
{
    ifstream srce(inputFilePath, ios::binary);
    ofstream dest(outputFilePath, ios::binary);
    dest << srce.rdbuf();
}

/************************************************************************************
 * THIS BLOCK CONTAINS NEW FUNCTIONS FOR PURPOSE OF ACCESSING AND COPYING
************************************************************************************/

string Sorter::getNewFilePath(const string& oldFilePath, const string& outputFolderPath) {
  string newFilePath = outputFolderPath + "/" + Folder::findNameFromPath(oldFilePath);
  return newFilePath;
}

void Sorter::copyFileIteration(vector<node> &dirList, const string& outputFolder, string inputFolderPath, string additionalPath) {
  // loop over all nodes (Files and Directories)
  string outPath = inputFolderPath + "/" + additionalPath + "/";
  for (int i = 0; i < dirList.size(); i++)
  {
    // If a File: perform operations necessary for copying it into the correct output directory
    if (dirList[i].type == "F")
    {
      string str = dirList[i].name.c_str();
      str = str.substr(str.length()-5, 5);
      for_each(str.begin(), str.end(), [](char &c) {
        c = tolower(c);
      });
      if (str.substr(1, 4) == ".jpg") {
      }
      else if (str == ".jpeg") {
      }
      else if (str.substr(1, 4) == ".png") {
      }
      else if (str.substr(1, 4) == ".gif") {
      }
      else if (str.substr(1, 4) == ".tif") {
      }
      else if (str == ".tiff") {
      }
      else  {
        continue;
      }
      char *fileName = const_cast<char *>(dirList[i].name.c_str());
      string folderPath = folderDest(fileName, outPath);
      copyFile(dirList[i].name.c_str(), getNewFilePath(dirList[i].name, folderPath).c_str());
    }
  }
}