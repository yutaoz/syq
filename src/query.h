#ifndef QUERY_H
#define QUERY_H

#include <stdio.h>
#include <wbemidl.h>

enum QType {
    STRV,
    INTV
};

typedef struct {
    HRESULT hres;
    IWbemLocator* pLoc;
    IWbemServices* pSvc;
    IEnumWbemClassObject* pEnumerator;
} Qstruk;

wchar_t* query(wchar_t* wstr, wchar_t* fs, enum QType qt, Qstruk* qs);

#endif
