#include <iostream>
#include "sol.hpp"
#include "asio.hpp"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : socket_(std::move(socket))
    {}

    void Start()
    {
        do_read();
    }

private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write(length);
            }
        });
    }

    void do_write(std::size_t length)
    {
        auto self(shared_from_this());
        asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t)
        {
            if (!ec)
            {
                std::cout << "=== running lua code ===" << std::endl;
    
                sol::state lua;
                lua.open_libraries();

                int value = lua.script("return 54");
                if (value == 54)
                {
                    std::cout << "Hello World" << std::endl;

                    lua["testdata"] = data_;
                    lua.script_file("PBtest.lua");
                }

                do_read();
            }
        });
    }

tcp::socket socket_;
enum { max_length = 1024 };
char data_[max_length];
};


class Server
{
public:
    Server(asio::io_context& io_context, short port) : acceptor_(io_context, tcp::endpoint(asio::ip::address::from_string("101.132.123.54"), port))
    {
        do_accept();
    }

private:
    void do_accept()
    {
        acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket))->Start();
            }

            do_accept();
        });
    }

tcp::acceptor acceptor_;
};


int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
            return 1; 
        }

        //std::cout << "============== Use Lua Start =================" << std::endl;
        //sol::state lua;
        //lua.open_libraries();

        //lua["filename"] = argv[1];
        //lua["messageName"] = argv[2];
        //lua.script_file("Transfor.lua");

        asio::io_context io_context;

        Server s(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
