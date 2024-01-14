/**
 * Implement some auxiliary functions.
 *
 * @author Yinhe Chen, Jian Lu
 * @version 1.3
 */

#ifndef SSEM_UTIL_H
#define SSEM_UTIL_H
#include <iostream>
#include <vector>
#include "Processor.h"
#include "Store.h"
using namespace std;

//define global variables
extern bool single;
extern bool all;
extern int STORE;
extern int REGISTER;
extern string fileName;

const int MIN_STORE_SIZE = 16;
const int MIN_REGISTER_SIZE = 32;
const int MAX_REGISTER_SIZE = 256;
const string INTRODUCTION = "Please write in this format: \n./SSEM [procedure=<'all'|'single'>] [file=<'filename'>] [store=<'store size'>] [register=<'register size']\nUse command '-h' to view the help file.";
const string PROCEDURE = "Please write in this format: \n./SSEM procedure [all] [single]\nUse command '-h' to view the help file.";
const string STORE_SIZE = "Please write in this format: \n./SSEM store [store size]\nUse command '-h' to view the help file.";
const string REGISTER_SIZE = "Please write in this format: \n./SSEM register [register size]\nUse command '-h' to view the help file.";
const string HELP_FILE = "helpfile";

enum Option {
    PROCESS = 1,
    FILENAME = 2,
    HELP = 3,
    STORESIZE = 4,
    REGISTERSIZE = 5
};

bool execute(Processor &pc, Store &store);
void fetchExecute(Processor &pc, Store &store);
bool analyticArgs(int argc, char *argv[]);
void display(Processor &pc, Store &st);


#endif //SSEM_UTIL_H