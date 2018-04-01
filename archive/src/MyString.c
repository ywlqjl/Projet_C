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
 * $Id: MyString.c 293 2011-10-02 15:05:44Z sebtic $
 */

#include <MyString.h>
#include <limits.h>

/** Like the tolower() function. It converts the letter c to lower case, if possible.
 * @param c the letter to convert
 * @return the lower case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toLowerChar)(char c) {
    if(c>='A'&& c<='Z')
    {
        c=(char)(c+('a'-'A'));
    }
    return c;
}

/** Like the toupper() function. It converts the letter c to upper case, if possible.
 * @param c the letter to convert
 * @return the upper case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toUpperChar)(char c) {
       if(c>='a'&& c<='z')
    {
        c=(char)(c-('a'-'A'));
    }
    return c;
}

/** Like the strcmp() function. It compares the two strings str1 and str2.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(compareString)(const char * str1, const char * str2) {
   /* int i=0;
    int ind=0;
       if(str1[0]=='\0'&&str2[0]=='\0'){
        ind=0;
    }
        if(str1[0]=='\0'&&str2[0]!='\0'){
        ind=-1;
    }
        if(str1[0]!='\0'&&str2[0]=='\0'){
        ind=1;
    }

    while (str1[i]!='\0'&& str2[i]!='\0'&&ind==0) {
        if(str1[i]>str2[i]){
            ind=1;
        }
        else if (str1[i]==str2[i]){
            ind=0;
        }
        else ind=-1;
        i++;

        if(ind==0 && str1[i]=='\0'){
            if (str2[i]=='\0'){
                ind=0;
            }
            else{
                ind=-1;
            }
        }

        if(ind==0 && str2[i]=='\0'){
            if (str1[i]=='\0'){
                ind=0;
            }
            else{
                ind=1;
            }
        }
    }
    return ind;*/

    /*while(*str1||*str2){
        if(*str1>*str2){
                return 1;
        }
        if(*str1<*str2){
                return -1;
        }
        else {
            str1++;
            str2++;
        }
    }
    return 0;*/
    while(*str1==*str2&&*str1&&*str2){
        str1++;
        str2++;
    }
    return *str1-*str2;
}

/** Like the strcasecmp() function. It compares the two strings str1 and str2, ignoring the case of the characters.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(icaseCompareString)(const char * str1, const char * str2) {
      int i =0;
      int ind =0;
      char temp1,  temp2;
        if(str1[0]=='\0'&&str2[0]=='\0'){
        ind=0;
    }
        if(str1[0]=='\0'&&str2[0]!='\0'){
        ind=-1;
    }
        if(str1[0]!='\0'&&str2[0]=='\0'){
        ind=1;
    }

        while (str1[i]!='\0'&& str2[i]!='\0'&&ind==0) {
        temp1=toLowerChar(str1[i]);
        temp2=toLowerChar(str2[i]);

        if(temp1>temp2){
            ind=1;
        }
        else if (temp1==temp2){
            ind=0;
        }
        else {ind=-1;}
        i++;
    }
        if(ind==0 && str2[i]=='\0'){
            if (str1[i]=='\0'){
                ind=0;
            }
            else{
                ind=1;
            }
        }
        if(ind==0 && str1[i]=='\0'){
            if (str2[i]=='\0'){
                ind=0;
            }
            else{
                ind=-1;
            }
        }
    return ind;
}

/** Like the strlen() function. It calculates the length of the string str, not including the terminating '\\0' character.
 * @param str the string
 * @return the number of characters in str.
 */
size_t IMPLEMENT(stringLength)(const char * str) {
     size_t length=0;
     int i=0;
    while(str[i]!=0){
        length++;
        i++;
    }

    return length;
}

/** Copy the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 *
 * @param dest the destination string
 * @param src the source string
 */
void IMPLEMENT(copyString)(char * dest, const char * src) {
    while(src!='\0'){
    *dest=*src;
    dest++;
    src++;
    }
}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize) {

    size_t    lengthS=stringLength(src);
    size_t    i = 0,  j=0;

    if(lengthS<=destSize){
            for(i=0; i<lengthS; i++){
                dest[i]=src[i];
            }
            dest[i]='\0';
        }
        else{
            for (j=0;j<destSize;j++){
                dest[j]=src[j];
            }
            dest[destSize-1]='\0';
        }

}

/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * IMPLEMENT(duplicateString)(const char * str) {
        char *duplicate;
        size_t lengthStr=stringLength(str);
        int i=0;
        duplicate=(char*)malloc(sizeof(char)*(lengthStr+1));
      while (str[i]!='\0') {
        duplicate[i]=str[i];
        i++;
    }
    duplicate[lengthStr]='\0';
    return duplicate;
}

/** Test if the string str begins by the string start, ignoring the case of the characters.
 * @param start the string which should be at the beginning of str
 * @param str the string to test
 * @return a non null number (true) if the str begins with the string start, false otherwise
 */
int IMPLEMENT(icaseStartWith)(const char * start, const char * str) {
        int i=0;
        int j=0;
        size_t lengthStart=stringLength(start);
        size_t lengthStr=stringLength(str);
if(lengthStart<=lengthStr){
      while (start[i]!='\0') {
        if(toLowerChar(str[i])==toLowerChar(start[i])){
            j++;
        }
        else{j=0;}
        i++;
    }
}
else{
    j=0;
}
    return j;
}

/** Test if the string str ends by the string start, ignoring the case of the characters.
 * @param end the string which should be at the end of str
 * @param str the string to test
 * @return a non null number (true) if the str ends with the string end, false otherwise
 */
