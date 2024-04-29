#include <iostream>
#include <unordered_map>
#include "../include/exif_extraction.h"
#include "../include/Folder.h"

typedef unordered_map<string, string> month;
typedef unordered_map<string, month> year;
year date;

string getExifDay(string exifstring)    {
    return exifstring.substr(8, 2);
}

string getExifMonth(string exifstring)    {
    return exifstring.substr(5, 2);
}

string getExifYear(string exifstring)   {
    return exifstring.substr(0, 4);
}

string getMonthString(string exifstring)
{
    unordered_map<string, string> month = {
        {"01", "1-January"},
        {"02", "2-February"},
        {"03", "3-March"},
        {"04", "4-April"},
        {"05", "5-May"},
        {"06", "6-June"},
        {"07", "7-July"},
        {"08", "8-August"},
        {"09", "9-September"},
        {"10", "10-October"},
        {"11", "11-November"},
        {"12", "12-December"},
    };
    return month.find(exifstring)->second;
}

string folderDest(string fileName, string destination)
{
    string exifstring;
    char *fileArray = const_cast<char *>(fileName.c_str());
    exifstring = dateToString(fileArray);

    if(exifstring.substr(0, 5) == "Error" || exifstring.empty())  {
        if  (date["NaN"]["NaN"].empty())    {
            date["NaN"]["NaN"] = destination + "Missing Date/";
            Folder outputFolder{"Missing Date", destination};
        }
        return date["NaN"]["NaN"];
    }
    if (date[getExifYear(exifstring)].empty()) {
        /*  Create year-folder  */
        Folder outputFolder{getExifYear(exifstring), destination};
    }
    if (date[getExifYear(exifstring)][getExifMonth(exifstring)].empty()) {
        /* Create month folder within the year folder */
        Folder outputFolder{getMonthString(getExifMonth(exifstring)), destination + getExifYear(exifstring) + "/"};
        date[getExifYear(exifstring)][getExifMonth(exifstring)] = destination + getExifYear(exifstring) + "/" + getMonthString(getExifMonth(exifstring));
    }   

    /* Get folder destination / return folder destination */
    return date[getExifYear(exifstring)][getExifMonth(exifstring)];
}
