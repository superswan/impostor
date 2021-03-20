#include <windows.h>
#include <stdio.h>

#define TCPIP_SUBKEY "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"

// profile struct
struct tcp_profile {
    int ttl;
    int stamp;
    int pmtu;
    int urg;
    int window;
    int sack;
};


// gets profile from profiles.ini and assigns values to the tcp_profile struct
int set_tcp_profile(struct tcp_profile *selected, char *profile) {
    LPCTSTR path = ".\\profiles.ini";
    int value;

    // we can use GetPrivateProfileInt since they are all integer values
    selected->ttl =  GetPrivateProfileInt(profile, "ttl", 0, path);
    selected->stamp = GetPrivateProfileInt(profile, "stamp", 0, path); 
    selected->pmtu =  GetPrivateProfileInt(profile, "pmtu", 0, path);
    selected->urg =  GetPrivateProfileInt(profile, "urg", 0, path);
    selected->window =  GetPrivateProfileInt(profile, "window", 0, path);
    selected->sack =  GetPrivateProfileInt(profile, "sack", 0, path);

    printf("Settings:\n");
    printf("TTL: %d\n",selected->ttl);
    printf("Timestamp: %d\n",selected->stamp);
    printf("PMTU: %d\n",selected->pmtu);
    printf("Urgent Pointer: %d\n",selected->urg);
    printf("Window Size: %d\n",selected->window);
    printf("SACK: %d\n",selected->sack);
}

// Set a value in registry
int set_reg_value(HKEY hkey, char* reg_value, DWORD value_data){
    DWORD size=sizeof(DWORD);

    RegSetValueEx(hkey,reg_value,0L,REG_DWORD,(CONST BYTE*)&value_data, size);
}

// Set TCP values
int set_tcp_stack(struct tcp_profile *selected, HKEY hkey){
    char dword_ttl[]="DefaultTTL";
    char dword_timestamp[]="Tcp13230pts";
    char dword_pmtu[]="EnablePMTUDiscovery";
    char dword_urgent[]="TcpUseRFC1122UrgentPointer";
    char dword_window[]="TcpWindowSize";
    char dword_sack[]="SackOpts";

    set_reg_value(hkey, dword_ttl, selected->ttl);
    set_reg_value(hkey, dword_timestamp, selected->stamp);
    set_reg_value(hkey, dword_pmtu, selected->pmtu);
    set_reg_value(hkey, dword_urgent, selected->urg);
    set_reg_value(hkey, dword_window, selected->window);
    set_reg_value(hkey, dword_sack, selected->sack);

}

int main(int argc, char *argv[]) {
    LONG result;
    HKEY hkey;
    struct tcp_profile selected;


    if (argc != 2){
        printf("usage: impostor <profile>\n");
        return 0;
    }

    // Find registry key and create if it doesn't exist
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TCPIP_SUBKEY, 0L, KEY_ALL_ACCESS,&hkey);

    // Check if registry key exists and for ability to access
    if (result != ERROR_SUCCESS){
        if (result == ERROR_FILE_NOT_FOUND) {
            printf("Key not found. \n");
            return -1;
        }
        else {
            printf("Error opening key. Are you admin?\n");
            return 0;
        }
    }

    // Modify registry key based on profile
    printf("Modifying registry to match profile: %s\n", argv[1]);
    set_tcp_profile(&selected, argv[1]);
    set_tcp_stack(&selected, hkey);
    printf("\nPlease restart for changes to take effect\n");




    return 0;
}