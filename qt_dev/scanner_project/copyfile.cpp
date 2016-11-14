#include <copyfile.h>
using namespace std;

int copyFile(const char* input, const char* output)
{
    // Open input file
    ifstream input_file(input, ios::binary);

    // Error handling
    if (input_file.fail()) {
        cout << "The file couldn't be opened" << endl;
        return -1;
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

    return 0;
}
