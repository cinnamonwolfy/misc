# Remote Login-Auth Protocol Rough Draft
## Author: pocketlinux32

### Introduction

About a year ago, I had created a login system for my file server, so that I
could manage it without the need of an SFTP client. I never ended up truly
sticking with it, due to the fact that it was extremely hacky (I would have to
start the login-auth script every time I wanted to authenticate a user. I would
do this from the shell, and I would give it plaintext passwords, not salted
ones). This protocol shall make it possible to authenticate login credentials
securely

### Example Packets

This would be a client-side packet/request
```
RLAP CLIENT 0.01
RLAP_STARTLIST
USER pocketlinux32 PLAINPASS password
USER lightripp3r HASHPASS $HASH_PASS
USER rj SSHPASS $SSH_KEY
... (more entries)
RLAP_ENDLIST

```
This would be a server-side packet/response
```
RLAP SERVER 0.01
RLAP_STARTLIST
ENTRY 1 USER YES PASS NO
ENTRY 2 USER NO
ENTRY 3 USER YES PASS YES
... (more entries)
RLAP_ENDLIST
```

### Packet Layout

An RLAP packet always starts by stating it's an RLAP packet, then it states its
role and protocol version.
```
RLAP CLIENT 0.01
```
The packet then declares the start of the data
```
RLAP_STARTLIST
```
Then it either gives a list of users and passwords (either plaintext or salted)
if a client, or a list of results if a server
```
# Client
USER pocketlinux32 HASHPASS $HASH_PASS
# Server
ENTRY 1 YES USER NO PASS
```
Finally, at the end of the list, the end of the data stream is declared
```
RLAP_ENDLIST
```

### Other Types of RLAP Packets

RLAP packets can carry more than just a list of items if you're the server.
They can also carry protocol errors and commands
```
# Error
E1: RLAP_ERR_INCOMPAT_PROT
# Command
RLAP_ENDCONN
```

### RLAP Errors

`RLAP_ERR_INCOMPAT_PROT` (Error 1): Client or Server sent an unknown or incompatible
protocol packet
`RLAP_ERR_INCOMPAT_VER` (Error 2): Client and Server versions are incompatible
