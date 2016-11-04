#ifndef COPYFILE_H
#define COPYFILE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

/* Copy of file input to an output file (output can contain path) */
void copyFile(const char* input, const char* output)
{
    // Open input file
    ifstream input_file(input, ios::binary);

    // Error handling
    if (input_file.fail()) {
        cout << "The file couldn't be opened" << endl;
        exit(0);
    }

    // Open output file
    ofstream output_file(output, ios::binary);

    // Copy file from input to output
    while (!input_file.eof()) {
        char buf[256];
        input_file.read(buf, sizeof(buf));
        output_file.write(buf, sizeof(buf));
    }

    // Closing input and output
    input_file.close();
    output_file.close();
}
#endif // COPYFILE_H
