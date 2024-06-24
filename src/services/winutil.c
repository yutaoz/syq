#include "winutil.h"
#include <wchar.h>

#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define BRIGHT_GREEN "\033[0;92m"
#define BRIGHT_BLUE "\033[0;94m"
#define BRIGHT_MAGENTA "\033[0;95m"
#define BRIGHT_CYAN "\033[0;96m"
#define RESET "\033[0m"

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    
    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }

    outModeInit = outMode;
    
    // enable ansi escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }   
}

void restoreConsole(void) {
    // reset colors
    printf("\x1b[0m");  
    
    // reset console mode
    if(!SetConsoleMode(stdoutHandle, outModeInit)) {
        exit(GetLastError());
    }
}
void dispOS(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Caption";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Caption FROM Win32_OperatingSystem", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[OS\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispCPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Name FROM Win32_Processor", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[CPU\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispCPUCores(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"NumberOfCores";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT NumberOfCores FROM Win32_Processor", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[CPU Cores\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void maxCPUClock(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"MaxClockSpeed";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT MaxClockSpeed FROM Win32_Processor", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[CPU Max Clock\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispGPUName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"Name";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT Name FROM Win32_VideoController", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[GPU\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispGPUDriverVersion(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"DriverVersion";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT DriverVersion FROM Win32_VideoController", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[GPU Driver Version\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispRefresh(Qstruk* qs) {
    enum QType qt = INTV;
    wchar_t* field = L"MaxRefreshRate";
    wchar_t w[256];
    wchar_t x[256];
    wcsncpy(w, query(L"SELECT MaxRefreshRate FROM Win32_VideoController", field, qt, qs), 255);
    field = L"CurrentRefreshRate";
    wcsncpy(x, query(L"SELECT CurrentRefreshRate FROM Win32_VideoController", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[Curr/Max Refresh Rate\]:");
    restoreConsole();
    printf(" %lshz/%lshz\n", w, x);
}

void dispSysName(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"SystemName";
    wchar_t w[256];
    wcsncpy(w, query(L"SELECT SystemName FROM Win32_VideoController", field, qt, qs), 255);
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[System\]:");
    restoreConsole();
    printf(" %ls\n", w);
}

void dispMemory(Qstruk* qs) {
    enum QType qt = STRV;
    wchar_t* field = L"FreePhysicalMemory";
    wchar_t w[256];
    wchar_t x[256];
    float GBCONV = 9.5367431640625E-7f;
    
    wcsncpy(w, query(L"SELECT FreePhysicalMemory FROM Win32_OperatingSystem", field, qt, qs), 255);
    field = L"TotalVisibleMemorySize";
    wcsncpy(x, query(L"SELECT TotalVisibleMemorySize FROM Win32_OperatingSystem", field, qt, qs), 255);
    float inuse = ((float)_wtoi(w)) * GBCONV;
    float max = ((float)_wtoi(x)) * GBCONV;
    setupConsole();
    printf(BRIGHT_MAGENTA "    \[Memory Usage\]:");
    restoreConsole();
    printf(" %.2fGB/%.2fGB", max - inuse, max);
}