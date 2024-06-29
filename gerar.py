import pandas as pd
import matplotlib.pyplot as plt

#Carregar o csv
file_path = 'resultado.csv'
data = pd.read_csv(file_path, delimiter=',')

#Colocar os dados no gráfico
def plot_data(data, operation_name, title):
    plt.figure(figsize=(14, 8))

    for tree in data['Nome Arvore'].unique():
        tree_data = data[(data[' Nome operacao'].str.strip() == operation_name) & (data['Nome Arvore'] == tree)]
        grouped_data = tree_data.groupby(' Quantidade Parametros')[' Custo Operacao'].mean()
        plt.plot(grouped_data.index, grouped_data.values, label=tree)

    plt.title(title)
    plt.xlabel('Quantidade de Parâmetros')
    plt.ylabel('Média de Custo Operação')
    plt.legend(title='Nome Arvore')
    plt.grid(True)
    plt.show()

plot_data(data, 'Insercao', 'Média de Custo Operação por Quantidade de Parâmetros e Nome da Árvore (Inserção)')
plot_data(data, 'Remocao', 'Média de Custo Operação por Quantidade de Parâmetros e Nome da Árvore (Remoção)')
