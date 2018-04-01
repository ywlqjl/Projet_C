/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: Dictionary.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Dictionary.h>

/** Create an empty dictionary on the heap
 * @return a new dictionary
 * @warning the dictionary should be destroyed using Dictionary_destroy()
 */
Dictionary * IMPLEMENT(Dictionary_create)(void)
{
    Dictionary * dictionary;
    dictionary=(Dictionary*)malloc(sizeof(Dictionary));
    if (dictionary==NULL) {
        fatalError("error!");
    }
    dictionary->count=0;
    dictionary->entries=NULL;
    return dictionary;
/*  return provided_Dictionary_create();*/
}

/** Destroy a dictionary
 * @param dictionary the dictionary
 */
void IMPLEMENT(Dictionary_destroy)(Dictionary * dictionary)
{
    int i=(dictionary->count)-1;
    if(dictionary==NULL)
        fatalError("Dictionary_destroy dictionary Error!");

    for(;i>=0;i--)
    {
        free((dictionary->entries[i]).name);(dictionary->entries[i]).name=NULL;
        if((dictionary->entries[i]).type==STRING_ENTRY)
        {
            free(((dictionary->entries[i]).value).stringValue);((dictionary->entries[i]).value).stringValue=NULL;
        }
    }
    free(dictionary->entries);dictionary->entries=NULL;
    free(dictionary);dictionary=NULL;
/*  provided_Dictionary_destroy(dictionary);*/
}

/** Get a pointer on the entry associated with the given entry name
 * @param dictionary the dictionary
 * @param name the name of the entry
 * @return a pointer on the entry or NULL if the entry was not found
 */
DictionaryEntry * IMPLEMENT(Dictionary_getEntry)(Dictionary * dictionary, const char * name)
{
    int i;
    for (i=0; i<dictionary->count; i++) {
        if (icaseCompareString(name,dictionary->entries[i].name)==0) {
            return dictionary->entries+i;
        }
    }
    return  NULL;
/*  return provided_Dictionary_getEntry(dictionary, name);*/
}

/** Define or change a dictionary entry as a string
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setStringEntry)(Dictionary * dictionary, const char * name, const char * value)
{/*
    DictionaryEntry *dictionaryEntry;
    dictionaryEntry=Dictionary_getEntry(dictionary, name);
    if (dictionaryEntry==NULL) {
        DictionaryEntry *temp;
        temp=realloc(dictionary->entries, sizeof(DictionaryEntry)*(size_t)(dictionary->count+1));
        if (temp==NULL) {
            fatalError("error");
            exit(0);
        }
            dictionary->entries=temp;
            dictionary->entries[dictionary->count].name=duplicateString(name);
            dictionary->count++;
            dictionaryEntry=&(dictionary->entries[dictionary->count]);

        if (dictionaryEntry->type==STRING_ENTRY) {
            free(dictionaryEntry->value.stringValue);
        }

        dictionaryEntry->type=STRING_ENTRY;
        dictionaryEntry->value.stringValue=duplicateString(value);

    }*/
    DictionaryEntry*tempDictionaryEntry;
    char*tempName=NULL;
    if(NULL==name)
        fatalError("Dictionary_setStringEntry entrer name Error!");
    if(NULL==value)
        fatalError("Dictionary_setStringEntry entrer value Error!");
    tempName=duplicateString(name);
    makeLowerCaseString(tempName);
    if(NULL==dictionary)
        dictionary=Dictionary_create();
    tempDictionaryEntry=Dictionary_getEntry(dictionary,tempName);
    if(NULL==dictionary->entries||NULL==tempDictionaryEntry)
    {
        dictionary->entries=(DictionaryEntry*)realloc(dictionary->entries,sizeof(DictionaryEntry)*(long unsigned int)(dictionary->count+1));
        (dictionary->entries[dictionary->count]).type=STRING_ENTRY;
        dictionary->entries[dictionary->count].name=(char*)calloc(stringLength(tempName)+1,sizeof(char));
        copyStringWithLength((dictionary->entries[dictionary->count]).name,tempName,stringLength(tempName)+1);
        ((dictionary->entries[dictionary->count]).value).stringValue=(char*)calloc(stringLength(value)+1,sizeof(char));
        copyStringWithLength(((dictionary->entries[dictionary->count]).value).stringValue,value,stringLength(value)+1);
        ++(dictionary->count);
    }
    else
    {
        tempDictionaryEntry->type=STRING_ENTRY;
        (tempDictionaryEntry->value).stringValue=(char*)malloc(sizeof(char)*sizeof(value));
        copyStringWithLength((tempDictionaryEntry->value).stringValue,value,sizeof(value)+1);
    }
    free(tempName);tempName=NULL;

/*  provided_Dictionary_setStringEntry(dictionary, name, value);*/
}

/** Define or change a dictionary entry as a number
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setNumberEntry)(Dictionary * dictionary, const char * name, double value)
{
/*    DictionaryEntry *dicEntry;
    dicEntry=Dictionary_getEntry(dictionary, name);
    int count = dictionary->count;

    if (dicEntry==NULL) {
        DictionaryEntry *temp;
        temp=realloc(dictionary->entries, sizeof(DictionaryEntry)*(size_t)(dictionary->count+1));
        if (temp==NULL) {
            fatalError("realloc error!")
        }
        dictionary->entries=temp;
        dictionary->entries[dictionary->count].name=duplicateString(name);
        dictionary->count++;
        dicEntry=&(dictionary->entries[dictionary->count]);
        if (dicEntry->type==STRING_ENTRY) {
            free(dicEntry->value.stringValue);
        }
        dicEntry->type=NUMBER_ENTRY;
        dicEntry->value.numberValue=value;
    }*/
    DictionaryEntry*tempDictionaryEntry;
    char*tempName=NULL;
    if(NULL==name)
        fatalError("Dictionary_setNumberEntry entrer name Error!");
    tempName=duplicateString(name);
    makeLowerCaseString(tempName);
    if(NULL==dictionary)
        dictionary=Dictionary_create();
    tempDictionaryEntry=Dictionary_getEntry(dictionary,name);
    if(NULL==dictionary->entries||NULL==tempDictionaryEntry)
    {
        dictionary->entries=(DictionaryEntry*)realloc(dictionary->entries,sizeof(DictionaryEntry)*(long unsigned int)(dictionary->count+1));
        (dictionary->entries[dictionary->count]).type=NUMBER_ENTRY;
        (dictionary->entries[dictionary->count]).name=(char*)calloc(stringLength(tempName)+1,sizeof(char));
        copyStringWithLength((dictionary->entries[dictionary->count]).name,tempName,stringLength(tempName)+1);
        (dictionary->entries[dictionary->count]).value.numberValue=value;
        ++(dictionary->count);
    }
    else
    {
        if(STRING_ENTRY==tempDictionaryEntry->type)
            free((tempDictionaryEntry->value).stringValue);(tempDictionaryEntry->value).stringValue=NULL;
        tempDictionaryEntry->type=NUMBER_ENTRY;
        (tempDictionaryEntry->value).numberValue=value;
    }
    free(tempName);tempName=NULL;

  /*provided_Dictionary_setNumberEntry(dictionary, name, value);*/
}

/** Create a new string on the heap which is the result of the formatting of format according to the dictionary content
 * @param dictionary the dictionary
 * @param format the string to format
 * @return a new string created on the heap
 * @warning the user is responsible for freeing the returned string
 */
char * IMPLEMENT(Dictionary_format)(Dictionary * dictionary, const char * format)
{

  return provided_Dictionary_format(dictionary, format);
}
