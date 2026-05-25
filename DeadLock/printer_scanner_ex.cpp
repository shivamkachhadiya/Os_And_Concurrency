//
// Created by shiva on 25-05-2026.
//
#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;

mutex printer;
mutex scanner;

void rajuKaKaam() {
    //raju aaya printer pehele liye
    cout<<"Raju: Printer lene ja rha hun...\n";
    lock_guard<mutex>printerLock(printer); //printer lock kar diya
    cout<<"Raju: Printer mila user kr rha hunn...\n";

    //raju printer use kr rha h tabhi shyam aata hei...
    this_thread::sleep_for(chrono::milliseconds(500));

    //ab raju ko scanner bhi chahiyeee
    cout<<"Raju: Scanner bhi chahiye, lene ja rha hun...\n";
    lock_guard<mutex>scannerLock(scanner); //scanner lock kr diya
    cout<<"Raju: Scanner use kr rha hunnn.....\n";
}

void shyamKaKaam() {
    //shyam aaya pehele scanner liya
    cout<<"Shyam: Scanner lene ja rha hun...\n";
    lock_guard<mutex>scannerLock(scanner);  //scanner lock kar diya
    cout<<"Shyam: Scanner mila use kr rha hun....\n";

    // Shyam scanner use kar raha hai
    this_thread::sleep_for(chrono::milliseconds(500));

    // Ab Shyam ko printer bhi chahiye
    cout<<"Shyam: Printer Bhi chahiye, lene ja rha hun...\n"<<endl;
    // Raju ne printer pehle se liya hua hai!
    // Shyam yahaan RUKA — printer ka wait kar raha hai
    lock_guard<mutex>printerLock(printer);
    cout<<"Shyam: printer bhi mil gaya...\n";  // ye kabhi nahi chalega
}

int main() {
    thread raju(rajuKaKaam);
    thread shyam(shyamKaKaam);

    raju.join();
    shyam.join();

    cout<<"kaam khatammm\n";
    return 0;
}


//
// TIME    RAJU (Thread1)              SHYAM (Thread2)
// ─────────────────────────────────────────────────────
// t=0ms   Start hua                  Start hua
//
// t=1ms   "Printer lene ja raha"
//         print kiya ✅
//
// t=2ms   Printer ka LOCK liya 🔒
//         Printer ab Raju ka hai
//
// t=3ms   "Printer mila!" print ✅
//
// t=4ms   sleep(100ms) 😴            "Scanner lene ja raha"
//                                    print kiya ✅
//
// t=5ms   😴 so raha hai             Scanner ka LOCK liya 🔒
//                                    Scanner ab Shyam ka hai
//
// t=6ms   😴 so raha hai             "Scanner mila!" print ✅
//
// t=7ms   😴 so raha hai             sleep(100ms) 😴
//
// ─────────────────────────────────────────────────────
//         100ms baad dono jaage
// ─────────────────────────────────────────────────────
//
// t=104ms "Scanner chahiye..."       😴 abhi so raha hai
//         print kiya ✅
//
// t=105ms Scanner ka LOCK            "Printer chahiye..."
//         LENE GAYA...               print kiya ✅
//         ❌ RUKA
//         Shyam ne scanner           Printer ka LOCK
//         pakda hua hai!             LENE GAYA...
//         Raju yahan RUKA 🛑         ❌ RUKA
//                                    Raju ne printer
//                                    pakda hua hai!
//                                    Shyam yahan RUKA 🛑
//
// ─────────────────────────────────────────────────────
//         DONO RUKE HAIN
//         Koi nahi hatega
//         DEADLOCK 💀
// ─────────────────────────────────────────────────────