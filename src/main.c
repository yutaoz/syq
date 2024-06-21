#include <windows.h>
#include <stdio.h>
#include <wbemidl.h>
#include <oleauto.h>
#include "query.h"
#include "services/winutil.h"

#pragma comment(lib, "wbemuuid.lib")

int main() {
    HRESULT hres;

    // init com
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        printf("Failed to initialize COM. Error code = 0x%x\n", hres);
        return 1;
    }

    // set general com security levels
    hres = CoInitializeSecurity(
        NULL,                        // security descriptor
        -1,                          // com negotiates auth service
        NULL,                        // auth services
        NULL,                        // reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // default auth level for proxies 
        RPC_C_IMP_LEVEL_IMPERSONATE, // default impersonation level for proxies
        NULL,                        // auth info
        EOAC_NONE,                   // additional capabilities of client or server 
        NULL                         // reserved
    );

    if (FAILED(hres)) {
        printf("Failed to initialize security. Error code = 0x%x\n", hres);
        CoUninitialize();
        return 1;
    }

    // init iwbem locator
    IWbemLocator *pLoc = NULL;

    hres = CoCreateInstance(
        &CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        &IID_IWbemLocator, (LPVOID *)&pLoc);

    if (FAILED(hres)) {
        printf("Failed to create IWbemLocator object. Error code = 0x%x\n", hres);
        CoUninitialize();
        return 1;
    }

    // connect to WMI
    IWbemServices *pSvc = NULL;

    // connect to the root\cimv2 namespace
    hres = pLoc->lpVtbl->ConnectServer(
        pLoc,
        L"ROOT\\CIMV2",  // namespace
        NULL,            // username
        NULL,            // passwrd
        0,               // locale
        NULL,            // security flags.
        0,               // authority
        0,               // context object
        &pSvc            // iwbemservices proxy
    );

    if (FAILED(hres)) {
        printf("Could not connect. Error code = 0x%x\n", hres);
        pLoc->lpVtbl->Release(pLoc);
        CoUninitialize();
        return 1;
    }

    // set security levels on iwbemservices proxy
    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        NULL,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE
    );

    if (FAILED(hres)) {
        printf("Could not set proxy blanket. Error code = 0x%x\n", hres);
        pSvc->lpVtbl->Release(pSvc);
        pLoc->lpVtbl->Release(pLoc);
        CoUninitialize();
        return 1;
    }

    // query wmi
    IEnumWbemClassObject* pEnumerator = NULL;

    Qstruk qs = {
        .hres = hres,
        .pLoc = pLoc,
        .pSvc = pSvc,
        .pEnumerator = pEnumerator
    };


    // DISPLAY SERVICES
    dispOS(&qs);
    dispSysName(&qs);
    dispCPUName(&qs);
    dispCPUCores(&qs);
    maxCPUClock(&qs);
    dispGPUName(&qs);
    dispGPUDriverVersion(&qs);
    dispRefresh(&qs);

    // cleanup
    pSvc->lpVtbl->Release(pSvc);
    pLoc->lpVtbl->Release(pLoc);
    pEnumerator->lpVtbl->Release(pEnumerator);
    CoUninitialize();

    return 0;
}
