#include "SBUS.h"
#include <iostream>
#include <string.h>

#include <chrono>

using std::chrono::steady_clock;
using std::chrono::milliseconds;

class GimbalPacket {
    private:
        unsigned char channels[22]; // 1-byte packets
        static SBUS sbus;
        std::string uartPath;
        sbus_packet_t packet = {
                    .ch17 = true,
                    .ch18 = false,
                    .failsafe = true,
                    .frameLost = false,
            };
    public:
        GimbalPacket(SBUS & sbus, std::string uartPath) { // default constructor sending 0
            this->sbus = sbus;
            this->uartPath = uartPath;
            
            for (int i=0; i<22; i++) 
                packet.channels[i] = 0;

            // set sbus
            sbus_err_t err = sbus.install(uartPath.c_str(), false);  // false for non-blocking
            if (err != SBUS_OK) {
                std::cerr << "SBUS install error: " << err << std::endl;
            }
        }

        void send() {

            sbus.write(this->packet);
            std::cout << "Packet sent: " << printPacketChannels;
        }

        void printPacketChannels() {
            for (uint16_t &i : packet.channels) 
                std::cout << i << " " << std::endl;
        }

        void sendEvery(int ms) {
            auto lastSend = steady_clock::now();
            auto now = steady_clock::now();
            auto count = 0;
            if (now - lastSend > milliseconds(ms)) {
                sbus.write(packet);
                std::cout << count << " " << "Sending: " << printPacketChannels;
                std::cout << std::endl;

                lastSend = now;
            }
        }

};

int main(int argc, char ** argv) {
    SBUS sbus;
    GimbalPacket testing (sbus, "/dev/ttyAMA0");
    // Gimbal Packet Init
    std::cout << "Packet ready" << std::endl;
    
    testing.sendEvery(500);

}
