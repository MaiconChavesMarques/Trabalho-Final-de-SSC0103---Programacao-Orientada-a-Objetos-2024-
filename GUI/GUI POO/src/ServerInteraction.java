public class ServerInteraction {
    private String serverAddress;
    private int port;
    SocketClient client;

    public ServerInteraction(String serverAddress, int port) {
        this.serverAddress = serverAddress;
        this.port = port;
        
    }

    public void startServer() {
        client = new SocketClient(serverAddress, port);
        client.start();
    }

    public String sendCommand(String command) {
        String response = client.sendCommand(command);
        System.out.println("Response: " + response);
        return response;
    }

    public void stopServer() {
        client.stop();
    }
}