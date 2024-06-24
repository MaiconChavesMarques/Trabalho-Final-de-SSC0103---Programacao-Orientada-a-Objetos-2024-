import javax.swing.SwingUtilities;

public class Main {
    public static void main(String[] args) throws Exception {
        System.out.println("Hello, World!"); 
        SwingUtilities.invokeLater(() -> new Tela());
    }
}
