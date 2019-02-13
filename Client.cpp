#include "asio.hpp"

using asio::ip::tcp;
enum { max_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: <host> <port>\n"
            return 1;
        }

        asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        asio::connect(s, resolve.resolve(argv[1], argv[2]));

        std::cout << "Enter message";
        char request[max_length];
        std::cin.getline(request, max_length);
        std::size_t request_length = std::strlen(request);
        asio::write(s, asio::buffer(request, request_length));

        char reply[max_length];
        std::size_t reply_length = asio::read(s, asio::buffer(reply, request_length));
        std::cout << "Reply is";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}