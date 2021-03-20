# impostor
spoof OS detection by messing with the tcp stack

Based on security cloak by Craig Heffner:
https://web.archive.org/web/20061202015837/http://www.craigheffner.com/security/

Inspired by:
https://nmap.org/book/nmap-defenses-trickery.html#nmap-defenses-os-spoofing

# usage
```./impostor <profile>```
profiles are defined in ```profiles.ini``` 

# Screenshots

## Linux
### Before:
[![nmap-ubuntu-1.png](https://i.postimg.cc/htvhTgXt/nmap-ubuntu-1.png)](https://postimg.cc/VJyYPx9x)
### After:
[![nmap-ubuntu-2.png](https://i.postimg.cc/6pZJD1Sh/nmap-ubuntu-2.png)](https://postimg.cc/zyqchpqL)

unfortunately the results are currently far form perfect. will most likely have to play with the window size on linux

## Windows
### Before:
[![nmap-windows.png](https://i.postimg.cc/3RqNXg8N/nmap-windows.png)](https://postimg.cc/CBjwYnfp)
### After:
[![nmap-windows-2.png](https://i.postimg.cc/CLkCKK7k/nmap-windows-2.png)](https://postimg.cc/HVW8Zdfk)

# TODO
~~windows version~~
* Continue research and explore advanced methods involing things like spoofed services
