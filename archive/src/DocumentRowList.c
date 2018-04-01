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
 * $Id: DocumentRowList.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentRowList.h>
#include <DocumentUtil.h>

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
void IMPLEMENT(DocumentRow_init)(DocumentRow * row) {
    row->code=duplicateString("");
    row->designation=duplicateString("");
    row->quantity=0.0;
    row->unity=duplicateString("");
    row->basePrice=0.0;
    row->sellingPrice=0.0;
    row->discount=0.0;
    row->rateOfVAT=0.0;
    row->next=NULL;
    /*provided_DocumentRow_init(row);*/
}

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
void IMPLEMENT(DocumentRow_finalize)(DocumentRow * row) {

    free(row->code);
    row->code=NULL;
    free(row->designation);
    row->designation=NULL;
    free(row->unity);
    row->unity=NULL;
    if(NULL!=row->next)
        free(row->next);row->next=NULL;
   /* provided_DocumentRow_finalize(row);*/
}

/** Create a new row on the heap and initialize it
 * @return the new row
 */
DocumentRow * IMPLEMENT(DocumentRow_create)(void) {

    DocumentRow *line;

    line=(DocumentRow*)malloc(sizeof(DocumentRow));
    if (line==NULL) {
        fatalError("line is NULL");
    }
    DocumentRow_init(line);

    return line;
   /* return provided_DocumentRow_create();*/
}

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
void IMPLEMENT(DocumentRow_destroy)(DocumentRow * row) {
    if(row==NULL){
    fatalError("row is invalid");
    }
    free(row->code);
    free(row->designation);
    free(row->unity);

    free(row);
   /* provided_DocumentRow_destroy(row);*/
}

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
void IMPLEMENT(DocumentRowList_init)(DocumentRow ** list) {


    *list=NULL;
    /*provided_DocumentRowList_init(list);*/
}

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */
void IMPLEMENT(DocumentRowList_finalize)(DocumentRow ** list) {
    DocumentRow *p;
    while(*list!=NULL){
        p=*list;
        *list=(*list)->next;
        DocumentRow_destroy(p);
    }

    /*provided_DocumentRowList_finalize(list);*/
}

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
DocumentRow * IMPLEMENT(DocumentRowList_get)(DocumentRow * list, int rowIndex) {
    if (rowIndex<0) {
        return NULL;
    }
    int i=0;
    while ((i<rowIndex )&&(list!=NULL) ){
        list=list->next;
        i++;
    }
    return list;
    /*return provided_DocumentRowList_get(list, rowIndex);*/
}

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
int IMPLEMENT(DocumentRowList_getRowCount)(DocumentRow * list) {

    int count=0;
    while (list!=NULL) {
        list=list->next;
        count++;
    }
    return count;
    /*return provided_DocumentRowList_getRowCount(list);*/
}

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
void IMPLEMENT(DocumentRowList_pushBack)(DocumentRow ** list, DocumentRow * row) {
    DocumentRow *p=*list;
    if(p==NULL){
        *list=row;
    }else{
        while (p->next!=NULL) {
        p=p->next;
    }
    p->next=row;
    row->next=NULL;
    /*free(p);*/
    }


    /*provided_DocumentRowList_pushBack(list, row);*/
}

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertBefore)(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    DocumentRow *p = *list;
    if(p == position){
        *list = row;
        (*list)->next = p;
    }else{

        while (p->next!=position&&(p->next!=NULL)) {
            p = p->next;
        }
        p->next=row;
        row->next=position;}
/*    provided_DocumentRowList_insertBefore(list, position, row);*/
}

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertAfter)(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    DocumentRow *p = *list;
    if(*list == NULL){
        *list = row;

    }else{
        p = position->next;
        position->next=row;
        row->next = p;

        }
    /*provided_DocumentRowList_insertAfter(list, position, row);*/
}

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
void IMPLEMENT(DocumentRowList_removeRow)(DocumentRow ** list, DocumentRow * position) {
/*
    DocumentRow *p=*list;
    if(p==position){
    *list=position->next;
    }else{
        while (p->next!=position&&p->next!=NULL) {
        p=p->next;
        }
    p->next=position->next;
    }*/


    DocumentRow *p = *list;
    if(p!=NULL)
    {
        while(p!=position&&p->next!=position&&p->next!=NULL)
        {
            p = p->next;
        }
        if(p!=position)
            p->next = position->next;
        else
            *list = position->next;
        DocumentRow_destroy(position);
    }

    /*provided_DocumentRowList_removeRow(list, position);*/
}

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
void IMPLEMENT(DocumentRow_writeRow)(DocumentRow * row, FILE * file) {
    writeString(row->code, file);
    writeString(row->designation, file);
    if( fwrite(&(row->quantity), sizeof(double), 1, file)!=1){
        fatalError("write failed!");
    }
    writeString(row->unity, file);
    if(fwrite(&(row->basePrice), sizeof(double), 1, file)!=1){
        fatalError("write failed!");
    }
    if(fwrite(&(row->sellingPrice), sizeof(double), 1, file)!=1){
        fatalError("write failed!");
    }
    if(fwrite(&(row->discount), sizeof(double), 1, file)!=1){
        fatalError("write failed!");
    }
    if(fwrite(&(row->rateOfVAT), sizeof(double), 1, file)!=1){
        fatalError("write failed!");
    }
  /*  provided_DocumentRow_writeRow(row, file);*/
}

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
DocumentRow * IMPLEMENT(DocumentRow_readRow)(FILE * file) {

    DocumentRow*row=(DocumentRow*)malloc(sizeof(DocumentRow));
    if(row == NULL)
    {
        fatalError("DocumentRowList_readRow *row Error");
    }
    row->code=readString(file);
    row->designation=readString(file);
    if(1!=fread(&(row->quantity),sizeof(double),1,file)){
        fatalError("DocumentRow_readRow fread Error!");
    }
    row->unity=readString(file);
    if(1!=fread(&(row->basePrice),sizeof(double),1,file)){
        fatalError("DocumentRow_readRow fread Error!");
    }
    if(1!=fread(&(row->sellingPrice),sizeof(double),1,file)){
        fatalError("DocumentRow_readRow fread Error!");
    }
    if(1!=fread(&(row->discount),sizeof(double),1,file)){
        fatalError("DocumentRow_readRow fread Error!");
    }
    if(1!=fread(&(row->rateOfVAT),sizeof(double),1,file)){
        fatalError("DocumentRow_readRow fread Error!");
    }
    row->next=NULL;
    return row;
/*  return provided_DocumentRow_readRow(fichier);*/
}
