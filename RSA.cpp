#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int generate_key(int seed);
bool prime_test(int number);
long long get_value(int a, long long m, long long number);
int encrypt_message(string str);
// long long exponent(long long base, long long exponent);

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
			ifstream inFile(argv[2]);
			string key_counter_str = "-1";
			int key_counter;

			if(inFile)
				{
					getline(inFile, key_counter_str);
				cout << key_counter_str << "ADSFASDFASDF" << endl;
			}
			
			inFile.close();
			key_counter = std::stoi(key_counter_str) + 1;

			ofstream out_key(argv[2]);
			out_key << key_counter << endl;
			out_key.close();

			long long public_key = 0;
			long long private_key = 0;

			// Create random number generator
			uniform_int_distribution<long long> u(100000000, 2000000000);
			random_device rd;
			// Mersenee twister engine
			mt19937_64 gen(rd());

			// Random seed for public key
			long long public_seed = u(gen);
			cout << "Public seed: " << public_seed << endl;

			// Random seed for private key
			long long private_seed = u(gen);
			cout << "Public seed: " << private_seed << endl;

			public_key = generate_key(public_seed);
			private_key = generate_key(private_seed);

			ofstream outFile ("key" + std::to_string(key_counter) + ".txt");

			cout << "public key: " << public_key << endl;
			cout << "private key: " << private_key << endl;

			outFile << public_key << endl << private_key << endl;
			outFile.close();

			break;
		}
		case 1:
		{
			// string test_word = "Hasjfads;fasjflasdjf;ladsfj;fadsfdasfadsfadsfadsfadsfadsfadsfadsfas;lfkjads;fkljads;flajd;lfadj";
			// size_t hashed_word = std::hash<std::string>{}(test_word);
			// cout << "the hash is " << hashed_word << endl;
			// string something =  std::hash<std:s:tring>{}(hashed_word);
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

int generate_key(int seed)
{
	//  25326001 seed for Miller-Rabin primality test
	int number = seed;
	while(true)
	{
		// cout << "lol" << endl;
		if(prime_test(number))
			break;
		number++;
	}
	// if(prime_test(number))
	// 	return number;
	return number;
}

// bool prime_test(int number)
// {
// 	if(number%2 == 0)
// 		return false;

// 	long long a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

// 	// finding n-1 = 2^k * m
// 	int divider = 2,
// 		temp = 1,
// 		n = number-1,
// 		k = 1,
// 		m = 1;

// 	temp = n/divider;

// 	while((temp * divider) == n)
// 	{
// 		m = temp;
// 		divider *= 2;
// 		k++;
// 		temp = n/divider;
// 	}
// 	k--;
// 	cout << "k = " << k << "   m = " << m << endl;
// 	// compute b_0 = a^m mod n or b_0^2 mod n if needed
// 	for(int i=0; i<9; i++)
// 	{
// 		long long b_0 = exponent(a[i], (long long) m) % number;
// 		cout << "b_0 = " << b_0;
// 		if(b_0 == 1 || b_0 == -1)
// 			continue;
// 		long long b_1 = exponent(b_0, 2) % 53 - number;
// 		cout << "   b_1 = "<< b_1 << endl;
// 		if(b_1 == 1)
// 			return false;
// 		else
// 			continue;
// 	}

// 	return true;
// }

// long long exponent(long long base, long long exponent)
// {
// 	long long value = 1;
// 	for(long long i=0; i<exponent; i++)
// 	{
// 		value *= base;
// 	}
// 	// cout << "the value   " << (int) value << endl;
// 	return value;
// }

bool prime_test(int number)
{

	long long primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	if(number % 2 == 0)
		return false;

	int k = 0;
	long long m = number-1;

	while(!(m&1))
	{
		cout << k << "  ";
		cout << m << endl;
		k++;
		m /= 2;
	}

	for(int i=0; i<9; i++)
	{
		int a = primes[i];
		bool composite = true;
		long long exp_val = get_value(a, m, number);
		if(exp_val==1 || exp_val==number-1)
			continue;
		for(int r=0; r<k-1; r++)
		{
			__int128_t temp = exp_val;
			temp = temp * temp % number;
			exp_val = temp;
			if(exp_val == number-1)
			{
				composite = false;
				break;
			}
		}
		if(composite)
			return false;
	}
	return true;
}

// The actual test for primality
long long get_value(int a, long long m, long long number)
{
	// cout << "hahah" << endl;
    if(m == 0)
    	return 1LL;

    if(m & 1)
    {
    	__int128_t temp = get_value(a, m-1, number);
    	return temp * a % number;
    }

    __int128_t temp = get_value(a, m/2, number);
    temp = temp * temp % number;
    return temp;
}
