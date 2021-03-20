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
### Before:
[![nmap-ubuntu-1.png](https://i.postimg.cc/htvhTgXt/nmap-ubuntu-1.png)](https://postimg.cc/VJyYPx9x)
### After:
[![nmap-ubuntu-2.png](https://i.postimg.cc/Cx9M88yc/nmap-ubuntu-2.png)](https://postimg.cc/0zdqRbyS)

unfortunately the results are currently far form perfect. will most likely have to play with the window size on linux

# TODO
windows version
