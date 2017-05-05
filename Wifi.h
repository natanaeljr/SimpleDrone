
/* --------------------------------------------------------------------------
AT – Test AT startup
Response OK


AT+RST – Restart module
Response OK


AT+GMR – View version info
Response
<AT version info>
<SDK version info>
<compile time>
OK
Parameters
<AT version info> information about AT version
<SDK version info> information about SDK version
<compile time> time of the bin was compiled



ATE – AT commands echo
Response OK
Parameters
ATE0: Switch echo off
ATE1: Switch echo on



AT+UART_DEF=<baudrate>, <databits>, <stopbits>, <parity>, <flow control>
Example AT+UART_DEF=115200, 8, 1, 0, 3
Response OK
Parameters
<baudrate> Baudrate range: 110 to 115200*40 (4.608 Mega)
<databits>
5: 5 bits data
6: 6 bits data
7: 7 bits data
8: 8 bits data
<stopbits>
1: 1 bit stop bit
2: 1.5 bit stop bit
3: 2 bit stop bit
<parity>
0: None
1: Odd
2: EVEN
<flow control>
0: disable flow control
1: enable RTS
2: enable CTS
3: enable both RTS and CTS



AT+SLEEP – sleep mode (It can only be used in station mode)
Command AT+SLEEP?
Response
+SLEEP : <sleep mode>
OK
Parameters
<sleep mode>
 0 : disable sleep mode
 1 : light-sleep mode
 2 : modem-sleep mode
Command AT+SLEEP=<sleep mode>
Response OK


-------------------------------------------------------------------------------------

AT+CWMODE_CUR – Set WiFi mode(sta/AP/sta+AP), won’t save to flash
Example AT+CWMODE_CUR=3
Command AT+CWMODE_CUR=?
Response
+CWMODE_CUR:( value scope of <mode>)
OK
Parameters
<mode>
 1 : station mode
 2 : softAP mode
 3 : softAP + station mode


 AT+CWJAP_CUR – Connect to AP, won‘t save to flash
Example
• AT+CWJAP_CUR ="abc", "0123456789"
• If SSID is "ab\, c" and password is "0123456789"\"
 AT+CWJAP_CUR="ab\\\, c", "0123456789\"\\"
• If several APs have the same SSID as "abc", target AP can be found by bssid:
 AT+CWJAP_CUR="abc", "0123456789", "ca:d7:19:d8:a6:44"
Command AT+CWJAP_CUR?
Response
+CWJAP_CUR:<ssid>, <bssid>, <channel>, <rssi>
OK
Parameters <ssid> string, AP’s SSID
Command AT+CWJAP_CUR=<ssid>, <pwd>[, <bssid>]
Response
OK
or
+CWJAP:<error code>
FAIL
Parameters
<ssid> string, AP’s SSID
<pwd> string, MAX: 64 bytes ASCII
[<bssid>] string, AP’s MAC address, for several APs may have the same SSID
<error code> only for reference, it is not reliable
1 : connection timeout
2 : wrong password
3 : cannot find target AP
4 : connection failed
This command requires station mode to be active.
Escape character syntax is needed if "SSID" or "password" contains any special
characters ( ’ , ’ or ’ " ’or ’ \ ’)


AT+CWLAP - Lists available APs
Example
• AT+CWLAP
 List of all available AP's detected by ESP8266
• AT+CWLAP="WiFi", "ca:d7:19:d8:a6:44", 6
 Find AP with specific SSID and MAC at specific channel.
• AT+CWLAP="WiFi"
 Find AP with specific SSID


 AT+CIPSTA_CUR – Set IP address of ESP8266 station, do not save to flash
Example AT+CIPSTA_CUR="192.168.6.100", "192.168.6.1", "255.255.255.0"
Command AT+CIPSTA_CUR?
Response
+CIPSTA_CUR:<IP>
OK
Parameters <IP> string, IP address of ESP8266 station
Command AT+CIPSTA_CUR=<IP>[, <gateway>, <netmask>]
Response OK
Parameters
<IP> string, IP address of ESP8266 station
[<gateway>] gateway
[<netmask>] netmask


