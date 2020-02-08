#include <iostream>
#include <fstream> // for ifstream
#include <string>
using namespace std;

/*
int convertToBin(int n){

  int i = 0;
  string temp = "";
    while (n > 0) {

        // storing remainder in binary array
        temp += to_string(n % 2);
        n = n / 2;
        i++;
    }

    return i;

}
*/

string reverseString(string s){
  string out = "";
  for(int i = s.size()-1; i >= 0; i--){
    out += s[i];
  }
  return out;
}

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

int main(int argc, char** argv)
{

  ofstream w;
  w.open("arthur_out.txt");
  cout << "argc: " << argc << endl;
  ifstream ifs;

  if(argc == 1) ifs.open("chall2_new2.orc");
  else ifs.open(argv[1]);

  if(!ifs){
    cout << "IFS didn't open correctly" << endl;
    return 0;
  }
  
  string line;
  string stream = "";
	getline(ifs,line);

  for(int i = 0; i < line.length(); i++){
    stream += std::bitset<8>(line[i]).to_string();
  }

  cout << "stream = " << stream << endl;


  // for(int j = 0; j < stream.length(); j++){
  //   string temp = "";
  //   if(j != 0 && j % 7 == 0){
  //     cout << "this is temp: " << temp << endl;
  //     cout << getCharacterFrom7Bits(temp) << endl;
  //     temp = "";
  //   }
  //   else{
  //     temp.append(stream[j]);
  //   }
  // }

  //string temp = stream.substr(0,7);
  //cout << "temp: " << temp << endl;
  string res = "";
  int linenum = 0;
  while(true){
    string temp = stream.substr(0,7);
    //cout << getCharacterFrom7Bits(temp) << " , " << "temp: " << reverseString(temp) << endl;
    cout << linenum << ": " << reverseString(temp)  << endl;
    //cout << endl;
    linenum++;
    w << getCharacterFrom7Bits(temp) << " , " << "temp: " << reverseString(temp) << endl;
    res += getCharacterFrom7Bits(temp);
    if(stream.length() < 7) break;
    stream = stream.substr(7);
  }

  ifs.close();
  
  //cout << "test: " << getCharacterFrom7Bits("1100001") << endl;


  //cout << "res: " << res << endl;
  //w << "res: " << res << endl;
  w.close();

  return 0;
}
