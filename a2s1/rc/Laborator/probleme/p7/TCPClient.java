package p7;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class TCPClient {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java TCPClient <port>");
            return;
        }

        int port;
        try {
            port = Integer.parseInt(args[0]);
            if (port <= 0 || port > 65535) {
                System.out.println("Invalid port number.");
                return;
            }
        } catch (NumberFormatException e) {
            System.out.println("Port invalid.");
            return;
        }

        String serverAddress = "192.168.64.24";  // IP address of the server
        try (Socket socket = new Socket(serverAddress, port)) {
            System.out.println("Connected to server.");

            // Input and output streams
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            DataInputStream in = new DataInputStream(socket.getInputStream());
            Scanner scanner = new Scanner(System.in);

            // Read a string from the user
            System.out.print("Enter a string: ");
            String inputString = scanner.nextLine();

            // Send string length (as unsigned 16-bit) and string data
            int length = inputString.length();
            out.writeShort(length);  // Send the length as 2 bytes
            out.writeBytes(inputString);  // Send the string data
            System.out.println("Sent string: " + inputString);
            System.out.println("String length: " + length);

            // Read substring parameters (start position and length) from the user
            System.out.print("Enter the start position for the substring: ");
            int start = scanner.nextInt();
            System.out.print("Enter the length of the desired substring: ");
            int subLength = scanner.nextInt();

            // Send start position and length as unsigned 16-bit values
            out.writeShort(start);
            out.writeShort(subLength);
            System.out.println("Start position: " + start + ", Length: " + subLength);

            // Receive the substring from the server
            byte[] result = new byte[subLength];
            in.readFully(result);  // Read exactly `subLength` bytes
            String substring = new String(result);

            // Display the result
            System.out.println("Received substring: " + substring);
            
            scanner.close();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
