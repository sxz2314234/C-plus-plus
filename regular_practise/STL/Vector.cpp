// Vector.cpp --using generic progamming(STL function)
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

struct Review
{
    string title;
    int rating;
};

bool operator<(const Review &, const Review &);
bool worsethan(const Review &, const Review &);
bool fillReview(Review &);
void showReview(const Review &);

int main()
{
    vector<Review> books;
    Review temp;
    while (fillReview(temp))
        books.push_back(temp);
    if (books.size() > 0)
    {
        cout << "Thank you. You entered the following "
             << books.size() << " ratings:\n"
             << "Rating\tBook\n";
        for_each(books.begin(), books.end(), showReview);
        // the same is:for(auto x:books)showReview(x);
        // or:for(auto pt=books.begin();pt!=books.end();++pt)showReview(*pt);
        // if not using the keyword"auto",we can declare it: vector<Review>::iterator pt;

        sort(books.begin(), books.end());
        cout << "Sorted by title:\nRating\tBook\n";
        for_each(books.begin(), books.end(), showReview);

        sort(books.begin(), books.end(), worsethan);
        cout << "Sorted by rating:\nRating\tBook\n";
        for_each(books.begin(), books.end(), showReview);

        random_device rd; // random seed
        mt19937 g(rd());  // random engine
        shuffle(books.begin(), books.end(), g);
        cout << "After shuffling:\nRating\tBook\n";
        for_each(books.begin(), books.end(), showReview);
    }

    else
        cout << "No entries. ";
    cout << "Bye.\n";
    return 0;
}

bool operator<(const Review &r1, const Review &r2)
{
    if (r1.title < r2.title)
        return true;
    else if (r1.title == r2.title && r1.rating < r2.rating)
        return true;
    else
        return false;
}

bool worsethan(const Review &r1, const Review &r2)
{
    if (r1.rating < r2.rating)
        return true;
    else
        return false;
}

bool fillReview(Review &rr)
{
    cout << "Enter book title (quit to quit) ";
    getline(cin, rr.title);
    if (rr.title == "quit")
        return false;
    cout << "Enter book rating: ";
    if (!(cin >> rr.rating))
        return false;
    while (cin.get() != '\n')
        continue;
    return true;
}

void showReview(const Review &rr)
{
    cout << rr.rating << '\t' << rr.title << endl;
}