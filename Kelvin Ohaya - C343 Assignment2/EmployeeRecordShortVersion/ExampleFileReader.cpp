// author Dr.H on 10/25/2019
// modified by Kelvin Ohaya on 10/6/2025
// compiled with g++ -std=c++1z driver.cpp
// This code read EmployeeRecords from a text file into a Sequence, then output the data.

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <cctype>
#include "../../Kelvin Ohaya - C343-Assignment1/src/Sequence/Sequence.h"
#include "EmployeeRecord.h"

typedef Sequence<EmployeeRecord> EmployeeSequence;
// wanted to try the smart pointers
typedef std::vector<std::unique_ptr<EmployeeRecord>> EmployeeRecords;

EmployeeRecords eRecords;

// returns  vector of split words
auto split(const string &s, char delim)
{
    std::vector<string> out;
    std::string token;
    std::stringstream ss(s);
    while (std::getline(ss, token, delim))
    {
        out.push_back(token);
    }
    return out;
};

// CSV line parser that handles quoted fields and commas inside quotes
std::vector<std::string> parseCSVLine(const std::string &line)
{
    std::vector<std::string> fields;
    std::string currentString;
    // checker for if the string is in quotes
    bool inQuotes = false;
    // use size_t for object sizes
    for (size_t i = 0; i < line.size(); ++i)
    {
        char c = line[i];
        if (inQuotes)
        {
            // if we encounter ANOTHER quote, now we have to check if it's an escaped quote, or the end of the field
            if (c == '"')
            {
                // look ahead for escaped quote
                if (i + 1 < line.size() && line[i + 1] == '"')
                {
                    // just add one quote to the string and skip over a character
                    currentString.push_back('"');
                    ++i;
                }
                else
                {
                    // End of the field, so just set inQuotes to false and don't do anything
                    inQuotes = false;
                }
            }
            // if it isn't a quote, add the character to the string.
            else
            {
                currentString.push_back(c);
            }
        }
        // cases where the parser hasn't encountered any quotes yet
        else
        {
            // on the first quote, set inQuotes to true
            if (c == '"')
            {
                inQuotes = true;
            }
            // if the parser encounters a comma, add what is currently in the string to the fields vector, and clear the string.
            else if (c == ',')
            {
                fields.push_back(currentString);
                currentString.clear();
            }
            // normal case: just add the current character to the string
            else
            {
                currentString.push_back(c);
            }
        }
    }
    // at the end of the line, push whatever is left in the current string back into the fields vector
    fields.push_back(currentString);
    // return the parsed input as a vector
    return fields;
}

// parse salary string like "$141,604 " -> 141604
int parseSalary(const string &rawString)
{
    // store the number in a string first
    string digits;
    for (char c : rawString)
    {
        // using unsigned char to ensure that no negative salaries are stored
        // add the digit if the char is a number
        if (std::isdigit((unsigned char)c))
            digits.push_back(c);
    }
    // if there are no digits, there is no salary
    if (digits.empty())
        return 0;

    // return the integer version of the string, or 0 if any issues happen
    try
    {
        return std::stoi(digits);
    }
    catch (...)
    {
        return 0;
    }
}

// Helper function for selection sort
// find index of employeeRecord with the smallest salary in pointerVector ranging from 'start' to the end of the vector
int findMinIndex(const EmployeeRecords &pointerVector, int start)
{
    // I did this before I found out about size_t
    size_t pointerVectorSize = pointerVector.size();
    if (pointerVectorSize == 0 || start >= pointerVectorSize)
        return -1;

    // set the first element to the smallest initially
    int minIndex = start;
    int currentSalary = pointerVector[start]->salary;

    // iteratively check each elemen't salary property to see if it is the lowest
    for (size_t i = start + 1; i < pointerVectorSize; ++i)
    {
        if (pointerVector[i]->salary < currentSalary)
        {
            minIndex = i;
            currentSalary = pointerVector[i]->salary;
        }
    }
    // return the lowest index
    return minIndex;
}

// selectionSort algorithm. Sorts the vectors based on the salary the element points to.
void selectionSortVector(EmployeeRecords &pointerVector)
{
    // sort based on employee salary using selection sort
    size_t pointerVectorSize = pointerVector.size();
    for (size_t i = 0; i + 1 < pointerVectorSize; ++i)
    {
        size_t minIndex = findMinIndex(pointerVector, i);
        // We won't do anything if:
        //  - minIndex is the first element (already sorted so that's fine)
        //  - minIndex is the current element (everything before is sorted so that's fine too)
        if (minIndex >= 0 && minIndex != i)
        {
            // use classic temporary variable switch to switch the numbers
            // move ownership of pointers so program knows who's responsible for deletion
            auto temp = std::move(pointerVector[minIndex]);
            pointerVector[minIndex] = std::move(pointerVector[i]);
            pointerVector[i] = std::move(temp);
        }
    }
}

// reading in data from the csv file
void doInputPersonDataFromFile(EmployeeSequence &personData, EmployeeRecords &pointerVector)
{
    string filename = "EmployeeSampleData/Employee Sample Data.csv";
    // file instream
    ifstream infile(filename);
    EmployeeRecord record;
    int dataSize;

    // if file reading doesnt work
    if (!infile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    if (infile.is_open())
    {
        // Check for a first line
        string firstLine;
        if (!std::getline(infile, firstLine))
        {
            cout << "File is empty" << endl;
            return;
        }

        string line;
        int count = 0;

        // iterate through each line
        while (std::getline(infile, line))
        {
            if (line.empty())
                continue;
            std::vector<string> cols;
            cols = parseCSVLine(line);

            EmployeeRecord rec;
            // map commonly used columns: EEID, Full Name, Job Title, Department, Gender, Age, Annual Salary, City
            rec.name = cols[1];
            rec.salary = parseSalary(cols[9]);
            rec.city = cols[12];
            rec.jobTitle = cols[2];
            rec.address = cols[12] + ", " + cols[11];
            // Parse age from string to int (Age is column 5)
            try
            {
                rec.age = stoi(cols[7]);
            }
            catch (...)
            {
                rec.age = 0;
            }
            personData.add(rec, count);
            // allocate on heap so pointer remains valid after this loop iteration
            std::unique_ptr<EmployeeRecord> heapRec = std::make_unique<EmployeeRecord>(EmployeeRecord(rec));
            pointerVector.push_back(std::move(heapRec));
            ++count;
        }
        cout << "Number of Records read (TSV): " << count << endl;
    }
} // doInputPersonDataFromFile>

int main(int argc, char *argv[])
{

    EmployeeSequence eSequence;
    cout << "Reading EmployeeRecords from file" << endl;
    doInputPersonDataFromFile(eSequence, eRecords);
    selectionSortVector(eRecords);

    cout << "\nTop 100 Employees By Salary (Descending Order)\n"
         << endl;
    for (int i = 99; i >= 0; --i)
    {
        std::cout << *eRecords[i] << std::endl;
    }
    cout << endl;

    // clean up eRecords
    eRecords.clear();
    cout << "Press any key to continue...";
    getchar();
    return 0;
}
