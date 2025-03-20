#include<stdio.h>
#include<string.h>

int checkPrivacy(int firstByteDecimal, int secondByteDecimal);

char checkClass(int firstByteDecimal, int secondByteDecimal, int thirdByteDecimal, int fourthByteDecimal);

void help();

int main(int argc, char *argv[]) {

	if (argc != 2) {
		help();
		return 1;
	}
	char addr[16] = "999.999.999.999";
	
	// copy command line argument to addr
	strcpy(addr, argv[1]);

	int firstByteDecimal = -1;
	int secondByteDecimal = -1;
	// I might do something interesting with these two at some point
	int thirdByteDecimal = -1;
	int fourthByteDecimal = -1;

	// parse the bytes
	sscanf(addr, "%d.%d.%d.%d", &firstByteDecimal, &secondByteDecimal, &thirdByteDecimal, &fourthByteDecimal);

	// if a byte entered by the user is negative, or the users doesn't enter a proper one, stop
	if (firstByteDecimal < 0 || secondByteDecimal < 0 || thirdByteDecimal < 0 || fourthByteDecimal < 0) {
		printf("Bad address\n");
		help();
		return 1;
	}

	// check class
	char class = (checkClass(firstByteDecimal, secondByteDecimal, thirdByteDecimal, fourthByteDecimal));

	// print class of address
	if (class == 'f') {
		printf("Bad class\n");
		help();
		return 1;
	} else {
		printf("Class : %c\n", class);
	}

	// check private or public and print it
	if (checkPrivacy(firstByteDecimal, secondByteDecimal) == 1) {
		printf("Is private\n");
	} 
	else {
		printf("Is public\n");
	}

	return 0;
}

char checkClass(int firstByteDecimal, int secondByteDecimal, int thirdByteDecimal, int fourthByteDecimal) {

	if (firstByteDecimal < 128) {
		return 'a';
	} else if (firstByteDecimal < 192) {
		return 'b';
	} else if (firstByteDecimal < 224) {
		return 'c';
	} else if (firstByteDecimal < 240) {
		return 'd';
	} else if (firstByteDecimal < 255) {
		return 'e';
	}
	// class f doesn't exist, this default is meant to signal a bad ip address ( >255 )
	return 'f';
}

int checkPrivacy(int firstByteDecimal, int secondByteDecimal) {
	int privacy = 0;
	// check class a
	if (firstByteDecimal == 10) {
		privacy = 1;
	}
	// check class b
	if (firstByteDecimal == 172 && secondByteDecimal > 15 && secondByteDecimal < 32) {
		privacy = 1;
	}
	// check class c
	if (firstByteDecimal == 192 && secondByteDecimal == 168) {
		privacy = 1;
	}
	return privacy;
}

void help() {
	printf("Usage : ipinfo [ipv4/24 address]\n");
}
