// filesys.cc
//	Routines to manage the overall operation of the file system.
//	Implements routines to map from textual file names to files.
//
//	Each file in the file system has:
//	   A file header, stored in a sector on disk
//		(the size of the file header data structure is arranged
//		to be precisely the size of 1 disk sector)
//	   A number of data blocks
//	   An entry in the file system directory
//
// 	The file system consists of several data structures:
//	   A bitmap of free disk sectors (cf. bitmap.h)
//	   A directory of file names and file headers
//
//      Both the bitmap and the directory are represented as normal
//	files.  Their file headers are located in specific sectors
//	(sector 0 and sector 1), so that the file system can find them
//	on bootup.
//
//	The file system assumes that the bitmap and directory files are
//	kept "open" continuously while Nachos is running.
//
//	For those operations (such as Create, Remove) that modify the
//	directory and/or bitmap, if the operation succeeds, the changes
//	are written immediately back to disk (the two files are kept
//	open during all this time).  If the operation fails, and we have
//	modified part of the directory and/or bitmap, we simply discard
//	the changed version, without writing it back to disk.
//
// 	Our implementation at this point has the following restrictions:
//
//	   there is no synchronization for concurrent accesses
//	   files have a fixed size, set when the file is created
//	   files cannot be bigger than about 3KB in size
//	   there is no hierarchical directory structure, and only a limited
//	     number of files can be added to the system
//	   there is no attempt to make the system robust to failures
//	    (if Nachos exits in the middle of an operation that modifies
//	    the file system, it may corrupt the disk)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "disk.h"
#include "bitmap.h"
#include "directory.h"
#include "filehdr.h"
#include "filesys.h"

#ifdef LAB5
#include "thread.h"
#endif

// Sectors containing the file headers for the bitmap of free sectors,
// and the directory of files.  These file headers are placed in well-known
// sectors, so that they can be located on boot-up.
#define FreeMapSector 		0
#define DirectorySector 	1

// Initial file sizes for the bitmap and directory; until the file system
// supports extensible files, the directory size sets the maximum number
// of files that can be loaded onto the disk.
#define FreeMapFileSize 	(NumSectors / BitsInByte)
#ifdef LAB5
#define NumDirEntries       2
#else
#define NumDirEntries 		10
#endif
#define DirectoryFileSize 	(sizeof(DirectoryEntry) * NumDirEntries)

//----------------------------------------------------------------------
// FileSystem::FileSystem
// 	Initialize the file system.  If format = TRUE, the disk has
//	nothing on it, and we need to initialize the disk to contain
//	an empty directory, and a bitmap of free sectors (with almost but
//	not all of the sectors marked as free).
//
//	If format = FALSE, we just have to open the files
//	representing the bitmap and the directory.
//
//	"format" -- should we initialize the disk?
//----------------------------------------------------------------------

FileSystem::FileSystem(bool format)
{
    DEBUG('f', "Initializing the file system.\n");
    if (format) {
        BitMap *freeMap = new BitMap(NumSectors);
        Directory *directory = new Directory(NumDirEntries);

        FileHeader *mapHdr = new FileHeader;
    	FileHeader *dirHdr = new FileHeader;
#ifdef LAB5
        dirHdr->SetToDir();
        dirHdr->SetParent(DirectorySector);
        directory->SetParent(DirectorySector);
        for (int i = 0; i != MAXFILEOPEN; ++i) {
            fileTable[i].inUse = 0;
        }
#endif

        DEBUG('f', "Formatting the file system.\n");

        // First, allocate space for FileHeaders for the directory and bitmap
        // (make sure no one else grabs these!)
    	freeMap->Mark(FreeMapSector);
    	freeMap->Mark(DirectorySector);

        // Second, allocate space for the data blocks containing the contents
        // of the directory and bitmap files.  There better be enough space!
    	ASSERT(mapHdr->Allocate(freeMap, FreeMapFileSize));
    	ASSERT(dirHdr->Allocate(freeMap, DirectoryFileSize));

        // Flush the bitmap and directory FileHeaders back to disk
        // We need to do this before we can "Open" the file, since open
        // reads the file header off of disk (and currently the disk has garbage
        // on it!).

        DEBUG('f', "Writing headers back to disk.\n");
    	mapHdr->WriteBack(FreeMapSector);
    	dirHdr->WriteBack(DirectorySector);

        // OK to open the bitmap and directory files now
        // The file system operations assume these two files are left open
        // while Nachos is running.

        freeMapFile = new OpenFile(FreeMapSector);
        directoryFile = new OpenFile(DirectorySector);

        // Once we have the files "open", we can write the initial version
        // of each file back to disk.  The directory at this point is completely
        // empty; but the bitmap has been changed to reflect the fact that
        // sectors on the disk have been allocated for the file headers and
        // to hold the file data for the directory and bitmap.

        DEBUG('f', "Writing bitmap and directory back to disk.\n");
    	freeMap->WriteBack(freeMapFile);	 // flush changes to disk
//printf("Writing root directory\n");
    	directory->WriteBack(directoryFile, freeMap);
//printf("Writing root directory success\n");

    	if (DebugIsEnabled('f')) {
    	    freeMap->Print();
    	    directory->Print();

            delete freeMap;
        	delete directory;
        	delete mapHdr;
        	delete dirHdr;
    	}
    } else {
    // if we are not formatting the disk, just open the files representing
    // the bitmap and directory; these are left open while Nachos is running
        freeMapFile = new OpenFile(FreeMapSector);
        directoryFile = new OpenFile(DirectorySector);
    }
}

