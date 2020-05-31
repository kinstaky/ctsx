// directory.h 
//	Data structures to manage a UNIX-like directory of file names.
// 
//      A directory is a table of pairs: <file name, sector #>,
//	giving the name of each file in the directory, and 
//	where to find its file header (the data structure describing
//	where to find the file's data blocks) on disk.
//
//      We assume mutual exclusion is provided by the caller.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "openfile.h"

#define FileNameMaxLen 		9	// for simplicity, we assume 
					// file names are <= 9 characters long

#ifdef LAB5
#include "system.h"

#define FileDirNameMaxLen      18   // max length of direct name
                            // 18 to make the sizeof(DirectoryEntry) == 32
                            // so, store 4 entries in one directory file
#define Success       0
#define FileNotFound  1
#define FileExist     2
#define FileTooLarge  3
#define DirNotEmpty   4
#define NameTooLong   5
#define NotDirectory  6


#endif

// The following class defines a "file name chain", restore the file name
// in the disk with a chain

class FileNameChain {
public:
    int nextSector;         // -1: without next, >=0: next sector to store the name
    char name;
};

// The following class defines a "directory entry", representing a file
// in the directory.  Each entry gives the name of the file, and where
// the file's header is to be found on disk.
//
// Internal data structures kept public so that Directory operations can
// access them directly.

class DirectoryEntry {
public:
    int sector;				// Location on disk to find the 
					//   FileHeader for this file 
#ifdef LAB5
    int nameSector;         // sector for saving the indirect name
    int nameLength;         // length of name

    bool inUse;             // Is this directory entry in use?
    char dirName[FileDirNameMaxLen + 1];   // direct name, +1 for '\0'

#else
    bool inUse;             // Is this directory entry in use?
    char name[FileNameMaxLen + 1];	// Text name for file, with +1 for 
					// the trailing '\0'
#endif
};

// The following class defines a UNIX-like "directory".  Each entry in
// the directory describes a file, and where to find it on disk.
//
// The directory data structure can be stored in memory, or on disk.
// When it is on disk, it is stored as a regular Nachos file.
//
// The constructor initializes a directory structure in memory; the
// FetchFrom/WriteBack operations shuffle the directory information
// from/to disk. 

class Directory {
  public:

    Directory(int size); 		// Initialize an empty directory
					// with space for "size" files
    ~Directory();			// De-allocate the directory

    void FetchFrom(OpenFile *file);  	// Init directory contents from disk
    void WriteBack(OpenFile *file, BitMap *freeMap);	// Write modifications to 
					// directory contents back to disk

    int Find(char *name);		// Find the sector number of the 
					// FileHeader for file: "name"

    int Add(char *name, int newSector, BitMap *freeMap);  // Add a file name into the directory

    int Remove(char *name);		// Remove a file from the directory

    void List(bool Recursive = true);			// Print the names of all the files
					//  in the directory
    void Print(bool Recursive = true);			// Verbose print of the contents
					//  of the directory -- all the file
					//  names and their contents.
#ifdef LAB5
    bool IsEmpty();
    void SetParent(int parent);
#endif

  private:
    int tableSize;			// Number of directory entries
    DirectoryEntry *table;		// Table of pairs: 
					// <file name, file header location> 
    void getFileName(DirectoryEntry *entry, char *name);
    int setFileName(DirectoryEntry *entry, char *name, BitMap *freeMap);


    int FindIndex(char *name);		// Find the index into the directory 
					//  table corresponding to "name"
};

#endif // DIRECTORY_H
