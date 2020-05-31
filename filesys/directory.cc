// directory.cc 
//	Routines to manage a directory of file names.
//
//	The directory is a table of fixed length entries; each
//	entry represents a single file, and contains the file name,
//	and the location of the file header on disk.  The fixed size
//	of each directory entry means that we have the restriction
//	of a fixed maximum size for file names.
//
//	The constructor initializes an empty directory of a certain size;
//	we use ReadFrom/WriteBack to fetch the contents of the directory
//	from disk, and to write back any modifications back to disk.
//
//	Also, this implementation has the restriction that the size
//	of the directory cannot expand.  In other words, once all the
//	entries in the directory are used, no more files can be created.
//	Fixing this is one of the parts to the assignment.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "utility.h"
#include "filehdr.h"
#include "directory.h"

//----------------------------------------------------------------------
// Directory::Directory
// 	Initialize a directory; initially, the directory is completely
//	empty.  If the disk is being formatted, an empty directory
//	is all we need, but otherwise, we need to call FetchFrom in order
//	to initialize it from disk.
//
//	"size" is the number of entries in the directory
//----------------------------------------------------------------------
#ifdef LAB5
Directory::Directory(int size) {
    tableSize = 2;
    table = new DirectoryEntry[tableSize];
    table[0].inUse = true;
    setFileName(table, "..\0", 0);
    table[1].inUse = false;
}
#else
Directory::Directory(int size)
{
    table = new DirectoryEntry[size];
    tableSize = size;
    for (int i = 0; i < tableSize; i++) {
	   table[i].inUse = FALSE;
    }
}
#endif

//----------------------------------------------------------------------
// Directory::~Directory
// 	De-allocate directory data structure.
//----------------------------------------------------------------------

Directory::~Directory()
{ 
    delete [] table;
} 

//----------------------------------------------------------------------
// Directory::FetchFrom
// 	Read the contents of the directory from disk.
//
//	"file" -- file containing the directory contents
//----------------------------------------------------------------------

void
Directory::FetchFrom(OpenFile *file)
{
#ifdef LAB5
    tableSize = file->Length() / sizeof(DirectoryEntry);
    delete[] table;
    table = new DirectoryEntry[tableSize];
    //printf("directory fetch, tablesize %d\n", tableSize);
#endif
    (void) file->ReadAt((char *)table, tableSize * sizeof(DirectoryEntry), 0);
}

//----------------------------------------------------------------------
// Directory::WriteBack
// 	Write any modifications to the directory back to disk
//
//	"file" -- file to contain the new directory contents
//----------------------------------------------------------------------

void
Directory::WriteBack(OpenFile *file, BitMap *freeMap)
{
#ifdef LAB5
    file->ChangeSize(tableSize*sizeof(DirectoryEntry), freeMap);
    //printf("directory writeback tablesize %d\n", tableSize);
    //printf("%d\n", file->Length());
#endif
    (void) file->WriteAt((char *)table, tableSize * sizeof(DirectoryEntry), 0, freeMap);
}

//----------------------------------------------------------------------
// Directory::FindIndex
// 	Look up file name in directory, and return its location in the table of
//	directory entries.  Return -1 if the name isn't in the directory.
//
//	"name" -- the file name to look up
//----------------------------------------------------------------------

int
Directory::FindIndex(char *name)
{
    for (int i = 0; i < tableSize; i++) {
        char *fileName = new char[table[i].nameLength+1];
        getFileName(table+i, fileName);
printf("tabel[%d].Use = %d, fileName %s, searchName: %s\n", i, table[i].inUse, fileName, name);
printf("strcmp(fileName, name) = %d\n", strcmp(fileName, name));
        if (table[i].inUse && !strcmp(fileName, name)) {
	        delete[] fileName;
            return i;
        }
        delete[] fileName;
    }
    return -1;		// name not in directory
}

//----------------------------------------------------------------------
// Directory::Find
// 	Look up file name in directory, and return the disk sector number
//	where the file's header is stored. Return -1 if the name isn't 
//	in the directory.
//
//	"name" -- the file name to look up
//----------------------------------------------------------------------

int
Directory::Find(char *name)
{
    int i = FindIndex(name);
    if (i != -1) return table[i].sector;
    return -1;
}

//----------------------------------------------------------------------
// Directory::Add
// 	Add a file into the directory.  Return TRUE if successful;
//	return FALSE if the file name is already in the directory, or if
//	the directory is completely full, and has no more space for
//	additional file names.
//
//	"name" -- the name of the file being added
//	"newSector" -- the disk sector containing the added file's header
//----------------------------------------------------------------------

