import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!"); 
        ServerInteraction server = new ServerInteraction("localhost", 8888);
        CriarComandos comandos = new CriarComandos(server);

        server.startServer();
        comandos.Buscar("binario6.bin", 989898, -1, null, null, null);

        SwingUtilities.invokeLater(() -> new Tela());
    }
}
