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
    PI_SETTINGS = 3,
    PI_PINGPONG = 4
};

enum PacketSettingsId {
    PSI_OFFLINE_MODE = 1,
    PSI_FIRMWARE_INFO = 2
};

inline std::string getPacketIdStr(int id){
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

inline std::string getPacketSettingsIdStr(int id){
    switch (id)
    {
        case PacketSettingsId::PSI_OFFLINE_MODE:
            return "PSI_OFFLINE_MODE";
        case PacketSettingsId::PSI_FIRMWARE_INFO:
            return "PSI_FIRMWARE_INFO";
        default:
            return "UNRECOGNIZED";
    }
}