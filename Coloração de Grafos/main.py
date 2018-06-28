from geopy.distance import geodesic
import csv
import click

with open('latlng.csv') as file:
	read = csv.DictReader(file, fieldnames=None)
	data = []
	for row in read:
		data.append(row)
matrix = []
column = read.fieldnames
with click.progressbar(list(data), label="Gerando matriz") as bar:
	for x in enumerate(bar):
		row = []
		for y in enumerate(data):
			col = 0
			if (x != y):
				a = (x[1]["lat"], x[1]["lng"])
				b = (y[1]["lat"], y[1]["lng"])
				col = geodesic(a, b).km
			row.append(col)
		matrix.append(row)

with open('matadj.csv', 'w', newline='') as file:
		write = csv.writer(file, delimiter=',')
		for row in matrix:
			write.writerow(row)