//----------------------------------------------------------------------
// FileSystem::Create
// 	Create a file in the Nachos file system (similar to UNIX create).
//	Since we can't increase the size of files dynamically, we have
//	to give Create the initial size of the file.
//
//	The steps to create a file are:
//	  Make sure the file doesn't already exist
//        Allocate a sector for the file header
// 	  Allocate space on disk for the data blocks for the file
//	  Add the name to the directory
//	  Store the new file header on disk
//	  Flush the changes to the bitmap and the directory back to disk
//
//	Return TRUE if everything goes ok, otherwise, return FALSE.
//
// 	Create fails if:
//   		file is already in directory
//	 	no free space for file header
//	 	no free entry for file in directory
//	 	no free space for data blocks for the file
//
// 	Note that this implementation assumes there is no concurrent access
//	to the file system!
//
//	"name" -- name of file to be created
//	"initialSize" -- size of file to be created
//----------------------------------------------------------------------
#ifndef LAB5

int FileSystem::Create(char *name, int initialSize)
{
    Directory *directory;
    BitMap *freeMap;
    FileHeader *hdr;
    int sector;
    bool success;

    DEBUG('f', "Creating file %s, size %d\n", name, initialSize);

    directory = new Directory(NumDirEntries);
    directory->FetchFrom(directoryFile);

    if (directory->Find(name) != -1) {
        success = FALSE;			// file is already in directory
    } else {
        freeMap = new BitMap(NumSectors);
        freeMap->FetchFrom(freeMapFile);
        sector = freeMap->Find();	// find a sector to hold the file header
    	if (sector == -1) {
            success = FALSE;		// no free block for file header
        } else if (directory->Add(name, sector) != Success) {
            success = FALSE;	// no space in directory
        } else {
            hdr = new FileHeader;
            if (!hdr->Allocate(freeMap, initialSize)) {
            success = FALSE;	// no space on disk for data
            } else {
                success = TRUE;
		              // everthing worked, flush all changes back to disk
                hdr->WriteBack(sector);
    	    	directory->WriteBack(directoryFile);
    	    	freeMap->WriteBack(freeMapFile);
            }
            delete hdr;
        }
        delete freeMap;
    }
    delete directory;
    return success;
}

#else
int FileSystem::Create(char *name, int initialSize) {
    char *fileName;
    if (name[0] != '/') return FileNotFound;
    int dirSector = namex(name, fileName);
    if (dirSector < 0) return FileNotFound;
    return Create(fileName, initialSize, dirSector);
}


int FileSystem::Create(char *name, int initialSize, int dirSector) {
    int success;
    BitMap *freeMap;
    FileHeader *hdr;
    Directory *directory;
    OpenFile *dirFile;

    DEBUG('f', "Creating file %s, size %d\n", name, initialSize);

    dirFile = new OpenFile(dirSector);
    directory = new Directory(NumDirEntries);
    directory->FetchFrom(dirFile);

    if (directory->Find(name) != -1) {
        success = FileExist;
        printf("Create: file exist\n");
    } else {
        freeMap = new BitMap(NumSectors);
        freeMap->FetchFrom(freeMapFile);
        int sector = freeMap->Find();           // for file header
        if (sector == -1) {
            success = FileTooLarge;
            printf("Create: no space for header\n");
        } else if ((success = directory->Add(name, sector, freeMap)) != Success) {       // not enough space in directory or path error
            freeMap->Clear(sector);
            printf("Create: no space for directory, error: %d\n", success);
        }else {
            hdr = new FileHeader;
            if (!hdr->Allocate(freeMap, initialSize)) {         // not enough space for file data
                success = FileTooLarge;
                freeMap->Clear(sector);
                ASSERT(directory->Remove(name) == Success);
                printf("Create: no space for file\n");
            } else {
                printf("Create: success hdr in sector %d\n", sector);
                success = Success;
                hdr->SetParent(dirSector);
                hdr->WriteBack(sector);
                directory->WriteBack(dirFile, freeMap);
                freeMap->WriteBack(freeMapFile);
            }
            delete hdr;
        }
        delete freeMap;
    }
    delete dirFile;
    delete directory;
    return success;
}


