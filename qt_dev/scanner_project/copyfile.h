#ifndef COPYFILE_H
#define COPYFILE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

/* Copy of file input(input can contain path) to an output file (output can contain path) */
int copyFile(const char* input, const char* output);

#endif // COPYFILE_H
