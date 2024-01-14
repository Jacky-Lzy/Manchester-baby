/**
 * Implement some auxiliary functions.
 *
 * @authors Yinhe Chen, Jian Lu
 * @version 1.3
 */

#include <unordered_map>
#include "Util.h"

bool single = false;
bool all = false;
int STORE = 32;
int REGISTER = 32;
string fileName = "Example.txt";

enum Opcode {
    JMP, // set CI to content of Store location
    JRP, // add content of Store location to CI
    LDN, // load Accumulator with negative form of Store content
    STO, // copy Accumulator to Store location
    SUB, // subtract content of Store location from Accumulator
    SUB_1,// subtract content of Store location from Accumulator
    CMP, // increment CI if Accumulator value negative, otherwise do nothing
    STP, // stop  set Stop lamp and halt machine
    ADD, // add content of Store location to Accumlator 
    MTP, // minus content of Store location to CI
    DIV, // divide content of Store location to CI
    MOD, // mod content of Store location to CI
    SQR, // square content of Store location to CI
    LDP, // load Accumulator to Store content
    MOV,  // load the next content of this line to store content
    AND, // execute AND between ACC and store content
    OR, //execute OR between ACC and store content
    NOT, //execute NOT between ACC and store content
    XOR //execute XOR between ACC and store content
};

/**
 * display the store CI PI ACC
 * 
 * @param pc the processor
 * @param st the store
 * 
 */
void display(Processor &pc, Store &st) {
    st.printStore();
    cout << "CI:" << endl;

    vector<char> temp = pc.getCi();

    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] == '1') {
            printf("1");
        } else {
            printf("0");
        }
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
    }

    cout << endl;
    cout << "PI:" << endl;
    temp = pc.getPi();
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] == '1') {
            printf("1");
        } else {
            printf("0");
        }
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
    }
    cout << endl;
    cout << "ACC:" << endl;
    temp = pc.getAcc();

    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] == '1') {
            printf("1");
        } else {
            printf("0");
        }
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
    }
    cout << endl;
}

/**
 * fetch-decode-execute 
 * 
 * @param pc the processor
 * @param store the store
 * 
 */
void fetchExecute(Processor &pc, Store &store) {
    bool exit = false;
    if (!single && !all) {
        cout << "Initial: " << endl << endl;
        display(pc, store);
    }
    for (int i = 1; !exit; i++) {
        pc.increaseCI(); //Increment
        if (all) {
            display(pc, store);
            cout << endl << "Cycle Number: " << i << endl << "Press enter to continue!" << endl;
            cin.get();
        }
        pc.setPi(store.getInstruction(pc.binToDec(pc.getCi()))); //Fetch
        if (all) {
            display(pc, store);
            cout << endl << "Cycle Number: " << i << endl << "Press enter to continue!" << endl;
            cin.get();
        }
        pc.decodeOP(); //Decode
        if (all) {
            display(pc, store);
            cout << endl << "Cycle Number: " << i << endl << "Press enter to continue!" << endl;
            cin.get();
        }
        exit = execute(pc, store);//Execute
        if (single || all) {
            display(pc, store);
            cout << endl << "Cycle Number: " << i << endl << "Press enter to continue!" << std::endl;
            cin.get();
        }
    }
    if (!single && !all) {
        cout << "Final: " << endl << endl;
        display(pc, store);
    }
}

/**
 * depends on opcode, finish 18 kind ofe execution
 * 
 * @param pc the processor
 * @param store the store
 * @return bool execute result
 * 
 */
