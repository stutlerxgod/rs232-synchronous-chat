#include <stdio.h>
#include "rs232.h"
#include <string.h>
#include <Windows.h>


void clear_buffer() 
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// func for read thread
DWORD WINAPI ReadThread(LPVOID lpParameter)
{
    struct rs232_obj* str = (struct rs232_obj*)lpParameter;
    // read message
    while (1) 
    {
        uint32_t tmp;
        char buffer[256];
        if (rs232_read(str, buffer, 255, &tmp) && tmp > 0)
        {
            buffer[tmp] = 0;
            printf("\n\nReceived from %s\n", buffer);
            printf("Your message to send: ");
        }
        Sleep(100);
    }
    return 0;
}

int main() {
    // select COM port
    int port_no;
    while (1) 
    {
        printf("Select COM port: ");
        if (scanf("%d", &port_no) != 1 || port_no < 0 || port_no > 255) 
        {
            printf("Invalid port number!\n");
            clear_buffer();
            continue;
        }
        break;
    }
    
    // clear input buffer
    clear_buffer();

    struct rs232_obj port;
    if (!rs232_open(&port, (uint8_t)port_no, 9600)) 
    {
        printf("Failed to open specified COM port!\n");
        return 1;
    }

    char user_name[20];

    while (1) 
    {
        printf("Select user_name: ");
        fgets(user_name, 255, stdin);

        if (strlen(user_name) < 4 || strlen(user_name) > 18) 
        {
            printf("Username is not valid!\n");
            memset(user_name, '\0', sizeof(user_name)-1);
            continue;
        }
        user_name[strlen(user_name)-1] = '\0';
        break;
    }

    // modify username by adding : symbol at the end
    strcat(user_name, ": ");
    int user_name_len = strlen(user_name);
    

    // start receive message thread
    HANDLE hThread = CreateThread(
        NULL,    // Thread attributes
        0,       // Stack size (0 = use default)
        ReadThread, // Thread start address
        &port,    // Parameter to pass to the thread
        0,       // Creation flags
        NULL);   // Thread id
    if (hThread == NULL)
    {
        // Thread creation failed.
        return 1;
    }


    // communication
    bool running = true;
    while (running) 
    {
        char buffer[31];
        uint32_t tmp;


        // add name before message
        memcpy(buffer, user_name, user_name_len);


        // get message from user
        while (1 && running) 
        {
            printf("Your message to send: ");
            fgets(buffer + user_name_len, 255, stdin);
            
            if (strlen(buffer + user_name_len) < 2 || strlen(buffer) > 30)
            {
                printf("message is too big|small!\n");
                continue;
            }
            break;
        }


        // send message
        if (!rs232_write(&port, (uint8_t*)buffer, strlen(buffer), &tmp)) 
        {
            printf("Failed to write data to COM port!\n");
        }
        running = running && strstr(buffer, "exit") != buffer;  
    }

    // close COM port
    rs232_close(&port);
    //end thread
    CloseHandle(hThread);

    return 0;
}