//----------------------------------------------------------------------
// FileSystem::CreateDir
//  Create a directory in the file system.
//----------------------------------------------------------------------

int FileSystem::CreateDir(char *name, int dirSector) {
    int ret = Create(name, 64, dirSector);
    if (ret == Success) {
        // set it to directory
        Directory *dir = new Directory(NumDirEntries);
        OpenFile *dirFile = new OpenFile(dirSector);
        dir->FetchFrom(dirFile);
        int sector = dir->Find(name);
        delete dir;
        delete dirFile;
        ASSERT(sector >= 0);
        FileHeader *hdr = new FileHeader;
        hdr->FetchFrom(sector);
        hdr->SetToDir();
        hdr->SetParent(dirSector);
        hdr->WriteBack(sector);
        delete hdr;
        // init the new directory
        dir = new Directory(NumDirEntries);
        dirFile = new OpenFile(sector);
        dir->SetParent(dirSector);
        dir->WriteBack(dirFile, 0);          // space is enough
        delete dirFile;
        delete dir;
    }
    return ret;
}


int FileSystem::CreateDir(char *name) {
    char *fileName;
    if (name[0] != '/') return FileNotFound;
    int dirSector = namex(name, fileName);
    if (dirSector < 0) return FileNotFound;
    return CreateDir(fileName, dirSector);
}


//----------------------------------------------------------------------
// FileSystem::namex
//  Analyse the path and name.
//----------------------------------------------------------------------

int FileSystem::namex(char *name, char *&fileName) {
//printf("namex: fileName is %s\n", name);
    fileName = name+1;                  // first char is '/' in root directory
    char *pch;
    int sector = 1;
    OpenFile *dirFile = NULL;
    Directory *currentDir = new Directory(NumDirEntries);
    currentDir->FetchFrom(directoryFile);

    while ((pch = strchr(fileName, '/')) != NULL) {
        *pch = '\0';
        sector = currentDir->Find(fileName);
        *pch = '/';
        if (sector < 0) {
            // char *nexts = strchr(pch+1, '/');       // I forget why I write this
            // if (nexts != NULL) {
            //     *nexts = '\0';
            // }
            return -1;
        }

        dirFile = new OpenFile(sector);
        currentDir->FetchFrom(dirFile);
        delete dirFile;
        fileName = pch+1;
    }
    delete currentDir;
    return sector;
}

#endif

#ifdef LAB5
//----------------------------------------------------------------------
// FileSystem::Open
// 	Open a file for reading and writing.
//	To open a file:
//	  Find the location of the file's header, using the directory
//	  Bring the header into memory
//
//	"name" -- the text name of the file to be opened
//----------------------------------------------------------------------
OpenFile* FileSystem::Open(char *name) {
    char *fileName;
    if (name[0] != '/') return NULL;
    int dirSector = namex(name, fileName);
    if (dirSector < 0) return FileNotFound;
// printf("open namex path %s, file %s\n", name, fileName);
    return Open(fileName, dirSector);
}