bool execute(Processor &pc, Store &store) {

    auto opcode = static_cast<Opcode>(pc.getOpcode());

    switch (opcode) {
        case JMP:
            //JMP - Jump to the instruction at the store
            pc.setCi(store.getInstruction(pc.getOperand()));
            break;
        case JRP:
            //JRP - Add content of Store line to CI
            pc.setCi(pc.decToBin(pc.binToDec(pc.getCi()) + pc.binToDec((store.getInstruction(pc.getOperand()))), REGISTER));
            break;
        case LDN:
            //LDN - Sets Accumulator to negative of line from the store
            pc.setAcc(pc.decToBin(-pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case STO:
            //STO - Copy content of Accumulator to Store line
            store.writeInStore(pc.getOperand(), pc.getAcc());
            break;
        case SUB:
            //SUB - Subtract content of Store line from Accumulator
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) - pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case SUB_1:
            //SUB - Subtract content of Store line from Accumulator
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) - pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case CMP:
            //CMP - If contents of Accumulator is less than zero, increment the CI;
            if (pc.binToDec(pc.getAcc()) < 0) { pc.increaseCI(); }
            break;
        case STP:
            //STP - STOP
            cout <<"Done!"<<endl;
            return true;
        case ADD:
            //ADD - adds 2 numbers
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) + pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case MTP:
            //MTP - multiply 2 numbers
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) * pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case DIV:
            //DIV - Divides acc by line in store
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) / pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case MOD:
            //MOD - Mods acc by line in the store
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) % pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case SQR:
            // multiplies acc by itself
            pc.setAcc(pc.decToBin(pc.binToDec(pc.getAcc()) * pc.binToDec(pc.getAcc()), REGISTER));
            break;
        case LDP:
            //LDP - Loads positive number;
            pc.setAcc(pc.decToBin(pc.binToDec(store.getInstruction(pc.getOperand())), REGISTER));
            break;
        case MOV: {
            //MOV - move the num in next line into the address this line.
            int address = pc.getOperand();
            pc.increaseCI();
            int num = pc.binToDec(store.getInstruction(pc.binToDec(pc.getCi())));
            store.writeInStore(address, pc.decToBin(num, 32));
            break;
        }
        case AND: {
            //AND - compare store with acc 
            vector<char> temp;
            for (size_t i = 0; i < pc.getAcc().size(); i++) {
                if ((pc.getAcc())[i] == '1' && (store.getInstruction(pc.getOperand()))[i] == '1') {
                    temp.push_back('1');
                } else {
                    temp.push_back('0');
                }
            }
            pc.setAcc(temp);
            break;
        }
        case OR: {
            //OR - compare store with acc 
            vector<char> temp;
            for (size_t i = 0; i < pc.getAcc().size(); i++) {
                if ((pc.getAcc())[i] == '1' || (store.getInstruction(pc.getOperand()))[i] == '1') {
                    temp.push_back('1');
                } else {
                    temp.push_back('0');
                }
            }
            pc.setAcc(temp);
            break;
        }
        case NOT: {
            //NOT - set acc with not acc
            vector<char> temp;
            for (char i: pc.getAcc()) {
                if (i == '1') {
                    temp.push_back('0');
                } else {
                    temp.push_back('1');
                }
            }
            pc.setAcc(temp);
            break;
        }
        case XOR: {
            //XOR - compare store with acc 
            vector<char> temp;
            for (size_t i = 0; i < pc.getAcc().size(); i++) {
                if ((pc.getAcc())[i] == (store.getInstruction(pc.getOperand()))[i]) {
                    temp.push_back('1');
                } else {
                    temp.push_back('0');
                }
            }
            pc.setAcc(temp);
            break;
        }
    }
    return false;
}


/**
 * transform a string to an integer
 * 
 * @param arg the string to be transformed
 * @return transformed integer
 * 
 */
int getIntArg(const string &arg) {
    try {
        return stoi(arg);
    }
    catch (...) {
        return -1;
    }
}

/**
 * analyze command line instruction
 * 
 * @param arg the order of commend
 * @param argv the commend itself
 * @return bool analyze result
 * 
 */
bool analyticArgs(int argc, char *argv[]) {
    int argNum = 1;
    string line;
    ifstream helpfile(HELP_FILE);
    int store_size;
    int register_size;

    unordered_map<string, int> option_map;
    option_map["procedure"] = PROCESS;
    option_map["file"] = FILENAME;
    option_map["help"] = HELP;
    option_map["store"] = STORESIZE;
    option_map["register"] = REGISTERSIZE;

    vector<string> args(argv + 1, argv + argc);

    while (argNum < argc) { //While there are still commands to process
        auto option_value = option_map[args[argNum - 1]];
        // get the option value from the map
        switch (option_value) {
            case PROCESS://Pause point option
                argNum++;
                if (argNum >= argc) {
                    cout << PROCEDURE << endl;
                    return false;
                }
                // move the if statement before the return statement
                if (args[argNum - 1] == "all") { all = true; }
                else if (args[argNum - 1] == "single") { single = true; }
                else {
                    cout << PROCEDURE << endl;
                    return false;
                }
                break;
            case FILENAME:// file option
                argNum++;
                if (argNum >= argc) {
                    cout << INTRODUCTION << endl;
                    return false;
                }
                fileName = args[argNum - 1];
                break;
            case HELP: // -h option
                if (helpfile.is_open()) {
                    while (getline(helpfile, line)) {
                        cout << line << endl;
                    }
                    helpfile.close();
                } else {
                    cout << "Unable to open helpfile, please make sure it has not been deleted or moved.";
                }
                return false;
            case STORESIZE: // store option
                argNum++;
                if (argNum >= argc) {
                    cout << STORE_SIZE << endl;
                    return false;
                }
                // check whether it is an integer
                store_size = getIntArg(args[argNum - 1]);
                if (store_size < MIN_STORE_SIZE) {
                    cout << "Please enter an integer more than 16" << endl;
                    return false;
                } else {
                    STORE = store_size;
                }
                break;
            case REGISTERSIZE: // register option
                argNum++;
                if (argNum >= argc) {
                    cout << REGISTER_SIZE << endl;
                    return false;
                }
                // check whether it is an integer
                register_size = getIntArg(args[argNum - 1]);
                if (register_size < MIN_REGISTER_SIZE || register_size > MAX_REGISTER_SIZE) {
                    // delete the newline character
                    cout << REGISTER_SIZE << endl
                         << "Make sure that the number you enter is between 32 and 256, inclusive."<< endl;
                    return false;
                } else {
                    REGISTER = register_size;
                }
                break;
            default:
                cout << INTRODUCTION << endl;
                return false;
        }
        argNum++;
    }
    return true;
}