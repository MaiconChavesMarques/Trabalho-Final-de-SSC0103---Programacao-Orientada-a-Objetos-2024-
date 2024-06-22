public class Jogador {
    public int id;
    public int idade;
    public String nomeJogador;
    public String nacionalidade;
    public String nomeClube;

    public Jogador(int id, String nomeJogador, int idade, String nacionalidade, String nomeClube) {
        this.id = id;
        this.nomeJogador = nomeJogador;
        this.idade = idade;
        this.nacionalidade = nacionalidade;
        this.nomeClube = nomeClube;
    }

    public int getId() {
        return id;
    }

    public int getIdade() {
        return idade;
    }

    public String getNomeJogador() {
        return nomeJogador;
    }

    public String getNacionalidade() {
        return nacionalidade;
    }

    public String getNomeClube() {
        return nomeClube;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public void setNomeJogador(String nomeJogador) {
        this.nomeJogador = nomeJogador;
    }

    public void setNacionalidade(String nacionalidade) {
        this.nacionalidade = nacionalidade;
    }

    public void setNomeClube(String nomeClube) {
        this.nomeClube = nomeClube;
    }

    @Override
    public String toString() {
        return "Jogador{" +
                "id=" + id +
                ", idade=" + idade +
                ", nomeJogador='" + nomeJogador + '\'' +
                ", nacionalidade='" + nacionalidade + '\'' +
                ", nomeClube='" + nomeClube + '\'' +
                '}';
    }
}
