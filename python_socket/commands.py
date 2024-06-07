from typing import List


def buscarRegistroOp(arquivoBin: str, numeroOperacoes: str, operacoes: List[str]) -> str:
    """Funcao que cria o comando de busca de registro

    Args:
        arquivoBin (str): nome do arquivo binario
        numeroOperacoes (str): quantidade de ops a serem realizadas
        operacoes (List[str]): lista de operacoes a serem realizadas

    Returns:
        str: comando de busca de registro
    """
    operacao = "3 " + arquivoBin + " " + numeroOperacoes + "\n"
    for op in operacoes:
        operacao += op + "\n"

    return operacao


def removerRegistroOp(arquivoBin: str, arquivoInd: str, numeroOperacoes: str, operacoes: List[str]) -> str:
    """Funcao que cria o comando de remocao de registro

    Args:
        arquivoBin (str): nome do arquivo binario
        arquivoInd (str): nome do arquivo de indices
        numeroOperacoes (str): quantidade de ops a serem realizadas
        operacoes (List[str]): lista de operacoes a serem realizadas

    Returns:
        str: comando de busca de registro
    """
    operacao = "5 " + arquivoBin + " " + arquivoInd + " s" + numeroOperacoes + "\n"
    for op in operacoes:
        operacao += op + "\n"

    return operacao


def inserirRegistroOp(arquivoBin: str, arquivoInd: str, numeroOperacoes: str, operacoes: List[str]) -> str:
    """Funcao que cria o comando de insercao de registro

    Args:
        arquivoBin (str): nome do arquivo binario
        arquivoInd (str): nome do arquivo de indices
        numeroOperacoes (str): quantidade de ops a serem realizadas
        operacoes (List[str]): lista de operacoes a serem realizadas

    Returns:
        str: comando de busca de registro
    """
    operacao = "6 " + arquivoBin + " " + arquivoInd + " s" + numeroOperacoes + "\n"
    for op in operacoes:
        operacao += op + "\n"

    return operacao
