#include <iostream>
#include "sol.hpp"
#include "asio.hpp"


void Session(asio::ip::tcp::socket socket)
{
    try 
    {
        while (true)
        {
            std::array<char, 1024> data;

            asio::error_code ec;
            std::size_t length = socket.read_some(asio::buffer(data), ec);

            std::cout << "=== running lua code ===" << std::endl;
    
            sol::state lua;
            lua.open_libraries();

            int value = lua.script("return 54");
            if (value == 54)
            {
                std::cout << "Hello World" << std::endl;
                lua.script_file("PBtest.lua");
            }

            if (ec == asio::error::eof)
            {
                std::cout << "连接被clinet妥善的关闭了" << std::endl;
                break;
            }
            else if (ec)
            {
                throw asio::system_error(ec);
            }

             asio::write(socket, asio::buffer(data, length));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }


}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1; 
    }

    unsigned short port = std::atoi(argv[1]);

    asio::io_context ioc;
    asio::ip::tcp::acceptor acceptor(ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

    try
    {
        while(true)
        {
            Session(acceptor.accept());
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
    }

    return 0;
}
