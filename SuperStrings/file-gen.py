hello1 = open("hello1.txt", "w")
for i in range(5000):
	hello1.write("hellohellohellohihi\n")
hello1.close()

hello2 = open("hello2.txt", "w")
for i in range(5000):
	hello2.write("hellohellohellohiha\n")
hello2.close()