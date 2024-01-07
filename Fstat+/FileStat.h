/*
 * FileStat.h
 *
 *  Created on: Jun 23, 2014
 *      Author: parham
 */

#ifndef FILESTAT_H_
#define FILESTAT_H_

#include <sys/stat.h>

namespace File {

class FileStat {
private:
	int fd;
	struct stat fileStatus;
public:

private:
	int getPhysicalBlock(int logicalBlockNumber) const;
public:
	FileStat(char* path);
	FileStat(int fd);
	FileStat(FileStat &fileStat);
	FileStat& operator=(FileStat &fileStat);
	int getInode() const;
	int getUID() const;
	int getLinkNumber() const;
	int getLogicalBlockNumber() const;
	int getFileSize() const;
	int* getPhysicalBlockList() const;
	virtual ~FileStat();
};

} /* namespace File */

#endif /* FILESTAT_H_ */
