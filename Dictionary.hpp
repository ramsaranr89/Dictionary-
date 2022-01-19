//
//  Dictionary.hpp
//  DS&Algo
//
//  Created by Ramsaran Ramasubbu on 1/3/21.
//  Copyright © 2021 Ramsaran Ramasubbu. All rights reserved.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

#define MAX_STRING_SIZE 2048
#define MAX_WORD_SIZE 256

void Dictionary_Execute();

//This class has functions to insert, delete and search from a hash table
//Class also deletes the size of dictionary

class Dictionary
{
public:
    struct DictEntry
    {
        char * word;
        char * meaning;
    };
    typedef struct DictEntry DictEntry;

    struct DictionaryTable
    {
        DictEntry * DictEntry;
        int size;
        int count;
    };
    typedef struct DictionaryTable DictionaryTable;
    
    DictionaryTable * table;
    
public:
    Dictionary();
    virtual ~Dictionary();
    
    //Add Entry
    void addEntry(char const *newWord, char const *meaning);
    
    //Delete Entry
    void deleteEntry(char const *word);
    
    //Search Entry
    void searchEntry(char const *word);
    
    //Computes
    int compute_hash(string s);
    
    //Delete Dictionary
    void dumpDict();
};

int compute_hash(string const& s);

#endif /* Dictionary_hpp */
