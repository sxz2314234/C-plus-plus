// fileio.cpp --saving to a file 
#include<iostream> //not need for many system
#include<fstream>
#include<string>

using namespace std;

int main()
{
    string filename;
    cout<<"Enter name for new file: ";
    cin>>filename;

    // create ouput stream object for new file and call it fout
    ofstream fout(filename.c_str());

    fout<<"For your eyes only!\n";  // write to file
    cout<<"Enter your secret number: ";  // write to screen
    float secret;
    cin>>secret;
    fout<<"Your secret number is "<<secret<<endl;
    fout.close();  // close file

    // creat input stream object for new file and call it fin
    ifstream fin(filename.c_str());
    cout<<"Here are the contents of "<<filename<<":\n";
    char ch;
    while(fin.get(ch))
    cout<<ch;
    cout<<"Done\n";
    fin.close();

    return 0;
}