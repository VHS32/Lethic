#include "..\Source\payloads.c"

int main()
{
	HANDLE mythread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Payload_3, 0, 0, 0);
    WaitForSingleObject(mythread, INFINITE);
	CloseHandle(mythread);
    return 0;
}
