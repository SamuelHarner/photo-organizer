CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -std=gnu++1z 

all: photo_sort

exif.o: exif.cpp 
	$(CXX) $(CXXFLAGS) -c exif.cpp 

exif_extract_selection.o: exif_extract_selection.cpp
	$(CXX) $(CXXFLAGS) -c exif_extract_selection.cpp 

jpegreader.o: jpegreader.cpp
	$(CXX) $(CXXFLAGS) -c jpegreader.cpp 

Folder.o: Folder.cpp
	$(CXX) $(CXXFLAGS) -c Folder.cpp

PhotoApp.o: PhotoApp.cpp
	$(CXX) $(CXXFLAGS) -c PhotoApp.cpp

Sorter.o: Sorter.cpp
	$(CXX) $(CXXFLAGS) -c Sorter.cpp

photo_sort: Sorter.o PhotoApp.o Folder.o exif_extract_selection.o jpegreader.o exif.o
	$(CXX) $(CXXFLAGS) -o photo_sort Sorter.o PhotoApp.o Folder.o exif_extract_selection.o jpegreader.o exif.o

clean:
	rm -f *.o  photo_sort photo_sort.exe