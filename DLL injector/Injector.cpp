#include <Windows.h>
#include <TlHelp32.h>
#include "injector.h"

using namespace std;


int DllInjector::inject(const char * szProcessName,const char * szPathToDll)
{
	ProcessList ProcessIDs = getProcessIDsByName(szProcessName);

	if (ProcessIDs.empty())
		return 1;

	DWORD processID = ProcessIDs.at(0); // first of processes

	return inject(processID, szPathToDll);

}

int DllInjector::inject(int processID, const char * szPathToDll)
{

	HANDLE processHandel;

	processHandel = OpenProcess(PROCESS_ALL_ACCESS, false, processID); // open...

	if (!processHandel)
		return 2;

	DWORD path_len = strlen(szPathToDll) + 1; // len + null-byte
	DWORD kernel_adr = (DWORD)GetProcAddress(LoadLibrary("Kernel32.dll"), "LoadLibraryA");
	LPVOID lpParams = VirtualAllocEx(processHandel, NULL, path_len, MEM_COMMIT, PAGE_READWRITE);


	if (!lpParams)
	{
		CloseHandle(processHandel);
		return 3;
	}

	if (!WriteProcessMemory(processHandel, lpParams, szPathToDll, path_len, nullptr))
	{
		CloseHandle(processHandel);
		return 4;
	}


	DWORD ThreadID;
	HANDLE hThread = CreateRemoteThread(processHandel, NULL, 0, (LPTHREAD_START_ROUTINE)kernel_adr, lpParams, 0, &ThreadID);
	if (!hThread)
	{
		DWORD ERROR_CODE = GetLastError();

		CloseHandle(processHandel);
		return 5;
	}

	CloseHandle(processHandel);
	return 0;
}

DllInjector::ProcessList DllInjector::getProcessIDsByName(const char * process_name)
{
	ProcessList IDs;

	HANDLE snapHandle;
	PROCESSENTRY32 processEntry = { 0 };

	if ((snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
		return IDs;

	processEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(snapHandle, &processEntry);
	do {
		if (!strcmp(processEntry.szExeFile, process_name))
		{
			IDs.push_back(processEntry.th32ProcessID);

		}
	} while (Process32Next(snapHandle, &processEntry));


	if (snapHandle != INVALID_HANDLE_VALUE)
		CloseHandle(snapHandle);

	return IDs;
}
