//
// Created by shiva on 25-05-2026.
//
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex printer;
mutex scanner;

void rajuKaKaam() {
    // Dono ek saath lo — ya dono milenge ya dono nahi milenge
    lock(printer,scanner);

    // adopt_lock matlab: hum khud lock kar chuke hain yad rakhna, tum sirf unlock krna
    // lock_guard sirf manage karega ab
    lock_guard<mutex>printerLock(printer,adopt_lock);
    lock_guard<mutex>scannerLock(scanner,adopt_lock);

    cout<<"Raju: Printer aur Scanner dono milte ! Kaam kar rha hoon....\n";
    //kam karo
    //scope end -> dono auto unlock
}

void shyamKaKaam() {
    //same dono ek sath lo
    lock(printer,scanner);

    lock_guard<mutex>printerLock(printer,adopt_lock);
    lock_guard<mutex>scannerLock(scanner,adopt_lock);
    cout<<"Shyam: printer aut scanenr dono mile ! kam kar rha hun,,,,,\n";
}

int main() {
    thread raju(rajuKaKaam);
    thread shyam(shyamKaKaam);

    raju.join();
    shyam.join();

    cout<<"dono ka kam done no deadlock/...."<<endl;

    return 0;
}
//
//
// Normal lock_guard — khud lock karta hai
// lock_guard<mutex> lock(mtx);
// // lock_guard ne khud mtx lock kiya
// // scope end pe unlock karega
//
// adopt_lock wala lock_guard — lock NAHI karta
// lock(printer, scanner);  // pehle se lock ho gaya
//
// lock_guard<mutex> l1(printer, adopt_lock);
// // adopt_lock matlab:
// // "printer pehle se locked hai
// //  tu mat karna lock
// //  sirf end mein unlock karna"
//
// adopt_lock ka kaam sirf itna hai
// Normal lock_guard:
// Constructor → lock karo + end mein unlock karo
//
// adopt_lock wala lock_guard:
// Constructor → sirf yaad rakho (lock mat karo) + end mein unlock karo
//
// Agar adopt_lock na likhe toh kya hoga?
// lock(printer, scanner);   // pehle se locked

// lock_guard<mutex> l1(printer); // dobara lock karne ki koshish
// // DEADLOCK — khud apne aap se

// Thread apna hi lock dobara lene ki koshish karega. Forever ruk jaayega.
//
// Ek line mein
//
// adopt_lock = "yaar pehle se locked hai, tu sirf end mein unlock karna"