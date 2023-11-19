#include <iostream>
#include <fstream>
using namespace std;
const int name = 50;
int main()
{
    ofstream outfile;
    ifstream infile;
    char file_name[name];
    cout << "please enter the name of the file you want to write.";
    cin >> file_name;
    outfile.open(file_name); // associate infile with input
    infile.open(file_name);
    // output to the text file
    int count = 1;
    for (; count <= 100; ++count)
    {
        outfile << '\t' << count;
        if (count % 10 == 0)
            outfile << endl;
    }
    outfile.close();
    // input from the text file
    if (!infile.is_open()) // failed to open file
    {
        cout << "Could not open the file " << file_name << endl;
        cout << "Programe terminating.\n";
        exit(EXIT_FAILURE);
    }
    int value;
    while (infile.good())
    {
        infile >> value;
        cout << value;
        if (!(value % 10))
            cout << '\t';
    }
    if (infile.eof())
        cout << "End of file reached.\n";
    else if (infile.fail())
        cout << "Input terminated by data mismatch.\n";
    else
        cout << "Input terminated for unknown reason.\n";
    infile.close();
    return 0;
}
