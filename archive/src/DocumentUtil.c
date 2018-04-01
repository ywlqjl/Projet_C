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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char digitToChar ( long N);
void digitTo36 ( long N);
char *ctoString(int N, size_t length );

char str4[100];
char str5[100];

char digitToChar ( long n)
{
    if (n >= 10)
        return (char)('A' + (n - 10));
    else
        return (char)(n + '0');
}
char * IMPLEMENT(computeDocumentNumber)(long id) {
    char  ch;
    long digit;
    int i=0;
    while(id % 36)
    {
        digit =id %36;
        ch = digitToChar (digit);
        str4[i] = ch;
        i++;
        id=id/36;
    }
    int j=0 ,k=0 ;
    for( j=i-1,k=0;j>=0;j--,k++)
    {
        str5[k]=str4[j];
    }

    char *dest_str;
    dest_str = (char *)malloc(sizeof(char) * (sizeof(str5) + 1));
    copyStringWithLength(dest_str, str5, sizeof(str5));

    return dest_str;
 /*   return provided_computeDocumentNumber(id);*/
}


char *toString(int id, size_t length) {
    char  ch;
    long digit;
    size_t i=length-1;
    char str[length];
    while(id % 10)
    {
        digit =id %10;
        ch = digitToChar (digit);
        str[i] = ch;
        i--;
        id=id/10;
    }
    char *dest_str;
    dest_str = (char *)malloc(sizeof(char) * (sizeof(length) + 1));
    copyStringWithLength(dest_str, str, sizeof(length));

    return dest_str;
}

/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(formatDate)(int day, int month, int year) {

    char*Date=(char*)malloc(sizeof(char)*20);
    sprintf(Date,"%02d/%02d/%4d",day,month,year);
    return Date;
/*    return provided_formatDate(day, month, year);*/
}


/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */
void IMPLEMENT(writeString)(const char * str, FILE * file) {

    size_t length=0;
    length=stringLength(str);
    if(file==NULL){
        fatalError("error");
    }
    if(fwrite(&length, sizeof(size_t), 1, file) < 1){
        fatalError("error");
    }
    if(length>0){

        if(fwrite(str, sizeof(char), length, file) != length){
            fatalError("error");
        }
    }


    /*provided_writeString(str,file);*/
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * IMPLEMENT(readString)(FILE * file) {

    char *contenue;
    size_t length=0;
    if(file==NULL){
        fatalError("error");
    }

    if (fread(&length, sizeof(size_t), 1, file)!=1) {
        fatalError("read error");
    }
    contenue=(char*)malloc(sizeof(char)*(length+1));
    if (contenue==NULL) {
        fatalError("malloc error");
    }

    if(length>0){
        if(fread(contenue, length , 1, file)!=1){
            fatalError("fread error");
        }
    }
        contenue[length]='\0';
    return contenue;

   /* return provided_readString(file);*/
}
