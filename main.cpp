#include <iostream>
#include "bornik_algorithm.h"
#include "ringbuffer.h"
#include <algorithm>

using namespace std;

template<class T>
class testPredicate {
public:
    bool operator()(T rhs) {
        return rhs == 5;
    }
};

class Point {
private:
    double x_;
    double y_;

public:
    Point() {
        x_ = 0;
        y_ = 0;
    }

    explicit Point(double x, double y) {
        x_ = x;
        y_ = y;
    }

    friend std::ostream &operator<<(std::ostream &out, const Point &rhs) {
        out << "Point {" << rhs.x_ << ", " << rhs.y_ << "}";
        return out;
    }
};

int main() {
    ringbuffer<int> s(5);
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_front(4);
    s.push_front(5);
    for (auto i = s.begin(); i != s.end(); ++i)
        cout << *i << " ";
    cout << endl;
    s.pop_back();
    s.pop_back();
    s.pop_front();
    s.pop_front();
    s.pop_front();
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_front(4);
    s.push_front(5);
    for (auto i = s.begin(); i != s.end(); ++i)
        cout << *i << " ";
    cout << endl;
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());
    for (auto i = s.begin(); i != s.end(); ++i)
        cout << *i << " ";
    cout << endl;
    cout << bornik::all_of(s.begin(), s.end(), testPredicate<int>()) << " ";
    cout << bornik::any_of(s.begin(), s.end(), testPredicate<int>()) << " ";
    cout << bornik::none_of(s.begin(), s.end(), testPredicate<int>()) << " ";
    cout << bornik::one_of(s.begin(), s.end(), testPredicate<int>()) << " ";
    cout << bornik::is_sorted(s.begin(), s.end(), greater<>()) << endl;
    cout << bornik::is_partitioned(s.begin(), s.end(), testPredicate<int>()) << " ";
    cout << *bornik::find_not(s.begin(), s.end(), 5) << " ";
    cout << *bornik::find_backward(s.begin(), s.end(), 1) << " ";
    cout << bornik::is_palindrome(s.begin(), s.end(), equal_to<>()) << endl;
    s.push_back(-7);
    for (auto i = s.begin(); i != s.end(); ++i)
        cout << *i << " ";
    cout << endl;
    cout << s.front() << " " << s.back() << " " << s.capacity() << " " << s.size() << endl;
    ringbuffer<Point> test(2);
    test.push_back(Point(1, 1));
    test.push_back(Point(1, 3));
    reverse(test.begin(), test.end());
    for (auto i = test.begin(); i != test.end(); ++i)
        cout << *i << " ";
    cout << endl;
    return 0;
}