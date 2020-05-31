// filehdr.cc 
//	Routines for managing the disk file header (in UNIX, this
//	would be called the i-node).
//
//	The file header is used to locate where on disk the 
//	file's data is stored.  We implement this as a fixed size
//	table of pointers -- each entry in the table points to the 
//	disk sector containing that portion of the file data
//	(in other words, there are no indirect or doubly indirect 
//	blocks). The table size is chosen so that the file header
//	will be just big enough to fit in one disk sector, 
//
//      Unlike in a real system, we do not keep track of file permissions, 
//	ownership, last modification date, etc., in the file header. 
//
//	A file header can be initialized in two ways:
//	   for a new file, by modifying the in-memory data structure
//	     to point to the newly allocated data blocks
//	   for a file already on disk, by reading the file header from disk
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "filehdr.h"


#ifdef LAB5
//----------------------------------------------------------------------
// FileHeader::FileHeader
//  Consturctor, init the parameter
//----------------------------------------------------------------------

FileHeader::FileHeader() {
    type = TypeNor;
    parentSector = -1;
    time(&createTime);
    readTime = createTime;
    writeTime = createTime;
    numBytes= 0;
}

//----------------------------------------------------------------------
// FileHeader::ChangeReadTime
//  Change the time of read time to now
//----------------------------------------------------------------------

void FileHeader::ChangeReadTime() {
    time(&readTime);
    return;
}

//----------------------------------------------------------------------
// FileHeader::ChangeWriteTime
//  Change the time of write time to now
//----------------------------------------------------------------------

void FileHeader::ChangeWriteTime() {
    time(&writeTime);
    return;
}

//----------------------------------------------------------------------
// FileHeader::SetToDir
//  set the file to directory type
//----------------------------------------------------------------------

void FileHeader::SetToDir() {
    type = TypeDir;
    return;
}

//----------------------------------------------------------------------
// FileHeader::IsDir
//  whether this file is directory
//----------------------------------------------------------------------

bool FileHeader::IsDir() {
    return (type == TypeDir);
}


//----------------------------------------------------------------------
// FileHeader::SetParent
//  Set the parent sector
//----------------------------------------------------------------------

void FileHeader::SetParent(int psector) {
    parentSector = psector;
    return;
}
#endif