int Directory::Add(char *name, int newSector, BitMap *freeMap) {
    if (FindIndex(name) != -1) return FileExist;
    for (int i = 0; i < tableSize; i++) {
        if (!table[i].inUse) {
            //printf("find %d\n", i);
            table[i].inUse = TRUE;
            if (setFileName(table+i, name, freeMap) != Success) {
                return NameTooLong;
            }
            // strncpy(table[i].name, name, FileNameMaxLen); 
            table[i].sector = newSector;
            return Success;
	   }
    }

#ifdef LAB5
    int oldSize = tableSize;
    tableSize *= 2;
    DirectoryEntry *nTable = new DirectoryEntry[tableSize];
    for (int i = 0; i != oldSize; ++i) {
        nTable[i].sector = table[i].sector;
        nTable[i].inUse = table[i].inUse;
        nTable[i].nameSector = table[i].nameSector;
        nTable[i].nameLength = table[i].nameLength;
        strncpy(nTable[i].dirName, table[i].dirName, FileDirNameMaxLen+1);
        nTable[i].dirName[FileDirNameMaxLen] = '\0';
    }
    delete[] table;
    table = nTable;
    for (int i = oldSize; i != tableSize; ++i) {
        table[i].inUse = false;
    }
    table[oldSize].inUse = true;
    table[oldSize].sector = newSector;
    if (setFileName(table+oldSize, name, freeMap) != Success) {
        tableSize = oldSize;
        return NameTooLong;
    }
    printf("Directroy add success, directory list below:\n");
    return Success;
#else
    return FileTooLarge;	// no space.  Fix when we have extensible files.
#endif
}

//----------------------------------------------------------------------
// Directory::Remove
// 	Remove a file name from the directory.  Return TRUE if successful;
//	return FALSE if the file isn't in the directory. 
//
//	"name" -- the file name to be removed
//----------------------------------------------------------------------

int Directory::Remove(char *name) {
    int i = FindIndex(name);

    if (i == -1) return FileNotFound; 		// name not in directory
    if (i == 0) return FileNotFound;         // .. parent directory, cannot remove
    table[i].inUse = FALSE;

#ifdef LAB5
    int useNum = 0;
    for (int i = 0; i != tableSize; ++i){
        if (table[i].inUse) ++useNum;
    }
    if (useNum < tableSize / 2) {
        for (int i = 0; i != tableSize; ++i) {
            if (table[i].inUse) continue;
            int j = i + 1;
            while (j != tableSize && !table[j].inUse) {
                ++j;
            }
            if (j == tableSize) break;
            table[i].inUse = table[j].inUse;
            table[j].inUse = false;
            table[i].sector = table[j].sector;
            table[i].nameSector = table[j].nameSector;
            table[i].nameLength = table[j].nameLength;
            strncpy(table[i].dirName, table[j].dirName, FileDirNameMaxLen);
        }
        for (int i = tableSize / 2; i != tableSize; ++i) {
            ASSERT(!table[i].inUse);
        }
        tableSize /= 2;
    }

#endif
    return Success;
}

//----------------------------------------------------------------------
// Directory::List
// 	List all the file names in the directory. 
//----------------------------------------------------------------------

void
Directory::List(bool Recursive = true)
{
    int sector;
    FileHeader *hdr = new FileHeader;
    for (int i = 0; i < tableSize; i++) {
    	if (table[i].inUse) {
            sector = table[i].sector;
            hdr->FetchFrom(sector);
            if (hdr->IsDir()) {
                printf("#");
            }
            char *fileName = new char[table[i].nameLength+1];
            getFileName(table+i, fileName);
            printf("%s\n", fileName);
printf("---------------sector %d\n", sector);
            delete[] fileName;
        }
    }

    if (Recursive) {
        Directory *dir = new Directory(2);
        for (int i = 0; i < tableSize; ++i) {
            if (table[i].inUse) {
                if (table[i].nameLength == 2 && table[i].dirName[0] == '.' && table[i].dirName[1] == '.') {
                    continue;
                }
                sector = table[i].sector;
                hdr->FetchFrom(sector);
                if (hdr->IsDir()) {
                    char *fileName = new char[table[i].nameLength+1];
                    getFileName(table+i, fileName);
                    OpenFile *dirFile = new OpenFile(sector);
                    dir->FetchFrom(dirFile);
                    printf("\n%s  (contains %d files) :\n", fileName, dir->tableSize);
                    dir->List(Recursive);
                    delete dirFile;
                    delete[] fileName;
                }
            }
        }
        delete dir;
    }
    delete hdr;
}

//----------------------------------------------------------------------
// Directory::Print
// 	List all the file names in the directory, their FileHeader locations,
//	and the contents of each file.  For debugging.
//----------------------------------------------------------------------

