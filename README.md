//Trabalho de Projeto de Arquivos sobre sobre complexidade algorítmica das estruturas de árvores estudadas durante o semestre.
Primeiramente, tudo é controlado pelo makefile.
Comandos importantes abaixo...
1.make clean (limpar arquivos de exec .o)
2.make para compilar e buildar o programa
3. ./program para rodar o prgorama
4.chmod +x program
obs: talvez seja necessário dar permissão para rodar o programa, basta usar o comando 4. 

Após rodar o programa, será gerado um arquivo resultado.csv
Caso queria baixar esse arquivo é necessário seguir os passos 6.
Precisei baixar o csv desse jeito pq bugou tudo aqui em casa.

5.Para gerar o gráfico basta digitar python gerar.py

6.
No terminal do CodeSpaces, use o comando cd para navegar até o diretório onde o arquivo CSV está localizado.
Inicie um servidor web simples usando Python:

Você pode usar o módulo http.server do Python para iniciar um servidor web simples. Execute o seguinte comando no terminal:
bash
Copiar código
python3 -m http.server 8080
Isso irá iniciar um servidor web na porta 8080 que serve o conteúdo do diretório atual.
Obtenha o URL para acessar o servidor:

No CodeSpaces, você verá um botão para "Forward Port" ou algo similar. Clique nesse botão e escolha a porta 8080.
O CodeSpaces fornecerá um URL que pode ser acessado pelo seu navegador para conectar ao servidor web que você iniciou.
Acesse o URL no seu navegador:

Abra o navegador e vá para o URL fornecido pelo CodeSpaces. Você verá a lista de arquivos e diretórios no diretório onde você iniciou o servidor.
Encontre o arquivo CSV na lista e clique nele para baixá-lo.
Finalize o servidor web dando um CTRL + C no terminal e GG.
