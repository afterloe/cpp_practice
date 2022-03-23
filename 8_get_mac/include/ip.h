/**
 * @file ip.h
 * @author afterloe (liumin@ascs.tech)
 * @brief
 * @version 1.0
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022 - MIT License
 *
 */
#ifndef __IP_H__
#define __IP_H__

#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

// #include <sys/types.h>
// #include <ifaddrs.h>

class IP
{
public:
    virtual char **getIPV4(void);
    virtual char *getIPV6(void);
    virtual char *getHostname(void);
    IP(void);

private:
    char *hostname;
};

#endif