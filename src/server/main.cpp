#include "../core/IRECore.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(20 * 1024);

void grabSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout << "\n\nRead " << length << " bytes\n\n";
                for (int i = 0; i < length; i++) {
                    std::cout << vBuffer[i];
                }
                grabSomeData(socket);
            }
        });
}

int main()
{
    // ire::InitCore(); // Test Core
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.F);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */

    asio::error_code ec;

    asio::io_context ioContext;

    asio::io_context::work idleWork(ioContext);

    std::thread thrContext = std::thread([&]() { ioContext.run(); });

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
    asio::ip::tcp::endpoint largeEndpoint(asio::ip::make_address("51.38.81.49", ec), 80);
    asio::ip::tcp::endpoint failedEndpoint(asio::ip::make_address("127.0.0.1", ec), 80);

    asio::ip::tcp::socket socket(ioContext);

    socket.connect(largeEndpoint, ec);

    if (!ec) {
        std::cout << "Connected\n";
    } else {
        std::cout << "Failed to connect to adress:  \n"
                  << ec.message() << "\n";
    }

    if (socket.is_open()) {

        grabSomeData(socket);

        std::string sRequest = "GET /index.html HTTP/1.1\r\n"
                               "HOST: example.com\r\n"
                               "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        // for testing
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20s);

        ioContext.stop();
        if (thrContext.joinable())
            thrContext.join();
    }

    return 0;
}
