#pragma once

#include <Windows.h>
#include <stdbool.h>
#include <inttypes.h>

struct rs232_obj 
{
	HANDLE handle;
	char port_name[32];
	int baudrate;
};

bool rs232_open(struct rs232_obj* port, uint8_t port_number, uint32_t baudrate);

bool rs232_close(struct rs232_obj* port);

bool rs232_read(struct rs232_obj* port, uint8_t* buffer, uint32_t buffer_size, 
				uint32_t* count);

bool rs232_write(struct rs232_obj* port, uint8_t* buffer, uint32_t buffer_size, 
				 uint32_t* count);