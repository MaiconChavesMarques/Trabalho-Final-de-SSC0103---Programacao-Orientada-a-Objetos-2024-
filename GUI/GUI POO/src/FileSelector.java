import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class FileSelector {

    public static String selectFile() {
        JFileChooser fileChooser = new JFileChooser();

        // Cria um filtro para arquivos de texto, com as extensões especificadas
        FileNameExtensionFilter filter = new FileNameExtensionFilter(
            "Arquivos de Texto", "txt", "csv", "java", "log",  "bin");
        
        // Aplica o filtro ao JFileChooser
        fileChooser.setFileFilter(filter);

        int returnValue = fileChooser.showOpenDialog(null);

        if (returnValue == JFileChooser.APPROVE_OPTION) {
            return fileChooser.getSelectedFile().getName();
        } else {
            return null; // Retorna null se nenhum arquivo foi selecionado
        }
    }
}
