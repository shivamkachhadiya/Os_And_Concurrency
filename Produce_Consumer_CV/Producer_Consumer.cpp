//
// Created by shiva on 26-05-2026.
//

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
using namespace std;

queue<int>buffer;
mutex mtx;
condition_variable cv;
int BUFFER_MAX=5;
int TOTAL=10;

void producer() {
    for (int i=1;i<=TOTAL;i++) {

        unique_lock<mutex>lock(mtx);

        //buffer full hei to wait kro

        while (buffer.size()==BUFFER_MAX) {
            cout<<"Producer: Buffer Full! wait kar rha hoon...\n";
            cv.wait(lock);
        }

        //item dala

        buffer.push(i);
        cout<<"Producer: item "<<i<<" dala . buffer size = "<<buffer.size()<<endl;

        cv.notify_one();   //consumer ko jagaooo;


    }
}

void consumer() {
    int consumed=0;

    while (consumed<TOTAL) {
        unique_lock<mutex>lock(mtx);

        //buffer empty hei to wait kro

        while (buffer.empty()) {
            cout<<"Consumer: Buffer Empty ! wait kar raha hoon...\n";
            cv.wait(lock);
        }

        int item=buffer.front();
        buffer.pop();
        consumed++;
        cout<<"Consumer: Item "<<item<<" nikala. buffer size = "<<buffer.size()<<endl;
        cv.notify_one();
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout<<"\n sabka kam khatam no deadlock\n";
    return 0;
}