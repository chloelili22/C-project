//
// Project 1 Starter Code - DNA Profiling
// Create an app that is able to build DNA strands using ourvector
// implementation and then determine who the DNA matches to in a database.

// The app has 5 commands:
// 1. Load in database - load_db
// 2. Display your data - display
// 3. Load in the dna - load_dna
// 4. Process the DNA - process
// 5. Search the database - search
// 6. Add a new individual to database - add_individual
//
// Author: Simin Li, UIC, Fall 2021
// Assignment: Project 01

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ourvector.h"

using namespace std;

// creat a data structure to group name and countTime vector.
struct Data {
    string name;
    ourvector<int>countTimes;
};

//
// functions declaration:
//
void loadDataFile(ourvector<Data>&People, string fileName,
ourvector<ourvector<char>>&STRs);
void printDNALoaded(ourvector<char>&DNA, bool loaded_dna);
void printDNAProcess(ourvector<ourvector<char>>&STRs,
ourvector<int>&dnaMatch, bool processed_dna);
void displayData(ourvector<Data>&People, ourvector<ourvector<char>>&STRs,
bool loaded_dna, ourvector<char>&DNA);
bool LoadDnaFile(string fileName, ourvector<char>&DNA);
void errorHandle_process(ourvector<ourvector<char>>&STRs, ourvector<char>&DNA);
bool processDNA(ourvector<int>&dnaMatch, ourvector<char>&DNA,
ourvector<ourvector<char>>&STRs, bool loaded_dna);
void retrieveStreak(ourvector<char>&DNA, ourvector<ourvector<char>>&STRs,
int&i, int&y, bool&matches, int&streak);
void searchDB(ourvector<Data>&People, ourvector<int>&dnaMatch,
bool processed_dna, bool loaded_dna, ourvector<ourvector<char>> STRs);
void add_individual(ourvector<Data>&People, ourvector<ourvector<char>> STRs);

//
// loadDataFile(): delete the privious data before loading any data.
// Try to open the input file and see if open successfully.
// If open failed, output error and ends excution of the function. If open
// successfully, read data of every line from input file. Then, extract the
// name and STRdata to store the STR data into STRs vector. Finally, using
// while loop to extract name and STRcounts to store into People vector with
// Data struct.
//
void loadDataFile(ourvector<Data>&People, string fileName,
ourvector<ourvector<char>>&STRs) {
        STRs.clear();
        People.clear();
        cin >> fileName;
        ifstream infile;
        infile.open(fileName);

        bool success = infile.is_open();
        cout << "Loading database..." << endl;

        // check if file can open, if open failed, output error message
        if (!success) {
            cout << "Error: unable to open '" << fileName << "'" << endl;
            return;
        }

        string name, STRdata, line;
        getline(infile, line);
        stringstream db(line);
        // read the line and extract name from the stream
        getline(db, name, ',');

        // loop through first line from input file and extract each STRdata
        while (getline(db, STRdata, ',')) {
            // vector to store characters from each STRdata
            ourvector<char>eachSTR;

            // foreach loop through STRdata to add every character into each
            // STR sequence and store every STR sequence into STRs vector
            for (char c : STRdata)
                eachSTR.push_back(c);

            STRs.push_back(eachSTR);
        }

        // loop through the lines after first one from input file and xtract
        // the names and STRcount from each line
        string temp;
        while (getline(infile, temp)) {
            Data human;
            stringstream eachLine(temp);
            getline(eachLine, human.name, ',');
            string STRcount;

            // using while loop to extract STRcounts and add to countTimes, and
            // then store the infor of name and countTimes into People vector
            while (getline(eachLine, STRcount, ','))
                human.countTimes.push_back(stoi(STRcount));

            People.push_back(human);
        }
}

//
// checkDNALoaded(): check if dna is loaded, return dna data in the vector.
// Otherwise, print out message "no DNA loaded".
//
void printDNALoaded(ourvector<char>&DNA, bool loaded_dna) {
    // loaded DNA successfully
    if (loaded_dna == true) {
        // loop throught the vector DNA and print out each DNA sequence
        for (int i = 0; i < DNA.size(); i++) {
            cout << DNA[i];
        }
        cout << endl;
        cout << endl;
    }
}


//
// checkDNAProcess(): check if DNA data is processed, return every STR
// sequence of STRs vector and the matched time. Otherwise, print out
// message.
//
void printDNAProcess(ourvector<ourvector<char>>&STRs, ourvector<int>&dnaMatch,
bool processed_dna) {
    // loop throught the 2D vector STRs, print out each STRs on the STRs vector
    for (int i = 0; i < STRs.size(); i++) {
        for (int t = 0; t < STRs[i].size(); t++) {
            cout << STRs[i][t];
        }
        // the size of STRs and dnaMatch size should be the same
        // loop throug dnaMatch vector and return the matched time
        cout << ": " << dnaMatch[i] << endl;
    }

    cout << endl;
}


