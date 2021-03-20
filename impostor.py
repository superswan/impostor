#!/usr/bin/python
""" 
Modifies the TCP stack in order to impersonate other operating systems. Based on Craig
Heffner's Security Cloak software. 

https://web.archive.org/web/20061202015837/http://www.craigheffner.com/security/
"""
import configparser
import os
import sys

profiles = configparser.ConfigParser()
profiles.read('profiles.ini')

selected_profile = str(sys.argv[1])

if __name__ == "__main__":
    # TCP stack options
    ttl = profiles[selected_profile]['ttl']
    timestamp = profiles[selected_profile]['stamp']
    pmtu = profiles[selected_profile]['pmtu']
    urgent = profiles[selected_profile]['urg']
    window_size = profiles[selected_profile]['window']
    sack = profiles[selected_profile]['sack']

    # Interface options
    interface = None
    mtu_size = profiles[selected_profile]['mtu']
    vendor_mac = None

    print(f"""
    Using Profile: {selected_profile}
    =============================================
    TTL = {ttl} 
    Enable Timestamp = {timestamp} 
    Enable PMTU = {pmtu} 
    Urgent Pointer = {urgent} 
    Window Size = {window_size} 
    SACK = {sack}
    MTU = {mtu_size} 
    """)

    
    # set TCP TTL
    os.system(f'sysctl net.ipv4.ip_default_ttl={ttl}')
    # set TCP timestamp
    os.system(f'sysctl -w net.ipv4.tcp_timestamps={timestamp}')
    # enable/disable PMTU
    os.system(f'echo  {pmtu}  >/proc/sys/net/ipv4/ip_no_pmtu_disc')
    # set Urgent Pointer field
    os.system(f'echo {urgent} >/proc/sys/net/ipv4/tcp_stdurg')
    # set window size
    os.system(f'sysctl -w net.ipv4.tcp_wmem="4096 {window_size} 4194304"')
    # enable/disable sack
    os.system(f'echo {sack} > /proc/sys/net/ipv4/tcp_sack')
    #set mtu
    #os.system(f'ifconfig {interface} mtu {mtu_size} up')
    