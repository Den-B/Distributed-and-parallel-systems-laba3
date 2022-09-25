#include "BasicLog.h"
#include "../exceptions/basic_exception.h"

BasicLog::BasicLog(string program_name, string file_name) {
    this->log_file_name = file_name;
    this->program_name = program_name;
}

void BasicLog::writeInFile(string message) {
    ofstream file(log_file_name, ios::app);
    if (file.is_open()) {
        file << message;
        file.close();
    }
}

void BasicLog::standartPrologue() {
    this->writeInFile("Begin_of_programm " + program_name + ".\n\n");
}

void BasicLog::standartEpilogue() {
    this->writeInFile("End_of_programm " + program_name + ".\n\n");
}

void BasicLog::printExceptionLog(basic_exception exception) {
    ofstream file(log_file_name, ios::app);
    if (file.is_open()) {
        file << "Exception log:" << endl;
        exception.full_information_about_current_error();
        file.close();
    }
}