#include "query.h"

// sunction creates a query to WMI constructed from the wstr query, the fs field, and the qt query result type
wchar_t* query(wchar_t* wstr, wchar_t* fs, enum QType qt, Qstruk* qs) {
    qs->hres = qs->pSvc->lpVtbl->ExecQuery(
        qs->pSvc,
        L"WQL",
        wstr,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &(qs->pEnumerator));

    if (FAILED(qs->hres)) {
        printf("Query failed: %ls\n", wstr);
        qs->pSvc->lpVtbl->Release(qs->pSvc);
        qs->pLoc->lpVtbl->Release(qs->pLoc);
        CoUninitialize();
        return 1;
    }

    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;
    //wchar_t* res = (wchar_t*)malloc(40 * sizeof(wchar_t));
    wchar_t res[256];
    int resSize = 256;
    res[0] = L'\0';

    while (qs->pEnumerator) {
        HRESULT hr = qs->pEnumerator->lpVtbl->Next(qs->pEnumerator, WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;

        hr = pclsObj->lpVtbl->Get(pclsObj, fs, 0, &vtProp, 0, 0);

        if (SUCCEEDED(hr)) {
            switch(qt) {
                case STRV:
                    wcsncpy(res, vtProp.bstrVal, resSize - 1); 
                    res[resSize - 1] = L'\0';
                    break;
                case INTV:
                    int num = vtProp.intVal;
                    swprintf(res, resSize, L"%d", num);
                    break;
            }
        }
        VariantClear(&vtProp);


        pclsObj->lpVtbl->Release(pclsObj);
    }
    return res;
}
