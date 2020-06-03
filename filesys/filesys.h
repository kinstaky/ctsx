// filesys.h 
//	Data structures to represent the Nachos file system.
//
//	A file system is a set of files stored on disk, organized
//	into directories.  Operations on the file system have to
//	do with "naming" -- creating, opening, and deleting files,
//	given a textual file name.  Operations on an individual
//	"open" file (read, write, close) are to be found in the OpenFile
//	class (openfile.h).
//
//	We define two separate implementations of the file system. 
//	The "STUB" version just re-defines the Nachos file system 
//	operations as operations on the native UNIX file system on the machine
//	running the Nachos simulation.  This is provided in case the
//	multiprogramming and virtual memory assignments (which make use
//	of the file system) are done before the file system assignment.
//
//	The other version is a "real" file system, built on top of 
//	a disk simulator.  The disk is simulated using the native UNIX 
//	file system (in a file named "DISK"). 
//
//	In the "real" implementation, there are two key data structures used 
//	in the file system.  There is a single "root" directory, listing
//	all of the files in the file system; unlike UNIX, the baseline
//	system does not provide a hierarchical directory structure.  
//	In addition, there is a bitmap for allocating
//	disk sectors.  Both the root directory and the bitmap are themselves
//	stored as files in the Nachos file system -- this causes an interesting
//	bootstrap problem when the simulated disk is initialized. 
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef FS_H
#define FS_H

#include "copyright.h"
#include "openfile.h"


#ifdef FILESYS_STUB 		// Temporarily implement file system calls as 
				// calls to UNIX, until the real file system
				// implementation is available

class FileSystem {
  public:
    FileSystem(bool format) {}

    bool Create(char *name, int initialSize) { 
  int fileDescriptor = OpenForWrite(name);

  if (fileDescriptor == -1) return FALSE;
  Close(fileDescriptor); 
  return TRUE; 
  }

    OpenFile* Open(char *name) {
    int fileDescriptor = OpenForReadWrite(name, FALSE);

    if (fileDescriptor == -1) return NULL;
    return new OpenFile(fileDescriptor);
      }

    bool Remove(char *name) { return Unlink(name) == 0; }

};

#else // FILESYS


struct FileTable {
    int sector;
    int inUse;
    int num;
    OpenFile *file;
};

#define MAXFILEOPEN   16

#define Success       0
#define FileNotFound  1
#define FileExist     2
#define FileTooLarge  3
#define DirNotEmpty   4
#define NameTooLong   5
#define NotDirectory  6
#define FileOpened    7


class FileSystem {
public:
    FileSystem(bool format);		// Initialize the file system.
					// Must be called *after* "synchDisk" 
					// has been initialized.
    					// If "format", there is nothing on
					// the disk, so initialize the directory
    					// and the bitmap of free blocks.

    int Create(char *name, int initialSize);  	
					// Create a file (UNIX creat)

    OpenFile* Open(char *name); 	// Open a file (UNIX open)

    int Remove(char *name);  		// Delete a file (UNIX unlink)

    void List();			// List all the files in the file system

    void Print();			// List all the files and their contents

#ifdef LAB5
    OpenFile *Open(char *name, int dirSector);
    int Close(OpenFile *file);
    int Create(char *name, int initialSize, int dirSector);
    int CreateDir(char *name);
    int CreateDir(char *name, int dirSector);
    int Remove(char *name, int dirSector);
    int RemoveDir(char *name, int dirSector);
    int RemoveDir(char *name);
    int namex(char *name, char *&fileName);
#endif

#ifdef LAB6
    int OpenID(char *name);
    void WriteID(char *buffer, int size, int index);
    int ReadID(char *buffer, int size, int index);
    void CloseID(int index);
    void PrintID(int index);  // for debug
#endif

private:
   OpenFile* freeMapFile;		// Bit map of free disk blocks,
					// represented as a file
   OpenFile* directoryFile;		// "Root" directory -- list of 
					// file names, represented as a file
#ifdef LAB5
   FileTable fileTable[MAXFILEOPEN];
#endif
};

#endif // FILESYS

#endif // FS_H
