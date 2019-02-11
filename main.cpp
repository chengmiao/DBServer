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

            asio::system_error ec;
            std::size_t length = socket.read_some(asio::buffered_read_stream<data>, ec);

            if (ec == asio::error::eof)
            {
                std::cout << "连接被clinet妥善的关闭了" << std::endl;

                std::cout << "=== running lua code ===" << std::endl;
    
                sol::state lua;
                lua.open_libraries();

                int value = lua.script("return 54");
                if (value == 54)
                {
                     std::cout << "Hello World" << std::endl;
                     lua.script_file("PBtest.lua");
                }

                break;
            }
            else if (ec)
            {
                throw asio::system_error(ec);
            }
        }

        asio::write(socket, asio::buffered_write_stream<data, length>);
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
            Session(accept.accept());
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception " << e.what() << std::endl;
    }

    return 0;
}
