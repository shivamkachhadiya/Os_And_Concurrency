//
// Created by shiva on 25-05-2026.
//
#include<iostream>
#include<thread>
using namespace std;

void MyTask(int id) {
    cout<<"This is my Task..."<<"thread .."<<id<<"is running..."<<this_thread::get_id()<<endl;
}

int main() {
    cout<<"Main thread id="<<this_thread::get_id()<<endl;
    cout<<"Cpu core avialable="<<thread::hardware_concurrency()<<endl;

    thread t1(MyTask,98);
    thread t2(MyTask,12);
    thread t3(MyTask,44);

    t1.join();
    t2.join();
    t3.join();

    cout<<"All threads DONE..."<<endl;
    return 0;
}