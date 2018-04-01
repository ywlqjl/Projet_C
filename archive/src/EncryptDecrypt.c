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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>
char encode(char key, char decoded){
    key=toLowerChar(key);
    decoded=toLowerChar(decoded);
    key=(char)(key-'a'+1);
    decoded=(char)(decoded-'a'+1);
    char a;
    a=(char)(((key+decoded)%26-1)+'a'-1);

    return a;
}

char decode(char key, char encoded){
    key=toUpperChar(key);
    encoded=toUpperChar(encoded);
    key=(char)((key-'a'+1));
    encoded=(char)(encoded-'a'+1);
    char decode;
    decode=(char)((26+(encoded-key))%26+'a');
    return decode;
}
void IMPLEMENT(encrypt)(const char * key, char * str) {
    size_t lk=0;
    size_t ls=0;
    size_t i=0;
    lk=stringLength(key);
    ls=stringLength(str);

    for (i=0; i<ls; i++) {

        str[i]=encode(key[i%lk], str[i]);

    }
   /* provided_encrypt(key,str);*/
}
void IMPLEMENT(decrypt)(const char * key, char * str) {
        size_t lk=0;
    size_t ls=0;
    size_t i=0;
    lk=stringLength(key);
    ls=stringLength(str);

    for (i=0; i<ls; i++) {

        str[i]=decode(key[i%lk], str[i]);

    }
   /* provided_decrypt(key,str);*/
}
