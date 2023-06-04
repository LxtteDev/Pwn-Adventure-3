# Pwn Adventure 3
*4/6/23 - Now*

Bit of an unusual project but I have decided to take on Pwnie Island and all its mysteries.

# Challenges, quests, and how I solved the

## Recon
**What I know:**
- Custom framework
- Very vulnerable

**What I need to know:**
- Important functions and their addresses
- What packets are being sent to the server
- Can I manipulate these packets
- What functions are trusted by the server *(Client side)*
- How was this coded

**Process analysis**
Get process information. Process ID, threads, and thread IDs.

Find process id: `pstree -aclp`
Get process information: `ps aux | grep ${id}`
View process files: `cd /proc/${id}`
Memory view: `cat maps | less` *(Less provides QOL features)*

*Information recovered*
- Coded in C++

**File analysis**
Get information about the files. File data and required libraries.

Get file information: `file PwnAdventure3-Linux-Shipping`
Get system libraries: `ldd PwnAdventure3-Linux-Shipping`
Get library information: `file libGameLogic.so`

*Information recovered*
- `libGameLogic.so` is not stripped

**Network recon**
Scan packets using [Wireshark](https://www.wireshark.org/) and `netstat`

Get network data: `netstat -a -c | grep -i pwn`
Intercept packets with wireshark: `tcp.port == 3333 && tcp.len > 0` *(Filter, only intercept tcp connections to port 3333 that contain a body)*
Switch to intercepting client data: `tcp.port == 3002 && tcp.len > 0` *(Filter, only intercept tcp connections to port 3002 that contain a body)*

*Information recovered*
- Communications are not encrypted

**What I know now**
- The game was coded in C++
- The libraries are not stripped
- The packets are not encrypted

## Disassembly
Disassemble using [Binary Ninja](https://binary.ninja/)

Gather information about function calls: `sudo gdb -p $(pidof ./PwnAdventure3-Linux-Shipping)` *(Attach gdp to game and add break point)*
Output *ClientWorld* class: `ptype ClientWorld` *(Found in Binary Ninja, Output to new .h file)*
Repair new .h file by compiling and adding extra classes.

**What I have done**
- Decompiled libGameLogic.so

## LD_PRELOAD
Hijack the main game functions to run my own.