OpenFile* FileSystem::Open(char *name, int dirSector) {
    Directory *directory = new Directory(NumDirEntries);
    OpenFile *dirFile = new OpenFile(dirSector);
    directory->FetchFrom(dirFile);
    delete dirFile;

    int sector = directory->Find(name);
    delete directory;

    if (sector == -1) {
        return NULL;
    }

// printf("dirSector is %d, Open sector %d\n", dirSector, sector);

    int opened = -1;
    for (int i = 0; i != MAXFILEOPEN; ++i) {
        if (fileTable[i].inUse == 1&& fileTable[i].sector == sector) {
            opened = i;
        }
    }
    if (opened == -1) {
        OpenFile *openFile = new OpenFile(sector);
        for (int i = 0; i != MAXFILEOPEN; ++i) {
            if (fileTable[i].inUse == 0) {
                fileTable[i].inUse = 1;
                fileTable[i].sector = sector;
                fileTable[i].num = 1;
                fileTable[i].file = openFile;
                for (int j = 0; j != MAXOPEN; ++j) {
                    if (currentThread->OpenTable[j].inUse == 0) {
                        currentThread->OpenTable[j].inUse = 1;
                        currentThread->OpenTable[j].file = openFile;
                        currentThread->OpenTable[j].position = 0;
                        break;
                    }
                }
                break;
            }
        }
        return openFile;
    } else {
        int threadOpened = -1;
        for (int j = 0; j != MAXOPEN; ++j) {
            if (currentThread->OpenTable[j].inUse == 1 && currentThread->OpenTable[j].file == fileTable[opened].file) {
                threadOpened = j;
            }
        }
        if (threadOpened == -1) {
            for (int j = 0; j != MAXOPEN; ++j) {
                if (currentThread->OpenTable[j].inUse == 0) {
                    currentThread->OpenTable[j].inUse = 1;
                    currentThread->OpenTable[j].file = fileTable[opened].file;
                    currentThread->OpenTable[j].position = 0;
                    fileTable[opened].num += 1;
                    return fileTable[opened].file;
                }
            }
            return NULL;        // thread's open table full
        }
        return NULL;        // thread already open this file
    }
}


#else
OpenFile *
FileSystem::Open(char *name)
{
    Directory *directory = new Directory(NumDirEntries);
    OpenFile *openFile = NULL;
    int sector;

    DEBUG('f', "Opening file %s\n", name);
    directory->FetchFrom(directoryFile);
    sector = directory->Find(name);
    if (sector >= 0)
	openFile = new OpenFile(sector);	// name was found in directory
    delete directory;
    return openFile;				// return NULL if not found
}
#endif

//----------------------------------------------------------------------
// FileSystem::Remove
// 	Delete a file from the file system.  This requires:
//	    Remove it from the directory
//	    Delete the space for its header
//	    Delete the space for its data blocks
//	    Write changes to directory, bitmap back to disk
//
//	Return TRUE if the file was deleted, FALSE if the file wasn't
//	in the file system.
//
//	"name" -- the text name of the file to be removed
//----------------------------------------------------------------------
#ifndef LAB5
int FileSystem::Remove(char *name)
{
    Directory *directory;
    BitMap *freeMap;
    FileHeader *fileHdr;
    int sector;

    directory = new Directory(NumDirEntries);
    directory->FetchFrom(directoryFile);
    sector = directory->Find(name);
    if (sector == -1) {
       delete directory;
       return FALSE;			 // file not found
    }
    fileHdr = new FileHeader;
    fileHdr->FetchFrom(sector);

    freeMap = new BitMap(NumSectors);
    freeMap->FetchFrom(freeMapFile);

    fileHdr->Deallocate(freeMap);  		// remove data blocks
    freeMap->Clear(sector);			// remove header block
    directory->Remove(name);

    freeMap->WriteBack(freeMapFile);		// flush to disk
    directory->WriteBack(directoryFile, freeMap);        // flush to disk
    delete fileHdr;
    delete directory;
    delete freeMap;
    return TRUE;
}

#else
int FileSystem::Remove(char *name, int dirSector) {
    Directory *directory;
    BitMap *freeMap;
    FileHeader *fileHdr;
    int sector;

    OpenFile *dirFile = new OpenFile(dirSector);
    directory = new Directory(NumDirEntries);
    directory->FetchFrom(dirFile);
    sector = directory->Find(name);
    if (sector == -1) {
        printf("Remove: file not found\n");
        delete directory;
        delete dirFile;
        return FileNotFound;
    }

    // check if opened
    for (int i = 0; i != MAXFILEOPEN; ++i) {
        if (fileTable[i].inUse == 1 && fileTable[i].sector == sector) {
            //printf("Remove: file opend %d\n", fileTable[i].num);
            delete directory;
            delete dirFile;
            return FileOpened;
        }
    }

    fileHdr = new FileHeader;
    fileHdr->FetchFrom(sector);


    if (fileHdr->IsDir()) {
        OpenFile *deleteFile = new OpenFile(sector);
        Directory *deleteDir = new Directory(NumDirEntries);
        deleteDir->FetchFrom(deleteFile);
        if (!deleteDir->IsEmpty()) {
            delete dirFile;
            delete fileHdr;
            delete directory;
            delete deleteFile;
            delete deleteDir;
            return DirNotEmpty;
        }
        delete deleteFile;
        delete deleteDir;
    }

    freeMap = new BitMap(NumSectors);
    freeMap->FetchFrom(freeMapFile);

    fileHdr->Deallocate(freeMap);
    freeMap->Clear(sector);
    ASSERT(directory->Remove(name) == Success);

    freeMap->WriteBack(freeMapFile);
    directory->WriteBack(dirFile, freeMap);

    delete fileHdr;
    delete directory;
    delete freeMap;

    return Success;
}


