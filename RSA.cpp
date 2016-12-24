#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <random>

using namespace std;

int generate_key(int seed);
int encrypt_message(string str);

int main(int argc, char *argv[])
{
	// Program takes in an integer argument
	// 0: Generate a public key and private key
	// 1: encrypt a message, with the public key and private key as the input. public key and private key in a text file
	// 2: decrypt a message, with the encrypted message, public key, and the private key as input. the last three in a text file
	int program = *argv[1] - '0';

	switch(program)
	{
		// Generate public and private key
		case 0:
		{
			// Create random number generator
			uniform_int_distribution<int> u(100000000, 2000000000);
			random_device rd;
			// Mersenee twister engine
			mt19937_64 gen(rd());

			// Random seed for public key
			unsigned int seed_for_public = u(gen);
			cout << "Public seed: " << seed_for_public << endl;

			// Random seed for private key
			unsigned int seed_for_private = u(gen);
			cout << "Public seed: " << seed_for_private << endl;

			break;
		}
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		default:
			cout << "Invalid arguments. Please input 0, 1, and 2, and the corresponding valid inputs" << endl;
	}

	return 0;
}
	

