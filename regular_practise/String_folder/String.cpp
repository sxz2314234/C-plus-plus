#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace sxz
{
    class String
    {
        // data
        char *str;
        int len;
        static const int CINLIM = 80; // cin input limit

    public:
        static int num_strings;
        String(); // default constructor
        String(const char *ch);
        String(const String &);
        ~String();

        friend ostream &operator<<(ostream &, const String &);
        friend istream &operator>>(istream &, String &);
        friend bool operator<(const String &, const String &);
        friend bool operator>(const String &, const String &);
        friend bool operator==(const String &, const String &);
        friend String operator+(const String &, const String &);
        String &operator=(const String &);
        String &operator=(const char *);
        char &operator[](int i);
        const char &operator[](int i) const;
    };
    String::String()
    {
        len = 0;
        str = new char[1];
        str[0] = '\0';
        num_strings++;
    }
    String operator+(const String &str1, const String &str2)
    {
        int total_len = str1.len + str2.len;
        char *temp = new char[total_len + 1];
        int num = 0;
        while (str1[num] != '\0' || str2[num] != '\0')
        {
            if (num < str1.len)
                temp[num] = str1[num];
            if (num < str2.len)
                temp[num + str1.len] = str2.str[num];
            num++;
        }
        temp[total_len] = '\0';
        String temp_string(temp);
        delete[] temp;
        return temp_string;
    }
    istream &operator>>(istream &in, String &st)
    {
        char temp[String::CINLIM];
        cin.get(temp, String::CINLIM);
        if (in)
            st = temp;
        while (in && in.get() != '\n')
            continue;
        return in;
    }
    bool operator<(const String &str1, const String &str2)
    {
        return std::strcmp(str1.str, str2.str);
    }
    bool operator>(const String &str1, const String &str2)
    {
        return str2 < str1;
    }
    bool operator==(const String &str1, const String &str2)
    {
        return std::strcmp(str1.str, str2.str) == 0;
    }
    char &String::operator[](int i)
    {
        return str[i];
    }
    const char &String::operator[](int i) const
    {
        return str[i];
    }
    String &String::operator=(const char *ch)
    {
        delete[] str;
        len = std::strlen(ch);

        str = new char[len + 1];
        std::strcpy(str, ch);
        num_strings++;
        return *this;
    }
    // duplicating constructor
    String::String(const String &string)
    {
        len = string.len;
        str = new char[len + 1];
        std::strcpy(str, string.str);
        ++num_strings;
    }
    String::String(const char *c)
    {
        len = std::strlen(c);
        str = new char[len + 1];
        std::strcpy(str, c);
        ++num_strings;
    }
    String::~String()
    {
        delete[] str;
        --num_strings;
    }
    ostream &operator<<(ostream &out, const String &string)
    {
        out << string.str;
        return out;
    }
    String &String::operator=(const String &string)
    {
        if (this == &string)
            return *this;

        delete[] str;
        len = string.len;
        str = new char[len + 1];
        std::strcpy(str, string.str);
        ++num_strings;
        return *this;
    }
    int String::num_strings = 0;
} // namespace sxz
