public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        ServerInteraction server = new ServerInteraction("localhost", 8888);
        server.startServer();
        //server.sendCommand("2 binario2.bin\0");
        server.sendCommand("4 binario4.bin\0");
        server.sendCommand("3 binario4.bin 3 1 nacionalidade \"SPAIN\" 2 idade 24 nacionalidade \"BRAZIL\" 1 id 253072\0");
        server.stopServer();  
        //new Tela();
    }
}
