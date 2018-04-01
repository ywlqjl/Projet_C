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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <CustomerRecordEditor.h>

const char * CUSTOMERDB_FILENAME = BASEPATH "/data/Customer.db";

CustomerDB * IMPLEMENT(CustomerDB_create)(const char * filename) {
    CustomerDB *customerDB;
    customerDB=(CustomerDB*)malloc(sizeof(CustomerDB));
    FILE *fp;
    fp=fopen(filename,"wb+");
    if(fp==NULL)
    {
        fatalError("can't create file!");
        return NULL;
        free(customerDB);
    }
    else{
        customerDB->file=fp;
        customerDB->recordCount=0;
        if(fwrite(&customerDB->recordCount, sizeof(int), 1, customerDB->file) < 1){
                fatalError("error: can not write");
        }
    }
    return customerDB;
    /*return provided_CustomerDB_create(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_open)(const char * filename) {
    CustomerDB *customerDB;
    customerDB=(CustomerDB*)malloc(sizeof(CustomerDB));
    if(customerDB == NULL){
        fatalError("error in malloc");
    }

    FILE *fp;
    fp=fopen(filename , "rb+");
    if(fp==NULL){
        free(customerDB);
        return NULL;

    }
    else {
            customerDB->file=fp;
        if(fread(&customerDB->recordCount , sizeof(int), 1, customerDB->file)<1){
            fclose(fp);
            free(customerDB);
            fatalError("error");
        }
    }

    return customerDB;
   /* return provided_CustomerDB_open(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_openOrCreate)(const char * filename) {
    CustomerDB *customerDB;
    CustomerDB *temp=CustomerDB_open(filename);
    if(temp==NULL){
         customerDB=CustomerDB_create(filename);
    }
    else{
          customerDB=CustomerDB_open(filename);
          free(temp);
    }
    return customerDB;
    /*return provided_CustomerDB_openOrCreate(filename);*/
}

void IMPLEMENT(CustomerDB_close)(CustomerDB * customerDB) {
    fseek(customerDB->file , 0L ,  SEEK_SET);
    if(fwrite(&(customerDB->recordCount ) , sizeof(int) , 1 , customerDB->file)!=1){
            fclose(customerDB->file);
            free(customerDB);
            fatalError("can not write recordCount,  close failed");

    }
            fclose(customerDB->file);
            free(customerDB);

   /* provided_CustomerDB_close(customerDB);*/
}

int IMPLEMENT(CustomerDB_getRecordCount)(CustomerDB * customerDB) {
      return customerDB->recordCount;
    /*return provided_CustomerDB_getRecordCount(customerDB);*/
}

char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}

void IMPLEMENT(CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record) {
    fseek(customerDB->file , 0L , SEEK_END);
    CustomerRecord_write(record,customerDB->file);
    customerDB->recordCount++;
    rewind(customerDB->file);
    if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file)!=1){
        fatalError("write error");
    }

   /* provided_CustomerDB_appendRecord(customerDB, record);*/
}

void IMPLEMENT(CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    int i;
    CustomerRecord tmprecord;
    CustomerRecord_init(&tmprecord);
    for(i = customerDB->recordCount;i>recordIndex;i--){
        CustomerDB_readRecord(customerDB, i-1, &tmprecord);
        CustomerDB_writeRecord(customerDB, i, &tmprecord);
          CustomerRecord_finalize(&tmprecord);
    }
    CustomerDB_writeRecord(customerDB, i, record);
}

void IMPLEMENT(CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex) {
    int i=0;
    CustomerRecord *buf;
    buf=(CustomerRecord*)malloc(sizeof(CustomerRecord));
    if(buf==NULL){
        fatalError("malloc failed!");
    }

        CustomerRecord_init(buf);
        if(recordIndex>=0&&recordIndex<=(customerDB->recordCount)){

            for(i=recordIndex;i<(customerDB->recordCount)-1;i++){

                CustomerDB_readRecord(customerDB,i+1,buf);
                CustomerDB_writeRecord(customerDB,i,buf);
            }
            CustomerRecord_finalize(buf);
            free(buf);
            customerDB->recordCount--;
            rewind(customerDB->file);
            if(fwrite(&(customerDB->recordCount),sizeof(int),1,customerDB->file)!=1){
                fatalError("write error");
            }
        }
        else
            fatalError("writeRecord error!");
    /*provided_CustomerDB_removeRecord(customerDB, recordIndex);*/
}

void IMPLEMENT(CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    if (fseek(customerDB->file, (long)(recordIndex*(int)CUSTOMERRECORD_SIZE+(int)sizeof(customerDB->recordCount)), SEEK_SET) != 0){
        printf("error read!");
        exit(-1);
    }
    else{
        CustomerRecord_read(record, customerDB->file);
    }
}

void IMPLEMENT(CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
      if (fseek(customerDB->file, recordIndex*(int)CUSTOMERRECORD_SIZE+(int)sizeof(customerDB->recordCount), SEEK_SET) != 0){
        printf("error!");
    }
    CustomerRecord_write(record, customerDB->file);
    if (recordIndex>=customerDB->recordCount){
        customerDB->recordCount++;
    }
}
