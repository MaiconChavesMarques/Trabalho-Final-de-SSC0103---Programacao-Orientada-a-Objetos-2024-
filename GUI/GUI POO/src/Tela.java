import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

public class Tela extends JFrame {
    private CardLayout cardLayout;
    private JPanel mainPanel;
    private JPanel initialPanel;
    private JPanel tablePanel;
    private List<Jogador> jogadores;

    public Tela() {
        setTitle("Gerenciamento de Registros");
        setSize(800, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Configura o CardLayout para gerenciar as telas
        cardLayout = new CardLayout();
        mainPanel = new JPanel(cardLayout);

        // Painel inicial
        initialPanel = new JPanel();
        initialPanel.setLayout(new BorderLayout());
        JLabel initialLabel = new JLabel("Bem-vindo ao Gerenciamento de Registros!", JLabel.CENTER);
        initialLabel.setFont(new Font("Arial", Font.BOLD, 20));
        initialPanel.add(initialLabel, BorderLayout.CENTER);

        JButton startButton = new JButton("Iniciar");
        startButton.addActionListener(e -> cardLayout.show(mainPanel, "tablePanel"));
        initialPanel.add(startButton, BorderLayout.SOUTH);

        // Painel da tabela
        tablePanel = new JPanel();
        tablePanel.setLayout(null);

        JMenuBar menuBar = new JMenuBar();
        this.setJMenuBar(menuBar);

        JMenu Arquivo = new JMenu("Arquivo");
        menuBar.add(Arquivo);

        JMenu Servidor = new JMenu("Servidor");
        menuBar.add(Servidor);

        JMenuItem Endereco = new JMenuItem("Endereço");
        Servidor.add(Endereco);

        JMenuItem Abrir = new JMenuItem("Abrir");
        Arquivo.add(Abrir);

        String[] colunas = {"ID", "Idade", "Nome", "Nacionalidade", "Nome do Clube"};

        // Criação da lista de jogadores
        jogadores = new ArrayList<>();
        jogadores.add(new Jogador(209658, "L. GORETZKA", 27, "GERMANY", "FC BAYERN MUNCHEN"));
        jogadores.add(new Jogador(212198, "BRUNO FERNANDES", 27, "PORTUGAL", "MANCHESTER UNITED"));
        jogadores.add(new Jogador(224334, "M. ACUNA", 30, "ARGENTINA", "SEVILLA FC"));
        jogadores.add(new Jogador(192985, "K. DE BRUYNE", 31, "BELGIUM", "MANCHESTER CITY"));
        jogadores.add(new Jogador(224232, "N. BARELLA", 25, "ITALY", "INTER"));
        jogadores.add(new Jogador(212622, "J. KIMMICH", 27, "GERMANY", "FC BAYERN MUNCHEN"));
        jogadores.add(new Jogador(197445, "D. ALABA", 30, "AUSTRIA", "REAL MADRID CF"));
        jogadores.add(new Jogador(187961, "PAULINHO", 32, "BRAZIL", "AL AHLI"));
        jogadores.add(new Jogador(208333, "E. CAN", 28, "GERMANY", "BORUSSIA DORTMUND"));
        jogadores.add(new Jogador(210514, "JOAO CANCELO", 28, "PORTUGAL", "MANCHESTER CITY"));
        jogadores.add(new Jogador(228251, "L. PELLEGRINI", 26, "ITALY", "ROMA"));
        jogadores.add(new Jogador(177003, "L. MODRIC", 36, "CROATIA", "REAL MADRID CF"));
        jogadores.add(new Jogador(223848, "S. MILINKOVIC-SAVIC", 27, "SERBIA", "LAZIO"));
        jogadores.add(new Jogador(225193, "MERINO", 26, "SPAIN", "REAL SOCIEDAD"));
        jogadores.add(new Jogador(226161, "MARCOS LLORENTE", 27, "SPAIN", "ATLETICO DE MADRID"));
        jogadores.add(new Jogador(212616, "R. DE PAUL", 28, "ARGENTINA", "ATLETICO DE MADRID"));
        jogadores.add(new Jogador(181458, "I. PERISIC", 33, "CROATIA", "TOTTENHAM HOTSPUR"));
        jogadores.add(new Jogador(228702, "F. DE JONG", 25, "NETHERLANDS", "FC BARCELONA"));
        jogadores.add(new Jogador(194765, "A. GRIEZMANN", 31, "FRANCE", "ATLETICO DE MADRID"));
        jogadores.add(new Jogador(193082, "J. CUADRADO", 34, "COLOMBIA", "JUVENTUS"));
        jogadores.add(new Jogador(208574, "F. KOSTIC", 29, "SERBIA", "EINTRACHT FRANKFURT"));
        jogadores.add(new Jogador(231281, "T. ALEXANDER-ARNOLD", 23, "ENGLAND", "LIVERPOOL"));
        jogadores.add(new Jogador(176580, "L. SUAREZ", 35, "URUGUAY", "CLUB NACIONAL DE FOOTBALL"));
        jogadores.add(new Jogador(235212, "A. HAKIMI", 23, "MOROCCO", "PARIS SAINT-GERMAIN"));
        jogadores.add(new Jogador(216352, "M. BROZOVIC", 29, "CROATIA", "INTER"));
        jogadores.add(new Jogador(209331, "M. SALAH", 30, "EGYPT", "LIVERPOOL"));
        jogadores.add(new Jogador(241096, "S. TONALI", 22, "ITALY", "AC MILAN"));
        jogadores.add(new Jogador(189509, "THIAGO", 31, "SPAIN", "LIVERPOOL"));
        jogadores.add(new Jogador(238074, "R. JAMES", 22, "ENGLAND", "CHELSEA"));

        // Convertendo a lista de jogadores para uma matriz de objetos
        Object[][] dados = new Object[jogadores.size()][5];
        for (int i = 0; i < jogadores.size(); i++) {
            Jogador jogador = jogadores.get(i);
            dados[i][0] = jogador.id;
            dados[i][1] = jogador.idade;
            dados[i][2] = jogador.nomeJogador;
            dados[i][3] = jogador.nacionalidade;
            dados[i][4] = jogador.nomeClube;
        }

        DefaultTableModel modelo = new DefaultTableModel(dados, colunas);
        JTable tabela = new JTable(modelo);
        JScrollPane scrollPane = new JScrollPane(tabela);
        scrollPane.setPreferredSize(new Dimension(780, 390));
        scrollPane.setBounds(10, 10, 780, 390);
        tablePanel.add(scrollPane);

        // Adiciona um ouvinte de eventos à tabela para exibir o menu de contexto
        tabela.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                showPopup(e);
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                showPopup(e);
            }

            private void showPopup(MouseEvent e) {
                if (e.isPopupTrigger()) {
                    JTable source = (JTable) e.getSource();
                    int row = source.rowAtPoint(e.getPoint());
                    int column = source.columnAtPoint(e.getPoint());

                    if (!source.isRowSelected(row))
                        source.changeSelection(row, column, false, false);

                    JPopupMenu popupMenu = new JPopupMenu();

                    JMenuItem editarItem = new JMenuItem("Editar");
                    editarItem.addActionListener(ev -> {
            
                        if (row != -1) {
                            // Obter valores da linha selecionada na tabela
                            String id = tabela.getValueAt(row, 0).toString();
                            String idade = tabela.getValueAt(row, 1).toString();
                            String nome = tabela.getValueAt(row, 2).toString();
                            String nacionalidade = tabela.getValueAt(row, 3).toString();
                            String clube = tabela.getValueAt(row, 4).toString();
                
                            // Mostrar janela de edição com valores obtidos
                            mostrarJanelaEditar(id, idade, nome, nacionalidade, clube);
                        }
                    });
                    popupMenu.add(editarItem);

                    JMenuItem imprimirItem = new JMenuItem("Imprimir");
                    imprimirItem.addActionListener(ev -> {
                        System.out.println("Imprimir clicado");
                        imprimirCampos(row);
                    });
                    popupMenu.add(imprimirItem);

                    popupMenu.show(source, e.getX(), e.getY());
                }
            }

            private void imprimirCampos(int row) {
                String id = tabela.getValueAt(row, 0).toString();
                String idade = tabela.getValueAt(row, 1).toString();
                String nomeJogador = tabela.getValueAt(row, 2).toString();
                String nacionalidade = tabela.getValueAt(row, 3).toString();
                String nomeClube = tabela.getValueAt(row, 4).toString();

                System.out.println("ID: " + id);
                System.out.println("Idade: " + idade);
                System.out.println("Nome do Jogador: " + nomeJogador);
                System.out.println("Nacionalidade: " + nacionalidade);
                System.out.println("Nome do Clube: " + nomeClube);
            }
        });

        JButton busca = new JButton("Buscar");
        busca.setBounds(640, 410, 150, 20);
        tablePanel.add(busca);

        JButton inserir = new JButton("Inserir");
        inserir.setBounds(485, 410, 150, 20);
        tablePanel.add(inserir);

        JButton listartodos = new JButton("Listar todos");
        listartodos.setBounds(10, 410, 150, 20);
        tablePanel.add(listartodos);

        // Adiciona os painéis ao CardLayout
        mainPanel.add(initialPanel, "initialPanel");
        mainPanel.add(tablePanel, "tablePanel");

        // Mostra a tela inicial
        cardLayout.show(mainPanel, "initialPanel");

        // ActionListener para o botão "Buscar"
        busca.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                mostrarJanelaBuscar();
            }
        });

        // ActionListener para o botão "Inserir"
        inserir.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                mostrarJanelaInserir();
            }
        });

        // ActionListener para o botão "Listar todos"
        listartodos.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(null, "Listar todos foi clicado!");
            }
        });

        add(mainPanel);
        setVisible(true);
    }

// Método para mostrar a janela de buscar
private void mostrarJanelaBuscar() {
    JFrame buscarFrame = new JFrame("Buscar Jogador");
    buscarFrame.setSize(400, 300);
    buscarFrame.setLayout(null); // Layout null para coordenadas absolutas

    JLabel idLabel = new JLabel("ID:");
    idLabel.setBounds(20, 20, 80, 25);
    buscarFrame.add(idLabel);

    JTextField idField = new JTextField();
    idField.setBounds(140, 20, 200, 25);
    buscarFrame.add(idField);

    JLabel idadeLabel = new JLabel("Idade:");
    idadeLabel.setBounds(20, 60, 80, 25);
    buscarFrame.add(idadeLabel);

    JTextField idadeField = new JTextField();
    idadeField.setBounds(140, 60, 200, 25);
    buscarFrame.add(idadeField);

    JLabel nomeLabel = new JLabel("Nome:");
    nomeLabel.setBounds(20, 100, 80, 25);
    buscarFrame.add(nomeLabel);

    JTextField nomeField = new JTextField();
    nomeField.setBounds(140, 100, 200, 25);
    buscarFrame.add(nomeField);

    JLabel nacionalidadeLabel = new JLabel("Nacionalidade:");
    nacionalidadeLabel.setBounds(20, 140, 120, 25);
    buscarFrame.add(nacionalidadeLabel);

    JTextField nacionalidadeField = new JTextField();
    nacionalidadeField.setBounds(140, 140, 200, 25);
    buscarFrame.add(nacionalidadeField);

    JLabel clubeLabel = new JLabel("Clube:");
    clubeLabel.setBounds(20, 180, 100, 25);
    buscarFrame.add(clubeLabel);

    JTextField clubeField = new JTextField();
    clubeField.setBounds(140, 180, 200, 25);
    buscarFrame.add(clubeField);

    JButton buscarButton = new JButton("Buscar");
    buscarButton.setBounds(150, 220, 100, 30);
    buscarButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            String texto = ""; // Inicializa a string vazia
            int numeroCampos = 0;

            if (!idField.getText().isEmpty()) {
                texto += "id " + idField.getText() + " "; // Adiciona o texto do campo ID à string
                numeroCampos++;
            }
            if (!idadeField.getText().isEmpty()) {
                texto += "idade " + idadeField.getText() + " "; // Adiciona o texto do campo Idade à string
                numeroCampos++;
            }
            if (!nomeField.getText().isEmpty()) {
                texto += "nomeJogador " + "\"" + nomeField.getText() + "\"" + " "; // Adiciona o texto do campo Nome à string
                numeroCampos++;
            }
            if (!nacionalidadeField.getText().isEmpty()) {
                texto += "nacionalidade " + "\"" + nacionalidadeField.getText() + "\"" + " "; // Adiciona o texto do campo Nacionalidade à string
                numeroCampos++;
            }
            if (!clubeField.getText().isEmpty()) {
                texto += "nomeClube " + "\"" + clubeField.getText() + "\"" + " "; // Adiciona o texto do campo Clube à string
                numeroCampos++;
            }

            if (texto.charAt(texto.length() - 1) == ' ') { // Verifica se o último caractere é um espaço
                texto = texto.substring(0, texto.length() - 1); // Remove o último caractere (espaço) da string
            }

            System.out.println("3 " + "binario9.bin " + "1\n" + numeroCampos + " " + texto + "\n");
            JOptionPane.showMessageDialog(buscarFrame, "Buscar foi clicado!");
            buscarFrame.dispose();
        }
    });
    buscarFrame.add(buscarButton);

    buscarFrame.setLocationRelativeTo(null);

    buscarFrame.setVisible(true);
}
 

