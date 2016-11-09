#ifndef SCANNER_H
#define SCANNER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;
int scanner(char *loc,char* arguments[10]);
int create_pdf(char *src, char *dest);
void arguments (char *test[10]);
int delete_pnm(char* src);

#endif // SCANNER_H
