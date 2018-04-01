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
 * $Id: PrintFormat.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <PrintFormat.h>
#include <Dictionary.h>

/** Initialize a print format
 * @param format a print format
 * @warning initialized print format should be finalized with PrintFormat_finalize()
 */
void IMPLEMENT(PrintFormat_init)(PrintFormat * format)
{

    if(format==NULL)
    {
        format=(PrintFormat*)malloc(sizeof(PrintFormat));
        if(format==NULL)
            fatalError("PrintFormat_init format Error!");
    }
    format->name=NULL;
    format->header=NULL;
    format->row=NULL;
    format->footer=NULL;
  /*provided_PrintFormat_init(format);*/
}

/** Finalize a print format
 * @param format the print format
 */
void IMPLEMENT(PrintFormat_finalize)(PrintFormat * format)
{
    if(format==NULL){
        fatalError("format is null!");
    }
    free(format->name);
    format->name=NULL;
    free(format->header);
    format->header=NULL;
    free(format->row);
    format->row=NULL;
    free(format->footer);
    format->footer=NULL;
/*  provided_PrintFormat_finalize(format);*/
}

/** Load a print format from a file
 * @param format an initialized print format to fill
 * @param filename the file name
 */
void IMPLEMENT(PrintFormat_loadFromFile)(PrintFormat * format, const char * filename)
{

  provided_PrintFormat_loadFromFile(format, filename);
}

