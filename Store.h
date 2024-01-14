/**
 * Define all the functions referred to the Store.
 *
 * @authors Yinhe Chen, Jian Lu, Haojun Xie, Zhengyi Li
 * @version 1.3
 */

#ifndef SSEM_STORE_H
#define SSEM_STORE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Store {
private:
    vector<vector<char>> store;//2D vector
    int length;
    int width;

public:
    Store(int length, int width);
    bool LoadFileIntoStore(const string fileName);
    vector<char>getInstruction(int i);
    void writeInStore(int i, vector<char> newItem);
    void printStore();
};

#endif //SSEM_STORE_H