// Método para mostrar a janela de inserir
private void mostrarJanelaInserir() {
    JFrame inserirFrame = new JFrame("Inserir Jogador");
    inserirFrame.setSize(400, 300);
    inserirFrame.setLayout(null); // Layout null para coordenadas absolutas

    JLabel idLabel = new JLabel("ID:");
    idLabel.setBounds(20, 20, 80, 25);
    inserirFrame.add(idLabel);

    JTextField idField = new JTextField();
    idField.setBounds(140, 20, 200, 25);
    inserirFrame.add(idField);

    JLabel idadeLabel = new JLabel("Idade:");
    idadeLabel.setBounds(20, 60, 80, 25);
    inserirFrame.add(idadeLabel);

    JTextField idadeField = new JTextField();
    idadeField.setBounds(140, 60, 200, 25);
    inserirFrame.add(idadeField);

    JLabel nomeLabel = new JLabel("Nome:");
    nomeLabel.setBounds(20, 100, 80, 25);
    inserirFrame.add(nomeLabel);

    JTextField nomeField = new JTextField();
    nomeField.setBounds(140, 100, 200, 25);
    inserirFrame.add(nomeField);

    JLabel nacionalidadeLabel = new JLabel("Nacionalidade:");
    nacionalidadeLabel.setBounds(20, 140, 120, 25);
    inserirFrame.add(nacionalidadeLabel);

    JTextField nacionalidadeField = new JTextField();
    nacionalidadeField.setBounds(140, 140, 200, 25);
    inserirFrame.add(nacionalidadeField);

    JLabel clubeLabel = new JLabel("Clube:");
    clubeLabel.setBounds(20, 180, 100, 25);
    inserirFrame.add(clubeLabel);

    JTextField clubeField = new JTextField();
    clubeField.setBounds(140, 180, 200, 25);
    inserirFrame.add(clubeField);

    JButton inserirButton = new JButton("Inserir");
    inserirButton.setBounds(150, 220, 100, 30);
    inserirButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            String texto = ""; // Inicializa a string vazia

            if (!idField.getText().isEmpty()) {
                texto += idField.getText() + " "; // Adiciona o texto do campo ID à string
            }else{
                texto += "NULO ";
            }
            if (!idadeField.getText().isEmpty()) {
                texto += idadeField.getText() + " "; // Adiciona o texto do campo Idade à string
            }else{
                texto += "NULO ";
            }
            if (!nomeField.getText().isEmpty()) {
                texto += "\"" + nomeField.getText() + "\"" + " "; // Adiciona o texto do campo Nome à string
            }else{
                texto += "NULO ";
            }
            if (!nacionalidadeField.getText().isEmpty()) {
                texto += "\"" + nacionalidadeField.getText() + "\"" + " "; // Adiciona o texto do campo Nacionalidade à string
            }else{
                texto += "NULO ";
            }
            if (!clubeField.getText().isEmpty()) {
                texto += "\"" + clubeField.getText() + "\"" + " "; // Adiciona o texto do campo Clube à string
            }else{
                texto += "NULO ";
            }

            if (texto.charAt(texto.length() - 1) == ' ') { // Verifica se o último caractere é um espaço
                texto = texto.substring(0, texto.length() - 1); // Remove o último caractere (espaço) da string
            }else{
                texto += "NULO ";
            }

            System.out.print("6 " + "binario4.bin indice4.bin 1\n"+ texto + "\n");
            JOptionPane.showMessageDialog(inserirFrame, "Inserir foi clicado!");
            inserirFrame.dispose();
        }
    });
    inserirFrame.add(inserirButton);

    inserirFrame.setLocationRelativeTo(null);

    inserirFrame.setVisible(true);
}

