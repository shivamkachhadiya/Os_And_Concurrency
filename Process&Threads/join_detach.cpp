//
// Created by shiva on 25-05-2026.
//
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void slowWork() {
    this_thread::sleep_for(chrono::milliseconds(500));
    cout<<"slow work done..."<<endl;
}
void quickWork() {
    cout<<"Qucik work done..."<<endl;
}

int main() {
    thread t1(slowWork);
    cout<<"wait for t1..."<<endl;
    t1.join();
    cout<<"t1 finish . main continues.."<<endl;


    thread t2(quickWork);
    t2.detach();
    cout<<"t2 detach. main does not wait..."<<endl;

    this_thread::sleep_for(chrono::milliseconds(100));
    return 0;
}




