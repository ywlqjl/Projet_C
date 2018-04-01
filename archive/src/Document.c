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
 * $Id: Document.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Document.h>
#include <DocumentUtil.h>
#include <DocumentRowList.h>

/** Initialize a document
 * @param document a pointer to a document
 * @warning An initialized document must be finalized by Document_finalize() to free all resources
 */
void IMPLEMENT(Document_init)(Document * document) {

   /* document->customer.name=duplicateString("");
    document->customer.postalCode=duplicateString("");
    document->customer.address=duplicateString("");
    document->customer.town=duplicateString("");*/
    CustomerRecord_init(&(document->customer));
    document->editDate=duplicateString("");
    document->expiryDate=duplicateString("");
    document->docNumber=duplicateString("");
    document->object=duplicateString("");
    document->operator=duplicateString("");
    document->rows=NULL;
    document->typeDocument=QUOTATION;

/*    provided_Document_init(document);*/
}

/** Finalize a document
 * @param document the document to finalize
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_finalize)(Document * document) {

    CustomerRecord_finalize(&(document->customer));

    free(document->editDate);
    free(document->expiryDate);
    free(document->docNumber);
    free(document->object);
    free(document->operator);

    DocumentRowList_finalize(&document->rows);
    /*provided_Document_finalize(document);*/
}

/** Save the content of a document to a file
 * @param document the document
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_saveToFile)(Document * document, const char * filename) {

    int rowsLength=DocumentRowList_getRowCount(document->rows);
    FILE *file;
    file=fopen(filename,"wb+");
    if(file==NULL){
        fatalError("saveToFile:failed to fopen!");
    }
    DocumentRow *row=document->rows;

    if(document==NULL){
        fatalError("saveToFile document Error!");
    }

    CustomerRecord_write(&(document->customer), file);
    writeString(document->editDate,file);
    writeString(document->expiryDate,file);
    writeString(document->docNumber,file);
    writeString(document->object,file);
    writeString(document->operator,file);

    if(fwrite(&rowsLength,sizeof(int),1,file)<1){
        fclose(file);
        fatalError("Document_saveToFile fwrite Error!");
    }

    while(row!=NULL)
    {
        DocumentRow_writeRow(row,file);
        row=row->next;
    }
    if(fwrite(&(document->typeDocument),sizeof(int),1,file)<1){
        fclose(file);
        fatalError("Document_saveToFile fwrite Error!");
    }

    fclose(file);
    file=NULL;

   /* provided_Document_saveToFile(document,filename);*/
}

/** Load the content of a document from a file
 * @param document the document to fill
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_loadFromFile)(Document * document, const char * filename) {

    int rowsLength;
    FILE *file=fopen(filename,"rb+");
    DocumentRow *rowtemp;
    int i=0;

    if(file==NULL){
        fatalError("failed to fopen file!");
    }

    if(fread(document->customer.name,CUSTOMERRECORD_NAME_SIZE,1,file)!=1){
        fatalError("Document_loadFromFile fread Error!");
    }
    if(fread(document->customer.address,CUSTOMERRECORD_ADDRESS_SIZE,1,file)!=1){
        fatalError("Document_loadFromFile fread Error!");
    }
    if(1!=fread(document->customer.postalCode,CUSTOMERRECORD_POSTALCODE_SIZE,1,file))
        fatalError("Document_loadFromFile fread Error!");
    if(1!=fread(document->customer.town,CUSTOMERRECORD_TOWN_SIZE,1,file))
        fatalError("Document_loadFromFile fread Error!");

    free(document->editDate);
    free(document->expiryDate);
    free(document->docNumber);
    free(document->object);
    free(document->operator);
    document->editDate=readString(file);
    document->expiryDate=readString(file);
    document->docNumber=readString(file);
    document->object=readString(file);
    document->operator=readString(file);
    if(fread(&rowsLength,sizeof(int),1,file)!=1){
        fatalError("rowLength fread Error!");
    }
    while(i<rowsLength){
        rowtemp = DocumentRow_readRow(file);
        DocumentRowList_pushBack(&(document->rows), rowtemp);
        i++;
    }
     if(fread(&(document->typeDocument), sizeof(document->typeDocument), 1, file)!=1){
        fclose(file);
        fatalError("error");
    }
    fclose(file);
/*    provided_Document_loadFromFile(document,filename);*/
}

