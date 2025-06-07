import java.io.*;
import java.net.*;

public class Client {
    private static final int MAX_LEN = 100;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java Client [port_number]");
            return;
        }

        int port = Integer.parseInt(args[0]);

        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(); // Create a UDP socket

            InetAddress serverAddress = InetAddress.getByName("192.168.64.24"); // Server's IP address
            byte[] buffer = new byte[MAX_LEN + 1]; // Buffer for sending data

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in)); // For reading user input
            System.out.print("Enter hostname: ");
            String hostname = reader.readLine(); // Read hostname from user input

            // Send the hostname to the server
            byte[] hostnameBytes = hostname.getBytes(); // Convert hostname to bytes
            DatagramPacket sendPacket = new DatagramPacket(hostnameBytes, hostnameBytes.length, serverAddress, port);
            socket.send(sendPacket); // Send the packet

            // Prepare to receive the IP address
            byte[] ipBuffer = new byte[4]; // Buffer for receiving IP address (4 bytes for IPv4)
            DatagramPacket receivePacket = new DatagramPacket(ipBuffer, ipBuffer.length); // Create a packet to receive the data
            socket.receive(receivePacket); // Block until the IP address is received

            // Convert received bytes to IP address
            int ipAddr = ((ipBuffer[0] & 0xFF) << 24) | ((ipBuffer[1] & 0xFF) << 16) | ((ipBuffer[2] & 0xFF) << 8) | (ipBuffer[3] & 0xFF);
            if (ipAddr == 0) {
                System.out.println("Hostname not found");
            } else {
                // Convert the integer IP address to a human-readable format
                String ipString = String.format("%d.%d.%d.%d", (ipAddr >> 24) & 0xFF, (ipAddr >> 16) & 0xFF, (ipAddr >> 8) & 0xFF, ipAddr & 0xFF);
                System.out.println("IP of hostname: " + ipString);
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            if (socket != null && !socket.isClosed()) {
                socket.close(); // Ensure the socket is closed
            }
        }
    }
}
