import csv
import random
import networkx as nx
import matplotlib.pyplot as plt

tamanho = 35
matriz = []
for x in range(tamanho):
 	linha = []
 	for y in range(tamanho):
 		linha.append(0)
 	matriz.append(linha)

def colocar1(x, y):
	matriz[x][y] = 1
	matriz[y][x] = 1

#9 periodo
colocar1(0,1) 
colocar1(0,2)
colocar1(0,3)
colocar1(0,4)
colocar1(0,5)
colocar1(0,6)
colocar1(0,7)
 
colocar1(1,2)
colocar1(1,3)
colocar1(1,4)
colocar1(1,5)
colocar1(1,6)
colocar1(1,7)

colocar1(2,3)
colocar1(2,4)
colocar1(2,5)
colocar1(2,6)
colocar1(2,7)

colocar1(3,4)
colocar1(3,5)
colocar1(3,6)
colocar1(3,7)

colocar1(4,5)
colocar1(4,6)
colocar1(4,7)

colocar1(5,6)
colocar1(5,7)

colocar1(6,7)

#7 periodo
colocar1(8,9)
colocar1(8,10)
colocar1(8,11)
colocar1(8,12)
colocar1(8,13)
colocar1(8,14)

colocar1(9,10)
colocar1(9,11)
colocar1(9,12)
colocar1(9,13)
colocar1(9,14)

colocar1(10,11)
colocar1(10,12)
colocar1(10,13)
colocar1(10,14)

colocar1(11,12)
colocar1(11,13)
colocar1(11,14)

colocar1(12,13)
colocar1(12,14)

colocar1(13,14)

#5 periodo
colocar1(15,16)
colocar1(15,17)
colocar1(15,18)
colocar1(15,19)

colocar1(16,17)
colocar1(16,18)
colocar1(16,19)

colocar1(17,18)
colocar1(17,19)

colocar1(18,19)


#3 periodo
colocar1(20,21)
colocar1(20,22)
colocar1(20,23)
colocar1(20,24)
colocar1(20,25)
colocar1(20,26)

colocar1(21,22)
colocar1(21,23)
colocar1(21,24)
colocar1(21,25)
colocar1(21,26)

colocar1(22,23)
colocar1(22,24)
colocar1(22,25)
colocar1(22,26)

colocar1(23,24)
colocar1(23,25)
colocar1(23,26)

colocar1(24,25)
colocar1(24,26)

colocar1(25,26)

#1 periodo
colocar1(27,28)
colocar1(27,29)
colocar1(27,30)
colocar1(27,31)
colocar1(27,32)
colocar1(27,33)
colocar1(27,34)

colocar1(28,29)
colocar1(28,30)
colocar1(28,31)
colocar1(28,32)
colocar1(28,33)
colocar1(28,34)

colocar1(29,30)
colocar1(29,31)
colocar1(29,32)
colocar1(29,33)
colocar1(29,34)

colocar1(30,31)
colocar1(30,32)
colocar1(30,33)
colocar1(30,34)

colocar1(31,32)
colocar1(31,33)
colocar1(31,34)

colocar1(32,33)
colocar1(32,34)

colocar1(33,34)

colocar1(27,25)
colocar1(30,22)

#quinto com terceiro
colocar1(18,23)

#quinto setimo
colocar1(11,18)

#setimo com terceiro
colocar1(14,22)

#nono com o setimo
colocar1(4,10)
colocar1(6,12)

#nono com o quinto
colocar1(7,19)




#colocar1(0, 8)
#colocar1(0, 15)
#colocar1(0, 20)
#colocar1(0, 27)

#colocar1(1, 9)
#colocar1(1, 16)
#colocar1(1, 21)
#colocar1(1, 28)

#colocar1(2, 10)
#colocar1(2, 17)
#colocar1(2, 22)
#colocar1(2, 29)

#colocar1(3, 11)
#colocar1(3, 18)
#colocar1(3, 23)
#colocar1(3, 30)

#colocar1(4, 12)
#colocar1(4, 19)
#colocar1(4, 24)
#colocar1(4, 31)

