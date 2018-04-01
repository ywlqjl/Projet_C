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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerRecord.h>

void IMPLEMENT(CustomerRecord_setValue_name)(CustomerRecord * record, const char * value)
{
    /*int i=0;
    while (*value!='\0' &&  i<(int)CUSTOMERRECORD_NAME_SIZE) {
        record->name[i]=value[i];
        i++;
    }*/
    copyStringWithLength( record->name, value, (size_t)CUSTOMERRECORD_NAME_SIZE );
/*  provided_CustomerRecord_setValue_name(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_address)(CustomerRecord * record, const char * value)
{
    int i=0;
    while (*value!='\0' &&  i<(int)CUSTOMERRECORD_ADDRESS_SIZE) {
        record->address[i]=value[i];
        i++;
    }
  /*provided_CustomerRecord_setValue_address(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_postalCode)(CustomerRecord * record, const char * value)
{
    int i=0;
    while (*value!='\0' && i<(int)CUSTOMERRECORD_POSTALCODE_SIZE) {
        record->postalCode[i]=value[i];
        i++;
    }
 /* provided_CustomerRecord_setValue_postalCode(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_town)(CustomerRecord * record, const char * value)
{
    int i=0;
     while (*value!='\0' &&  i<(int)CUSTOMERRECORD_TOWN_SIZE) {
        record->town[i]=value[i];
        i++;
    }
  /*provided_CustomerRecord_setValue_town(record, value);*/
}

char * IMPLEMENT(CustomerRecord_getValue_name)(CustomerRecord * record)
{
      return duplicateString(record->name);
 /* return provided_CustomerRecord_getValue_name(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_address)(CustomerRecord * record)
{
      return duplicateString(record->address);
/*  return provided_CustomerRecord_getValue_address(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_postalCode)(CustomerRecord * record)
{
      return duplicateString(record->postalCode);
  /*return provided_CustomerRecord_getValue_postalCode(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_town)(CustomerRecord * record)
{
      return duplicateString(record->town);
 /* return provided_CustomerRecord_getValue_town(record);*/
}

void IMPLEMENT(CustomerRecord_init)(CustomerRecord * record)
{
    size_t i;
    for (i=0; i<(size_t)CUSTOMERRECORD_NAME_SIZE; i++) {
        record->name[i]='\0';
    }
    for (i=0; i<(size_t)CUSTOMERRECORD_ADDRESS_SIZE; i++) {
        record->address[i]='\0';
    }
    for (i=0; i<(size_t)CUSTOMERRECORD_POSTALCODE_SIZE; i++) {
        record->postalCode[i]='\0';
    }
    for (i=0; i<(size_t)CUSTOMERRECORD_POSTALCODE_SIZE; i++) {
        record->town[i]='\0';
    }
  /*provided_CustomerRecord_init(record);*/
}

void IMPLEMENT(CustomerRecord_finalize)(CustomerRecord *UNUSED(record))
{
  /*provided_CustomerRecord_finalize(record);*/
}

void IMPLEMENT(CustomerRecord_read)(CustomerRecord * record, FILE * file)
{
        char name[CUSTOMERRECORD_NAME_SIZE];
        char address[CUSTOMERRECORD_ADDRESS_SIZE];
        char postalCode[CUSTOMERRECORD_POSTALCODE_SIZE];
        char town[CUSTOMERRECORD_TOWN_SIZE];

        memset(name, '\0' , sizeof(char)*CUSTOMERRECORD_NAME_SIZE);
        memset(address, '\0' , sizeof(char)*CUSTOMERRECORD_ADDRESS_SIZE);
        memset(postalCode, '\0' , sizeof(char)*CUSTOMERRECORD_POSTALCODE_SIZE);
        memset(town, '\0' , sizeof(char)*CUSTOMERRECORD_TOWN_SIZE);


        if(fread(name,CUSTOMERRECORD_NAME_SIZE,1, file)!=1){
                fatalError("failed to read name!");
        };
        if(fread(address,CUSTOMERRECORD_ADDRESS_SIZE,1, file)!=1){
                fatalError("failed to read address!");
        };
        if(fread(postalCode,CUSTOMERRECORD_POSTALCODE_SIZE,1, file)!=1){
                fatalError("failed to read postalCode!");
        }
        if(fread(town,CUSTOMERRECORD_TOWN_SIZE,1, file)!=1){
                fatalError("failed to read town!");
        }

        copyStringWithLength( record->name, name, (size_t)CUSTOMERRECORD_NAME_SIZE );
        copyStringWithLength( record->address ,address ,  (size_t)CUSTOMERRECORD_ADDRESS_SIZE);
        copyStringWithLength( record->postalCode , postalCode ,   (size_t)CUSTOMERRECORD_POSTALCODE_SIZE);
        copyStringWithLength( record->town ,  town , (size_t)CUSTOMERRECORD_TOWN_SIZE);

  /*provided_CustomerRecord_read(record, file);*/
}

void IMPLEMENT(CustomerRecord_write)(CustomerRecord * record, FILE * file)
{
    char name[CUSTOMERRECORD_NAME_SIZE];
    char address[CUSTOMERRECORD_ADDRESS_SIZE];
    char postalCode[CUSTOMERRECORD_POSTALCODE_SIZE];
    char town[CUSTOMERRECORD_TOWN_SIZE];

    memset(name, '\0' , sizeof(char)*CUSTOMERRECORD_NAME_SIZE);
    memset(address, '\0' , sizeof(char)*CUSTOMERRECORD_ADDRESS_SIZE);
    memset(postalCode, '\0' , sizeof(char)*CUSTOMERRECORD_POSTALCODE_SIZE);
    memset(town, '\0' , sizeof(char)*CUSTOMERRECORD_TOWN_SIZE);

        copyStringWithLength( name, record->name,  (size_t)CUSTOMERRECORD_NAME_SIZE );
        copyStringWithLength( address , record->address , (size_t)CUSTOMERRECORD_ADDRESS_SIZE);
        copyStringWithLength( postalCode , record->postalCode ,  (size_t)CUSTOMERRECORD_POSTALCODE_SIZE);
        copyStringWithLength( town , record->town , (size_t)CUSTOMERRECORD_TOWN_SIZE);

        if(   fwrite(name, CUSTOMERRECORD_NAME_SIZE, 1, file)!=1){
                fatalError("failed to write name!");
        }
        if(  fwrite(address, CUSTOMERRECORD_ADDRESS_SIZE, 1, file)!=1){
                fatalError("failed to write address!");
        }
        if(  fwrite(postalCode, CUSTOMERRECORD_POSTALCODE_SIZE, 1, file)!=1){
                fatalError("failed to write postalCode!");
        }
        if(  fwrite(town, CUSTOMERRECORD_TOWN_SIZE, 1, file)!=1){
                fatalError("failed to write town!");
        }

      /*size_t i=0;
        while(name[i]!='\0'&& i <(size_t)CUSTOMERRECORD_NAME_SIZE){
            i++;
        }*/
/*  provided_CustomerRecord_write(record, file);*/
 }

