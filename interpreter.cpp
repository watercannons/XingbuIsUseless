#include <iostream>
#include <fstream> // for ifstream
#include <string>
#include <vector>
#include <math.h>
using namespace std;

#define Byte7 char
#define Word28 int
#define Text7 string

enum Bool : Byte7 {FALSE,TRUE};

class noMoreByte7s{};

unsigned int MI = 0;
vector<string> F;

enum FileType : Byte7 { EXE = 0, OBJ = 1 };

struct Permissions {
    Word28 word28;
    Bool executable() { return (Bool)((word28>>4)&1); }
    Bool writeable() { return (Bool)((word28>>5)&1); }
    Bool readable() { return (Bool)((word28>>6)&1); }
};
enum SymbolType : Byte7 { EXTERN, FUNC };
struct Symbol {
    Text7 name;
    SymbolType type;
    Bool isDefined;
    Word28 section;
    Word28 offset;
};
struct SymbolTable {
    Word28 numEntries;
    Symbol * symbols;
};
enum SegmentType : Byte7 {
    PROGBITS,
    NOTE,
};
struct Section {
    Permissions permissions;
    Word28 offset;
    Text7 name;
    Word28 size;
};
struct SectionTable {
    Word28 numEntries;
    Section * section;
};
struct Segment {
    Text7 name;
    Word28 offset;
    Word28 base;
    Word28 size;
    Permissions permissions;
    SegmentType type;
};
struct SegmentTable {
    Word28 numEntries;
    Segment * segment;
};
struct Relocation {
    Word28 offset;
    Word28 section;
    Text7 symbol;
    Word28 plus;
};
struct RelocationTable {
    Word28 numEntries;
    Relocation * relocations;
};

int Int28(Word28 str);
char getCharacterFrom7Bits(string s);
int getWord28();
string getText7();
char getByte7();
Permissions getPermissions();


char getCharacterFrom7Bits(string s){
  int backtodec = 0;

//   if(s[6] == '1') backtodec += 64;
//   if(s[5] == '1') backtodec += 32;
//   if(s[4] == '1') backtodec += 16;
//   if(s[3] == '1') backtodec += 8;
//   if(s[2] == '1') backtodec += 4;
//   if(s[1] == '1') backtodec += 2;
//   if(s[0] == '1') backtodec += 1;

  if(s[6] == '1') backtodec += 1;
  if(s[5] == '1') backtodec += 2;
  if(s[4] == '1') backtodec += 4;
  if(s[3] == '1') backtodec += 8;
  if(s[2] == '1') backtodec += 16;
  if(s[1] == '1') backtodec += 32;
  if(s[0] == '1') backtodec += 64;
  int ascii = stoi(s);
  return (char)backtodec;
}


int getWord28() {
    int out = 0;
    for (unsigned char i = 0; i < 4; i++)
        out = (out >> 7) | getByte7()<<21;
    return out;
}

string getText7() {
    string out = "";
    // cout << "in get7" << endl;
    while (F[MI]!="0000000"){
       out += getByte7();
    }
    MI++;
    return out;
}
char getByte7() {
    if ( MI >= F.size() ) throw noMoreByte7s();
    char c =  getCharacterFrom7Bits(F[MI++]);
    return c;
}
Permissions getPermissions() {
    Permissions p;
    p.word28 = getByte7();
    cout << "Permissions: " << p.word28 << endl;
    return p;
}

Symbol getSymbol() {
    Symbol s;

    s.name = getText7();
    cout << "   Symbol Name: " << s.name << endl;
    s.type = (SymbolType)getByte7();
    cout << "   Symbol Type: " << s.type << endl;
    s.isDefined = (Bool)getByte7();
    cout << "   Symbol Defined: " << s.isDefined << endl;
    if (s.isDefined) {
        s.section = getWord28();
        cout << "       Symbol Section: " << s.section << endl;
        s.offset = getWord28();
        cout << "       Symbol Offset: " << s.offset << endl;
    }

    return s;

}

