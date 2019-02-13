#include <iostream>
#include "asio.hpp"

#include "test.pb.h"

using asio::ip::tcp;
enum { max_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: <host> <port>\n";
            return 1;
        }

        asio::io_context io_context;

        tcp::socket s(io_context);
        tcp::resolver resolver(io_context);
        asio::connect(s, resolver.resolve(argv[1], argv[2]));

        //std::cout << "Enter message";
        char request[max_length];
        //std::cin.getline(request, max_length);
        //std::size_t request_length = std::strlen(request);

        test::Person msg;
        msg.set_name("ChengMiao");
        msg.set_age(30);
        msg.set_address("ShangHai");
        test::Phone* msg1 = msg.add_contacts();
        msg1->set_name("Linda");
        msg1->set_phonenumber(18550101361);

        msg.SerializeToArray(request, msg.ByteSize());
        asio::write(s, asio::buffer(request, msg.ByteSize()));

        char reply[max_length];
        std::size_t reply_length = asio::read(s, asio::buffer(reply, msg.ByteSize()));
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