//
// displayData: display the database from text file, which include their
// user name and DNA counted times. Then call function to display DNA loaded
// and process data.
//
void displayData(ourvector<Data>&People, ourvector<ourvector<char>>&STRs,
bool loaded_dna, ourvector<char>&DNA, bool processed_dna,
ourvector<int>&dnaMatch) {
    // check if database is not loaded, output message
    if (People.size() <= 0)
        cout << "No database loaded." << endl;
    else
        cout << "Database loaded: " << endl;

    // loop through the data vector and print out each name
    for (int i = 0; i < People.size(); i++) {
        cout << People[i].name;

        // loop through countTimes vector and print out the counts
        for (int k = 0; k < People[i].countTimes.size(); k++)
          cout << " " << People[i].countTimes[k];

        cout << endl;
    }

    cout << endl;

    // check if DNA loaded, output message
    if (DNA.size() <= 0) {
        cout << "No DNA loaded." << endl << endl;
    } else {
        cout <<"DNA loaded: " << endl;
        // call function to display loaded DNA data
        printDNALoaded(DNA, loaded_dna);
    }

    // process DNA successfully
    if (processed_dna == true) {
       // cout << "DNA has been processed." << endl;
       cout << "DNA processed, STR counts: " << endl;
       // call function to print STRs sequence and the matched time
       printDNAProcess(STRs, dnaMatch, processed_dna);
    } else {
        // processed data loaded failed, output message
        cout << "No DNA has been processed." << endl;
    }
}


//
// LoadDnaFile: delete the prievious DNA database and open and read DNA file
// at first. Then, call display function when the command is display to
// print out the DNA data.
//

bool LoadDnaFile(string fileName, ourvector<char>&DNA) {
    cin >> fileName;
    ifstream infile;
    infile.open(fileName);

    // delete privious DNA data from input DNA file
    DNA.clear();
    bool success = infile.is_open();
    cout << "Loading DNA..." << endl;

    // check if file can open, if open failed, output error message
    if (!success) {
        cout << "Error: unable to open '" << fileName << "'" << endl;
        return false;
    }

    string DNAdata, DNAchar;
    getline(infile, DNAdata);

    // save DNAdata into DNA vector by using push_back function
    for (size_t i = 0; i < DNAdata.size(); i++) {
        DNA.push_back(DNAdata[i]);
    }

    return true;
}


//
// errorHandle_process(): print out error message before loading DNA
// AND database.
//
void errorHandle_process(ourvector<ourvector<char>>&STRs, ourvector<char>&DNA) {
    if (STRs.size() <= 0)
        cout << "No database loaded." << endl;
    else if (DNA.size() <= 0)
        cout << "No DNA loaded." << endl;
    else
        cout << "Processing DNA..." << endl;
}


//
// retrieveStreak(): using for loop to loop through STRs vector, and
// compare each STR sequence with DNA data to check if there is any
// match, then update streak.
//
void retrieveStreak(ourvector<char>&DNA, ourvector<ourvector<char>>&STRs,
int&i, int&y, bool& matches, int&streak) {
    // loop though STRs and check if the first STRs has matches char with DNA
    for (int k = 0; k < STRs[y].size(); k++) {
        // if they do not match, break
        if (DNA[i + k]!= STRs[y][k]) {
            matches = false;
            // every time the STR sequence does not match to the DNA
            // sequence, set streak to 0 and recounting
            streak = 0;
            break;
        }
    }
}

//
// ProcessDNA(): Loop through the DNA sequence from input text file,
// count up the longest consecutive repeated STR sequence for each STR
// listed on the data file.
//
bool processDNA(ourvector<int>&dnaMatch, ourvector<char>&DNA,
ourvector<ourvector<char>>&STRs, bool loaded_dna) {
    errorHandle_process(STRs, DNA);

    if (STRs.size() == 0 || loaded_dna == false) {
         return 0;
    }

    int streak = 0, maxStreak = 0;
    bool matches = true;

    // loop through each STR, compare STR with the first char in DNAsequence
    for (int y = 0; y < STRs.size(); y++) {
        streak = 0, maxStreak = 0;

        // loop through the DNA sequence and stop at the bound of STRs
        for (int i = 0; i <= DNA.size() - STRs[y].size(); i++) {
            matches = true;
            // call function to retrieve streak by comparing STRs with DNA data
            retrieveStreak(DNA, STRs, i, y, matches, streak);

            // if they match, move to next bounded of STRs and increase streak
            if (matches == true) {
                i += STRs[y].size() - 1;
                streak += 1;
                // update maxStreak: it should be greater or equal to streak
                if (maxStreak < streak)
                    maxStreak = streak;
            }
        }

    // save maxStreak into dnaMatch vector
    dnaMatch.push_back(maxStreak);
    }
    return true;
}


