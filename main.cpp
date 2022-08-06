#include "SBUS.h"
#include <iostream>
#include <string.h>

#include <chrono>
#include <algorithm>

using std::chrono::steady_clock;
using std::chrono::milliseconds;

class GimbalPacket {

    private:
        std::string uartPath;
        SBUS sbus;
        uint32_t signal;
        static int ms;

        sbus_packet_t packet = {
                    .ch17 = true,
                    .ch18 = false,
                    .failsafe = true,
                    .frameLost = false,
            };

    public:
        GimbalPacket(SBUS & sbus, std::string uartPath, uint16_t signal, int ms=1000) { 
            this->ms = ms;
            this->sbus = sbus;
            this->uartPath = uartPath;
        }

        // only write the signal once
        void send(void) {
            sbus.write(this->packet);
            this->printPacketChannels();
        }

        void printPacketChannels(void) {
            std::cout << "Sending: ";
            for (uint16_t &i : packet.channels) 
                std::cout << i << " ";
            std::cout << std::endl;
        }

        // write signal every n ms 
        void sendRepeat(void) {
            sbus_err_t err;
            // non-blocking mode, read() will check if any data is available and return immediately
            int count (0);
            while ((err = sbus.read()) != SBUS_FAIL)
            {
                // desync means a packet was misaligned and not received properly
                if (err == SBUS_ERR_DESYNC)
                {
                    std::cerr << "SBUS desync" << std::endl;
                }

                static auto lastWrite = steady_clock::now();
                auto now = steady_clock::now();

                /*
                * Receiving happens independently so we can do other things.
                * Here we send a packet every second.
                */
                if (now - lastWrite > milliseconds(ms))
                {
                    lastWrite = now;

                    // make sure to limit sending frequency, SBUS is not that fast
                    sbus.write(packet);
                    std::cout<<count++<<": ";
                    this->printPacketChannels();
                }
            }
        }

        static void onPacket(const sbus_packet_t &packet) {
            static auto lastPrint = steady_clock::now();
            auto now = steady_clock::now();

            if (now - lastPrint > milliseconds(ms/2))
            {
                for (int i = 0; i < 16; ++i)
                    std::cout << "ch" << i + 1 << ": " << packet.channels[i] << "\t";

                std::cout << "ch17: " << (packet.ch17 ? "true" : "false") << "\t"
                    << "ch18: " << (packet.ch18 ? "true" : "false");

                if (packet.frameLost)
                    std::cout << "\tFrame lost";

                if (packet.failsafe)
                    std::cout << "\tFailsafe active";

                std::cout << std::endl;

                lastPrint = now;
            }
        }

        void basicPacketConfig(void) {
            // set sbus
            sbus_err_t err = sbus.install(uartPath.c_str(), false);  // false for non-blocking
            
            //fill array with 0 speed values
            std::fill_n(packet.channels, 16, 1023);

            // channels of pan, tilt, roll
            packet.channels[0] = packet.channels[1] = packet.channels[3] = signal;
            
            if (err != SBUS_OK) {
                std::cerr << "SBUS install error: " << err << std::endl;
            }
            
            std::cout << "--------Static Packet Assembled--------" << std::endl;

            sbus.onPacket(onPacket);
        }
};

int main(int argc, char ** argv) {
    SBUS sbus;
    GimbalPacket testing (sbus, "/dev/ttyAMA0", 500);
    // Gimbal Packet Init

    testing.basicPacketConfig();

    testing.sendRepeat();
}
