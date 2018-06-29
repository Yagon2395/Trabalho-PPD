import random
tam = input()
print(tam)
matriz = []
for i in range(0,int(tam)):
	row = []
	for j in range(0,int(tam)):
		if(j > i):
			x = random.randint(0,1)
		elif(i ==j):
			x = 0
		else:
			x = matriz[j][i]
		row.append(x)
		if(j != 0):
			print(" ", end = "")
		if(i == j ):
			print(0, end = "")
		else:	
			print(x, end = "")
	matriz.append(row)
	print("\n", end ="")