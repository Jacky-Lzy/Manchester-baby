/**
 * Implement all the functions referred to the accumulator and instructions
 *
 * @authors Yinhe Chen, Jiarong He, Jian lu, Haojun Xie
 * @version 1.3
 */

#include "Processor.h"

Processor::Processor() {

}

/**
 * Constructor
 * @param size the length of CI, PI, ACC
 */
Processor::Processor(int size) : width(size) {
    CI.resize(width);
    PI.resize(width);
    ACC.resize(width);

    for (int i = 0; i < width; i++) {
        CI[i] = '0';
        PI[i] = '0';
        ACC[i] = '0';
    }
    operand = 0;
    opcode = 0;
}

/**
 * Destructor
 */
Processor::~Processor() {

}

/**
 * Get the value of CI
 * @return vector the value of CI
 */
const vector<char> &Processor::getCi() const { return CI; }

/**
 * Get the value of PI
 * @return vector the value of PI
 */
const vector<char> &Processor::getPi() const { return PI; }

/**
 * Get the value of ACC
 * @return vector the value of ACC
 */
const vector<char> &Processor::getAcc() const { return ACC; }

/**
 * Get the value of operand
 * @return vector the value of operand
 */
int Processor::getOperand() const { return operand; }

/**
 * Get the value of opcode
 * @return vector the value of opcode
 */
int Processor::getOpcode() const { return opcode; }

/**
 * Set the value of CI
 * @param ci control instruction
 */
void Processor::setCi(const vector<char> &ci) { CI = ci; }

/**
 * Set the value of PI
 * @param pi present instruction
 */
void Processor::setPi(const vector<char> &pi) { PI = pi; }

/**
 * Set the value of ACC
 * @param acc accumulator
 */
void Processor::setAcc(const vector<char> &acc) { ACC = acc; }

/**
 * CI increases 1 automatically each time
 */
void Processor::increaseCI() {
    bool mark = true;
    int i = 0;

    while (mark) {
        if (i >= CI.size()) {
            // Out of bounds, add '0' to the highest bit
            CI.push_back('0');
            mark = false;
        } else if (CI[i] == '0') {
            CI[i] = '1';
            mark = false;
        } else {
            CI[i] = '0';
        }
        ++i;
    }
}

/**
 * Decode the operand and opcode
 */
void Processor::decodeOP() {
    // Extract operand and opcode
    vector<char> operandBinary(PI.begin(), PI.begin() + 6);
    vector<char> opcodeBinary(PI.begin() + 13, PI.begin() + 19);

    operand = binToDec(operandBinary);
    opcode = binToDec(opcodeBinary);
}

/**
 * Transform binary number to decimal number
 * @param binSequence the binary number that need to be transformed
 * @return the decimal number
 */
long long int Processor::binToDec(const vector<char> &binSequence) {
    // By default, the last bit of the binary sequence is a positive and negative discriminator
    int index = 1;
    long long int Dec = 0;
    int i;

    for (i = 0; i < binSequence.size() - 1; i++) {
        if (binSequence[i] == '1') {
            Dec += index;
        }
        index = index << 1;
    }

    if (binSequence[i] == '0') {
        return Dec;
    } else {
        return 0 - Dec;
    }

}

/**
 * Transform decimal number to binary number
 * @param integer the number that need to be transformed
 * @param size the size of the binary number
 * @return vector which store the binary number
 */
vector<char> Processor::decToBin(long long int integer, int size) {
    /*
     * Here, if the generated binary sequence is greater than or equal to size,it defaults to positive;
     * otherwise, the last digit of the returned sequence identifies positive or negative
     */
    vector<char> bin;
    int num;
    if (integer < 0) {
        num = -integer;
    } else {
        num = integer;
    }

    while (num != 0) {
        if (num % 2 == 0) {
            bin.push_back('0');
        } else {
            bin.push_back('1');
        }
        num = num >> 1;
    }

    while (bin.size() < size - 1) {
        bin.push_back('0');
    }

    if (integer < 0 && bin.size() == size - 1) {
        bin.push_back('1');
    } else if (bin.size() == size - 1) {
        bin.push_back('0');
    }

    return bin;
}