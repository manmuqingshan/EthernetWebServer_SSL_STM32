/****************************************************************************************************************************
  Ethernet_URLEncoder.h - Dead simple HTTP WebClient.
  For STM32F/L/H/G/WB/MP1 with built-in Ethernet LAN8742A (Nucleo-144, DISCOVERY, etc) or W5x00/ENC28J60 shield/module
  
  EthernetWebServer_SSL_STM32 is a library for STM32 using the Ethernet shields to run WebServer and Client with/without SSL

  Use SSLClient Library code from https://github.com/OPEnSLab-OSU/SSLClient
  
  Built by Khoi Hoang https://github.com/khoih-prog/EthernetWebServer_SSL_STM32
  Licensed under MIT license
       
  Licensed under MIT license
  
  Version: 1.4.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      14/11/2020 Initial coding for STM32F/L/H/G/WB/MP1 to support Ethernet shields using SSL. Supporting BI LAN8742A, 
                                  W5x00 using Ethernetx, ENC28J60 using EthernetENC and UIPEthernet libraries   
  ...
  1.4.0   K Hoang      25/12/2021 Reduce usage of Arduino String with std::string. Fix bug
  1.4.1   K Hoang      27/12/2021 Fix wrong http status header bug and authenticate issue caused by libb64
  1.4.2   K Hoang      11/01/2022 Fix libb64 fallthrough compile warning
  1.4.3   K Hoang      02/03/2022 Fix decoding error bug
 *************************************************************************************************************************************/
 
// Library to simplify HTTP fetching on Arduino
// (c) Copyright Arduino. 2019
// Released under Apache License, version 2.0

#pragma once

#include <Arduino.h>

#include "detail/Debug_STM32.h"


class EthernetURLEncoderClass
{
  public:
    EthernetURLEncoderClass();
    virtual ~EthernetURLEncoderClass();

    static String encode(const char* str);
    static String encode(const String& str);

  private:
    static String encode(const char* str, int length);
};

extern EthernetURLEncoderClass EthernetURLEncoder;
