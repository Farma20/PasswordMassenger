#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // ��� stringstream
#include "cipher.h"


std::ifstream fin;
std::ofstream fout;


int main(int argc, char* argv[]) //int argc, char* argv[]
{
	std::string Config = "C:\\Users\\iurba\\Desktop\\��������\\�����\\Password Manager\\Password Manager\\password.txt";
	std::string EnCom; //������ ������
	std::string Text; // ������ ��� ������ ������������
	 //������ � ����������� ��������� ������
	for (int i = 1; i < argc; i++)
	{
		std::string S = argv[i];

		if (S == "--config")
			Config = argv[i+1];

		if (S == "help")
			EnCom = "help";

		if (S == "get")
		{
			EnCom = "get";
			Text = argv[i + 1];
		}

		if (S == "add")
		{
			EnCom = "add";
			Text = argv[i + 1];
		}

		if (S == "del")
		{
			EnCom = "del";
			Text = argv[i + 1];
		}

		if (S == "chk")
		{
			EnCom = "chk";
			Text = argv[i + 1];
		}
	}



	std::string Boof = "";

	fin.open(Config);
	//���� ������ ������ ���, �� ������� �����
	if (fin.peek() == EOF)
	{
		std::cout << "Welcome! Enter the new master password: ";
		std::cin >> Boof;

		fout.open(Config);
		fout << Hesh(Boof) << std::endl;
		fout.close();

		std::cout << "Master password saved" << std::endl;
	}
	fin.close();


	fin.open(Config);

	std::cout << "Enter the master password" << std::endl;
	std::string Master;
	std::cin >> Master;
	std::string File_Mast;

	std::getline(fin, File_Mast); //���������� � ������ ������ ������

	int int_File_Mast;
	std::stringstream convert(File_Mast);
	convert >> int_File_Mast; // ��������� ������ ������ �� ������ � �����


	//���� �������� ������ ������ �� �����, �� ��������� �����������
	if (Hesh(Master) != int_File_Mast)
	{
		std::cout << "Wrong master password";
		return 0;
	}
	fin.close();
    

	if (EnCom == "")
	{
		std::cout << "Welcome to password manager\n help - List available command / exit, q, quit - to finish the application" << std::endl;
		std::cin >> EnCom;
	}

	int g = 0;//���� �� �������� � ����������� ��� ������, �� �������� 0
	//�������� ����. �� ����� �������� �� ��� ���, ���� ������������ �� ������ ������� ������
	while (EnCom != "exit" && EnCom != "q" && EnCom != "quit")
	{

		//������� help ������� ��� ��������� �������
		if (EnCom == "help")
		{
			std::cout << "Available command: " << std::endl;
			std::cout << "master - changing master password\n";
			std::cout << "add - add new password\n";
			std::cout << "get - get your password\n";
			std::cout << "del - delete your password\n";
			std::cout << "chk - checking for a password" << std::endl;

		}

		//������� master ������ ����� ������ 
		else if (EnCom == "master")
		{
			std::cout << "Enter the current master password: ";
			std::cin >> Text;

			fin.open(Config);

			std::getline(fin, Boof); //���������� � ������ ������ ������

			std::stringstream convert(Boof);
			convert >> int_File_Mast; // ��������� ������ ������ �� ������ � �����

			std::string All_file = "";

			//���� ������ ������, �� ������ ���
			if (Hesh(Text) == int_File_Mast)
			{
				std::cout << "Enter the new master password: ";
				std::cin >> Boof;

				std::stringstream hesh; //��������� ����� � ������
				hesh << Hesh(Boof);
				std::string B = hesh.str();

				All_file += B;


				while (!fin.eof())
				{
					All_file += "\n";

					getline(fin, Boof);

					Boof = decryption(Boof, File_Mast);

					Boof = encryption(Boof, B);

					All_file += Boof;
				}

				fout.open(Config);
				fout << All_file;
				fout.close();

				std::cout << "New master password saved" << std::endl;

				File_Mast = B;
			}

			//���� �������� ������ ������ �� �����, �� ������� �� ������� master
			else
				std::cout << "Wrong master password" << std::endl;

			fin.close();

		}

		//������� get �������� ������ ������ � ����� ������
		else if (EnCom == "get")
		{
			if (Text == "")
			{
				g = 1;
				std::cout << "Enter the site name: ";
				std::cin >> Boof;
				Text = Boof + ":";
				std::cout << "Enter your login: ";
				std::cin >> Boof;
				Text += Boof + ":";
			}

			std::string CorStr = "";
			std::string password = "";
			fin.open(Config);

			bool flag = 0;

			while (!fin.eof()) //���� ����� ����������� �� ������� ����� ����� ��� �� ��������� break;
			{
				std::getline(fin, CorStr); //������ ������ �� �����

				CorStr = decryption(CorStr, File_Mast);

				int f = CorStr.find(Text); // ���� ������ � ������ ����������, �� ������� ������ ������� ����� ����� -1;
				if (f >= 0) //������� ���� ����� ����������
				{
					flag = 1;
					for (int i = Text.length(); i < CorStr.length(); i++)
						password += CorStr[i];
				}
			}
			fin.close();

			if (flag == 1)
			{
				std::cout << password << std::endl;
			}
			else
				std::cout << "Password not find" << std::endl;

			if (g == 0)
				return 0;
		}

		//������� add ��������� ����� ������
		else if (EnCom == "add")
		{
			if(Text == "")
			{
				g = 1;
				std::cout << "Enter the site name: ";
				std::cin >> Boof;
				Text = Boof + ":";
				std::cout << "Enter your login: ";
				std::cin >> Boof;
				Text += Boof + ":";
				std::cout << "Enter your password: ";
				std::cin >> Boof;
				Text += Boof;
			}
			Text = encryption(Text, File_Mast);

			fout.open(Config, std::ios_base::app);

			fout << Text << std::endl;
			std::cout << "Success!" << std::endl;
			fout.close();

			if (g == 0)
				return 0;
		}

		//������� del ������� ������
		else if (EnCom == "del")
		{
			if(Text == "")
			{
				g = 1;
				std::cout << "Enter the site name: ";
				std::cin >> Boof;
				Text += Boof + ":";
				std::cout << "Enter your login: ";
				std::cin >> Boof;
				Text += Boof + ":";
			}
			Text = encryption(Text, File_Mast);
			std::string All_file = "";

			fin.open(Config);

			getline(fin, Boof); //��������� ������ ������, ��� ��� ��� ������ ������
			All_file += Boof;

			int Flag;
			while (!fin.eof())//���������� �� ����� �����, �������� ��� � All_file ��� ��������� ������
			{
				getline(fin, Boof);

				Flag = Boof.find(Text);
				if (Flag == -1)
				{
					All_file += "\n";
					All_file += Boof;
				}
			}
			fin.close();

			fout.open(Config);
			fout << All_file;
			fout.close();
			

			std::cout << "Passwor deleted" << std::endl;
			
			if (g == 0)
				return 0;
		}

		//������� chk ��������� ������� ������������� ������
		else if (EnCom == "chk")
		{
			if(Text == "")
			{
				g = 1;
				std::cout << "Enter the site name: ";
				std::cin >> Boof;
				Text += Boof + ":";
				std::cout << "Enter your login: ";
				std::cin >> Boof;
				Text += Boof + ":";
			}
			Text = encryption(Text, File_Mast);

			std::string CorStr = "";
			std::string password = "";
			fin.open(Config);

			int flag = -1;
			while (!fin.eof()) //���� ����� ����������� �� ������� ����� ����� ��� �� ��������� break;
			{
				std::getline(fin, CorStr); //������ ������ �� �����
				flag = CorStr.find(Text); //����� � ���� ������ ��������� ������ � ������(���� ���������� ���, �� ������� -1)

				if (flag > -1) //������� ���� � ������� ���� ����������
				{
					std::cout << "Paasword exists!" << std::endl;
					break;
				}
			}

			if (flag == -1)
				std::cout << "Password does not exists" << std::endl;

			fin.close();

			if (g == 0)
				return 0;
		}

		//���� ������� �� ���������� ������� �������������� ��������
		else
			std::cout << "Uncnown command. Try again" << std::endl;

		std::cin >> EnCom;
		Text = "";
		Boof = "";
	}

	std::cout << "GoodBye" << std::endl;
}

