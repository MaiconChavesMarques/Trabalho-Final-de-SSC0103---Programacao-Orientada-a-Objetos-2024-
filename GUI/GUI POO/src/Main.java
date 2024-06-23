import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!");
        ServerInteraction server = new ServerInteraction("localhost", 8888);
        CriarComandos comandos = new CriarComandos(server);

        server.startServer();
        server.sendCommand("4 binario7.bin indice7.bin\0");
        comandos.Buscar("binario7.bin", -1, 20, null, null, null);
        comandos.PegarTodosJogadores("binario7.bin");
        //server.sendCommand("2 binario2.bin\0");
        //server.sendCommand("4 binario4.bin indice4.bin\0");
        //server.sendCommand("3 binario4.bin 3 1 nacionalidade \"SPAIN\" 2 idade 24 nacionalidade \"BRAZIL\" 1 id 253072\0");
        //server.stopServer();  
        SwingUtilities.invokeLater(() -> new Tela());
    }
}
