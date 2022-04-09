/**
 * @file ip.cpp
 * @author afterloe (liumin@ascs.tech)
 * @brief
 * @version 1.0
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022 - MIT License
 *
 */
#include "ip.h"

IP::IP(void)
{
    this->hostname = new char[0x80];
}

char **IP::getIPV4(void)
{
    char **ips = new char*[0x80];
    struct hostent *hent;
    hent = gethostbyname(this->hostname);
    for(int i = 0; hent->h_addr_list[i]; i++) {
        ips[i] = inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i]));
    }

    return ips;
}

char *IP::getIPV6(void)
{
    std::cout << "" << std::endl;
    return NULL;
}

char *IP::getHostname(void)
{
    gethostname(this->hostname, 0x80);
    return this->hostname;
}