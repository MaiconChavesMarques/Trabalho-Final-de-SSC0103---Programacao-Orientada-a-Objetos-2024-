import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;

public class Tela extends JFrame {
    public Tela(){
        setTitle("Gerenciamento de Registros");
        setSize(800, 500);
        setLayout(null);
        setDefaultCloseOperation((JFrame.EXIT_ON_CLOSE));
        setLocationRelativeTo(null);
        
        JMenuBar menuBar = new JMenuBar();
        this.setJMenuBar(menuBar);
        
        JMenu Arquivo = new JMenu("Arquivo");
        menuBar.add(Arquivo);
        
        JMenuItem Abrir = new JMenuItem("Abrir");
        Arquivo.add(Abrir);

        String[] colunas = {"ID", "Nome", "Idade"};
        Object[][] dados = {
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40},
            {1, "Andre", 25},
            {2, "Iara", 30},
            {3, "Nadia", 28},
            {4, "Xena", 35},
            {5, "Ze", 40}
        };

        DefaultTableModel modelo = new DefaultTableModel(dados, colunas);
        
        JTable tabela = new JTable(modelo);
        
        JScrollPane scrollPane = new JScrollPane(tabela);

        scrollPane.setPreferredSize(new Dimension(780, 390));
        scrollPane.setBounds(10, 10, 780, 390); // Posicionamento absoluto do JScrollPane
        add(scrollPane);

        JButton busca = new JButton("Buscar");
        busca.setBounds(640, 410, 150, 20);
        busca.setFont(new Font("Arial", Font.BOLD, 15));
        busca.setForeground(new Color(10, 10, 10));
        busca.setBackground(new Color(211, 211, 211));
        add(busca);

        JButton inserir = new JButton("Inserir");
        inserir.setBounds(485, 410, 150, 20);
        inserir.setFont(new Font("Arial", Font.BOLD, 15));
        inserir.setForeground(new Color(10, 10, 10));
        inserir.setBackground(new Color(211, 211, 211));
        add(inserir);        

        setVisible(true);
    }

    
}
