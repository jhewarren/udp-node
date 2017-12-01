# main
preset variables
load config
load libraries
parse command line

validate usage: <app> {c/s/e}
output loaded settings
prompt to continue or quit

// need to launch server then emulator then client
//  ... can add functionality to check for presence

if 'c' then run client (manual mode)
if 's' then run server
if 'e' then run emulator
if 'h' then display instructions
if 'l' then list configuration details
[if 'd' then run demo (auto mode)]
else error out with information

# server (aka slave)
load file structure
open socket to listen
if a message arrives then acknowledge and parse it
open reverse socket to client

if command is to get then run send (file name)
if command is to put then run recv (file name)
if command is catalog then run catalog

close socket
return to beginning

# client (aka master)
load file structure
open socket to emulator [or server/slave]

wait for user input
validate user input

open
if get then call get
if send the call send
if catalog then call catalog

[# demo / auto mode
// needs file structure handle, primary socket handle, secondary socket handle

call get listing
for each file name
    call send file name

open file structure
for each file
end demo/auto mode]

# emulator
open socket to server
open socket to client

listen on server socket
for each packet received
if first packet then save socket info
log pktinfo to log file

# send

# receive

# catalogue (file structure handle, socket handle)
packetize and send files listing

# was-pkt-lost
