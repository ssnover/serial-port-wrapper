/*
 * file: serial-port-wrapper.hpp
 * purpose: Class definition for a C++ class which wraps the interface to a
 *          Linux serial port for the Raspberry Pi.
 */

#ifndef SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP
#define SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP

#include <mutex>
#include "serial-port-wrapper-intf.hpp"

class SERIAL_PORT_WRAPPER final : public SERIAL_PORT_WRAPPER_INTF
{
public:

    static SERIAL_PORT_WRAPPER & getInstance();

    /*
     * Deleted assignment and copy to enforce access through the static method.
     */
    SERIAL_PORT_WRAPPER(SERIAL_PORT_WRAPPER const &) = delete;
    SERIAL_PORT_WRAPPER const & operator=(SERIAL_PORT_WRAPPER const &) = delete;

    ~SERIAL_PORT_WRAPPER();

    /*
     * SERIAL_PORT_WRAPPER_INTF Methods
     */

    bool setBaudRate(BAUDRATE baud) override;

    int writeOut(char const * const input_buffer, unsigned int length) override;

    int readIn(char * const read_buffer) override;

private:
    /*
     * Private to enforce the singleton.
     */
    SERIAL_PORT_WRAPPER();

    char const * const my_filepath;
    int my_serial_file_descriptor;
    BAUDRATE my_baudrate;
    std::mutex my_mutex;

}; // class SERIAL_PORT_WRAPPER

#endif // SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_HPP
