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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogRecord.h>

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_code)(const char * value)
{
    int i=0;
    int count=0;
    for (i=0; value[i]!='\0'; i++) {
        if ((value[i]>='0'&&value[i]<='9')||(value[i]>='A'&&value[i]<='Z')||(value[i]>='a'&&value[i]<='z')) {
            count=count+1;
        }
        else{
            return 0;
        }
    }
    return 1;
  /*return provided_CatalogRecord_isValueValid_code(value);*/
}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_positiveNumber)(const char * value)
{
    int i=0;
    if(value==NULL){
        fatalError("value is null!");
    }
    for(i=0;value[i]!='\0';i++){
        if(!((value[i]=='.')||(value[i]=='-')||(value[i]>='0'&&value[i]<='9'))){
        return 0;
        break;
        }

    }
    double number= strtod(value, NULL);
    if(number>0){
    return 1;
    }
    else return 0;
  /*return provided_CatalogRecord_isValueValid_positiveNumber(value);*/
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_code)(CatalogRecord * record, const char * value)
{

    if (CatalogRecord_isValueValid_code(value)) {
        free(record->code);
        record->code=duplicateString(value);
    }
    else{
        printf("error");
        exit(0);
    }
  /*provided_CatalogRecord_setValue_code(record, value);*/
}

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_designation)(CatalogRecord * record, const char * value)
{
         free(record->designation);
         record->designation=duplicateString(value);
  /*provided_CatalogRecord_setValue_designation(record, value);*/
}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_unity)(CatalogRecord * record, const char * value)
{
         free(record->unity);
         record->unity=duplicateString(value);
  /*provided_CatalogRecord_setValue_unity(record, value);*/
}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_basePrice)(CatalogRecord * record, const char * value)
{
         record->basePrice=strtod(value,NULL);
  /*provided_CatalogRecord_setValue_basePrice(record, value);*/
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_sellingPrice)(CatalogRecord * record, const char * value)
{
         record->sellingPrice=strtod(value,NULL);
  /*provided_CatalogRecord_setValue_sellingPrice(record, value);*/
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_rateOfVAT)(CatalogRecord * record, const char * value)
{
        record->rateOfVAT=strtod(value,NULL);
  /*provided_CatalogRecord_setValue_rateOfVAT(record, value);*/
}

/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_code)(CatalogRecord * record)
{
    return duplicateString(record->code);
 /* return provided_CatalogRecord_getValue_code(record);*/
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_designation)(CatalogRecord * record)
{
    return duplicateString(record->designation);
  /*return provided_CatalogRecord_getValue_designation(record);*/
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_unity)(CatalogRecord * record)
{
    char * recordcopy;
    int i=0;
    recordcopy=(char *)malloc(sizeof(char)*CATALOGRECORD_UNITY_SIZE);
    memset(recordcopy,'\0',CATALOGRECORD_UNITY_SIZE);
    for ( i=0; record->unity[i]!='\0'; i++) {
        recordcopy[i]=record->unity[i];
    }
    return recordcopy;
/*  return provided_CatalogRecord_getValue_unity(record);*/
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_basePrice)(CatalogRecord * record)
{
    char * recordcopy;
    recordcopy=(char *)malloc(sizeof(char)*CATALOGRECORD_BASEPRICE_SIZE);
    sprintf(recordcopy, "%04.2f", record->basePrice);
    return recordcopy;
  /*return provided_CatalogRecord_getValue_basePrice(record);*/
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_sellingPrice)(CatalogRecord * record)
{
    char * recordcopy;
    recordcopy=(char *)malloc(sizeof(char)*CATALOGRECORD_SELLINGPRICE_SIZE);
    sprintf(recordcopy, "%04.2f", record->sellingPrice);
    return recordcopy;
  /*return provided_CatalogRecord_getValue_sellingPrice(record);*/
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_rateOfVAT)(CatalogRecord * record)
{
    char * recordcopy;
    recordcopy=(char *)malloc(sizeof(char)*CATALOGRECORD_RATEOFVAT_SIZE);
    sprintf(recordcopy, "%04.2f", record->rateOfVAT);
    return recordcopy;
/*  return provided_CatalogRecord_getValue_rateOfVAT(record);*/
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void IMPLEMENT(CatalogRecord_init)(CatalogRecord * record)
{
    record->code=duplicateString("");
    record->designation=duplicateString("");
    record->unity=duplicateString("");
    record->basePrice=0.0;
    record->sellingPrice=0.0;
    record->rateOfVAT=0.0;
  /*provided_CatalogRecord_init(record);*/
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void IMPLEMENT(CatalogRecord_finalize)(CatalogRecord * record)
{
    free(record->code);
    free(record->designation);
    free(record->unity);
   /* free(record);*/

 /*provided_CatalogRecord_finalize(record);*/
}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void IMPLEMENT(CatalogRecord_read)(CatalogRecord * record, FILE * file)
{
        char code[CATALOGRECORD_CODE_SIZE];
        char designation[CATALOGRECORD_DESIGNATION_SIZE];
        char unity[CATALOGRECORD_UNITY_SIZE];
        double basePriceCopy=0;
        double sellingPriceCopy=0;
        double rateOfVATCopy=0;

        memset(code, '\0' , sizeof(char)*CATALOGRECORD_CODE_SIZE);
        memset(designation, '\0' , sizeof(char)*CATALOGRECORD_DESIGNATION_SIZE);
        memset(unity, '\0' , sizeof(char)*CATALOGRECORD_UNITY_SIZE);

        if(  fread(code, CATALOGRECORD_CODE_SIZE, 1, file)!=1){
                fatalError("failed to read code!");
        }
        if(  fread(designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file)!=1){
                fatalError("failed to read designation!");
        }
        if(  fread(unity, CATALOGRECORD_UNITY_SIZE, 1, file)!=1){
                fatalError("failed to read unity!");
        }
        if(  fread(&basePriceCopy, CATALOGRECORD_BASEPRICE_SIZE, 1, file)!=1){
                fatalError("failed to read basePrice!");
        }
        if(  fread(&sellingPriceCopy, CATALOGRECORD_SELLINGPRICE_SIZE, 1, file)!=1){
                fatalError("failed to read sellingPrice!");
        }
        if(  fread(&rateOfVATCopy, CATALOGRECORD_RATEOFVAT_SIZE, 1, file)!=1){
                fatalError("failed to read rateOfVAT!");
        }
        copyStringWithLength( record->code , code,  (size_t)CATALOGRECORD_CODE_SIZE );
        copyStringWithLength( record->designation , designation , (size_t)CATALOGRECORD_DESIGNATION_SIZE);
        copyStringWithLength( record->unity , unity ,  (size_t)CATALOGRECORD_UNITY_SIZE);
        record->basePrice=basePriceCopy;
        record->sellingPrice=sellingPriceCopy;
        record->rateOfVAT=rateOfVATCopy;

  /*provided_CatalogRecord_read(record, file);*/
}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void IMPLEMENT(CatalogRecord_write)(CatalogRecord * record, FILE * file)
{
        char code[CATALOGRECORD_CODE_SIZE];
        char designation[CATALOGRECORD_DESIGNATION_SIZE];
        char unity[CATALOGRECORD_UNITY_SIZE];
        double basePriceCopy=0;
        double sellingPriceCopy=0;
        double rateOfVATCopy=0;

        memset(code, '\0', sizeof(char)*CATALOGRECORD_CODE_SIZE);
        memset(designation, '\0' , sizeof(char)*CATALOGRECORD_DESIGNATION_SIZE);
        memset(unity, '\0' , sizeof(char)*CATALOGRECORD_UNITY_SIZE);

        copyStringWithLength( code, record->code,  (size_t)CATALOGRECORD_CODE_SIZE );
        copyStringWithLength( designation , record->designation , (size_t)CATALOGRECORD_DESIGNATION_SIZE);
        copyStringWithLength( unity , record->unity ,  (size_t)CATALOGRECORD_UNITY_SIZE);
        basePriceCopy=record->basePrice;
        sellingPriceCopy=record->sellingPrice;
        rateOfVATCopy=record->rateOfVAT;

        if(  fwrite(code, CATALOGRECORD_CODE_SIZE, 1, file)!=1){
                fatalError("failed to write name!");
        }
        if(  fwrite(designation, CATALOGRECORD_DESIGNATION_SIZE, 1, file)!=1){
                fatalError("failed to write designation!");
        }
        if(  fwrite(unity, CATALOGRECORD_UNITY_SIZE, 1, file)!=1){
                fatalError("failed to write unity!");
        }
        if(  fwrite(&basePriceCopy, CATALOGRECORD_BASEPRICE_SIZE, 1, file)!=1){
                fatalError("failed to write basePrice!");
        }
        if(  fwrite(&sellingPriceCopy, CATALOGRECORD_SELLINGPRICE_SIZE, 1, file)!=1){
                fatalError("failed to write sellingPrice!");
        }
        if(  fwrite(&rateOfVATCopy, CATALOGRECORD_RATEOFVAT_SIZE, 1, file)!=1){
                fatalError("failed to write rateOfVAT!");
        }



  /*provided_CatalogRecord_write(record, file);*/
}

