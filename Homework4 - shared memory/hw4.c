//Pinchas Plevinski 322211558

#include <windows.h>
#include <stdio.h>
#define FILENAME  "gibrish.bin" 

int main()
{
    // get system memory allignement granularity (usually 65536) 
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    int mem_buffer_size = sys_info.dwAllocationGranularity;
	BOOL reader;
	HANDLE hFile;
	HANDLE hMappedFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "myFile");
	if (hMappedFile == NULL)
		// open mapped file failed,
		// the file is not already mapped into other process memory
		reader = TRUE;		// this process should be doing the reading part
	else
		reader = FALSE;		// this process should be doing the writing part

	if (reader)
	{
		printf("I am reader process\n");
		hFile = CreateFileA(FILENAME,  // file name 
			GENERIC_READ | GENERIC_WRITE, // access type
			FILE_SHARE_WRITE | FILE_SHARE_READ, // other processes can share to write 
			NULL,	 	// security 
			OPEN_EXISTING,	 // open only if file exists 
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		DWORD file_size = GetFileSize(hFile, NULL);
		// create file mapping object
		hMappedFile = CreateFileMappingA(
			hFile, 		// file handle 
			NULL, 		// default security 
			PAGE_READWRITE, // read access 
			0,		 // maximum object size (high-order DWORD)
			0,		 // maximum object size (low-order DWORD)
			// 0 means map the whole file 
			"myFile");		 // name of mapping object, in case we  want to share it

		if (hMappedFile == NULL)
		{
			printf("Could not create file mapping object.\n");
			return 1;
		}
		
		// read the file
		LPSTR pBuf;

		pBuf = (LPSTR)MapViewOfFile(
			hMappedFile, 	// handle to map object 
			FILE_MAP_ALL_ACCESS, // read/write permission 
			0, 		// start point (upper word) 
			0, 	// start point (lower word) 
			mem_buffer_size); // how many bytes to read 

		if (pBuf == NULL)
		{
			printf("Could not map view of file.\n");

			CloseHandle(hMappedFile);

			return 1;
		}
	
		while (TRUE)
		{
			if (pBuf[0] == *(LPCSTR)"*")
			{
				printf("Reader found *\n");
				break;
			}
		}

		UnmapViewOfFile(pBuf);
		CloseHandle(hMappedFile);
		CloseHandle(hFile);
	}
	else
	{
		printf("I am writer process\n");
		//HANDLE hMappedFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "myFile");
		LPSTR pBuf;
		pBuf = (LPSTR)MapViewOfFile(
			hMappedFile, 	// handle to map object 
			FILE_MAP_ALL_ACCESS, // read/write permission 
			0, 		// start point (upper word) 
			0, 	// start point (lower word) 
			mem_buffer_size); // how many bytes to read 

		if (pBuf == NULL)
		{
			printf("Could not map view of file.\n");

			CloseHandle(hMappedFile);

			return 1;
		}
		*((LPSTR)pBuf) = '*';
		printf("Writer process finishing\n");
		UnmapViewOfFile(pBuf);
		CloseHandle(hMappedFile);
	}
	return 0;
}