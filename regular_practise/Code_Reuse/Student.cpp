// define a Student class using containment
#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <valarray>

using std::string;

class Student
{
    // We put the typedef in the class scope in order that
    // only when in the class scope,we can use ArrayDb
    typedef std::valarray<double> ArrayDb;
    string name;    // contained object
    ArrayDb scores; // contained object

    // private method for scores output
    std::ostream &arr_out(std::ostream &os) const;

public:
    Student() : name("Nobody Student"), scores(){};
    explicit Student(const string &s) : name(s), scores(){}; // The keyword ensure to invoke the switch function explicitly
    explicit Student(int n) : name("Nully"), scores(n){};
    Student(const string &n, int s) : name(n), scores(s){};
    Student(const string &s, const ArrayDb &n) : name(s), scores(n){};
    Student(const char *str, const double *db, int n) : name(str), scores(db, n){};
    ~Student(){};
    double Average() const;
    const string &Name() const;
    double &operator[](int i) { return scores[i]; }
    double operator[](int i) const { return scores[i]; }
    // friend
    friend std::istream &operator>>(std::istream &in, Student &stu);
    friend std::ostream &operator<<(std::ostream &in, const Student &stu);
};

// Student class in new version
class newStudent : private string, private std::valarray<double>
{
    typedef std::valarray<double> ArrayDb;

    // private methods to output scores
    std::ostream &arr_out(std::ostream &);

public:
    newStudent() : string("Null student"), ArrayDb(){};
    explicit newStudent(const string &s) : string(s), ArrayDb(){};
    explicit newStudent(int n) : string("Nully"), ArrayDb(n){};
    explicit newStudent(const string &s, int n) : string(s), ArrayDb(n){};
    explicit newStudent(const string &s, const ArrayDb &n) : string(s), ArrayDb(n){};
    explicit newStudent(const char *str, const double *db, int n) : string(str), ArrayDb(db, n){};
    ~newStudent(){};
    double Average() const;
    double &operator[](int i) { return ArrayDb::operator[](i); }
    double operator[](int i) const { return ArrayDb::operator[](i); }
    const string &Name() const;
    // friend
    friend std::istream &operator>>(std::istream &in, newStudent &);
    friend std::ostream &operator<<(std::ostream &in, const newStudent &);
};
#endif