//
// searchDB(): using the STR counts (dnaMatch) we found in mileston 4 to
// search the database and find the dnaMatch info match to which people.
// If the dnaMatch is found, return the name of that people. Otherwise,
// print out message.
//

void searchDB(ourvector<Data>&People, ourvector<int>&dnaMatch,
bool processed_dna, bool loaded_dna, ourvector<ourvector<char>> STRs) {
    // check if there is databaded loaded or DNA processed
    if (STRs.size() <= 0) {
        cout << "No database loaded." << endl;
        return;
    } else if (loaded_dna == false) {
        cout << "No DNA loaded." << endl;
        return;
    } else if (processed_dna == false) {
        cout << "No DNA processed." << endl;
        return;
    }

    cout << "Searching database..." << endl;
    bool countTimeMatch = true;

    // loop through each Person in People and the countTimes and compare
    // countTimes with dnaMatch, chack if they are matched.
    // If matches, return the name of that People. If no match,
    // output Not found in database

    for (int i = 0; i < People.size(); i++) {
        // assume the search data is found
        countTimeMatch = true;

        // using loop to compare all dnaMatch with someone's countTime
        for (int k = 0; k < People[i].countTimes.size(); k++) {
            // dnaMatch is not matching with someone's countTime
            if (dnaMatch[k] != People[i].countTimes[k]) {
                countTimeMatch = false;
            }
        }

        // dnaMatch matches with someone's countTimes, output the person's name
        if (countTimeMatch == true) {
            cout <<"Found in database!  DNA matches: " <<
            People[i].name << endl;
            return;  // no need to loop because we found the matching person
        }
    }

    cout << "Not found in database." << endl;
}


//
// add_individual(): a command that adds a new individual to the database.
// Get a new user name and STRs countTimes and store into database. Perhaps
// use STR counts for one of the DNA files that does not currently
// exist.
//

void add_individual(ourvector<Data>&People, ourvector<ourvector<char>> STRs) {
    // insert new user to the database
    Data newUser;
    cout << "Enter a new individual name: " << endl;
    cin >> newUser.name;

    int num;
    cout << "Enter some new numbers of countTimes for each STRs: " << endl;

    // loop through the STRs sequence, input the number of countTimes of
    // each STRs and store it
    for (int i = 0; i < STRs.size(); i++) {
        cin >> num;
        newUser.countTimes.push_back(num);
    }
    People.push_back(newUser);
}


int main() {
    ourvector<Data>People;
    ourvector<ourvector<char>> STRs;
    ourvector<char>DNA;
    ourvector<int>dnaMatch;

    bool loaded_dna = false;
    bool processed_dna = false;
    cout << "Welcome to the DNA Profiling Application." << endl;
    // inputCmdOpr(People, STRs, DNA, dnaMatch, loaded_dna, processed_dna);

    string command, fileName;
    cout << "Enter command or # to exit: ";
    cin >> command;

    // loop until the input command is #, then exit
    while (command != "#") {
        // cmd is load_db, call openFile function to load in the database
        if (command == "load_db")
            loadDataFile(People, fileName, STRs);

        // cmd is display, call display function to get database from text file
        else if (command == "display")
            displayData(People, STRs, loaded_dna, DNA, processed_dna, dnaMatch);

        // cmd is load_dna, call LoadDna function to read and save dan data
        else if (command == "load_dna")
            loaded_dna = LoadDnaFile(fileName, DNA);

        // cmd is process,  call processed_dna to count the time of each STR
        // sequence matches to file
        else if (command == "process")
            processed_dna = processDNA(dnaMatch, DNA, STRs, loaded_dna);

        // cmd is search, call searchDB function to compare the dnaMatch with
        // every person's countTimes, output the mathed person
        else if (command == "search")
            searchDB(People, dnaMatch, processed_dna, loaded_dna, STRs);

        // cmd is add, call function to add individual infor to the database.
        else if (command == "add")
            add_individual(People, STRs);

        // cmd is invaild, return error message
        else
            cout << "** Invalid command, try again..." << endl;

        cout << "Enter command or # to exit: ";
        cin >> command;
    }

    // infile.close();
    return 0;
}
