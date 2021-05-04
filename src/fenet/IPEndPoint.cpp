#include "IPEndPoint.h"
#include <iostream>

namespace fenet
{
    IPEndPoint::IPEndPoint(const char* _ip, unsigned short _port)
    {
        port = _port;

        //IPv4 
        in_addr addr; //Stores an IP address in_addr6 for IPv6
        int result = inet_pton(AF_INET, _ip, &addr); // pton -> Presentation to network format
        if (result == 1)
        {
                ipString = _ip;
                hostName = _ip;
                ipBytes.resize(4);
                memcpy(&ipBytes[0], &addr.S_un.S_addr, 4);

                ipVersion = IPVersion::IPv4;
                return;
        }

        //Resolve Hostname to IPv4 Address
        addrinfo hints = {};
        hints.ai_family = AF_INET; //IPv4 only 
        addrinfo* hostinfo = nullptr;
        result = getaddrinfo(_ip, NULL, &hints, &hostinfo);
        if(result == 0)
        {
            sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);
            ipString.resize(16);
            inet_ntop(AF_INET, &host_addr->sin_addr, &ipString[0], 16); //16 for IPv4 46 for IPv6

            hostName = _ip;
            ULONG ipLong = host_addr->sin_addr.S_un.S_addr;
            ipBytes.resize(sizeof(ULONG));
            memcpy(&ipBytes[0], &ipLong, 4);
            ipVersion = IPVersion::IPv4;
            freeaddrinfo(hostinfo);
            return;
        }

        //IPv6
        in6_addr addr6; //Stores an IP address in_addr6 for IPv6
        result = inet_pton(AF_INET6, _ip, &addr6); // pton -> Presentation to network format
        if (result == 1)
        {
                ipString = _ip;
                hostName = _ip;
                ipBytes.resize(16);
                memcpy(&ipBytes[0], &addr6.u, 16);

                ipVersion = IPVersion::IPv6;
                return;
        }

        //Resolve Hostname to IPv6 Address
        addrinfo hintsv6 = {};
        hintsv6.ai_family = AF_INET6; //IPv4 only 
        addrinfo* hostinfov6 = nullptr;
        result = getaddrinfo(_ip, NULL, &hintsv6, &hostinfov6);
        if (result == 0)
        {
            sockaddr_in6* host_addr = reinterpret_cast<sockaddr_in6*>(hostinfov6->ai_addr);
            ipString.resize(46);
            inet_ntop(AF_INET6, &host_addr->sin6_addr, &ipString[0], 46); //16 for IPv4 46 for IPv6

            hostName = _ip;
            
            ipBytes.resize(16);
            memcpy(&ipBytes[0], &host_addr->sin6_addr, 16);
            ipVersion = IPVersion::IPv6;
            freeaddrinfo(hostinfo);
            return;
        }
    }
    IPEndPoint::IPEndPoint(sockaddr* addr)
    {
        if (addr->sa_family == AF_INET)
        {
            sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
            ipVersion = IPVersion::IPv4;
            port = ntohs(addrv4->sin_port);
            ipBytes.resize(sizeof(ULONG));
            memcpy(&ipBytes[0], &addrv4->sin_addr, sizeof(ULONG));

            ipString.resize(16);
            inet_ntop(AF_INET, &addrv4->sin_addr, &ipString[0], 16); //16 for IPv4 46 for IPv6

            hostName = ipString;

        }
        else if(addr->sa_family == AF_INET6)
        {
            sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>(addr);
            ipVersion = IPVersion::IPv6;
            port = ntohs(addrv6->sin6_port);
            ipBytes.resize(16);
            memcpy(&ipBytes[0], &addrv6->sin6_addr, 16);

            ipString.resize(46);
            inet_ntop(AF_INET6, &addrv6->sin6_addr, &ipString[0], 46); //16 for IPv4 46 for IPv6

            hostName = ipString;
        }
    }

    IPVersion IPEndPoint::GetIPVersion()
    {
        return ipVersion;
    }
    std::string IPEndPoint::GetHostName()
    {
        return hostName;
    }
    std::string IPEndPoint::GetIPString()
    {
        return ipString;
    }
    std::vector<uint8_t> IPEndPoint::GetIPBytes()
    {
        return ipBytes;
    }
    unsigned short IPEndPoint::GetPort()
    {
        return port;
    }
    sockaddr_in IPEndPoint::GetSockaddrIPv4()
    {
        sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        memcpy(&addr.sin_addr, &ipBytes[0], sizeof(ULONG));
        addr.sin_port = htons(port);
        return addr ;
    }
    sockaddr_in6 IPEndPoint::GetSockaddrIPv6()
    {
        sockaddr_in6 addr = {};
        addr.sin6_family = AF_INET6;
        memcpy(&addr.sin6_addr, &ipBytes[0], 16);
        addr.sin6_port = htons(port);
        return addr;
    }
    void IPEndPoint::PrintInfo()
    {
        switch (ipVersion)
        {
        case IPVersion::IPv4:
            {
                std::cout << "IPv4 Confirmed" << std::endl;
                break;
            }
        case IPVersion::IPv6:
            {
            std::cout << "IPv6 Confirmed" << std::endl;
            break;
            }
        default:
            std::cout << "Unknown IP Version" << std::endl;
        }

        std::cout << "Hostname: " << hostName << std::endl;
        std::cout << "IP: " << ipString << std::endl;
        std::cout << "Port: " << port << std::endl;
        std::cout << "IP Bytes..." << std::endl;
        for (int i = 0; i < ipBytes.size(); i++)
        {
            std::cout << (int)ipBytes[i] << std::endl;
        }
    }
}

