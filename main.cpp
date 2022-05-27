#include "SBUS.h"
#include "sbus_packet.h"
#include <chrono>

#include <iostream>

#define RONIN_CHANNELS 27 //i think so

static string PATH;


SBUS rpi_sbus;

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;
using std::chrono::steady_clock;
using std::chrono::milliseconds;

//packet resolver for auto sends by Ronin SC
static void onPacket(const sbus_packet_t &packet)
{
    static auto lastPrint = steady_clock::now();
    auto now = steady_clock::now();

    if (now - lastPrint > milliseconds(500))
    {
        for (int i = 0; i < 16; ++i)
            cout << "ch" << i + 1 << ": " << packet.channels[i] << "\t";

        cout << "ch17: " << (packet.ch17 ? "true" : "false") << "\t"
             << "ch18: " << (packet.ch18 ? "true" : "false");

        if (packet.frameLost)
            cout << "\tFrame lost";

        if (packet.failsafe)
            cout << "\tFailsafe active";

        cout << endl;

        lastPrint = now;
    }
}


int main(int argc, char** argv) {
    cout<<"Packets send test";
    rpi_sbus.onPacket(onPacket); //call back

    sbus_err_t err = rpi_sbus.install(PATH.c_str(), false);

    if (err != SBUS_OK)
    {
        cerr << "SBUS install error: " << err << endl;
        return err;
    }

    cout << "SBUS installed" << endl;

    while ((err = rpi_sbus.read()) != SBUS_FAIL)
    {
        // desync means a packet was misaligned and not received properly
        if (err == SBUS_ERR_DESYNC)
        {
            cerr << "SBUS desync" << endl;
        }

        static auto lastWrite = steady_clock::now();
        auto now = steady_clock::now();

        /*
         * Receiving happens independently so we can do other things.
         * Here we send a packet every second.
         */
        if (now - lastWrite > milliseconds(1000))
        {
            lastWrite = now;

            sbus_packet_t packet;

            packet = 
             {
                    packet.ch17 = true,
                    packet.ch18 = false,
                    packet.failsafe = true,
                    packet.frameLost = false,
            };

            for (int i = 0; i < RONIN_CHANNELS; i++)
            {
                packet.channels[i] = i + 1;
            }

            rpi_sbus.write(packet);
        }
    }
}
