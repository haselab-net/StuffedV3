/**
 * enums for ws communication
 */

#include <iostream>
#include <string>
#include <sstream>

enum PacketId {
    PI_NONE = 0,
    PI_JSFILE = 1,
    PI_COMMAND = 2,
    PI_SETTINGS = 3
};

enum PacketSettingsId {
    DEVELOPMENT_MODE = 1
};

std::string getPacketIdStr(int id){
    switch (id)
    {
        case PacketId::PI_NONE:
            return "PI_NONE";
        case PacketId::PI_JSFILE:
            return "PI_JSFILE";
        case PacketId::PI_COMMAND:
            return "PI_COMMAND";
        default:
            return "UNRECOGNIZED";
    }
}

std::string getPacketSettingsIdStr(int id){
    switch (id)
    {
        case PacketSettingsId::DEVELOPMENT_MODE:
            return "DEVELOPMENT_MODE";
    
        default:
            return "UNRECOGNIZED";
    }
}