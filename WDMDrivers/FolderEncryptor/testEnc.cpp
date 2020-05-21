// CNGEncryptor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <bcrypt.h>

int wmain() {
    HANDLE outFile = CreateFile(L"sometest.enc", GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
    BCRYPT_ALG_HANDLE encAlgoHandle{ INVALID_HANDLE_VALUE };
    auto numberOfBlocks{ 5 };
    DWORD blockSize =  512 ;
    DWORD cbKeyObject{ 0 };
    DWORD cbData{ 0 };
    PBYTE pbKeyobject{ nullptr };
    PBYTE writeBlock = NULL;

    NTSTATUS status = BCryptOpenAlgorithmProvider(&encAlgoHandle, 
                        BCRYPT_AES_ALGORITHM, NULL, 0);

    if (status < 0) goto CleanUp;

    // Getting the key properties of the algorithm
    BCryptGetProperty(encAlgoHandle, BCRYPT_OBJECT_LENGTH,
        (PBYTE)&cbKeyObject, sizeof(DWORD), &cbData, 0);
    pbKeyobject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbKeyObject);
    
    BCryptGetProperty(encAlgoHandle, BCRYPT_BLOCK_LENGTH, (PBYTE)&blockSize,
        sizeof(DWORD), &cbData, 0);

    std::cout << "Key length:" << cbKeyObject << "\n";
    std::cout << "Block length" << blockSize << "\n";

    writeBlock = new BYTE[blockSize];
    memset(writeBlock, 65, blockSize);

    for (auto i = 0; i < numberOfBlocks; i++) {
        DWORD dwWritten;
        
        // TODO: Encrypt the buffer
        
        auto writeStatus = WriteFile(outFile, writeBlock, blockSize, &dwWritten, NULL);

        if (TRUE == writeStatus && dwWritten == blockSize) {
            std::cout << "Write Okay, block#" << i + 1 << "\n";
        }
    }

CleanUp:
    delete[] writeBlock;
    if (pbKeyobject) HeapFree(GetProcessHeap(), 0, pbKeyobject);
    if( INVALID_HANDLE_VALUE != outFile ) CloseHandle(outFile);
    if (INVALID_HANDLE_VALUE != encAlgoHandle) BCryptCloseAlgorithmProvider(encAlgoHandle,0);
}
