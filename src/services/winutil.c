#include "winutil.h"


void dispOS(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Caption";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Caption FROM Win32_OperatingSystem", field, qt, qs), 255);
    printf("OS: %ls\n", w);
}

void dispCPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Name FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU: %ls\n", w);

}

void dispCPUCores(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"NumberOfCores";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT NumberOfCores FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU Cores: %ls\n", w);
}

void maxCPUClock(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"MaxClockSpeed";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT MaxClockSpeed FROM Win32_Processor", field, qt, qs), 255);
    printf("CPU Max Clock: %ls\n", w);
}

void dispGPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Name FROM Win32_VideoController", field, qt, qs), 255);
    printf("GPU: %ls\n", w);
}

void dispGPUDriverVersion(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"DriverVersion";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT DriverVersion FROM Win32_VideoController", field, qt, qs), 255);
    printf("GPU Driver Version: %ls\n", w);
}

void dispRefresh(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"MaxRefreshRate";
    wchar_t w[256];
    wchar_t x[256];
    wcsncpy(w, query(L"SELECT MaxRefreshRate FROM Win32_VideoController", field, qt, qs), 255);
    field = L"CurrentRefreshRate";
    wcsncpy(x, query(L"SELECT CurrentRefreshRate FROM Win32_VideoController", field, qt, qs), 255);
    printf("Curr/Max Refresh Rate: %lshz/%lshz\n", w, x);
}

void dispSysName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"SystemName";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT SystemName FROM Win32_VideoController", field, qt, qs), 255);
    printf("System: %ls\n", w);
}
