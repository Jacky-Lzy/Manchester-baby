#include<iostream>
#include "Processor.h"
#include "Store.h"
#include "Util.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (!analyticArgs(argc, argv)) { return 0; }

    //Creates Store object
    Store store(STORE, REGISTER);

    //Load file from user into store
    if (!store.LoadFileIntoStore(fileName)) {
        cout << "Error reading file: " << fileName << endl;
        return 0;
    }

    Processor pc (REGISTER);

    fetchExecute(pc, store);

    if (argc == 1) {
        cout << "Use '-h' to view more options" << endl << endl << endl << endl;
    }

    return 0;
}

