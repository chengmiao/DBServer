#include <iostream>
#include "sol.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "=== running lua code ===" << std::endl;
    
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);

    int value = lua.script("return 54");
    if (value == 54)
    {
        std::cout << "Hello World" << std::endl;
        lua.script_file("PBtest.lua");
    }

    return 0;
}
