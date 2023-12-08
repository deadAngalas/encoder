#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<cctype> //toupper
#include<cstring> // strcmp

using namespace std;

void ProgEnd()
{
  system("cls");
  cout << "\n\n\t\t\tCLOSING...\n\n";
  cout <<"              ,---------------------------," << endl;
  cout <<"              |  ---------------------  |"<< endl;
  cout <<"              | |                       | |"<< endl;
  cout <<"              | |                       | |"<< endl;
  cout <<"              | |        Encoder        | |"<< endl;
  cout <<"              | |    Vigenere cipher    | |"<< endl;
  cout <<"              | |                       | |"<< endl;
  cout <<"              |  _____________________  |"<< endl;
  cout <<"              |___________________________|"<< endl;
  cout <<"            ,---_____     []     _______------,"<< endl;
  cout <<"            |      ______________           |"<< endl;
  cout <<"        ___________________________________   | ___"<< endl;
  cout <<"        |                                   |   |    )"<< endl;
  cout <<"        |  _ _ _                 [-------]  |   |   ("<< endl;
  cout <<"        |  o o o                 [-------]  |      _)_"<< endl;
  cout <<"        |__________________________________ |       "<< endl;
  cout <<"    -------------------------------------|      ( )"<< endl;
  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  cout << endl;
}

int IndexFor(char sym)
{
  if(sym == ' ')
  {
    return 26;
  }
  else if(sym == '.')
  {
    return 27;
  }
  else if(sym >= 65 && sym <= 90) // all uppercase letter 'A' - 'Z'
  {
    return sym - 'A';
    // sym = 'A' ->  65 - 65 = [0] index in array alphabet A
    // sym = 'K' ->  75 - 65 = [10] index in array alphabet K
  }
  else return 0;
}

void Encryption(string alphabet, int &fileSize)
{
  string key;
  ifstream t1;

  t1.open("t1.txt");
  if(!t1)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  t1.seekg(0, ios::end); // end file == file size
  fileSize = t1.tellg(); // current position
  t1.seekg(0, ios::beg); // return file beginning

  char content[fileSize + 1];

  t1.read(content, fileSize);
  t1.close();
  content[fileSize] = '\0';

  int k = 0;
  cout << "Your secret message: [";
  while(k < fileSize)
  {
    cout << content[k];
    k++;
  }
  cout << "]\n\n";

  char symC;
  for(char &symC : content)
  {
    symC = toupper(symC);
  }

  bool isOK = false;
  while(isOK == false)
  {
    cout << "Enter key: ";
    getline(cin, key);
    if(key.length() > fileSize)
    {
      cout << "\nKey length must be less or the same as message length!\n\n";
    }
    else isOK = true;
  }

  char symK;
  for(char &symK : key)
  {
    symK = toupper(symK);
  }

  string code;
  for(int i = 0; i < fileSize; i++)
  {
    if(content[i] == ' ' || content[i] == '.')
    {
      code += content[i];
    }
    else
    {
      code += alphabet[(IndexFor(content[i]) + IndexFor(key[i % key.length()])) % alphabet.length()];
      //cout << IndexFor(key[i % key.length()]) << " "; // 0 % 6 = 0 -> key[0] = H -> h index in alphabet = 7 ---- % key.length() lai atkartojas key index
      //cout << IndexFor(content[i]) << " "; // index for message
      //cout << (IndexFor(content[i]) + IndexFor(key[i % key.length()])) % alphabet.length() << " "; // index values after + and %
      //cout << alphabet[(IndexFor(content[i]) + IndexFor(key[i % key.length()])) % alphabet.length()] << " "; // result crypyted text
    }
  }

  ofstream t2;
  t2.open("t2.txt");

  if(!t2)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  t2 << code;
  t2.close();

  system("cls");
  cout << "\nMessage was successfully encrypted! DO NOT FORGET THE KEY!" << endl;
}

void Decryption(string alphabet, int fileSize)
{
  ifstream t1;
  ifstream t2;

  t1.open("t1.txt");
  if(!t1)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  char content[fileSize + 1];

  t1.read(content, fileSize);
  t1.close();
  content[fileSize] = '\0';

  t2.open("t2.txt");
  if(!t2)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  string code, key;
  getline(t2, code);
  t2.close();

  cout << "Received message: " << code << endl;

  cout << "\nEnter key: ";
  getline(cin, key);
  char symK;

  for(char &symK : key)
  {
    symK = toupper(symK);
  }

  string uncode;
  for(int i = 0; i < fileSize; i++)
  {
    if(code[i] == ' ' || code[i] == '.')
    {
      uncode += code[i];
    }
    else
    {
      uncode += alphabet[(IndexFor(code[i]) - IndexFor(key[i % key.length()]) + alphabet.length()) % alphabet.length()];
      // the same scheme as in encryption, but if there is negative number in (IndexFor(code[i]) - IndexFor(key[i % key.length()])
      // -> + alphabet.length() and after % alphabet.length(), if sum is positive + alphabet.length() nothing changes as,
      // for example, 3 + 26 = 29; 29%26 = 3
    }
  }

  ofstream t3;
  t3.open("t3.txt");
  if(!t3)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  t3 << uncode;
  t3.close();
  system("cls");

  char s;
  for(char &s : content)
  {
    s = toupper(s);
  }

  if(content == uncode)
  {
    cout << "\nMessage was successfully decrypted!" << endl;
    cout << "\nSecret message: [" << uncode << "]";
  }
  else cout << "\nMessage was not decrypted! Incorrect key!" << endl;
}

int main()
{
  enum KEYS { num1 = 49, num2 = 50, num3 = 51 , num4 = 52, num5 = 53, num6 = 54, num7 = 55, num8 = 56, num9 = 57 };

  int choice;
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .";
  int fileSize;
  int isEncrypted = 0;

  system("cls");
  cout << "\n\t      Encoder\n\n";
  cout << "\n Author: Vladislav Ryazancev\n Ver: 1.1.1\n Date (start): 08.12.2023 / 11:04\n Date (end): 11.12.2023 / 13:49\n\n";

  do
    {
      system("pause>nul");
      system("cls");
      cout << "\n\t\tMENU\n\n";
      cout << "\n------------- ENCRYPT -------------\n";
      cout << "1. Encrypt file\n";
      cout << "\n------------- DECRYPT -------------\n";
      cout << "2. Decrypt file\n";
      cout << "\n-------------- STOP ---------------\n";
      cout << "3. Stop Program\n\n";
      cout << "-----------------------------------\n\n";

      choice = getch();

      switch(choice)
      {
        case num1:
        {
          isEncrypted++;
          Encryption(alphabet, fileSize);
          break;
        }
        case num2:
        {
          if(isEncrypted > 0)
          {
            Decryption(alphabet, fileSize);
          }
          else cout << "File is not encrypted!\n";
          break;
        }
        case num3:
        {
          cout << "\nProgram is stopped! Goodbye!"; ProgEnd(); break;
          break;
        }
        default: cout << "Incorrect input!\n";
      }
    } while(choice != num3);

  system("pause>nul");
  return 0;
}