private void mostrarJanelaEditar(String id, String idade, String nome, String nacionalidade, String clube) {
    JFrame editarFrame = new JFrame("Editar Jogador");
    editarFrame.setSize(400, 300);
    editarFrame.setLayout(null); // Layout null para coordenadas absolutas

    JLabel idLabel = new JLabel("ID:");
    idLabel.setBounds(20, 20, 80, 25);
    editarFrame.add(idLabel);

    JTextField idField = new JTextField(id); // Valor obtido da tabela
    idField.setBounds(140, 20, 200, 25);
    editarFrame.add(idField);

    JLabel idadeLabel = new JLabel("Idade:");
    idadeLabel.setBounds(20, 60, 80, 25);
    editarFrame.add(idadeLabel);

    JTextField idadeField = new JTextField(idade); // Valor obtido da tabela
    idadeField.setBounds(140, 60, 200, 25);
    editarFrame.add(idadeField);

    JLabel nomeLabel = new JLabel("Nome:");
    nomeLabel.setBounds(20, 100, 80, 25);
    editarFrame.add(nomeLabel);

    JTextField nomeField = new JTextField(nome); // Valor obtido da tabela
    nomeField.setBounds(140, 100, 200, 25);
    editarFrame.add(nomeField);

    JLabel nacionalidadeLabel = new JLabel("Nacionalidade:");
    nacionalidadeLabel.setBounds(20, 140, 120, 25);
    editarFrame.add(nacionalidadeLabel);

    JTextField nacionalidadeField = new JTextField(nacionalidade); // Valor obtido da tabela
    nacionalidadeField.setBounds(140, 140, 200, 25);
    editarFrame.add(nacionalidadeField);

    JLabel clubeLabel = new JLabel("Clube:");
    clubeLabel.setBounds(20, 180, 100, 25);
    editarFrame.add(clubeLabel);

    JTextField clubeField = new JTextField(clube); // Valor obtido da tabela
    clubeField.setBounds(140, 180, 200, 25);
    editarFrame.add(clubeField);

    JButton editarButton = new JButton("Editar");
    editarButton.setBounds(150, 220, 100, 30);
    editarButton.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            String texto = ""; // Inicializa a string vazia

            System.out.print("Remova: " + "5 " + "binario4.bin indice4.bin 1\n");
            System.out.print("1 id " + id + "\n");

            if (!idField.getText().isEmpty()) {
                texto += idField.getText() + " "; // Adiciona o texto do campo ID à string
            } else {
                texto += "NULO ";
            }
            if (!idadeField.getText().isEmpty()) {
                texto += idadeField.getText() + " "; // Adiciona o texto do campo Idade à string
            } else {
                texto += "NULO ";
            }
            if (!nomeField.getText().isEmpty()) {
                texto += "\"" + nomeField.getText() + "\"" + " "; // Adiciona o texto do campo Nome à string
            } else {
                texto += "NULO ";
            }
            if (!nacionalidadeField.getText().isEmpty()) {
                texto += "\"" + nacionalidadeField.getText() + "\"" + " "; // Adiciona o texto do campo Nacionalidade à string
            } else {
                texto += "NULO ";
            }
            if (!clubeField.getText().isEmpty()) {
                texto += "\"" + clubeField.getText() + "\"" + " "; // Adiciona o texto do campo Clube à string
            } else {
                texto += "NULO ";
            }

            if (texto.charAt(texto.length() - 1) == ' ') { // Verifica se o último caractere é um espaço
                texto = texto.substring(0, texto.length() - 1); // Remove o último caractere (espaço) da string
            } else {
                texto += "NULO ";
            }

            System.out.print("6 " + "binario4.bin indice4.bin 1\n" + texto + "\n");
            JOptionPane.showMessageDialog(editarFrame, "Editar foi clicado!");
            editarFrame.dispose();
        }
    });
    editarFrame.add(editarButton);

    editarFrame.setLocationRelativeTo(null);

    editarFrame.setVisible(true);
}

/*
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Tela());
    }
*/
}
