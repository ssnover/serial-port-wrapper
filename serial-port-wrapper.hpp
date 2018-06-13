/*
 * file: serial-port-wrapper.hpp
 * purpose: Class definition for a C++ class which wraps the interface to a
 * Linux
 *          serial port for the Raspberry Pi.
 */

#ifndef SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP
#define SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP

#include <memory>

class SERIAL_PORT_WRAPPER
{
public:
    enum class BAUDRATE
    {
        HZ_9600 = 0u,
        HZ_19200 = 1u,
        HZ_38400 = 2u,
        HZ_115200 = 3u,
    };

    static SERIAL_PORT_WRAPPER & getInstance();

    /*
     * Deleted assignment and copy to enforce access through the static method.
     */
    SERIAL_PORT_WRAPPER(SERIAL_PORT_WRAPPER const &) = delete;
    SERIAL_PORT_WRAPPER const & operator=(SERIAL_PORT_WRAPPER const &) = delete;

    ~SERIAL_PORT_WRAPPER();

    void setBaudRate(BAUDRATE baud);

    int writeOut(char const * const input_buffer, unsigned int length);

    int readIn(char * const read_buffer);

private:
    /*
     * Private to enforce the singleton.
     */
    SERIAL_PORT_WRAPPER();

    char const * const my_filepath;
    int my_serial_file_descriptor;
    BAUDRATE my_baudrate;

}; // class SERIAL_PORT_WRAPPER

#endif // SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP
