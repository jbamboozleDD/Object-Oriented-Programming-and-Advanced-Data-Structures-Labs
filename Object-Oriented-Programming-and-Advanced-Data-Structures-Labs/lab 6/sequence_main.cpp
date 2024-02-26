#include "node.h"
#include "sequence.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using namespace coen79_lab6;

void printSequence(sequence &s){
    sequence seq(s);
    seq.start();
    // Loop to print the sequence.
    while(seq.is_item()) {
        cout << seq.current() << " ";
        seq.advance();
    }
    cout << endl;
}

int main(){
    sequence seq1;
    seq1.attach(42);
    printSequence(seq1);
    seq1.attach(25);
    printSequence(seq1);
    seq1.attach(2);
    printSequence(seq1);
    seq1.insert(9);
    printSequence(seq1);
    seq1.insert(17);
    printSequence(seq1);
    seq1.attach(13);
    printSequence(seq1);

    cout << " *** End Removal Test *** " << endl;
    seq1.end();
    if(seq1.is_item()){
        seq1.remove_current();
    }
    printSequence(seq1);

    cout << " *** Start Removal Test *** " << endl;
    seq1.start();
    if(seq1.is_item()){
        seq1.remove_current();
    }
    printSequence(seq1);

    cout << " *** Middle Removal Test *** " << endl;
    seq1.start();
    seq1.advance();
    seq1.remove_current();
    printSequence(seq1);

    cout << " *** First Assignment Test *** " << endl;
    sequence seq2 = seq1;
    seq1.attach(5);
    printSequence(seq1);
    printSequence(seq2);
    seq2.insert(18);
    seq2.attach(92);
    printSequence(seq2);

    cout << " *** More Assignment Tests *** " << endl;
    sequence seqA;
    sequence seqEmpty;
    sequence seqOneItem;
    sequence seqTenItems;
    seqA.attach(0);
    seqA.attach(1);
    seqA.attach(2);
    seqA.attach(3);
    seqA.attach(4);
    seqOneItem.attach(1.001);
    seqTenItems.attach(0);
    seqTenItems.attach(1);
    seqTenItems.attach(2);
    seqTenItems.attach(3);
    seqTenItems.attach(4);
    seqTenItems.attach(5);
    seqTenItems.attach(6);
    seqTenItems.attach(7);
    seqTenItems.attach(8);
    seqTenItems.attach(9);
    printSequence(seqA);
    cout<<endl;
    printSequence(seqOneItem);
    cout << "Is item: " << seqA.is_item() << endl;
    seqOneItem.advance();
    seqA = seqOneItem;
    printSequence(seqA);
    cout << "Is item: " << seqA.is_item() << endl;
    seqTenItems.start();
    seqA = seqTenItems;
    printSequence(seqA);
    cout << "Is item: " << seqA.is_item() << endl;
    for (int i = 0; i < 4; ++i){
        seqTenItems.advance();
    }
    seqA = seqTenItems;
    printSequence(seqA);
    cout << "Is item: " << seqA.is_item() << endl;
    seqTenItems.end();
    seqA = seqTenItems;
    printSequence(seqA);
    cout << "Is item: " << seqA.is_item() << endl;
    seqTenItems.advance();
    seqA = seqTenItems;
    printSequence(seqA);
    cout << "Is item: " << seqA.is_item() << endl;

    cout << " *** Lab Example *** " << endl;
    sequence labsequence;
    cout << "Size: " << labsequence.size() << endl;
    cout << "Is_Item: " << labsequence.is_item() << endl;
    labsequence.insert(12);
    printSequence(labsequence);
    labsequence.insert(17);
    printSequence(labsequence);
    labsequence.advance();
    cout << "Is_Item: " << labsequence.is_item() << endl;
    labsequence.insert(7);
    printSequence(labsequence);
    labsequence.attach(4);
    printSequence(labsequence);
    labsequence.advance();
    labsequence.advance();
    cout << "Size: " << labsequence.size() << endl;
    cout << "Is_Item: " << labsequence.is_item() << endl;
    labsequence.insert(3);
    printSequence(labsequence);
    labsequence.advance();
    labsequence.remove_current();
    printSequence(labsequence);
    labsequence.advance();
    labsequence.remove_current();
    printSequence(labsequence);
    labsequence.advance();
    labsequence.attach(11);
    printSequence(labsequence);
    labsequence.start();
    cout << "Start: " << labsequence.current() << endl;
    labsequence.end();
    cout << "End: " << labsequence.current();
}