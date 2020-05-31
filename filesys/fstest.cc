// fstest.cc 
//	Simple test routines for the file system.  
//
//	We implement:
//	   Copy -- copy a file from UNIX to Nachos
//	   Print -- cat the contents of a Nachos file 
//	   Perftest -- a stress test for the Nachos file system
//		read and write a really large file in tiny chunks
//		(won't work on baseline system!)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "utility.h"
#include "filesys.h"
#include "system.h"
#include "thread.h"
#include "disk.h"
#include "stats.h"

#define TransferSize 	10 	// make it small, just to be difficult

//----------------------------------------------------------------------
// Copy
// 	Copy the contents of the UNIX file "from" to the Nachos file "to"
//----------------------------------------------------------------------

void
Copy(char *from, char *to)
{
    FILE *fp;
    OpenFile* openFile;
    int amountRead, fileLength;
    char *buffer;

// Open UNIX file
    if ((fp = fopen(from, "r")) == NULL) {	 
	printf("Copy: couldn't open input file %s\n", from);
	return;
    }

// Figure out length of UNIX file
    fseek(fp, 0, 2);		
    fileLength = ftell(fp);
    fseek(fp, 0, 0);

// Create a Nachos file of the same length
printf("Copying file %s, size %d, to file %s\n", from, fileLength, to);
    DEBUG('f', "Copying file %s, size %d, to file %s\n", from, fileLength, to);
#ifdef LAB5
    int success;
    if ((success = fileSystem->Create(to, fileLength)) != Success) {
        switch (success) {
            case FileNotFound:
                printf("Copy: Path error\n");
                break;
            case FileExist:
                printf("Copy: File Exist\n");
                break;
            case FileTooLarge:
                printf("Copy: File too large\n");
                break;
            case NameTooLong:
                printf("Copy: File name too long, without enough space\n");
                break;
            default:
                printf("Copy: Undefined error %d\n", success);
        }
        fclose(fp);
        return;
    }
#else
    if (!fileSystem->Create(to, fileLength)) {	 // Create Nachos file
	   printf("Copy: couldn't create output file %s\n", to);
	   fclose(fp);
	   return;
    }
#endif
    openFile = fileSystem->Open(to);
    ASSERT(openFile != NULL);
// Copy the data in TransferSize chunks
    buffer = new char[TransferSize];
    while ((amountRead = fread(buffer, sizeof(char), TransferSize, fp)) > 0) {
	   openFile->Write(buffer, amountRead, 0);
    }
    delete [] buffer;

// Close the UNIX and the Nachos files
    delete openFile;
    fclose(fp);
}

#ifdef LAB5
//----------------------------------------------------------------------
// MakeDir
//  Create directory through absolute path
//----------------------------------------------------------------------

void MakeDir(char *name) {
    int success = fileSystem->CreateDir(name);
    if (success == Success) return;
    switch (success) {
        case FileNotFound:
            printf("MakeDir: Path error\n");
            break;
        case FileExist:
            printf("MakeDir: File exist\n");
            break;
        case FileTooLarge:
            printf("MakeDir: File too large, without enough space\n");
            break;
        case NameTooLong:
            printf("MakeDir: File name too long, without enough space\n");
            break;
        default:
            printf("MakeDir: Undefined error %d\n", success);
    }
    return;
}



//----------------------------------------------------------------------
// Remove
//  Remove a file or directory.
//----------------------------------------------------------------------
void Remove(char *name) {
    int success = fileSystem->Remove(name);
    if (success == Success) return;
    switch (success) {
        case FileNotFound:
            printf("Remove: File not found or path error\n");
            break;
        case DirNotEmpty:
            printf("Remove: Directory not empty\n");
            break;
        default:
            printf("Remove: Undefined error %d\n", success);
    }
    return;
}

#endif

//----------------------------------------------------------------------
// Print
// 	Print the contents of the Nachos file "name".
//----------------------------------------------------------------------

void
Print(char *name)
{
    OpenFile *openFile;    
    int i, amountRead;
    char *buffer;

    if ((openFile = fileSystem->Open(name)) == NULL) {
	printf("Print: unable to open file %s\n", name);
	return;
    }
    
    buffer = new char[TransferSize];
    while ((amountRead = openFile->Read(buffer, TransferSize)) > 0)
	for (i = 0; i < amountRead; i++)
	    printf("%c", buffer[i]);
    delete [] buffer;

    delete openFile;		// close the Nachos file
    return;
}


//----------------------------------------------------------------------
// PerformanceTest
// 	Stress the Nachos file system by creating a large file, writing
//	it out a bit at a time, reading it back a bit at a time, and then
//	deleting the file.
//
//	Implemented as three separate routines:
//	  FileWrite -- write the file
//	  FileRead -- read the file
//	  PerformanceTest -- overall control, and print out performance #'s
//----------------------------------------------------------------------

#define FileName 	"TestFile"
#define Contents 	"1234567890"
#define ContentSize 	strlen(Contents)
#define FileSize 	((int)(ContentSize * 5000))

static void 
FileWrite()
{
    OpenFile *openFile;    
    int i, numBytes;

    printf("Sequential write of %d byte file, in %d byte chunks\n", 
	FileSize, ContentSize);
    if (!fileSystem->Create(FileName, 0)) {
      printf("Perf test: can't create %s\n", FileName);
      return;
    }
    openFile = fileSystem->Open(FileName);
    if (openFile == NULL) {
	printf("Perf test: unable to open %s\n", FileName);
	return;
    }
    for (i = 0; i < FileSize; i += ContentSize) {
        numBytes = openFile->Write(Contents, ContentSize, 0);
	if (numBytes < 10) {
	    printf("Perf test: unable to write %s\n", FileName);
	    delete openFile;
	    return;
	}
    }
    delete openFile;	// close file
}

static void 
FileRead()
{
    OpenFile *openFile;    
    char *buffer = new char[ContentSize];
    int i, numBytes;

    printf("Sequential read of %d byte file, in %d byte chunks\n", 
	FileSize, ContentSize);

    if ((openFile = fileSystem->Open(FileName)) == NULL) {
	printf("Perf test: unable to open file %s\n", FileName);
	delete [] buffer;
	return;
    }
    for (i = 0; i < FileSize; i += ContentSize) {
        numBytes = openFile->Read(buffer, ContentSize);
	if ((numBytes < 10) || strncmp(buffer, Contents, ContentSize)) {
	    printf("Perf test: unable to read %s\n", FileName);
	    delete openFile;
	    delete [] buffer;
	    return;
	}
    }
    delete [] buffer;
    delete openFile;	// close file
}

void
PerformanceTest()
{
    printf("Starting file system performance test:\n");
    stats->Print();
    FileWrite();
    FileRead();
    if (!fileSystem->Remove(FileName)) {
      printf("Perf test: unable to remove %s\n", FileName);
      return;
    }
    stats->Print();
}

