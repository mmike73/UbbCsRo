import socket
import struct

def main():
    import sys

    if len(sys.argv) < 2:
        print("Usage: python TCPClient.py <port>")
        return

    try:
        port = int(sys.argv[1])
        if port <= 0 or port > 65535:
            print("Invalid port number.")
            return
    except ValueError:
        print("Port invalid.")
        return

    server_address = "192.168.64.24"  # IP address of the server

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            client_socket.connect((server_address, port))
            print("Connected to server.")

            # Read a string from the user
            input_string = input("Enter a string: ")

            # Send string length (as unsigned 16-bit) and string data
            length = len(input_string)
            client_socket.sendall(struct.pack('>H', length))  # Send the length as 2 bytes
            client_socket.sendall(input_string.encode())  # Send the string data
            print("Sent string:", input_string)
            print("String length:", length)

            # Read substring parameters (start position and length) from the user
            start = int(input("Enter the start position for the substring: "))
            sub_length = int(input("Enter the length of the desired substring: "))

            # Send start position and length as unsigned 16-bit values
            client_socket.sendall(struct.pack('>H', start))
            client_socket.sendall(struct.pack('>H', sub_length))
            print("Start position:", start, ", Length:", sub_length)

            # Receive the substring from the server
            result = client_socket.recv(sub_length)  # Read exactly `sub_length` bytes
            substring = result.decode()

            # Display the result
            print("Received substring:", substring)

    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()
