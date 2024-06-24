import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!"); 
        ServerInteraction server = new ServerInteraction("localhost", 8888);
        server.startServer();

        CriarComandos comandos = new CriarComandos(server);

        System.out.println(comandos.PegarTodosJogadores("binario8.bin"));

        SwingUtilities.invokeLater(() -> new Tela());
    }
}
