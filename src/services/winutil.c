#include "winutil.h"


void dispOS(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Caption";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT * FROM Win32_OperatingSystem", field, qt, qs), 255);
    printf("OS: %ls\n", w);
}

void dispCPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT * FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU: %ls\n", w);

}

void dispCPUCores(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"NumberOfCores";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT * FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU Cores: %ls\n", w);
}

void maxCPUClock(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"MaxClockSpeed";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT * FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU Max Clock: %ls\n", w);
}

void dispGPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Name FROM Win32_VideoController", field, qt, qs), 255);
    printf("GPU: %ls\n", w);
}