int IMPLEMENT(icaseEndWith)(const char * end, const char * str) {
        size_t i=0;
        int j=0;
        size_t lengthEnd=stringLength(end);
        size_t lengthStr=stringLength(str);
        if(lengthEnd<=lengthStr){
      while (end[i]!='\0') {
        if(toLowerChar(str[lengthStr-i+1])==toLowerChar(end[i])){
            j++;
        }
        else{j=0;}
        i++;
    }
}
else{
    j=0;
}
    return j;
    /*return provided_icaseEndWith(end, str);*/
}

/** Create a new string on the heap which is the result of the concatenation of the two strings.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str1 the first string
 * @param str2 the second string
 * @return the new string
 */
char * IMPLEMENT(concatenateString)(const char * str1, const char * str2) {
    char *newString;
    int i=0;
    int j=0;
    int n=0;
    size_t length1=stringLength(str1);
    size_t length2=stringLength(str2);
    newString=(char *)malloc((length1+length2+1)*sizeof(char));
    if(newString==NULL){
        printf("C'est faux");
        exit(0);
    }
    while (str1[i]!='\0'){
        newString[n]=str1[i];
        i++;
        n++;
    }
    while (str2[j]!='\0') {
        newString[n]=str2[j];
        j++;
        n++;
    }

    newString[n]='\0';
    return newString;
  /*  return provided_concatenateString(str1, str2);*/
}

/** Like the index() function. It returns a pointer to the first occurrence of the character c in the string str.
 * @param str the string to search in
 * @param c the character to find
 * @return a pointer to the first occurrence of the character c in the string str if c is in str, NULL otherwise
 */
const char * IMPLEMENT(indexOfChar)(const char *str, char c) {
        int p=0;
        while (*str!='\0'&& p==0) {
        if(*str==c){
            p=1;
        }
        else {p=0;}
        str++;
    }
    if(p==0){
        return NULL;
    }
    return str-1;
    /*return provided_indexOfChar(str, c);*/
}

/** Create a copy on the heap of part of a string. The new string contains the characters pointed from start (inclusive) to end (exclusive).
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param start a pointer to the first character of the new string
 * @param end a pointer to the next character of the new string (the pointed character is not part of the new string)
 * @return the new string
 *
 * @code
 * char * str = "abcdef";
 * char * s1 = subString(str,str);
 * char * s2 = subString(str,str+strlen(str));
 * char * s3 = subString(str+1,str+2);
 *
 * We get:
 *    s1: "";
 *    s2: "abcdef";
 *    s3: "b";
 * @endcode
 */
char * IMPLEMENT(subString)(const char * start, const char * end) {
    size_t lengthS=stringLength(start);
    size_t lengthE=stringLength(end);
    size_t a=0;
    char *newS;
    newS=(char*)malloc(sizeof(char)*(lengthS-lengthE+1));

    if (   *end=='\0'){
            for(a=0; start[a]!='\0';a++){
            newS[a]=start[a];
             }
             a=0;
    }

    else if(    indexOfString(start,end)==NULL){
        newS='\0';
        return newS;
    }
    else{
            for(a=0; start[a]!=* indexOfString(start,end);a++){
            newS[a]=start[a];
             }

    }
    newS[lengthS-lengthE]='\0';
    return newS;
   /* return provided_subString(start, end);*/
}

/** Like the strstr() function. It returns a pointer to the first occurrence of the string aiguille in the string meule_de_foin.
 * @param meule_de_foin the string to search in
 * @param aiguille the string to find
 * @return a pointer to the first occurrence of the string aiguille in the string meule_de_foin if aiguille is in meule_de_foin, NULL otherwise
 */
const char * IMPLEMENT(indexOfString)(const char *meule_de_foin, const char *aiguille) {
    size_t i=0;
    size_t j=0;
    size_t lengthA=stringLength(aiguille);

    while(aiguille[j]!='\0'&&meule_de_foin[i]!='\0'){
           if(meule_de_foin[i]==aiguille[j]){
       j++;
    }
    else{
        j=0;
    }
  i++;
    }
        if(j!=lengthA){
            return NULL;
        }
        return meule_de_foin+i-lengthA;
      /*   return provided_indexOfString(meule_de_foin, aiguille);*/
}

/** Convert a string to upper case.
 * @param str the string to convert
 */
void IMPLEMENT(makeUpperCaseString)(char * str) {
        int i=0;
    for (i=0; str[i]!='\0'; i++) {
        str[i]=toUpperChar(str[i]);
    }
}

/** Convert a string to lower case.
 * @param str the string to convert
 */
void IMPLEMENT(makeLowerCaseString)(char * str) {
    int i=0;
    for (i=0; str[i]!='\0'; i++) {
        str[i]=toLowerChar(str[i]);
    }
}

/** Create a new string on the heap which contents is the result of the insertion in src of insertLength characters from  toBeInserted at position insertPosition.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param src the string in which the insertion is done
 * @param insertPosition the position where the insertion is done
 * @param toBeInserted a pointer on the first character to insert
 * @param insertLength the number of character to insert
 * @return the new string
 */
char * IMPLEMENT(insertString)(const char * src, int insertPosition, const char * toBeInserted,
        int insertLength) {
         char* newS;

         size_t lengthS=0;
         int i=0;
         size_t j=0;
         size_t k=0;
        lengthS=stringLength(src);
         size_t lengthInsert;
         lengthInsert=(size_t)insertLength;
         newS=(char*)malloc(sizeof(char)*(lengthS+lengthInsert+1));

         while(i!=insertPosition){
              newS[i]=src[k];
              i++;
              k++;
         }

         while(j<lengthInsert){
            newS[i]=toBeInserted[j];
            i++;
            j++;
         }
         while(src[k]!='\0'){
            newS[i]=src[k];
            i++;
            k++;
         }

        newS[i]='\0';

       return newS;
     /*  return provided_insertString(src, insertPosition, toBeInserted, insertLength);*/
}
