/**
 * Define all the functions referred to the accumulator and instruction.
 *
 * @author Yinhe Chen, Jiarong He, Jian lu, Haojun Xie
 * @version 1.3
 */

#ifndef SSEM_PROCESSOR_H
#define SSEM_PROCESSOR_H

#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <vector>

using namespace std;

class Processor {
public:
    Processor(int size);

    virtual ~Processor();

    Processor();
    void increaseCI();
    void decodeOP();
    long long int binToDec(const vector<char>& binSequence);
    vector<char> decToBin(long long int integer, int size);
    const vector<char> &getCi() const;
    const vector<char> &getPi() const;
    const vector<char> &getAcc() const;
    int getOperand() const;
    int getOpcode() const;
    void setCi(const vector<char> &ci);
    void setPi(const vector<char> &pi);
    void setAcc(const vector<char> &acc);

private:
    vector<char> CI; //Control instruction
    vector<char> PI; //Present instruction
    vector<char> ACC; //Accumulator instruction
    int operand;
    int opcode;
    int width;
};


#endif //SSEM_PROCESSOR_H
