/**
 * Implement all the functions referred to the Store.
 *
 * @authors Jian Lu, Haojun Xie, Zhengyi Li
 * @version 1.3
 */
#include "Store.h"

/**
 * constructor with length and width
 * 
 * @param length the length of store
 * @param width the width of store
 * 
 */
Store::Store(int length, int width) {
    this->length = length;
    this->width = width;
    for (int i = 0; i < length; i++) {
        vector<char> line;
        for (int j = 0; j < width; j++) {
            line.push_back('0');
        }
        this->store.push_back(line);
    }

}

/**
 * load file into store
 * 
 * @param fileName the name or path of file
 * @return bool load result
 * 
 */
bool Store::LoadFileIntoStore(const string fileName) {
    ifstream infile(fileName);
    if (!infile.is_open()) {
        cerr << "Can not open file: " << fileName << endl;
        return false;
    }

    string line;
    int row = 0;

    while (getline(infile, line)) {
        vector<char> tempLine;
        for (int i = 0; i < line.size(); i++) {
            if (i < width) {
                tempLine.push_back(line[i]);
            }
        }
        while (tempLine.size() < width){
            tempLine.push_back(' ');
        }
        store[row] = tempLine;

        ++row;

        if (row >= length)
            break;
    }

    infile.close();
    return true;
}

/**
 * get specific instruction
 * 
 * @param i the line which need to be extracted
 * @return all information of this line
 * 
 */
vector<char> Store::getInstruction(int i) {
    return this->store[i];
}

/**
 * write one line into store
 * 
 * @param i the line to write in
 * @param newItem all information to be added
 */
void Store::writeInStore(int i, vector<char> newItem) {
    this->store[i]=newItem;
}

/**
 * print all store
 */
void Store::printStore() {
    cout << "STORE:" << endl;
    for (int i = 0; i < length; i++) {
        printf("%d,\t",i);
        for (int j = 0; j < width; j++) {
            if (store[i][j] == '1') {
                printf("1");
            } else {
                printf("0");
            }
            if ((j + 1) % 4 == 0) {
                printf(" ");
            }
        }
        cout << endl;
    }
    cout << endl;
}