#ifdef LAB5
//----------------------------------------------------------------------
// FileHeader::Allocate
//  Change the size of the file, allocate more data blocks if size > 0
//  and deallocate if size < 0
//
//  "freeMap" is the bit map of free disk sectors
//  "fileSize" is the bit map of free disk sectors
//----------------------------------------------------------------------
bool FileHeader::Allocate(BitMap *freeMap, int fileSize) {
printf("Allocate %d\n", fileSize);
    if (fileSize == 0) return true;
    if (fileSize > 0) {
        MixDirSector mds;
        int oldSectors = divRoundUp(numBytes, SectorSize);
        int oldMixSectors = mixSectorsNeed(oldSectors);
        int newSectors = divRoundUp(fileSize+numBytes, SectorSize);
        int newMixSectors = mixSectorsNeed(newSectors);
// printf("fileSize %d, oldSectors %d, oldMixS %d, newSectors %d, newMixS %d\n", fileSize, oldSectors, oldMixSectors, newSectors, newMixSectors);
        if (freeMap->NumClear() < newSectors + newMixSectors - oldSectors - oldMixSectors) {
            return false;                   // without enough space
        }

        // map the mixture directory blocks
        int sector = -1;
        int lastSector = -1;
        for (int i = oldMixSectors+1; i <= newMixSectors; ++i) {
            if (i == 1) {
                indirect = freeMap->Find();
// printf("indirect %d\n", indirect);
                continue;
            }
            int index;
            sector = SectorToMixI(i, index);
            if (sector != lastSector) {             // only fetch and write when change
                if (lastSector != -1) mds.WriteBack(lastSector);
                mds.FetchFrom(sector);
                lastSector = sector;
            }
            mds.InDirect[index] = freeMap->Find();

// printf("i = %d, Mix sector %d, index %d, value %d\n", i, sector, index, mds.InDirect[index]);
        }
        if (lastSector != -1) mds.WriteBack(lastSector);
        // map the data blocks
        sector = -1;
        lastSector = -1;
        for (int i = oldSectors; i != newSectors; ++i) {
            if (i < NumDirect) {
                directSector[i] = freeMap->Find();
            }
            else {
                int index;
                sector = SectorToMixD(i, index);
                if (sector != lastSector) {
                    if (lastSector != -1) mds.WriteBack(lastSector);            // write back if change sector
                    mds.FetchFrom(sector);
                    lastSector = sector;
                }
                mds.Direct[index] = freeMap->Find();
// printf("i = %d, Direct index %d, mix sector %d, value %d\n", i, index, sector, mds.Direct[index]);
            }
        }
        if (lastSector != -1) mds.WriteBack(lastSector);
        numSectors = newSectors;
    } else {                          // fileSize < 0
        if (numBytes + fileSize < 0) return false;
        MixDirSector mds;
        int oldSectors = divRoundUp(numBytes, SectorSize);
        int oldMixSectors = mixSectorsNeed(oldSectors);
        int newSectors = divRoundUp(fileSize+numBytes, SectorSize);
        int newMixSectors = mixSectorsNeed(newSectors);

//printf("fileSize %d, oldSectors %d, oldMixS %d, newSectors %d, newMixS %d\n", fileSize+numBytes, oldSectors, oldMixSectors, newSectors, newMixSectors);
        // delete the data blocks
        int sector;
        for (int i = oldSectors-1; i >= newSectors; --i) {
//printf("sector %d\n", i);
            if (i < NumDirect) {
                ASSERT(freeMap->Test(directSector[i]));
                freeMap->Clear(directSector[i]);
            } else {
                int index;
                sector = SectorToMixD(i, index);
                mds.FetchFrom(sector);
                ASSERT(freeMap->Test(mds.Direct[index]));
                freeMap->Clear(mds.Direct[index]);
            }
        }

        // delete the mix directory block
        for (int i = oldMixSectors; i > newMixSectors; --i) {
//printf("mixSector %d\n", i);
            if (i == 1) {
                ASSERT(freeMap->Test(indirect));
                freeMap->Clear(indirect);
                continue;
            }
            int index;
            sector = SectorToMixI(i, index);
            mds.FetchFrom(sector);
            ASSERT(freeMap->Test(mds.InDirect[index]));
            freeMap->Clear(mds.InDirect[index]);
        }

        numSectors = newSectors;
    }

    numBytes += fileSize;
printf("%s:%d\n", __FILE__, __LINE__);
    return true;
}

//----------------------------------------------------------------------
// FileHeader::Deallocate
//  De-allocate all the space allocated for data blocks for this file.
//
//  "freeMap" is the bit map of free disk sectors
//----------------------------------------------------------------------

void FileHeader::Deallocate(BitMap *freeMap) {
    Allocate(freeMap, -numBytes);
    return;
}


//----------------------------------------------------------------------
// FileHeader::mixSearch
//  help function of SectoryToMix, returning the sector number
//
//  num  : search the num th node
//----------------------------------------------------------------------
int FileHeader::mixSearch(int num) {
    num -= 1;
    int index = num % 16;
    num /= 16;
    int sector;
    if (num == 0) sector = indirect;
    else sector = mixSearch(num);
    MixDirSector mds;
    mds.FetchFrom(sector);
    return mds.InDirect[index];
}


//----------------------------------------------------------------------
// FileHeader::SectorToMixI
//  Return the sector of the MixDirSector that contains the indirectly
//  link to the num th MixDirSector
//----------------------------------------------------------------------

