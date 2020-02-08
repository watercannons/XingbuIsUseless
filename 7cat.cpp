#include <iostream>
#include <fstream> // for ifstream
#include <string>
using namespace std;


char getCharacterFrom7Bits(string s){
  int backtodec = 0;

  if(s[6] == '1') backtodec += 64;
  if(s[5] == '1') backtodec += 32;
  if(s[4] == '1') backtodec += 16;
  if(s[3] == '1') backtodec += 8;
  if(s[2] == '1') backtodec += 4;
  if(s[1] == '1') backtodec += 2;
  if(s[0] == '1') backtodec += 1;
  int ascii = stoi(s);
  return (char)backtodec;
}

int main()
{
  ifstream ifs;
  ifs.open("convertCat.txt");

  string line;
  string stream = "";
	getline(ifs,line);

  for(int i = 0; i < line.length(); i++){
    stream += std::bitset<8>(line[i]).to_string();
  }


  string temp = stream.substr(0,7);
  string res = "";
  while(true){
    string temp = stream.substr(0,7);
    //cout << "Converted Bin: " << temp << endl;
    res += getCharacterFrom7Bits(temp);
    if(stream.length() < 7) break;
    stream = stream.substr(7);
  }

  cout << "res: " << res << endl;
  return 0;
}