int FileSystem::Remove(char *name) {
    char *fileName;
    if (name[0] != '/') return FileNotFound;
    int dirSector = namex(name, fileName);
    if (dirSector < 0) return FileNotFound;
    return Remove(fileName, dirSector);
}


//----------------------------------------------------------------------
// FileSystem::RemoveDir
//  remove the empty directory
//----------------------------------------------------------------------

int FileSystem::RemoveDir(char *name, int dirSector) {
    Directory *directory;
    BitMap *freeMap;
    FileHeader *hdr;
    int sector;

    OpenFile *dirFile = new OpenFile(dirSector);
    directory = new Directory(NumDirEntries);
    directory->FetchFrom(dirFile);
    sector = directory->Find(name);
    if (sector == -1) {
        delete dirFile;
        delete directory;
        return FileNotFound;
    }

    hdr = new FileHeader;
    hdr->FetchFrom(sector);
    if (!hdr->IsDir()) {
        delete dirFile;
        delete hdr;
        delete directory;
        return NotDirectory;
    }

    OpenFile *deleteFile = new OpenFile(sector);
    Directory *deleteDir = new Directory(NumDirEntries);
    deleteDir->FetchFrom(deleteFile);
    if (!deleteDir->IsEmpty()) {
        delete dirFile;
        delete hdr;
        delete directory;
        delete deleteFile;
        delete deleteDir;
        return NotDirectory;
    }
    delete deleteFile;
    delete deleteDir;

    freeMap = new BitMap(NumSectors);
    freeMap->FetchFrom(freeMapFile);
    hdr->Deallocate(freeMap);
    freeMap->Clear(sector);
    ASSERT(directory->Remove(name) == Success);

    delete dirFile;
    delete directory;
    delete hdr;
    delete freeMap;

    return Success;
}


int FileSystem::RemoveDir(char *name) {
    char *fileName;
    if (name[0] != '/') return FileNotFound;
    int dirSector = namex(name, fileName);
    if (dirSector < 0) return FileNotFound;
    return RemoveDir(fileName, dirSector);
}


#endif

//----------------------------------------------------------------------
// FileSystem::List
// 	List all the files in the file system directory.
//----------------------------------------------------------------------

void
FileSystem::List()
{
    Directory *directory = new Directory(NumDirEntries);

    directory->FetchFrom(directoryFile);
    directory->List();
    delete directory;
}

//----------------------------------------------------------------------
// FileSystem::Print
// 	Print everything about the file system:
//	  the contents of the bitmap
//	  the contents of the directory
//	  for each file in the directory,
//	      the contents of the file header
//	      the data in the file
//----------------------------------------------------------------------

void
FileSystem::Print()
{
    FileHeader *bitHdr = new FileHeader;
    FileHeader *dirHdr = new FileHeader;
    BitMap *freeMap = new BitMap(NumSectors);
    Directory *directory = new Directory(NumDirEntries);

    printf("Bit map file header:\n");
    bitHdr->FetchFrom(FreeMapSector);
    bitHdr->Print();

    printf("Directory file header:\n");
    dirHdr->FetchFrom(DirectorySector);
    dirHdr->Print();

    freeMap->FetchFrom(freeMapFile);
    freeMap->Print();

    directory->FetchFrom(directoryFile);
    directory->Print();

    delete bitHdr;
    delete dirHdr;
    delete freeMap;
    delete directory;
}


#ifdef LAB5
int FileSystem::Close(OpenFile *file) {
    for (int i = 0; i != MAXFILEOPEN; ++i) {
        if (fileTable[i].inUse == 1 && fileTable[i].file == file) {
            fileTable[i].num -= 1;
            if (fileTable[i].num == 0) {
                delete file;
                fileTable[i].inUse = 0;
            }
            for (int j = 0; j != MAXOPEN; ++j) {
                if (currentThread->OpenTable[j].inUse == 1 && currentThread->OpenTable[j].file == file) {
                    currentThread->OpenTable[j].inUse = 0;
//printf("Close success, global open num is %d\n", fileTable[i].num);
                    return 0;
                }
            }
            return -1;      // file not found in thread
        }
    }
    return -1;          // file not found
}
#endif