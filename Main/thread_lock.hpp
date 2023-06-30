#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>

using namespace std;

mutex m;
condition_variable cond;
bool start = false;

void print_thread(int id) {
    cout << "start thread # " << id << endl;
    unique_lock<mutex> lock(m);

    while(!start) {
        cout << "cond \n";
        cond.wait(lock);
    }
    cout << "end thread: # " << id << endl; 
}

void action() {
    unique_lock<mutex> lock(m);
    cout << "weakup " << endl;
    start = true;
    cond.notify_all();
}


void test_lock() {
    thread thd[5];
    for (int i = 0; i < 5; i++) {
        thd[i] = thread(print_thread, i);
    }
    cout << "loading all the thread" << endl;
    action();
    cout << "link thread" << endl;
    for(auto& th: thd) {
        th.join();
    }
    cout << "main thread over" << endl;
}




