import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!"); 
        ServerInteraction server = new ServerInteraction("localhost", 8888);

        server.startServer();
        server.sendCommand("3 binario6.bin 1 1 id 989898\0");

        SwingUtilities.invokeLater(() -> new Tela());
    }
}
