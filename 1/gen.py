from random import *
f = open("in1", "w")
maxf = 20
n = randint(1, maxf)
m = randint(1, maxf)
for i in range(n):
	c = randint(-1, 1)
	while c != -1:
		col = randint(1, m)
		val = randint(-maxf, maxf)
		f.write(str(col) + '\n')
		f.write(str(val) + '\n')
		c = randint(-1, 1)

	f.write("-2\n")
f.write("-1\n")