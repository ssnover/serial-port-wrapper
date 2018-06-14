/*
 * file: serial-port-wrapper.cpp
 * purpose: Implements a C++ wrapper interface over the Raspberry Pi's serial
 *          port.
 */

#include "serial-port-wrapper.hpp"
#include <cassert>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

namespace
{
struct termios terminal_configuration;
std::string const RASPBERRY_PI_SERIAL_PATH("/dev/serial0");
SERIAL_PORT_WRAPPER::BAUDRATE const DEFAULT_BAUDRATE(SERIAL_PORT_WRAPPER::BAUDRATE::HZ_9600);

int mapBaudRateToTermiosValue(SERIAL_PORT_WRAPPER::BAUDRATE baud)
{
    using BAUDRATE = SERIAL_PORT_WRAPPER::BAUDRATE;

    switch (baud)
    {
        case BAUDRATE::HZ_9600:
            return B9600;
        case BAUDRATE::HZ_19200:
            return B19200;
        case BAUDRATE::HZ_38400:
            return B38400;
        case BAUDRATE::HZ_115200:
            return B115200;
    }
}

} // anonymous namespace

//TODO: Find a more graceful way to handle errors.
SERIAL_PORT_WRAPPER::SERIAL_PORT_WRAPPER()
    : my_filepath(RASPBERRY_PI_SERIAL_PATH.c_str()),
      my_serial_file_descriptor(0),
      my_baudrate(DEFAULT_BAUDRATE)
{
    this->my_serial_file_descriptor = open(this->my_filepath, O_RDWR | O_NOCTTY);

    if (!isatty(this->my_serial_file_descriptor))
    {
        std::cerr << "Fatal Error: File descriptor is not a tty device, " << this->my_filepath;
        exit(EXIT_FAILURE);
    }

    if (-1 == this->my_serial_file_descriptor)
    {
        // There was an error
        std::cerr << "Fatal Error: Could not open serial port " << this->my_filepath;
        exit(EXIT_FAILURE);
    }

    /*
     * CONTROL MODES
     * CS8 -> Character size is 8 bits.
     * CLOCAL -> Ignore modem control lines.
     * CREAD -> Enable receiver.
     */
    terminal_configuration.c_cflag =
        static_cast<tcflag_t>(CS8 | CLOCAL | CREAD | mapBaudRateToTermiosValue(this->my_baudrate));

    /*
     * INPUT MODES
     * IGNBRK -> Ignore break condition. Must be set if BRKINT is not set.
     * IGNPAR -> Ignore characters with parity errors.
     */
    terminal_configuration.c_iflag = IGNBRK | IGNPAR;
    /*
     * OUTPUT MODES
     * Do not process output characters.
     */
    terminal_configuration.c_oflag = 0;
    /*
     * LOCAL MODES
     * Disable ICANON, terminal is reading in noncanonical mode.
     */
    terminal_configuration.c_lflag = 0;
    /*
     * Set flags for managing read() return conditions.
     *
     * Setting VMIN to 1 allows the read to return reading 1 byte.
     * Setting VTIME to 10 sets a timeout to 1 second (10 * 100 milliseconds).
     */
    terminal_configuration.c_cc[VMIN] = 1;
    terminal_configuration.c_cc[VTIME] = 10;

    /*
     * Flush the input buffer.
     */
    tcflush(this->my_serial_file_descriptor, TCIFLUSH);
    /*
     * Configure terminal with settings.
     */
    tcsetattr(this->my_serial_file_descriptor, TCSANOW, &terminal_configuration);
}

SERIAL_PORT_WRAPPER::~SERIAL_PORT_WRAPPER()
{

    // Close the file.
    close(this->my_serial_file_descriptor);
}

SERIAL_PORT_WRAPPER & SERIAL_PORT_WRAPPER::getInstance()
{
    static SERIAL_PORT_WRAPPER instance;
    return instance;
}

bool SERIAL_PORT_WRAPPER::setBaudRate(SERIAL_PORT_WRAPPER::BAUDRATE baud)
{
    // Lock the scoped mutex
    std::lock_guard<std::mutex> lock(this->my_mutex);
    cfsetspeed(&terminal_configuration, static_cast<speed_t>(mapBaudRateToTermiosValue(baud)));
    return (-1 != tcsetattr(this->my_serial_file_descriptor, TCSANOW, &terminal_configuration));
}

int SERIAL_PORT_WRAPPER::writeOut(char const * const input_buffer, unsigned int length)
{
    // Lock the scoped mutex
    std::lock_guard<std::mutex> lock(this->my_mutex);
    write(this->my_serial_file_descriptor, input_buffer, length);
}

int SERIAL_PORT_WRAPPER::readIn(char * const read_buffer)
{
    // Lock the scoped mutex
    std::lock_guard<std::mutex> lock(this->my_mutex);
    return static_cast<int>(
        read(this->my_serial_file_descriptor, read_buffer, sizeof(read_buffer)));
}
