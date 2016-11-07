#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>



using namespace std;
int scanner(char *loc,char* arguments[]);
int create_pdf(char *src, char *dest);
void arguments (char *test[]);
