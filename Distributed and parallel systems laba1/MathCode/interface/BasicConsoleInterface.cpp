#include "BasicConsoleInterface.h"
#include "../exceptions/number_cast_exception.h"

using namespace std;

 BasicConsoleInterface:: BasicConsoleInterface( string program_name, string recorder_file) {
    log = new BasicLog(program_name,recorder_file);
    this->program_name = program_name;
    this->file_name = recorder_file;
    setlocale(LC_ALL, "russian");
}

void  BasicConsoleInterface::lineIntent() {
    cout << endl << endl;
}

int  BasicConsoleInterface::readNumber() {
    string buffer_string;
    int result_number;
    while (true) {
        cin >> buffer_string;
        if (buffer_string.empty()) {
            cout << "ќшибка.ѕуста€ строка.¬ведите заново: ";
        }
        else {
            try {
                result_number = stoi(buffer_string);
                log->writeInFile("The recordered string is " + buffer_string + ".\n");
                return result_number;
            }
            catch (invalid_argument exception) {
                throw number_cast_exception("It's not number");
            }
           
        }
    }
}


string  BasicConsoleInterface::getFileName() {
    return file_name;
}

string  BasicConsoleInterface::getProgramName() {
    return program_name;
}

int  BasicConsoleInterface::inputNumber(string what_is_number) {
    cout << "¬ведите " + what_is_number + ": ";
    return readNumber();
}

vector<int> BasicConsoleInterface::inputNumberArray(string what_is_number,int count_of_numbers){
    cout << "¬ведите " + what_is_number + ": ";
    if (count_of_numbers < 1)throw  incorrect_input_data_exception("wrong count of numbers in the array");
    vector<int> result;
    for (int i = 0; i < count_of_numbers; i++) {
        result.push_back(readNumber());
    }
    return result;
}


string  BasicConsoleInterface::inputString() {
    string buffer_string;
    while (buffer_string.empty()) {
        getline(cin, buffer_string);
    }
    log->writeInFile("The recordered string is " + buffer_string + ".\n");
    return buffer_string;

}


void  BasicConsoleInterface::printResultString(string message) {
    cout << "Result: " + message << endl;
    log->writeInFile("The displayed string is " + message + ".\n");
}

void  BasicConsoleInterface::printString(string message) {
    cout << message << endl;
    log->writeInFile(message);
}

void  BasicConsoleInterface::printStringLn(string message) {
    cout << message << endl;
    log->writeInFile(message + ".\n");
}

void  BasicConsoleInterface::standartPrologue() {
    cout << "Launching the program: "+program_name + " .Record file is "+file_name + "." << endl;
    log->standartPrologue();
}

void  BasicConsoleInterface::standartEpilogue() {
    cout << "End of the program: " + program_name + " .Record file is " + file_name + "." << endl;
    log->standartEpilogue();
}

void  BasicConsoleInterface::writeExceptionLogInFile(basic_exception exception) {
    log->printExceptionLog(exception);
}
BasicLog*  BasicConsoleInterface::getLog() {
    return log;
}

 BasicConsoleInterface::~ BasicConsoleInterface() {
    delete log;
}