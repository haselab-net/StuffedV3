/**
 * enums for ws communication
 */

#include <string>

enum PacketId {
    PI_NONE = 0,
    PI_JSFILE = 1,
    PI_COMMAND = 2
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
            return "UNRECOGNIZED"
    }
}