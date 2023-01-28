/**
 * @file server.cpp
 * @author Oleksandr Ishchuk (o.v.ishchuk@gmail.com)
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Do what the fuck you want (c) 2023
 * 
 */

#include <SFML/Network.hpp>
#include "commands.hpp"
#include <iostream>

class Server
{
public:
    Server()
    {
        clock.restart();
        socket.bind(m_port);
        socket.setBlocking(false);
    }
    ~Server()
    {

    }
    void start()
    {
        state = RUN;
        run();
    }
private:
    enum State
    {
        RUN,
        STOP,
        STANDBY,
        ERROR
    };
    State state = STOP;
    int command = COMMAND_STANDBY;
    sf::Clock clock; // for time handling
    sf::UdpSocket socket;
    sf::IpAddress m_ip = "127.0.0.1";
    sf::IpAddress client_ip = "127.0.0.1";
    unsigned short client_port = 59301;
    unsigned short m_port = 59300;
    
    void stop()
    {
        state = STOP;
    }
    
    void run()
    {
        std::cout << "\n==================\n"
                    << "STARTING SERVER!!!\n"
                    << "==================\n" << std::endl;

        int currentTime;  // for fresh elapsed time
        int previousTime; // to prevent multiple output ('while' is too fast)

        while ( state != STOP )
        {
            sf::Packet packet;
            packet << COMMAND_POLLING;
            socket.receive(packet, client_ip, client_port);
            packet >> command;

            // some active work imitation
            currentTime = clock.getElapsedTime().asSeconds();
            if ( currentTime % 1 == 0 && currentTime != previousTime )
            {
                previousTime = currentTime;
                std::cout << currentTime << ": Server running." << std::endl;
            }

            // here we handle accepted commmands defined in 'commands.hpp'
            if ( command != COMMAND_POLLING )
            {
                switch ( command )
                {
                case COMMAND_STOP:
                    stop();
                    std::cout << "\n===========================\n"
                              << "SERVER IS STOPPED BY CLIENT\n"
                              << "===========================" << std::endl;
                    break;
                
                default:
                    break;
                }
            }
        }
    }
};

int main()
{
    Server srv;
    srv.start();

    return 0;
}