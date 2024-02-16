# Computer Networks 2 Project: SNMP Protocol Communication
This project is done as the part of the faculy course "Computer Networks 2". It focuses on communicating with routers via the SNMP protocol using Java code.

## General Information
Environment: Ubuntu virtual machine in the GNS3 simulator
Tools: iReasoning SNMP API and MIB Browser

## Project Tasks
Configure router R3 to assign a Local Preference (LP) value of 100 to all routes coming from R1 and a value of 150 to all routes coming from R2.
Configure router R3 to set the LP value to 50 for a route when it receives a route with a community value of 3:50, and to set the LP value to 200 for a route when it receives a route with a Community value of 3:200.
Configure router R1 to attach a Community value of 3:200 to the route 192.168.10.0/24 when advertising it to R3. The method of configuring Community values is provided here.

## SNMP Monitoring Application
Develop an application that monitors SNMP protocol activity on all routers. Use the SNMP part of the MIB-2. The application should collect the following statistical parameters of SNMP operation on each router every 10 seconds:

- Number of incoming SNMP packets
- Number of outgoing SNMP packets
- Number of get requests
- Number of set requests
- Number of generated traps
- Number of invalid community values in requests

## Verification of Solution
Enable traps, generate requests with incorrect community values, and continuously monitor SNMP statistics.
