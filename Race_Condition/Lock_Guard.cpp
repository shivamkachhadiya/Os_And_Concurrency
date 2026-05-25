//
// Created by shiva on 25-05-2026.
//
#include<iostream>
#include <mutex>
#include<thread>
using namespace std;
int counter=0;
mutex mtx;
void add() {
    for (int i=0;i<200000;i++) {
        lock_guard<mutex>lock(mtx);
        counter++;
    }
}

int main() {
    thread t1(add);
    thread t2(add);
    t1.join();
    t2.join();
    cout<<counter<<endl;
    return 0;
}