SymbolTable getSymbolTable() {
    SymbolTable st;
    st.numEntries = getWord28();
    cout << "SymbolTable numEntries: " <<  st.numEntries << endl;

    st.symbols = new Symbol[st.numEntries];
    for (Word28 i = 0; i < st.numEntries; i++)
        st.symbols[i] = Symbol(getSymbol());

    return st;
}

Relocation getRelocation() {
    Relocation r;

    r.offset = getWord28();
    cout << "   Relocation Offset: " << r.offset << endl;
    r.section = getWord28();
    cout << "   Relocation selection: " << r.section << endl;
    r.symbol = getText7();
    cout << "   Relocation symbol: " << r.symbol << endl;
    r.plus = getWord28();
    cout << "   Relocation plus: " << r.plus << endl;
    return r;

}

RelocationTable getRelocationTable() {
    RelocationTable rt;

    rt.numEntries = getWord28();
    cout << "Relocation Table Entries: " << rt.numEntries << endl;

    for (Word28 i = 0; i < rt.numEntries; i++)
        rt.relocations[i] = Relocation( getRelocation() );

    return rt;
}
Section getSection() {
    Section s;
    cout << "   Section getPermissions:    ";
    s.permissions =  getPermissions();
    s.offset = getWord28();
    cout << "   Section offset: " << s.offset << endl;
    s.name = getText7();
    cout << "   Section name: " << s.name << endl;
    s.size = getWord28();
    cout << "   Section size: " << s.size << endl;
    return s;
}
SectionTable getSectionTable() {
    SectionTable st;

    st.numEntries = getWord28();
    cout << "SectionTable numEntries: " << st.numEntries << endl;
    st.section = new Section[ st.numEntries ];
    for (Word28 i = 0; i < st.numEntries; i++)
        st.section[i] = Section(  getSection() );

    return st;
}
Segment getSegment() {
    Segment s;

    s.name = getText7();
    cout << "   Segment numEntries: " << s.name << endl;
    s.offset  = getWord28();
    cout << "   Segment offset: " << s.offset << endl;
    s.base = getWord28();
    cout << "   Segment base: " << s.base << endl;
    s.size = getWord28();
    cout << "   Segment size: " << s.size << endl;

    cout << "   Segment getPermissions:    ";
    s.permissions = getPermissions();
    s.type = (SegmentType)getByte7();
    cout << "   Segment type: " << s.type << endl;

    return s;
}
SegmentTable getSegmentTable() {
    SegmentTable st;

    st.numEntries = getWord28();
    cout << "SegmentTable numEntries: " << st.numEntries << endl;
    st.segment = new Segment[ st.numEntries ];
    for (Word28 i = 0; i < st.numEntries; i++)
        st.segment[i] = Segment(  getSegment() );

    return st;
}

int main(){
    ifstream ifs;
    ifs.open("clean2.txt");
    string line;
    //cout << "ethan1" << endl;
    while (getline(ifs,line)) {
        if(line == "---") break;
        F.push_back(line);
        //cout << "f.size: " << F.size() << endl;
    }
    //cout << "ethan2" << endl;



    Text7 header = getText7();
    cout << "Header: " <<header << endl;
    FileType type = (FileType)getByte7();
    cout << "FileType: "<< (FileType)type << endl;
    Bool hasEntryPoint = (Bool)getByte7();
    cout << "hasEntryPoint: " << (int)hasEntryPoint << endl;
    if (hasEntryPoint)
    {
        Word28 entryPoint = 0;
        entryPoint = getWord28();
        cout << "EntryPoint: " << entryPoint << endl;
    }
        

    SymbolTable symbolTable( getSymbolTable() );

    RelocationTable relocationTable = RelocationTable( getRelocationTable() );

    // SectionTable sectionTable = SectionTable( getSectionTable() );

    // SegmentTable segmentTable = SegmentTable( getSegmentTable() );

    // Byte7 * contents = new Byte7[ F.size() - MI ];
    // // try { for (size_t i = 0; true; i++) contents[i] = getByte7(); }
    // for (size_t i = 0; true; i++) {
    //     try { contents[i] = getByte7(); }
    //     catch ( noMoreByte7s e ) {break;}
    // }
    

    cout << "ethan rox!!!!!!\n"; 

    return 0;
    
}