/*
 * test.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: parham
 */

#include "FileStat.h"

#include <stdio.h>
#include <stdlib.h>

#include <exception>

int main(int argc, char **argv) {
	try {
		File::FileStat file(*(argv + 1));
		printf(
				"iNode: %d \nLink Number: %d\nLogical Block Number: %d\nSize: %d\n",
				file.getInode(), file.getLinkNumber(),
				file.getLogicalBlockNumber(), file.getFileSize());
		printf("UID : %d\n", file.getUID());
	} catch (const std::exception &exception) {
		fprintf(stderr, "%s\n", exception.what());
	}
}

