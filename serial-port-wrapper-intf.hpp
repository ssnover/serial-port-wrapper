/*
 * file: serial-port-wrapper-intf.hpp
 * purpose: Interface class for abstracting dependencies on the SERIAL_PORT_WRAPPER
 *          object.
 */

#ifndef SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_INTF_HPP
#define SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_INTF_HPP

#include <cstdint>


class SERIAL_PORT_WRAPPER_INTF
{
private:
public:

    enum class BAUDRATE : uint8_t
    {
        HZ_9600 = 0u,
        HZ_19200 = 1u,
        HZ_38400 = 2u,
        HZ_115200 = 3u,
    };

    SERIAL_PORT_WRAPPER_INTF(SERIAL_PORT_WRAPPER_INTF const &) = delete;
    SERIAL_PORT_WRAPPER_INTF const & operator=(SERIAL_PORT_WRAPPER_INTF const &) = delete;

    SERIAL_PORT_WRAPPER_INTF() {}
    virtual ~SERIAL_PORT_WRAPPER_INTF() {}

    virtual bool setBaudRate(BAUDRATE baud) = 0;

    virtual int writeOut(char const * const input_buffer, unsigned int length) = 0;

    virtual int readIn(char * const output_buffer) = 0;

}; // class SERIAL_PORT_WRAPPER_INTF

#endif // SERIAL_PORT_WRAPPER_SERIAL_PORT_WRAPPER_INTF_HPP