void
Directory::Print(bool Recursive = true)
{ 
    FileHeader *hdr = new FileHeader;

    printf("Directory contents:\n");
    for (int i = 0; i < tableSize; i++)
	if (table[i].inUse) {
        char *fileName = new char[table[i].nameLength+1];
        getFileName(table+i, fileName);
	    printf("Name: %s, Sector: %d\n", fileName, table[i].sector);
        delete[] fileName;
	    hdr->FetchFrom(table[i].sector);
	    hdr->Print();
	}
    printf("\n");
    
    if (Recursive) {
        Directory *dir = new Directory(2);
        for (int i = 0; i != tableSize; ++i) {
            if (table[i].inUse) {
                if (table[i].nameLength == 2 && table[i].dirName[0] == '.' && table[i].dirName[1] == '.') {
                    continue;
                }
                hdr->FetchFrom(table[i].sector);
                if (hdr->IsDir()) {
                    char *fileName = new char[table[i].nameLength+1];
                    getFileName(table+i, fileName);
                    printf("\n%s:\n", fileName);
                    OpenFile *dirFile = new OpenFile(table[i].sector);
                    dir->FetchFrom(dirFile);
                    dir->Print(Recursive);
                    delete[] fileName;
                }
            }
        }
    }


    delete hdr;
}


//----------------------------------------------------------------------
// Directory::getFileName
// Get the file name. In lab5, we design a unlimit length name.
// Otherwise, a fixed length name.
//----------------------------------------------------------------------

void Directory::getFileName(DirectoryEntry *entry, char *name) {
#ifdef LAB5
    int len = entry->nameLength;
    name[len] = '\0';
    if (len <= FileDirNameMaxLen) {
        strncpy(name, entry->dirName, len);
    } else {
        strncpy(name, entry->dirName, FileDirNameMaxLen);
        int gLen = FileDirNameMaxLen;                   // length of name already get
        int nameSectorSize = SectorSize - sizeof(int);
        char buf[SectorSize];
        FileNameChain *fnc = (FileNameChain*)&buf;
        for (int i = entry->nameSector; i != -1; i = fnc->nextSector) {
            synchDisk->ReadSector(i, (char*)&buf);
            if (gLen + nameSectorSize > len) {
                strncpy(name+gLen, buf+sizeof(int), len-gLen);
            } else {
                strncpy(name+gLen, buf+sizeof(int), nameSectorSize);
            }
            gLen += nameSectorSize;
        }
    }
    ASSERT(strlen(name) == len);
#else
    strncpy(name, entry->name, FileNameMaxLen)
#endif
    return;
}


//----------------------------------------------------------------------
// Directory::setFileName
// Set the file name. In lab5, we design a unlimit length name.
// Otherwise, a fixed length name.
//----------------------------------------------------------------------

int Directory::setFileName(DirectoryEntry *entry, char *name, BitMap *freeMap) {
#ifdef LAB5
    int len = strlen(name);
    entry->nameLength = len;
    if (len <= FileDirNameMaxLen) {
        strncpy(entry->dirName, name, len);
        entry->dirName[len] = '\0';
    } else {
        strncpy(entry->dirName, name, FileDirNameMaxLen);
        entry->dirName[FileDirNameMaxLen] = '\0';
        len -= FileDirNameMaxLen;
        int pos = FileDirNameMaxLen;
        int nameSectorSize = SectorSize - sizeof(int);

        int numSectors  = divRoundUp(len, nameSectorSize);
        if (numSectors > freeMap->NumClear()) {
            return NameTooLong;
        }

        int lastSector = -1;
        char buf[SectorSize];
        FileNameChain *fnc = (FileNameChain*)&buf;

        if (numSectors * nameSectorSize > len) {
            int sector = freeMap->Find();
            fnc->nextSector = lastSector;
            pos = (numSectors - 1) * nameSectorSize;
            strncpy(buf+sizeof(int), name+pos+FileDirNameMaxLen, len-pos+1);
            synchDisk->WriteSector(sector, buf);
            pos -= nameSectorSize;
            lastSector = sector;
        }

        while (pos >= 0) {
            int sector = freeMap->Find();
            fnc->nextSector = lastSector;
            lastSector = sector;
            strncpy(buf+sizeof(int), name+pos+FileDirNameMaxLen, nameSectorSize);
            synchDisk->WriteSector(sector, buf);
            pos -= nameSectorSize;
        }
        entry->nameSector = lastSector;
    }
    return Success;
#else
    strncpy(entry->name, name, FileNameMaxLen);
    return true;
#endif
}

#ifdef LAB5
//----------------------------------------------------------------------
// Directory::IsEmpty
//  empty directory
//----------------------------------------------------------------------

bool Directory::IsEmpty() {
    bool empty = true;
    printf("%d, %d, %s\n", table[0].inUse, table[0].nameLength, table[0].dirName);
    ASSERT(table[0].inUse && table[0].nameLength == 2 && table[0].dirName[0] == '.' && table[0].dirName[1] == '.');
    for (int i = 1; i != tableSize; ++i) {
        if (table[i].inUse) {
            empty = false;
        }
    }
    return empty;
}

//----------------------------------------------------------------------
// Directory::SetParent
//  set ".." file point to the parent
//----------------------------------------------------------------------

void Directory::SetParent(int parent) {
    ASSERT(table[0].nameLength == 2 && table[0].dirName[0] == '.' && table[0].dirName[1] == '.');
    table[0].sector = parent;
}

#endif