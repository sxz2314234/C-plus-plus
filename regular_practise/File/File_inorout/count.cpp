// count.cpp --counting characters in a list of files
// Command lines handling technology
#include<iostream>
#include<fstream>
#include<cstdlib>  // for exit

// the argc is the amount of the arguments in command line,
// then, the argv is an array of point to the arguments
// For example the command line in UNIX or Linux:
// wc report1 report2,report3
// wc is an executable file,the reports are file names  
int main(int argc,char* argv[]) 
{
    using namespace std;
    if(argc==1)  // quit if no argument
    {
        cerr<<"Usage: "<<argv[0]<<"filename[s]\n";
        exit(EXIT_FAILURE);
    }

    ifstream fin;  // open stream
    long count;
    long total=0;
    char ch;

    for(int file=1;file<argc;++file)
    {
        fin.open(argv[file]);  // connect stream to argv[file]
        if(!fin.is_open())
        {
            cerr<<"Could not open "<<argv[file]<<endl;
            fin.clear();
            continue;
        }
        count=0;
        while(fin.get(ch))
        count++;
        cout<<count<<" characters in "<<argv[file]<<endl;
        total+=count;
        fin.clear();  // needed for some implementations
        fin.close();  // disconnect file
    }

    cout<<total<<" characters in all file\n";
    return 0;
}  