#!/bin/bash

# Comprehensive System Management Script

# Task 1: Monitor and manage system processes
echo "Listing all running processes with detailed memory and CPU usage..."
ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem > processes.txt

echo "Finding and terminating all processes by a specific user (e.g., username 'testuser')..."
pkill -u testuser

echo "Changing the priority of a CPU-intensive process to reduce its impact (e.g., PID 1234)..."
renice 10 -p 1234

# Task 2: Optimize system memory usage
echo "Displaying current memory usage and saving to a log file..."
free -h > memory_usage.log

echo "Adding and optimizing a 4GB swap file and enabling it..."
sudo fallocate -l 4G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

echo "Optimizing system swap and cache pressure..."
sudo sysctl -w vm.swappiness=10
sudo sysctl -w vm.vfs_cache_pressure=50

echo "Monitoring memory and swap usage in real-time and logging results..."
vmstat 1 10 > vmstat.log

# Task 3: Manage filesystem structure and disk space
echo "Creating a complex directory structure for a large project..."
mkdir -p project/{src/{main,test},bin,docs/{manuals,reports}}

echo "Copying example files into the appropriate directories and logging the operations..."
cp /path/to/example/files/* project/src/main/
cp /path/to/example/tests/* project/src/test/

echo "Generating a detailed report of the directory structure and disk usage..."
tree project/ > project_structure.txt
du -sh project/ > project_size.txt

# Task 4: Monitor and analyze network traffic
echo "Displaying the current IP address and network interface details..."
ip a > ip_details.txt

echo "Performing a network scan and logging the active devices on the network..."
sudo nmap -sP 192.168.1.0/24 > network_scan.log

echo "Capturing and analyzing network packets for a specific interface (e.g., eth0) and saving the capture file..."
sudo tcpdump -i eth0 -w capture.pcap

echo "Visualizing network traffic using iftop and saving the output..."
sudo iftop -i eth0 > network_traffic.txt

echo "System Management Script completed."
