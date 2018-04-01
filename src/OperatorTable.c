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
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <EncryptDecrypt.h>

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_create)(void) {
    OperatorTable *s = NULL;
    s = (OperatorTable *)malloc(sizeof(OperatorTable));
    if( s==NULL){
        printf("error");
        exit(0);
    }
    s->recordCount=0;
    s->records=NULL;

    return s;
    /*return provided_OperatorTable_create();*/
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_destroy)(OperatorTable * table) {
    int i=0;
    while(i<table->recordCount){
        free(table->records[i][0]);
        free(table->records[i][1]);
        free(table->records[i]);
        i++;
    }
    free(table->records);
    free(table);
   /* provided_OperatorTable_destroy(table);*/
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_loadFromFile)(const char * filename) {
    FILE *fp;
    OperatorTable *operatorClient;
    operatorClient=OperatorTable_create();
   /* operateur->records =(char***) malloc(sizeof(char**) *(size_t)(operateur->recordCount));*/

/*    if(operateur->records==NULL){
            fatalError("The malloc is incorrect !");
        }*/
    fp=fopen(filename, "r+");
    if(fp==NULL){
        return operatorClient;
    }
    else{
        fseek( fp , sizeof(int) , SEEK_SET);
    }
    char namebuffer[OPERATORTABLE_MAXNAMESIZE ];
    char passwordbuffer[OPERATORTABLE_MAXPASSWORDSIZE];
    while(fgets(namebuffer , OPERATORTABLE_MAXNAMESIZE , fp )){
        if( fgets(passwordbuffer , OPERATORTABLE_MAXPASSWORDSIZE  , fp )){
            namebuffer[stringLength(namebuffer)-1]='\0';
            passwordbuffer[stringLength(passwordbuffer)-1]='\0';
            decrypt(OperatorCryptKey , namebuffer) ;
            decrypt(OperatorCryptKey , passwordbuffer);
            OperatorTable_setOperator(operatorClient ,  namebuffer , passwordbuffer);
        }
    }
    return operatorClient;
    fclose(fp);

    /*return provided_OperatorTable_loadFromFile(filename);*/
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_saveToFile)(OperatorTable * table, const char * filename) {
    FILE *fp;
    fp=fopen(filename, "w+");
    char *name;
    char *password;
    int i=0;
    if (fp==NULL) {
        fatalError("open error");
    }

      fseek( fp , sizeof(int) , SEEK_SET);
      while(i<table->recordCount){
            name = duplicateString(table->records[i][0]) ;
            password = duplicateString(table->records[i][1]) ;
            encrypt(OperatorCryptKey , name) ;
            encrypt(OperatorCryptKey , password);

            fputs(name , fp );
            fputs("\n" , fp);
            free(name);
            fputs(password , fp );
            fputs("\n" , fp);
            free(password);

        i++;
    }
    fclose(fp);
  /*  provided_OperatorTable_saveToFile(table, filename);*/
}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_getRecordCount)(OperatorTable * table) {
    return table->recordCount;
    /*return provided_OperatorTable_getRecordCount(table);*/
}
/** Get the nacme of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getName)(OperatorTable * table, int recordIndex) {
     return table->records[recordIndex][0];
    /*return provided_OperatorTable_getName(table, recordIndex);*/
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the password of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getPassword)(OperatorTable * table, int recordIndex) {
    return table->records[recordIndex][1];
   /* return provided_OperatorTable_getPassword(table, recordIndex);*/
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_findOperator)(OperatorTable * table, const char * name) {

    int i=0;
    for (i=0; i<table->recordCount; i++) {
        if(compareString(table->records[i][0], name)==0){

            return  i;
            break;
        }
    }
     return -1;
   /* return provided_OperatorTable_findOperator(table, name);*/
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_setOperator)(OperatorTable * table, const char * name, const char * password) {

    int position=OperatorTable_findOperator(table, name);
    if(position>=0)
    {
        copyStringWithLength(table->records[position][1],password,OPERATORTABLE_MAXPASSWORDSIZE);
    }
    else
    {
        position=table->recordCount;
        char ***p=(char***)realloc(table->records, (size_t)(position+1)*sizeof(char**));
        if(p!=NULL)
        {
            table->records = p;
            table->records[position]=(char**)malloc(2*sizeof(char*));
            table->records[position][0]=(char*)malloc(OPERATORTABLE_MAXNAMESIZE*sizeof(char));
            table->records[position][1]=(char*)malloc(OPERATORTABLE_MAXPASSWORDSIZE*sizeof(char));
            table->recordCount++;

            copyStringWithLength(table->records[position][0],name,OPERATORTABLE_MAXNAMESIZE);
            copyStringWithLength(table->records[position][1],password,OPERATORTABLE_MAXPASSWORDSIZE);
        }
        else fatalError("malloc failed");
    }
    return position;

   /* return provided_OperatorTable_setOperator(table, name, password);*/
}

/** Remove an operator from the table.
 * @param table the table of operatorsc
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_removeRecord)(OperatorTable * table, int recordIndex) {
    int j=0;
    for ( j=recordIndex; j<table->recordCount-1; ++j) {
        copyStringWithLength(table->records[j][0],table->records[j+1][0],OPERATORTABLE_MAXNAMESIZE);
        copyStringWithLength(table->records[j][1],table->records[j+1][1],OPERATORTABLE_MAXPASSWORDSIZE);
    }
    free(table->records[table->recordCount-1][0]);
    table->records[(table->recordCount)-1][0]=NULL;

    free(table->records[table->recordCount-1][1]);
    table->records[(table->recordCount)-1][1]=NULL;

    free(table->records[table->recordCount-1]) ;
    table->records[(table->recordCount)-1]=NULL;

    (table->recordCount)--;


 /*   provided_OperatorTable_removeRecord(table, recordIndex);*/
}

