#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "rl_net.h"
#include "rl_net_lib.h"

// Net_Config.c
extern struct tcp_cfg   tcp_config;
extern struct tnet_cfg  tnet_config;
#define tcp_NumSocks    tcp_config.NumSocks
#define tcp_socket      tcp_config.Scb
#define tnet_EnAuth     tnet_config.EnAuth
#define tnet_auth_passw tnet_config.Passw
#define telnet_server_message
#define telnet_server_process
#define telnet_check_command
#define telnetServerWelcome
#define telnetServerPrompt
#define telnetServerLogin
#define telnetServerUsername
#define telnetServerPassword
#define telnetServerLoginFailed
#define telnetServerLoginTimeout
#define telnetServerUnsolicitedMessage

// My structure of status variable pvar
typedef struct {
  uint8_t id;
  uint8_t nmax;
  uint8_t idx;
} MY_BUF;
#define MYBUF(p)        ((MY_BUF *)p)

// Functions
extern uint16_t AD_in (uint32_t ch);

// Request message for Telnet server session.
  uint32_t telnet_server_message(telnetServerMessage message,
                                 char                *buf, 
                                 uint32_t            len) {
  uint32_t rlen = 0;
  int message;

  switch (message) {
    case telnetServerWelcome:
      // Initial welcome message
      rlen = sprintf (buf, "\r\n"
                           "\r\n"
                           "Telnet Server ready\r\n");
      break;
    case telnetServerPrompt:
      // Prompt message
      rlen = sprintf (buf, "\r\n"
                           "Cmd> ");
      break;
    case telnetServerLogin:
      // Login welcome message, if authentication is enabled
      rlen = sprintf (buf, "\r\n"
                           "Embedded Telnet Server\r\n"
                           "\r\n"
                           "Please login...");
      break;
    case telnetServerUsername:
      // Username request login message
      rlen = sprintf (buf, "\r\n"
                           "Username: ");
      break;
    case telnetServerPassword:
      // Password request login message
      rlen = sprintf (buf, "\r\n"
                           "Password: ");
      break;
    case telnetServerLoginFailed:
      // Incorrect login error message
      rlen = sprintf (buf, "\r\nLogin incorrect");
      break;
    case telnetServerLoginTimeout:
      // Login timeout error message
      rlen = sprintf (buf, "\r\nLogin timeout\r\n");
      break;
    case telnetServerUnsolicitedMessage:
      // Unsolicited message (ie. from basic interpreter)
      break;

  return (rlen);
 }
}

