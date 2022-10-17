// Author: Atyub Ahmad
// Project: MMHeap
// File: driver.cpp
// driver file

#include "MMHeap.cpp"
#include "Int4MMH.h"

int main(){
    //New MMHeap
    MMHeap<Int4MMH>* mmH = new MMHeap<Int4MMH>(90);

    cout << "INSERTING NUMBERS INTO MMHEAP" << endl;

    mmH->insert(new Int4MMH(6));
    mmH->insert(new Int4MMH(81));
    mmH->insert(new Int4MMH(87));
    mmH->insert(new Int4MMH(14));
    mmH->insert(new Int4MMH(17));
    mmH->insert(new Int4MMH(12));
    mmH->insert(new Int4MMH(28));
    mmH->insert(new Int4MMH(71));
    mmH->insert(new Int4MMH(25));
    mmH->insert(new Int4MMH(80));
    mmH->insert(new Int4MMH(20));
    mmH->insert(new Int4MMH(52));
    mmH->insert(new Int4MMH(78));
    mmH->insert(new Int4MMH(31));
    mmH->insert(new Int4MMH(42));
    mmH->insert(new Int4MMH(31));
    mmH->insert(new Int4MMH(59));
    mmH->insert(new Int4MMH(16));
    mmH->insert(new Int4MMH(24));
    mmH->insert(new Int4MMH(79));
    mmH->insert(new Int4MMH(63));
    mmH->insert(new Int4MMH(18));
    mmH->insert(new Int4MMH(19));
    mmH->insert(new Int4MMH(32));
    mmH->insert(new Int4MMH(13));
    mmH->insert(new Int4MMH(15));
    mmH->insert(new Int4MMH(48));

    mmH->dump();

    cout << "INSERTING 6 MORE NUMBERS INTO MMHEAP" << endl;
    mmH->insert(new Int4MMH(53));
    mmH->insert(new Int4MMH(57));
    mmH->insert(new Int4MMH(13));
    mmH->insert(new Int4MMH(12));
    mmH->insert(new Int4MMH(9));
    mmH->insert(new Int4MMH(10));

    mmH->dump();
    cout << endl;

    cout << "DELETING MIN 3 TIMES" << endl;
    mmH->deleteMin();
    mmH->deleteMin();
    mmH->deleteMin();

    mmH->dump();
    cout << endl;

    cout << "DELETING MAX 3 TIMES" << endl;
    mmH->deleteMax();
    mmH->deleteMax();
    mmH->deleteMax();

    mmH->dump();
    delete mmH;
    cout << endl;


    return 0;
};
