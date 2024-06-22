import java.io.*;
import java.net.*;

public class SocketClient {
    private String serverAddress;
    private int port;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public SocketClient(String serverAddress, int port) {
        this.serverAddress = serverAddress;
        this.port = port;
    }

    public void start() {
        try {
            clientSocket = new Socket(serverAddress, port);
            System.out.println("Connected to server " + serverAddress + " on port " + port);
            out = new PrintWriter(clientSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + serverAddress);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " + serverAddress);
            System.exit(1);
        }
    }

    public String sendCommand(String command) {
        if (clientSocket == null || clientSocket.isClosed()) {
            throw new IllegalStateException("Socket is not connected. Please call start() first.");
        }
    
        System.out.println("Sending command: " + command);
    
        try (Socket clientSocket = new Socket(serverAddress, port);
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in))) {

            while (true) {
                out.println(command);

                StringBuilder response = new StringBuilder();
                int character;
                while ((character = in.read()) != -1) {
                    if (character == '\0') {
                        break;
                    }
                    response.append((char) character);
                }

                System.out.println("Received: " + response.toString());

                return response.toString();
            }
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + serverAddress);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to " + serverAddress);
            System.exit(1);
        }

        return null;
    }

    public void stop() {
        try {
            if (in != null) {
                in.close();
            }
            if (out != null) {
                out.close();
            }
            if (clientSocket != null) {
                clientSocket.close();
            }
        } catch (IOException e) {
            System.err.println("Error closing the connection.");
        }
    }
}
