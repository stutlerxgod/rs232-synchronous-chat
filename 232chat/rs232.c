#include "rs232.h"
#include <stdio.h>

bool rs232_open(struct rs232_obj* port, uint8_t port_number, uint32_t baudrate) 
{
	// init structure
	port->baudrate = baudrate;
	port->handle = INVALID_HANDLE_VALUE;
	sprintf(port->port_name, "\\\\.\\COM%d", (int)port_number);
	
	// open COM port
	HANDLE handle = CreateFileA(
		port->port_name,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (handle == INVALID_HANDLE_VALUE) // does not exist or is used by another process
		return false;

	// set COM port parameters
	DCB params = { 0 };
	params.DCBlength = sizeof(DCB);
	if (!GetCommState(handle, &params)) {
		CloseHandle(handle);
		return false;
	}
	// change params
	params.BaudRate = port->baudrate;
	params.ByteSize = 8;
	params.Parity = NOPARITY;
	params.StopBits = ONESTOPBIT;
	// apply params
	if (!SetCommState(handle, &params)) {
		CloseHandle(handle);
		return false;
	}

	// set timeouts
	COMMTIMEOUTS timeouts = {
		.ReadIntervalTimeout = 0,
		.ReadTotalTimeoutMultiplier = 1,
		.ReadTotalTimeoutConstant = 1,
		.WriteTotalTimeoutConstant = 1,
		.WriteTotalTimeoutMultiplier = 1
	};
	if (!SetCommTimeouts(handle, &timeouts)) {
		CloseHandle(handle);
		return false;
	}

	// everything is OK
	port->handle = handle;
	return true;
}

bool rs232_close(struct rs232_obj* port) 
{
	if (port->handle != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(port->handle);
		port->handle = INVALID_HANDLE_VALUE;
		return true;
	}
	return false;
}

bool rs232_read(struct rs232_obj* port, uint8_t* buffer, uint32_t buffer_size,
	uint32_t* count) 
{
	if (port->handle == INVALID_HANDLE_VALUE)
		return false;

	DWORD bytesRead;
	if (!ReadFile(port->handle, buffer, buffer_size, &bytesRead, NULL)) 
	{
		return false;
	}

	*count = bytesRead;
	return true;
}

bool rs232_write(struct rs232_obj* port, uint8_t* buffer, uint32_t buffer_size,
	uint32_t* count) 
{
	if (port->handle == INVALID_HANDLE_VALUE)
		return false;

	DWORD bytesWritten;
	if (!WriteFile(port->handle, buffer, buffer_size, &bytesWritten, NULL)) 
	{
		return false;
	}

	*count = bytesWritten;
	return true;
}
