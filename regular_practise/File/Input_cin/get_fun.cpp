// get_fun.cpp --using get() and getline()
#include <iostream>

const int Lim = 255;

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    char input[Lim];

    cout << "Enter a string for getline() processing:\n";
    cin.getline(input, Lim, '#'); // enter: Please pass\n me a #3 melon
    cout << "Here is your input:\n";
    cout << input << "\nDone with phase 1\n";

    char ch;
    cin.get(ch);
    cout << "The next input character is " << ch << endl;
    if (ch != '\n')
        cin.ignore(Lim, '\n');  // discard the rest of line
    
    // while ((ch = cin.get()) != EOF)
    //     cout << (char)ch << " ";

    cout<<"Enter a string for get() processing:\n";
    cin.get(input,Lim,'#');
    cout<<"Here is your input:\n";
    cout<<input<<"\nDone with phase 2\n";

    cin.get(ch);
    cout<<"The next input character is "<<ch<<endl;

    return 0;
}