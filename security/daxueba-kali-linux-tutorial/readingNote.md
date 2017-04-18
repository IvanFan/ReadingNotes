# daxueba Kali linux tutorial

start: 2017-04-13
end: not yet

## Install Kali Linux

I followed the user guide to install the kali linux on VMware.  

- Remember to assign enough space for kali linux. According to my owner experience and the error met during the installation, we need to assign minmum 15 G to the virtual environment
- Remember to assign enough memory to the virtual environment. First time I just assigned the default memory size(256mb), then I could not open the terminal within kali linux

Comments: 

It seems like we can install kali linux mini into andorid smart phone. I should try it sometime.

## Information collection

Information collection is essential for the penetration test. 

### Enum Service

Enum service means collecting data about one aspect from the internet. 

#### DNS Enum

__Tool: dnsenum__
```
dnsenum --enum website.domain.com
```

This tool will return host address, domain service address, mail service address and google result.  

It also has options


__Tool: fierce__
```
fierce -dns baidu.com
```
This command will try to find all sub-doamins 

#### SNMP enum
SNMP is a protocal 
It's better to shut it down if you don't need to use it because it has potential risk of getting attacks  

__Tool: snmpwalk__
```
snapwalk -c public xxx.xxx.xx.xxx -v 2c
```
I tested this command with two serve and only got response timeout  

__Tool: snmpcheck__

```
snmpcheck -t xxx.xxx.xxx.xxx
```
not working  
only throw error no community name specified
which is a snmp v2 specified issue

### Scope scan

__Tool: dmitry__
```
dmitry -wnpb ivanfan.net
```

Comments: it can return the domain service provider details and the port which is open

