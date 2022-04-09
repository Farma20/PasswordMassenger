#include <string>
#include "cipher.h"


//функция шифрования
std::string encryption(std::string _Text, std::string _Master) //функция шифрования
{
	int j = 0;
	char XOR;

	for (int i = 0; i < _Text.length(); i++)
	{
		if (j == _Master.length()) j = 0;

		XOR = _Text[i] ^ _Master[j];

		if (XOR > 32)
		{
			_Text[i] = _Text[i] ^ _Master[j];
			++j;
		}
		else if('1' <= _Text[i] <= '7')
		{
			_Text[i] += 2;
		}
	}

	return _Text;
}

//функция дешифрования
std::string decryption(std::string _Text, std::string _Master) //функция дешифрования
{
	int j = 0;
	char XOR;

	for (int i = 0; i < _Text.length(); i++)
	{
		if (j == _Master.length()) j = 0;


		XOR = _Text[i] ^ _Master[j];

		if (XOR > 32)
		{
			_Text[i] = _Text[i] ^ _Master[j];
			++j;
		}
		else if ('3' <= _Text[i] <= '9')
		{
			_Text[i] -= 2;
		}
	}
	return _Text;
}
//функция Хеширования
int Hesh(std::string _Boof)
{
	int sum = 0;
	for (int i = 0; i < _Boof.length(); i++)
		sum += _Boof[i];

	return sum * 231;
}
