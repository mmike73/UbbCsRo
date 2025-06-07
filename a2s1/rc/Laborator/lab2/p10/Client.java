import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;

public class Client {

    public static void main(String[] args) {
        String adresa_server = "192.168.64.24";
        int port = 57577;

        try (Socket socket = new Socket(adresa_server, port)) {
            System.out.println("Conectat la server");

            DataInputStream in = new DataInputStream(socket.getInputStream());
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Introdu primul string: ");
            String s1 = reader.readLine();
            System.out.print("Introdu al doilea string: ");
            String s2 = reader.readLine();

            if (s1.length() > 100 || s2.length() > 100) {
                System.out.println("Maxim 100!!!");
                return;
            }

            int l1 = s1.length();
            int l2 = s2.length();
            byte[] l1Bytes = ByteBuffer.allocate(2).putShort((short) l1).array();
            byte[] l2Bytes = ByteBuffer.allocate(2).putShort((short) l2).array();
            out.write(l1Bytes);
            out.writeBytes(s1);
            out.write(l2Bytes);
            out.writeBytes(s2);

            char resultChar = (char) in.readUnsignedByte();
            int resultCount = in.readUnsignedShort();
            System.out.printf("Character '%c' appears %d times\n", resultChar, resultCount);

        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
