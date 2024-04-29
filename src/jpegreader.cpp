#include <iostream>
#include <stdio.h>
#include <string>
#include "../include/exif.h"
#include "../include/exif_extraction.h"

using namespace std;

string dateToString(char *argv)
{
    // Read the JPEG file into a buffer
    FILE *fp = fopen(argv, "rb");
    if (!fp)
    {
        return "Can't open file.\n";
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize)
    {
        delete[] buf;
        return "Can't read file.\n";
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code)
    {   
        return "Error parsing EXIF: code %d\n";
    }
    return result.DateTime.c_str();
}
