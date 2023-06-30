#include<iostream>
#include<thread>

using namespace std;

void thread_func1(int num) {
    for(int i = 0; i < num; i++) {
        cout << "thread_func1" << endl;
    }
}

class dummy_thread{
public:
    void operator() (int num) {
        for(int i = 0; i < num; i++) {
            cout << "operator " << endl;
        }
    }
};

void test_thread() {
    // function thread
    thread thd(thread_func1, 3);
    // class operator thread
    thread thd2(dummy_thread(), 3);
    // functional, lambda expression
    auto thread_func2 = [](int num) {
        for (int i = 0; i < num; i++) {
            cout << "lambda " << endl;
        }
    };
    thread thd3(thread_func2, 3);
    thd.join();
    thd2.join();
    thd3.join();
    cout << "thread running ... " << endl;
}