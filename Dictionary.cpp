//
//  Dictionary.cpp
//  DS&Algo
//
//  Created by Ramsaran Ramasubbu on 1/3/21.
//  Copyright © 2021 Ramsaran Ramasubbu. All rights reserved.
//

#include "Dictionary.hpp"
#include <iostream>
#include <string>

using namespace std;

#define DICTIONARY_SIZE 100000

Dictionary :: Dictionary()
{
    this->table = (struct DictionaryTable *)malloc(sizeof(DictionaryTable));
    
    table->size = DICTIONARY_SIZE;
    table->count = 0;
    table->DictEntry = (struct DictEntry *)calloc(table->size, sizeof(DictEntry));
    
    //when there is an issue with calloc
    if(table->DictEntry == NULL)
        free(table);
}

Dictionary :: ~Dictionary()
{
    for(int i = 0; i < table->size; i++)
    {
        if(table->DictEntry[i].word != NULL)
        {
            free((void*)table->DictEntry[i].word);
        }
    }
    // Then free entries array and table itself.
    free(table->DictEntry);
    free(table);
}

// abcde - a*31^5 + b*31^4 .... e*31^0
//polynomial rolling hash function
int Dictionary :: compute_hash(string s)
{
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s)
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value % DICTIONARY_SIZE;
}

//Add Entry
void Dictionary :: addEntry(char const *newWord, char const *meaning)
{
    int index = compute_hash(newWord);
    
    table->DictEntry[index].word = (char *)malloc(sizeof(newWord));
    table->DictEntry[index].meaning = (char *)malloc(sizeof(meaning));
    table->count++;
    
    strcpy(table->DictEntry[index].word, newWord);
    strcpy(table->DictEntry[index].meaning, meaning);
    
    cout << table->DictEntry[index].word << " ";
    cout << table->DictEntry[index].meaning << endl;
    
    return;
}

void Dictionary :: searchEntry(char const *word)
{
    int index = compute_hash(word);
    
    if(table->DictEntry[index].word == NULL)
    {
        cout << "Key not found" << endl;
        return;
    }
    
    cout << "Key found ";
    cout << "Meaning is : " <<  table->DictEntry[index].meaning << endl;
    
    return;
}

void Dictionary :: deleteEntry(char const *word)
{
    int index = compute_hash(word);
    
    if(table->DictEntry[index].word == NULL)
    {
        cout << "Key not found" << endl;
        return;
    }
    
    cout << "Key found - Deleting it" << endl;
    table->DictEntry[index].meaning = NULL;
    table->DictEntry[index].word = NULL;
    table->count--;
    
    free(table->DictEntry[index].meaning);
    free(table->DictEntry[index].word);
    
    return;
}

void Dictionary_Execute()
{
    Dictionary * dictobj = new Dictionary;
    
    cout << "************ Adding Words and Meaning ******************" << endl;
    
    dictobj->addEntry("Apple", "Fruit");
    dictobj->addEntry("Bat", "Bird");
    dictobj->addEntry("Cat", "Animal");
    
    cout << "Total Entries : " << dictobj->table->count << endl;
    
    cout << "************** Searching  Words ***********************" << endl;
    
    dictobj->searchEntry("Apple");
    dictobj->searchEntry("Cat");
    
    cout << "************** Deleting  Words ************************" << endl;
    
    dictobj->deleteEntry("Apple");
    
    cout << "************** Searching Deleted Word ******************" << endl;
    
    dictobj->searchEntry("Apple");
    
    cout << "Total Entries : " << dictobj->table->count << endl;
    
    cout << "********************************************************" << endl;
    
    cout << "Success" << endl;
    return;
}