int FileHeader::SectorToMixI(int num, int &index) {
    ASSERT(num > 1);
    if (num <= 17) {
        index = num - 2;
        return indirect;
    }
    index = (num-2) % 16;
    num -= 17;
    return mixSearch(num);
}


//----------------------------------------------------------------------
// FileHeader::SectorToMixD
//  Return the sector of the MixDirSector that directly contian the
//  data block as input sector
//----------------------------------------------------------------------

int FileHeader::SectorToMixD(int sector, int &index) {
    if (sector < NumDirect) {
        index = sector;
        return directSector[sector];
    }
    sector -= NumDirect;
    if (sector < 16) {
        index = sector;
        return indirect;
    }
    sector -= 16;
    index = sector % 16;
    return mixSearch(sector/16+1);
}

//----------------------------------------------------------------------
// FileHeader::ByteToSector
//  This new function call the ByteToEntry
//----------------------------------------------------------------------

int FileHeader::ByteToSector(int offset) {
    int sector = offset / SectorSize;
    if (sector < NumDirect) {
        return directSector[sector];
    }
    int index;
    sector = SectorToMixD(sector, index);
    MixDirSector mds;
    mds.FetchFrom(sector);
    return mds.Direct[index];
}

//----------------------------------------------------------------------
// FileHeader::mixSectorNeed
//  The MixDirSector needed by sectors
//----------------------------------------------------------------------

int FileHeader::mixSectorsNeed(int sectors) {
    if (sectors <= NumDirect) return 0;
    sectors -= NumDirect;
    return divRoundUp(sectors, 16);
}


#else
//----------------------------------------------------------------------
// FileHeader::Allocate
//  Initialize a fresh file header for a newly created file.
//  Allocate data blocks for the file out of the map of free disk blocks.
//  Return FALSE if there are not enough free blocks to accomodate
//  the new file.
//
//  "freeMap" is the bit map of free disk sectors
//  "fileSize" is the bit map of free disk sectors
//----------------------------------------------------------------------

bool
FileHeader::Allocate(BitMap *freeMap, int fileSize)
{ 
    numBytes = fileSize;
    numSectors  = divRoundUp(fileSize, SectorSize);
    if (freeMap->NumClear() < numSectors)
	return FALSE;		// not enough space

    for (int i = 0; i < numSectors; i++)
	dataSectors[i] = freeMap->Find();
    return TRUE;
}


//----------------------------------------------------------------------
// FileHeader::ByteToSector
//  Return which disk sector is storing a particular byte within the file.
//      This is essentially a translation from a virtual address (the
//  offset in the file) to a physical address (the sector where the
//  data at the offset is stored).
//
//  "offset" is the location within the file of the byte in question
//----------------------------------------------------------------------

int
FileHeader::ByteToSector(int offset)
{
    return(dataSectors[offset / SectorSize]);
}


//----------------------------------------------------------------------
// FileHeader::Deallocate
// 	De-allocate all the space allocated for data blocks for this file.
//
//	"freeMap" is the bit map of free disk sectors
//----------------------------------------------------------------------

void 
FileHeader::Deallocate(BitMap *freeMap)
{
    for (int i = 0; i < numSectors; i++) {
	ASSERT(freeMap->Test((int) dataSectors[i]));  // ought to be marked!
	freeMap->Clear((int) dataSectors[i]);
    }
}

#endif

//----------------------------------------------------------------------
// FileHeader::FetchFrom
// 	Fetch contents of file header from disk. 
//
//	"sector" is the disk sector containing the file header
//----------------------------------------------------------------------

void
FileHeader::FetchFrom(int sector)
{
    synchDisk->ReadSector(sector, (char *)this);
}

//----------------------------------------------------------------------
// FileHeader::WriteBack
// 	Write the modified contents of the file header back to disk. 
//
//	"sector" is the disk sector to contain the file header
//----------------------------------------------------------------------

void
FileHeader::WriteBack(int sector)
{
    synchDisk->WriteSector(sector, (char *)this); 
}


