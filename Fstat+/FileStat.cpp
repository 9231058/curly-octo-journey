/*
 * FileStat.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: parham
 */

#include "FileStat.h"
#include "IOExeption.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/fs.h>

namespace File {

int FileStat::getPhysicalBlock(int logicalBlockNumber) const {
	int result = ioctl(fd, FIBMAP, &logicalBlockNumber);
	if (result < 0) {
		throw IOExeption("ioctl failed", strerror(errno));
	}
	return logicalBlockNumber;
}

FileStat::FileStat(char* path) {
	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		throw IOExeption("open failed", strerror(errno));
	}
	this->fd = fd;
	int result = fstat(fd, &fileStatus);
	if (result < 0) {
		throw IOExeption("fstat failed", strerror(errno));
	}
}

FileStat::FileStat(int fd) {
	this->fd = fd;
	int result = fstat(fd, &fileStatus);
	if (result < 0) {
		throw IOExeption("fstat failed", strerror(errno));
	}
}

FileStat::FileStat(FileStat &fileStat) {
	fd = fileStat.fd;
	fileStatus = fileStat.fileStatus;
}

FileStat& FileStat::operator =(FileStat& fileStat) {
	fd = fileStat.fd;
	fileStatus = fileStat.fileStatus;
	return *this;
}

int FileStat::getInode() const {
	return fileStatus.st_ino;
}

int FileStat::getUID() const {
	return fileStatus.st_uid;
}

int FileStat::getLinkNumber() const {
	return fileStatus.st_nlink;
}

int FileStat::getFileSize() const {
	return fileStatus.st_size;
}

int FileStat::getLogicalBlockNumber() const {
	return fileStatus.st_blocks;
}

int* FileStat::getPhysicalBlockList() const {
	int* physicalBlocks = new int[getLogicalBlockNumber()];
	for (int i = 0; i < getLogicalBlockNumber(); i++) {
		physicalBlocks[i] = getPhysicalBlock(i);
	}
	return physicalBlocks;
}

FileStat::~FileStat() {
}

} /* namespace File */
