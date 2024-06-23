import java.util.ArrayList;
import java.util.List;

public class CriarComandos {
    private ServerInteraction server;

    public CriarComandos(ServerInteraction server) {
        this.server = server;
    }

    private int contarComandos(int id, int idade, String nomeJogador, String nacionalidade, String nomeClube) {
        /*
         * Funcao que conta o numero de comandos que foram passados
         * 
         * Args:
         *  id (int): id do jogador
         *  idade (int): idade do jogador
         *  nomeJogador (String): nome do jogador
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         * 
         * Returns:
         *  int: numero de comandos que foram passados
         */
        
        int numComandos = 0;

        if(id != -1) {
            numComandos++;
        }

        if(idade != -1) {
            numComandos++;
        }

        if(nomeJogador != null) {
            numComandos++;
        }

        if(nacionalidade != null) {
            numComandos++;
        }

        if(nomeClube != null) {
            numComandos++;
        }

        return numComandos;
    }

    private String criarComandoMultiplosParametros(int id, int idade, String nomeJogador, String nacionalidade, String nomeClube) {
        /*
         * Funcao que cria o comando de busca com multiplos parametros
         * 
         * Args:
         *  id (int): id do jogador
         *  idade (int): idade do jogador
         *  nomeJogador (String): nome do jogador
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         * 
         * Returns:
         *  String: comando com multiplos parametros
         */
        
        String comando = "";

        if(id != -1) {
            comando += "id " + id + " ";
        }

        if(idade != -1) {
            comando += "idade " + idade + " ";
        }

        if(nomeJogador != null) {
            comando += "nomeJogador \"" + nomeJogador + "\" ";
        }

        if(nacionalidade != null) {
            comando += "nacionalidade \"" + nacionalidade + "\" ";
        }

        if(nomeClube != null) {
            comando += "nomeClube \"" + nomeClube + "\" ";
        }

        return comando;
    }

    private List<Jogador> parseBuscarRetorno(String retorno) {
        /*
         * Funcao que faz o parse do retorno da busca
         * 
         * Args:
         *  retorno (String): retorno da busca
         * 
         * Returns:
         *  List<Jogador>: lista de jogadores que foram encontrados
         */
        
        List<Jogador> jogadores = new ArrayList<>();

        String[] lines = retorno.split("\\n\\n");

        for (String line : lines) {
            String[] parts = line.split("\\n");
            if (parts.length == 5) {
                int id = Integer.parseInt(parts[0].trim());
                int idade = Integer.parseInt(parts[1].trim());
                String nomeJogador = parts[2].trim();
                String nacionalidade = parts[3].trim();
                String nomeClube = parts[4].trim();

                Jogador jogador = new Jogador(id, nomeJogador, idade, nacionalidade, nomeClube);
                jogadores.add(jogador);
                //System.out.println(jogador);
            }
        }

        return jogadores;
    }

    public List<Jogador> Buscar(String nomeArquivo, int id, int idade, String nomeJogador, String nacionalidade, String nomeClube) {
        /*
         * Funcao que cria o comando de busca e envia para o servidor
         * 
         * Args:
         *  nomeArquivo (String): nome do arquivo binario
         *  id (int): id do jogador
         *  idade (int): idade do jogador
         *  nomeJogador (String): nome do jogador
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         * 
         * Returns:
         *  List<Jogador>: lista de jogadores que foram encontrados
         */
        
        List<Jogador> jogadores = new ArrayList<>();

        int numComandos = contarComandos(id, idade, nomeJogador, nacionalidade, nomeClube);

        if(numComandos == 0) {
            System.out.println("Nenhum comando foi passado");
            return null;
        }
        
        String comando = "3 " + nomeArquivo + " 1 "; // definindo o comando de busca
        comando += numComandos + " "; // definindo o numero de comandos
        comando += criarComandoMultiplosParametros(id, idade, nomeJogador, nacionalidade, nomeClube);
        comando += "\0";

        String retorno = server.sendCommand(comando); // enviando o comando para o servidor

        jogadores = parseBuscarRetorno(retorno);

        return jogadores;
    }

