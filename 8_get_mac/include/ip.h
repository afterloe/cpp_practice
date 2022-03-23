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

#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

class IP{
    public:
        virtual char* getIPV4(void);
        virtual char* getIPV6(void);
        virtual char* getHostname(void);
};

#endif