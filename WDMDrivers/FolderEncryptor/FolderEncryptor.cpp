// FolderEncryptor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ErrorObject.h"

#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <string>

void doDummyEncryption(TCHAR* fileName) {
	HANDLE hSourceFile = INVALID_HANDLE_VALUE;
	HANDLE hDestinationFile = INVALID_HANDLE_VALUE;

	hSourceFile = ::CreateFile(fileName, 
					FILE_GENERIC_READ, 
					FILE_SHARE_READ, 
					NULL, OPEN_EXISTING, 
					FILE_FLAG_SEQUENTIAL_SCAN, 
					NULL);

	if ( INVALID_HANDLE_VALUE == hSourceFile) {
		throw ErrorObject{};
	}

	TCHAR encryptedFileName[MAX_PATH];
	ZeroMemory(encryptedFileName, MAX_PATH);

	_tcscat_s(encryptedFileName, fileName);
	_tcscat_s(encryptedFileName, _T(".enc"));

	hDestinationFile = ::CreateFile(encryptedFileName, 
							FILE_GENERIC_WRITE, 
							0, 
							NULL, 
							CREATE_ALWAYS, 
							0, 
							NULL);

	BOOL bReadReadReturnStatus = TRUE;

	PVOID readBuffer, nextAddress;
	readBuffer = VirtualAlloc(&nextAddress, 512, MEM_COMMIT, PAGE_READWRITE);

	while (TRUE == bReadReadReturnStatus) {
		DWORD dwRead, dwWritten;
		bReadReadReturnStatus = ReadFile(hSourceFile, readBuffer, 512, &dwRead, NULL);

		WriteFile(hDestinationFile, readBuffer, dwRead, &dwWritten, NULL);

		if (dwRead != dwWritten) {
			throw ErrorObject{};
		}
	}
	if (hDestinationFile == INVALID_HANDLE_VALUE) {
		throw ErrorObject{};
	}

	CloseHandle(hDestinationFile);
	CloseHandle(hSourceFile);
}

int _tmain(int argc, TCHAR* argv[]) {
	try {
		doDummyEncryption(argv[0]);
	}
	catch( ErrorObject e ) {
		std::wcout << e.getErrorString() << std::endl;
	}

    std::cout << "Encrypts files in a folder specified\n"; 
}
