abel: configuration_1.c
	gcc -o configuration_1 configuration_1.c

baker: configuration_2.c
	gcc -o configuration_2 configuration_2.c

random: configuration_3.c
	gcc -o configuration_3 configuration_3.c

clean:
	rm -f configuration_1 configuration_2 configuration_3

all: clean abel baker random