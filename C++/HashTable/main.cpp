/*
 * Aidan Pizzo
 * Data Structures
 * Project 2
 *
 * This function will read in dictionary files and store them in 2 hash tables.
 * One hash table will handle collisions using chaning and the other using quadratic probing.
 * The main function will then read in a file of words and spell check them by referring to
 * the dictionary hash tables.
 */

#include "hashTableChaining.h"
#include "hashTableQP.h"
#include <fstream>
#include <chrono>

int main(int argc, const char * argv[]) {
    try {

        if (argc < 3) // if command line arguments are invalid
        {
            cout << "Must pass a dictionary file and input file on command line\n";
            return 0;
        }

        // read file names from command line
        string dictionaryFile = string(argv[1]);
        string inputFile = string(argv[2]);

        ifstream inFile;
        if (!inFile) // if file doesn't open, throw exception
        {
            cout << "File failed to open, check path and name: \n";
            cout << dictionaryFile << endl;
            throw logic_error("File failed to open");
        }

        inFile.open(dictionaryFile.c_str()); // open lexicon file
        // get number of lines in dictionary file
        string line;
        int dictLength = 0;
        while(inFile >> line){
            dictLength++;
        }
        inFile.close();

        // create chaining hash table
        // record start time
        auto ht1TimeStart = chrono::steady_clock::now();
        HashTableChain hashtable1 = HashTableChain(dictLength);

        while(inFile >> line){
//            cout << "Inserting " << line << " at index " << hashtable1.hashFunction(line) << endl;
            hashtable1.insert(line);
//            hashtable1.printTable();
//            cout << endl << endl;
        }
        inFile.close();

        //record end time
        auto ht1TimeEnd = std::chrono::steady_clock::now();

        // calculate elapsed time, convert to nanoseconds
        double elapsed_time = chrono::duration_cast<chrono::nanoseconds>(ht1TimeEnd - ht1TimeStart).count();
        cout << "Time taken to construct hashtable 1: " << elapsed_time << " nanoseconds\n";

        // PERFORM SPELL CHECK WITH HASH TABLE 1, record time taken
        int ht1spellCheck = 0;
        inFile.open(inputFile.c_str()); // open file to spell check
        auto ht1SpellTimeStart = chrono::steady_clock::now();
        while(inFile >> line){
            ht1spellCheck += hashtable1.spellCheck(line);
        }
        inFile.close();
        auto ht1SpellTimeEnd = std::chrono::steady_clock::now();
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(ht1SpellTimeEnd - ht1SpellTimeStart).count();
        cout << "Time taken to spell check hashtable 1: " << elapsed_time << " nanoseconds\n";
        cout << "Number of misspelled words: " << ht1spellCheck << endl << endl;

        inFile.open(dictionaryFile.c_str());


        auto ht2TimeStart = chrono::steady_clock::now();
        // create quadratic probing hash table
        HashTableQP hashtable2 = HashTableQP(dictLength*2);
        while(inFile >> line){
//            cout << "Inserting " << line << " at index " << hashtable2.hashFunction(line) << endl;
            hashtable2.insert(line);
//            hashtable2.printTable();
//            cout << endl << endl;
        }
        inFile.close();

        //record end time
        auto ht2TimeEnd = std::chrono::steady_clock::now();

        // calculate elapsed time, convert to nanoseconds
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(ht2TimeEnd - ht2TimeStart).count();
        cout << "Time taken to construct hashtable 2: " << elapsed_time << " nanoseconds\n";


        // SPELL CHECK WITH TABLE 2
        int ht2spellCheck = 0;
        inFile.open(inputFile.c_str()); // open file to spell check
        auto ht2SpellTimeStart = chrono::steady_clock::now();
        while(inFile >> line){
            ht2spellCheck += hashtable2.spellCheck(line);
        }
        inFile.close();
        auto ht2SpellTimeEnd = std::chrono::steady_clock::now();
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(ht2SpellTimeEnd - ht2SpellTimeStart).count();
        cout << "Time taken to spell check hashtable 2: " << elapsed_time << " nanoseconds\n";
        cout << "Number of misspelled words: " << ht2spellCheck << endl << endl;


    } // END try block
    catch (out_of_range &e)
    {
        cout << "Caught out_of_range exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (invalid_argument &e)
    {
        cout << "Caught invalid_argument exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (logic_error &e)
    {
        cout << "Caught logic_error exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught in function main." << endl;
    }

    return 0;

} // END main function

