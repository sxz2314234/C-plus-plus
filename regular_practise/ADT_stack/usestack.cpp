// usestack.cpp  --testing the Stack class
#include<iostream>
#include"head_stack.cpp"
#include<cctype>

using namespace std;

int main()
{
    stock<unsigned long> st;  //creat an empty
    char ch;
    unsigned long po;
    cout<<"Please enter A to add a purchase order,\n"
    <<"P to process a PO, or Q to quit.\n";
    while(cin>>ch&&toupper(ch)!='Q')
    {
        while(cin.get()!='\n')continue;
        if(!isalpha(ch))
        {
            cout<<'\a';
            continue;
        }
        switch(ch)
        {
            case 'A':
            case 'a':cout<<"Enter a PO number to add: ";
            cin>>po;
            if(st.iffull())cout<<"Stack is already full.";
            else st.push(po);
            break;
            case 'P':
            case 'p':if(st.ifempty())cout<<"Stack is already empty.";
            else
            {
                st.pop(po);
                cout<<"PO #"<<po<<" popped \n";
            }
            break;
        }
        cout<<"Please enter A to add a purchase order,\n"
    <<"P to process a PO, or Q to quit.\n";
    }
    cout<<"Buy\n";
    return 0;
}