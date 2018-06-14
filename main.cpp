/*
 * file: main.cpp
 * purpose: Entry point for the test program.
 */
#include <iostream>
#include "serial-port-wrapper.hpp"


int main()
{
    SERIAL_PORT_WRAPPER & my_serial_port(SERIAL_PORT_WRAPPER::getInstance());

    char buffer[16] = {0};

    for (int i = 1; i < 255; ++i)
    {
        if (!(i % 16))
        {
            buffer[i % 16] = static_cast<char>(i);
        }
        else
        {
            my_serial_port.writeOut(buffer, 16);
        }
    }
    my_serial_port.writeOut(buffer, 16);

    char in_buffer[256] = {0};
    std::cout << "Received " << my_serial_port.readIn(in_buffer) << " characters over UART." << std::endl;

    for (int i = 0; i < sizeof(in_buffer); ++i)
    {
        if (in_buffer[i] != (i + 1))
        {
            std::cout << "Value " << i << " did not match" << std::endl;
        }
    }

    return 0;
}