    public Jogador Inserir(String nomeArquivoBin, String nomeArquivoInd, int id, String nomeJogador, int idade, String nacionalidade, String nomeClube) {
        /*
         * Funcao que cria o comando de insercao e envia para o servidor
         * 
         * Args:
         *  nomeArquivoBin (String): nome do arquivo binario
         *  nomeArquivoInd (String): nome do arquivo de indice
         *  id (int): id do jogador. Deve ser -1 se nao for passado
         *  nomeJogador (String): nome do jogador.
         *  idade (int): idade do jogador. Deve ser -1 se nao for passado
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         * 
         * Returns:
         *  Jogador: jogador que foi inserido
         */
        
        Jogador jogador = new Jogador(id, nomeJogador, idade, nacionalidade, nomeClube);

        String idString;

        if(id == -1) {
            idString = "NULO";
        } else {
            idString = Integer.toString(id);
        }

        String idadeString;

        if(idade == -1) {
            idadeString = "NULO";
        } else {
            idadeString = Integer.toString(idade);
        }

        if(nomeJogador == null) {
            nomeJogador = "NULO";
        }

        if(nacionalidade == null) {
            nacionalidade = "NULO";
        }

        if(nomeClube == null) {
            nomeClube = "NULO";
        }

        String comando = "6 " + nomeArquivoBin + " " + nomeArquivoInd + " 1" +  " " + idString + " " + idadeString + " \"" + nomeJogador + "\" \"" + nacionalidade + "\" \"" + nomeClube + "\"\0";
        
        server.sendCommand(comando); // enviando o comando para o servidor

        return jogador;
    }

    public Jogador Remover(String nomeArquivoBin, String nomeArquivoInd, int id, String nomeJogador, int idade, String nacionalidade, String nomeClube) {
        /*
         * Funcao que cria o comando de remocao e envia para o servidor
         * 
         * Args:
         *  nomeArquivoBin (String): nome do arquivo binario
         *  nomeArquivoInd (String): nome do arquivo de indice
         *  id (int): id do jogador. Deve ser -1 se nao for passado
         *  nomeJogador (String): nome do jogador.
         *  idade (int): idade do jogador. Deve ser -1 se nao for passado
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         * 
         * Returns:
         *  Jogador: jogador que foi removido
         */

        Jogador jogador = new Jogador(id, nomeJogador, idade, nacionalidade, nomeClube);
        
        int numComandos = contarComandos(id, idade, nomeJogador, nacionalidade, nomeClube);

        if(numComandos == 0) {
            System.out.println("Nenhum comando foi passado");
            return null;
        }

        String comando = "5 " + nomeArquivoBin + " " + nomeArquivoInd + " 1 "; // definindo o comando de remocao
        comando += numComandos + " "; // definindo o numero de comandos
        comando += criarComandoMultiplosParametros(id, idade, nomeJogador, nacionalidade, nomeClube);
        comando += "\0";

        server.sendCommand(comando); // enviando o comando para o servidor

        return jogador;
    }

    public Jogador Modificar(String nomeArquivoBin, String nomeArquivoInd, Jogador jogadorAntigo, int id, int idade, String nomeJogador, String nacionalidade, String nomeClube)
    {
        /*
         * Funcao que cria o comando de modificacao e envia para o servidor
         * 
         * Args:
         *  nomeArquivoBin (String): nome do arquivo binario
         *  nomeArquivoInd (String): nome do arquivo de indice
         *  jogadorAntigo (Jogador): jogador que sera modificado
         *  id (int): id do jogador. Deve ser -1 se nao for passado
         *  idade (int): idade do jogador. Deve ser -1 se nao for passado
         *  nomeJogador (String): nome do jogador.
         *  nacionalidade (String): nacionalidade do jogador
         *  nomeClube (String): nome do clube do jogador
         *
         * Returns:
         *  Jogador: jogador apos modificacao
         */

        Remover(nomeArquivoBin, nomeArquivoInd, jogadorAntigo.getId(), jogadorAntigo.getNomeJogador(), jogadorAntigo.getIdade(), jogadorAntigo.getNacionalidade(), jogadorAntigo.getNomeClube());
        return Inserir(nomeArquivoBin, nomeArquivoInd, id, nomeJogador, idade, nacionalidade, nomeClube);
    }

    public List<Jogador> PegarTodosJogadores(String nomeArquivoBin)
    {
        /*
         * Funcao que cria o comando de pegar todos os jogadores e envia para o servidor
         * 
         * Args:
         *  nomeArquivoBin (String): nome do arquivo binario
         * 
         * Returns:
         *  List<Jogador>: lista de jogadores que foram encontrados
         */

        String comando = "2 " + nomeArquivoBin + "\0"; // definindo o comando de pegar todos os jogadores

        String retorno = server.sendCommand(comando); // enviando o comando para o servidor

        List<Jogador> jogadores;
        jogadores = parseBuscarRetorno(retorno);
        System.out.println(jogadores);

        return jogadores;
    }
}