#colocar1(5, 13)
#colocar1(5, 25)
#colocar1(5, 32)

#colocar1(6, 14)
#colocar1(6, 26)
#colocar1(6, 33)

#colocar1(7, 34)

#grafo =[(0, 8), (0, 15), (0, 20), (0, 27), (1, 9), (1, 16), (1, 21),(1, 28),
#(2, 10), (2, 17), (2, 22), (2, 29), (3, 11), (3, 18), (3, 23), (3, 30), (4, 12), 
#(4, 19), (4, 24), (4, 31), (5, 13), (5, 25), (5, 32), (6, 14), (6, 26), (6, 33), (7, 34)]

grafo = [(0,1), 
(0,2),
(0,3),
(0,4),
(0,5),
(0,6),
(0,7),
(1,2),
(1,3),
(1,4),
(1,5),
(1,6),
(1,7),
(2,3),
(2,4),
(2,5),
(2,6),
(2,7),
(3,4),
(3,5),
(3,6),
(3,7),
(4,5),
(4,6),
(4,7),
(5,6),
(5,7),
(6,7),
(8,9),
(8,10),
(8,11),
(8,12),
(8,13),
(8,14),
(9,10),
(9,11),
(9,12),
(9,13),
(9,14),
(10,11),
(10,12),
(10,13),
(10,14),
(11,12),
(11,13),
(11,14),
(12,13),
(12,14),
(13,14),
(15,16),
(15,17),
(15,18),
(15,19),
(16,17),
(16,18),
(16,19),
(17,18),
(17,19),
(18,19),
(20,21),
(20,22),
(20,23),
(20,24),
(20,25),
(20,26),
(21,22),
(21,23),
(21,24),
(21,25),
(21,26),
(22,23),
(22,24),
(22,25),
(22,26),
(23,24),
(23,25),
(23,26),
(24,25),
(24,26),
(25,26),
(27,28),
(27,29),
(27,30),
(27,31),
(27,32),
(27,33),
(27,34),
(28,29),
(28,30),
(28,31),
(28,32),
(28,33),
(28,34),
(29,30),
(29,31),
(29,32),
(29,33),
(29,34),
(30,31),
(30,32),
(30,33),
(30,34),
(31,32),
(31,33),
(31,34),
(32,33),
(32,34),
(33,34),
(27,25),
(30,22),
(18,23),
(11,18),
(14,22),
(4,10),
(6,12),
(7,19)]

grafo_colorido = [1,2,3,4,6,5,7,8,1,2,4,6,5,3,7,1,2,3,5,4,1,2,8,6,3,5,4,7,1,2,9,3,4,5,6]

def draw_graph(graph):
    nodes = set([n1 for n1, n2 in graph] + [n2 for n1, n2 in graph])
    G=nx.Graph()
    for node in nodes:
        G.add_node(node)
    for edge in graph:
        G.add_edge(edge[0], edge[1])
    pos = nx.shell_layout(G)

    color_map = []
    
    for i in range (0,len(grafo_colorido)):
    	G.nodes[i]['cor'] = grafo_colorido[i]
    	if(G.nodes[i]['cor'] == 1):
    		color_map.append("blue")
    	elif(G.nodes[i]['cor'] == 2):
    		color_map.append("green")
    	elif(G.nodes[i]['cor'] == 3):
    		color_map.append("yellow")
    	elif(G.nodes[i]['cor'] == 4):
    		color_map.append("purple")
    	elif(G.nodes[i]['cor'] == 5):
    		color_map.append("brown")
    	elif(G.nodes[i]['cor'] == 6):
    		color_map.append("#aaaaaa")
    	elif(G.nodes[i]['cor'] == 7):
    		color_map.append("pink")
    	elif(G.nodes[i]['cor'] == 8):
    		color_map.append("orange")
    	else:
    		color_map.append("red")

	#node_color = color_map
    nx.draw(G, pos,node_color = color_map,with_labels=True)
    plt.show()

draw_graph(grafo)

with open('horario.csv', 'w', newline='') as file:
	write = csv.writer(file, delimiter=' ')
	for row in matriz:
		write.writerow(row)