//----------------------------------------------------------------------
// FileHeader::FileLength
// 	Return the number of bytes in the file.
//----------------------------------------------------------------------

int
FileHeader::FileLength()
{
    return numBytes;
}

//----------------------------------------------------------------------
// FileHeader::Print
// 	Print the contents of the file header, and the contents of all
//	the data blocks pointed to by the file header.
//----------------------------------------------------------------------

void
FileHeader::Print()
{
    int i, j, k;
    char *data = new char[SectorSize];

    printf("FileHeader contents.  File size: %d.\n", numBytes);

#ifdef LAB5
    printf("type %s, parent %d\n", type == TypeDir ? "directory" : "normal", parentSector);
    tm *info;
    info = gmtime(&createTime);
    printf("create: %d/%d/%d %d:%d:%d\n", info->tm_year+1900, info->tm_mon+1, info->tm_mday, (info->tm_hour+8)%24, info->tm_min, info->tm_sec);
    info = gmtime(&readTime);
    printf("last visit: %d/%d/%d %d:%d:%d\n", info->tm_year+1900, info->tm_mon+1, info->tm_mday, (info->tm_hour+8)%24, info->tm_min, info->tm_sec);
    info = gmtime(&writeTime);
    printf("last modified: %d/%d/%d %d:%d:%d\n", info->tm_year+1900, info->tm_mon+1, info->tm_mday, (info->tm_hour+8)%24, info->tm_min, info->tm_sec);

    printf("File blocks:\n");
    for (i = 0; i != numSectors; ++i) {
        printf("%d ", ByteToSector(i*SectorSize));
    }
    printf("\nFile contents:\n");
    for (i = k = 0; i != numSectors; ++i) {
        synchDisk->ReadSector(ByteToSector(i*SectorSize), data);
        for (j = 0; (j != SectorSize) && (k != numBytes); ++j, ++k) {
            if ('\040' <= data[j] && data[j] <= '\176') printf("%c", data[j]);
            else printf("\\%x", (unsigned char)data[j]);
        }
        printf("\n");
    }
    printf("\n==============================================================\n\n");
#else
    printf("File blocks:\n");
    for (i = 0; i < numSectors; i++) printf("%d ", dataSectors[i]);
    printf("\nFile contents:\n");
    for (i = k = 0; i < numSectors; i++) {
    synchDisk->ReadSector(dataSectors[i], data);
        for (j = 0; (j < SectorSize) && (k < numBytes); j++, k++) {
        if ('\040' <= data[j] && data[j] <= '\176')   // isprint(data[j])
        printf("%c", data[j]);
            else
        printf("\\%x", (unsigned char)data[j]);
    }
        printf("\n"); 
    }
#endif
    delete [] data;
}


//----------------------------------------------------------------------
// MixDirSector::FetchFrom
//  Fetch from disk
//----------------------------------------------------------------------

void MixDirSector::FetchFrom(int sectorNumber) {
    synchDisk->ReadSector(sectorNumber, (char*)this);
    return;
}

//----------------------------------------------------------------------
// MixDirSector::WriteBack
//  Write back to disk
//----------------------------------------------------------------------

void MixDirSector::WriteBack(int sectorNumber) {
    synchDisk->WriteSector(sectorNumber, (char*)this);
    return;
}

//----------------------------------------------------------------------
// MixDirSector::Print
// print information
//----------------------------------------------------------------------

void MixDirSector::Print() {
    printf("MixDirSector contents.\n");
    printf("Direct sectors\n");
    for (int i = 0; i != 4; ++i) {
        for (int j = 0; j != 4; ++j) {
            printf("%d\t", Direct[i+j*4]);
        }
        printf("\n");
    }

    printf("InDirect sectors\n");
    for (int i = 0; i != 4; ++i) {
        for (int j = 0; j != 4; ++j) {
            printf("%d\t", InDirect[i+j*4]);
        }
        printf("\n");
    }
    return;
}