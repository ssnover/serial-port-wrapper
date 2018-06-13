/*
 * file: main.cpp
 * purpose: Entry point for the test program.
 */
#include "serial-port-wrapper.hpp"


int main()
{
    SERIAL_PORT_WRAPPER & my_serial_port(SERIAL_PORT_WRAPPER::getInstance());

    char recent_character(0);
    char buffer[256];

    while (recent_character != 0xFF)
    {
        if (my_serial_port.readIn(buffer))
        {
            for (int i = 1; i < sizeof(buffer); ++i)
            {
                if (0 == buffer[i])
                {
                    recent_character = buffer[i - 1];
                }
            }
        }
    }

    return 0;
}