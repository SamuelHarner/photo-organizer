#ifndef EXIF_EXTRACTION_H
#define EXIF_EXTRACTION_H

#include <string>

using namespace std;

// jpegreader.cpp
string dateToString(char *argv);

// exif_extract_selection.cpp
string getExifDay(string exifstring);

string getExifMonth(string exifstring);

string getExifYear(string exifstring);

string getMonthString(string exifstring);

string folderDest(string fileName, string destination);

#endif