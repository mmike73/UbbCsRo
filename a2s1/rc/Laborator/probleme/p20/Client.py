import socket

MAX_LEN = 100

def main():
    import sys
    if len(sys.argv) < 2:
        print("Usage: python client.py [port_number]")
        return

    port = int(sys.argv[1])

    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('192.168.64.24', port)  # Server's IP address and port

    hostname = input("Enter hostname: ")  # Read hostname from user input

    if len(hostname) > MAX_LEN:
        print("Hostname exceeds maximum length.")
        return

    # Send the hostname to the server
    sock.sendto(hostname.encode(), server_address)  # Encode the hostname and send

    # Prepare to receive the IP address
    ip_buffer, sender_addr = sock.recvfrom(4)  # Buffer for receiving IP address (4 bytes for IPv4)

    # Convert received bytes to IP address
    ip_addr = int.from_bytes(ip_buffer, 'big')
    
    if ip_addr == 0:
        print("Hostname not found")
    else:
        # Convert the integer IP address to a human-readable format
        ip_string = f"{(ip_addr >> 24) & 0xFF}.{(ip_addr >> 16) & 0xFF}.{(ip_addr >> 8) & 0xFF}.{ip_addr & 0xFF}"
        print(f"IP of hostname: {ip_string}")

    sock.close()  # Ensure the socket is closed

if __name__ == "__main__":
    main()  # Call the main function
