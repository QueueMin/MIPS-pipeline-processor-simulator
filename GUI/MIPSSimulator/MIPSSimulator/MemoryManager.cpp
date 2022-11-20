#ifndef FILEREADER_INCLUDED
#define FILEREADER_INCLUDED
#include <iostream>
#include <fstream>
#include <bitset>
#include <map>
#include <vector>
#include <string>

#include "Elements.cpp"
#include "Translate.cpp"

struct CheckList
{
  std::string oper;
  std::string target;
  int num;
};

// fileReader class의 객체는 instruction 파일을 읽어오고, 해당 파일의 정보들을
// 메모리에 저장할 데이터와 수행할 operation등으로 분류하여 field에 저장.
// 
class MemoryManager{
  private:
    std::map<std::string, std::bitset<32>> Mem;
    std::map<std::string, std::bitset<32>> Stack;
    std::map<std::string, std::bitset<32>> Program;
    std::map<std::string, std::bitset<32>> WordsAddress;
    std::map<std::string, int> Words;
    std::map<std::string, int> JumpIdx; // index 0 에서부터의 거리

    std::bitset<32> startPC = hexToBin("0x00400024");
    std::bitset<32> startSP = hexToBin("0x7ffffe40");
    std::bitset<32> startGP = hexToBin("0x10008000");
    std::bitset<32> startData;

    int fileLength = -1;

    // instruction이 대상으로 하는 register의 번호를 정수로 return
    int registerNumber(std::string registerNum){
      if (registerNum == "$0" || registerNum == "$zero")
        return 0;
      if (registerNum == "$1" || registerNum == "$at")
        return 1;
      if (registerNum == "$2" || registerNum == "$v0")
        return 2;
      if (registerNum == "$3" || registerNum == "$v1")
        return 3;
      if (registerNum == "$4" || registerNum == "$a0")
        return 4;
      if (registerNum == "$5" || registerNum == "$a1")
        return 5;
      if (registerNum == "$6" || registerNum == "$a2")
        return 6;
      if (registerNum == "$7" || registerNum == "$a3")
        return 7;
      if (registerNum == "$8" || registerNum == "$t0")
        return 8;
      if (registerNum == "$9" || registerNum == "$t1")
        return 9;
      if (registerNum == "$10" || registerNum == "$t2")
        return 10;
      if (registerNum == "$11" || registerNum == "$t3")
        return 11;
      if (registerNum == "$12" || registerNum == "$t4")
        return 12;
      if (registerNum == "$13" || registerNum == "$t5")
        return 13;
      if (registerNum == "$14" || registerNum == "$t6")
        return 14;
      if (registerNum == "$15" || registerNum == "$t7")
        return 15;
      if (registerNum == "$16" || registerNum == "$s0")
        return 16;
      if (registerNum == "$17" || registerNum == "$s1")
        return 17;
      if (registerNum == "$18" || registerNum == "$s2")
        return 18;
      if (registerNum == "$19" || registerNum == "$s3")
        return 19;
      if (registerNum == "$20" || registerNum == "$s4")
        return 20;
      if (registerNum == "$21" || registerNum == "$s5")
        return 21;
      if (registerNum == "$22" || registerNum == "$s6")
        return 22;
      if (registerNum == "$23" || registerNum == "$s7")
        return 23;
      if (registerNum == "$24" || registerNum == "$t8")
        return 24;
      if (registerNum == "$25" || registerNum == "$t9")
        return 25;
      if (registerNum == "$26" || registerNum == "$k0")
        return 26;
      if (registerNum == "$27" || registerNum == "$k1")
        return 27;
      if (registerNum == "$28" || registerNum == "$gp")
        return 28;
      if (registerNum == "$29" || registerNum == "$sp")
        return 29;
      if (registerNum == "$30" || registerNum == "$fp")
        return 30;
      if (registerNum == "$31" || registerNum == "$ra")
        return 31;
    }

    // j format encode를 수행하여 32비트의 bitset으로 정리 후 return 
    std::bitset<32> encode_J(std::string oper, std::string con){
      std::bitset<6> opcode;
      std::bitset<26> JumpAddress;
      std::bitset<32> returnBitset;

      // opcode를 최종 return할 bitset에 저장
      opcode = OP_J;
      for (int i = 0; i < 6; i++)
        returnBitset[i + 26] = opcode[i];

      // JumpIdx map에서 현재 jump하려는 주소가 있는지 체크.
      if (JumpIdx.find(con) != JumpIdx.end()){
        JumpAddress = (binToDec(startPC) / 4) + JumpIdx[con];
      }

      // jumpIdx에 정보가 없을시 0으로 초기화, 이후에 순회하며 재정의
      for (int i = 0; i < 26; i++)
        returnBitset[i] = JumpAddress[i];
      return returnBitset;
    }
    
    // i format encode를 수행하여 32비트의 bitset으로 정리 후 return
    std::bitset<32> encode_I(std::string oper, std::string rt, std::string con, std::string rs = ""){
      std::string tmp = "";
      std::bitset<5> regNum;
      std::bitset<6> opcode;
      std::bitset<16> ival;
      std::bitset<32> returnBitset;

      // 수행할 operation을 opcode로 변환
      if (oper == "lw")
        opcode = OP_LW;
      else if (oper == "sw")
        opcode = OP_SW;
      else if (oper == "beq")
        opcode = OP_BEQ;

      // 변환된 opcode를 최종
      for (int i = 0; i < 6; i++)
        returnBitset[i + 26] = opcode[i];

      // rt
      for (int i = 0; i < rt.length(); i++)
      {
        if (rt[i] == ',')
        {
          rt.replace(rt.find(","), 1, "");
          break;
        }
      }

      regNum = registerNumber(rt);
      for (int i = 0; i < 5; i++)
        returnBitset[i + 16] = regNum[i];


      if (oper == "beq")
      {
        // rs
        for (int i = 0; i < rs.length(); i++)
        {
          if (rs[i] == ',')
          {
            rs.replace(rs.find(","), 1, "");
            break;
          }
        }
        regNum = registerNumber(rs);
        for (int i = 0; i < 5; i++)
          returnBitset[i + 21] = regNum[i];

        // offset은 파일 두번째 순회시에 삽입
      }
      else // con을 rs와 상수로 분리 및 저장
      {
        tmp = "";
        for (int i = 0; i < con.length(); i++)
        {
          if (con[i] == '(')
            break;
          tmp += con[i];
        }
        ival = std::stoi(tmp);
        for (int i = 0; i < 16; i++)
          returnBitset[i] = ival[i];

        // rs
        rs = con.substr(tmp.length(), con.length() - 1);
        rs.replace(rs.find("("), 1, "");
        rs.replace(rs.find(")"), 1, "");
        regNum = registerNumber(rs);
        for (int i = 0; i < 5; i++)
          returnBitset[i + 21] = regNum[i];
      }
      return returnBitset;
    }

    // r format encode를 수행하여 32비트의 bitset으로 정리 후 return
    std::bitset<32> encode_R(std::string oper, std::string rd, std::string rs, std::string rt){
      std::bitset<5> tmp5bit;
      std::bitset<6> tmp6bit;
      std::bitset<32> returnBitset;
      // opcode
      if (oper == "add")
      {
        tmp6bit = OP_ADD;
        for (int i = 0; i < 6; i++)
          returnBitset[i + 26] = tmp6bit[i];
        tmp6bit = FUNCT_ADD;
      }
      else if (oper == "sub")
      {
        tmp6bit = OP_SUB;
        for (int i = 0; i < 6; i++)
          returnBitset[i + 26] = tmp6bit[i];
        tmp6bit = FUNCT_SUB;
      }
      else if (oper == "and")
      {
        tmp6bit = OP_AND;
        for (int i = 0; i < 6; i++)
          returnBitset[i + 26] = tmp6bit[i];
        tmp6bit = FUNCT_AND;
      }
      else if (oper == "or")
      {
        tmp6bit = OP_OR;
        for (int i = 0; i < 6; i++)
          returnBitset[i + 26] = tmp6bit[i];
        tmp6bit = FUNCT_OR;
      }
      else if (oper == "slt")
      {
        tmp6bit = OP_SLT;
        for (int i = 0; i < 6; i++)
          returnBitset[i + 26] = tmp6bit[i];
        tmp6bit = FUNCT_SLT;
      }

      // shamt
      tmp5bit = 0;
      for (int i = 0; i < 5; i++)
        returnBitset[i + 6] = tmp5bit[i];

      // function
      for (int i = 0; i < 6; i++)
        returnBitset[i] = tmp6bit[i];

      // rd
      for (int i = 0; i < rd.length(); i++)
      {
        if (rd[i] == ',')
        {
          rd.replace(rd.find(","), 1, "");
          break;
        }
      }
      tmp5bit = registerNumber(rd);
      for (int i = 0; i < 5; i++)
        returnBitset[i + 11] = tmp5bit[i];

      // rt
      tmp5bit = registerNumber(rt);
      for (int i = 0; i < 5; i++)
        returnBitset[i + 16] = tmp5bit[i];

      // rs
      for (int i = 0; i < rs.length(); i++)
      {
        if (rs[i] == ',')
        {
          rs.replace(rs.find(","), 1, "");
          break;
        }
      }
      tmp5bit = registerNumber(rs);
      for (int i = 0; i < 5; i++)
        returnBitset[i + 21] = tmp5bit[i];

      return returnBitset;
    }

  public:

    // string type의 파일명을 받아 실질적으로 fileReader 객체의 필드를
    // 해당 파일을 읽어 초기화. 앞서 정의한 format 별 encode 함수들을 활용
    void fileRead(std::string fileName){
      
      // 기존에 읽었던 파일로부터의 정보들을 삭제.
      Mem.clear();
      Stack.clear();
      Program.clear();
      Words.clear();
      JumpIdx.clear();
      int idx = -1;
      fileLength = -1; // add fileLength reset


      std::vector<CheckList> check;

      std::ifstream fin(fileName);
      if (!fin)
      {
        std::cout << "file is NOT exist\n";
        return;
      }
      std::string oper, rs, rt, rd, con, tmp;
      while (!fin.eof())
      {
        oper = "";
        fin >> oper >> rd;
        if (oper == "")
          break;
        if (rd == ":") // JumpIdx 저장 beq 이동시 사용
        {
          JumpIdx.insert({oper, idx + 1});
          fin >> oper >> rd;
        }
        if (oper == ".data")
        {
          int Wcnt = 0;
          startData = hexToBin(rd);
          fin >> oper;
          if (oper != ".word")
          {
            for (int i = 0; i < oper.length(); i++)
            {
              if (oper[i] == ':')
              {
                oper.replace(oper.find(":"), 1, "");
                break;
              }
            }

            WordsAddress.insert({oper, startData});
            fin >> oper;
          }
          fin >> rd;
          while (oper == ".word")
          {
            Words.insert({decToHex(binToDec(startData) + Wcnt++ * 4), stoi(rd)});
            fin >> oper >> rd;
          }
        }
        if (oper == ".text")
        {
          startPC = hexToBin(rd);
        }
        if (oper == ".globl")
        {
          // 항상 main에서 시작할것이기 때문에 생략
        }
        else if (oper == "j") // Jformat
        {
          idx++;
          Program.insert({decToHex(binToDec(startPC) + idx * 4), encode_J(oper, rd)});
          CheckList elem;
          elem.oper = oper;
          elem.target = rd;
          elem.num = idx;
          check.push_back(elem);
        }
        else if (oper == "lw" || oper == "sw" || oper == "beq") // Iformat
        {
          fin >> con;
          if (oper == "beq")
          {
            rt = con;
            fin >> con;
            idx++;
            Program.insert({decToHex(binToDec(startPC) + idx * 4), encode_I(oper, rt, con, rd)}); // 디폴트 입력때문에 순서를 바꿈
            CheckList elem;
            elem.oper = oper;
            elem.target = con;
            elem.num = idx;
            check.push_back(elem);
          }
          else
          {
            idx++;
            Program.insert({decToHex(binToDec(startPC) + idx * 4), encode_I(oper, rd, con)});
          }
        }
        else if(oper == "add" || oper == "sub" || oper == "and" || oper == "or" || oper == "slt") // Rformat
        {
          fin >> rs >> rt;
          idx++;
          Program.insert({decToHex(binToDec(startPC) + idx * 4), encode_R(oper, rd, rs, rt)});
        }
        fileLength = std::max(fileLength, idx); //wrong
        // fileLength = idx;
      }
      while (!check.empty()) // beq offset,j address
      {
        std::string oper = check.back().oper;
        std::string target = check.back().target;
        idx = check.back().num;
        check.pop_back();
        std::bitset<16> offset;
        std::bitset<26> address;
        if (oper == "j")
        {
          address = (binToDec(startPC) / 4) + JumpIdx[target];
          for (int i = 0; i < 26; i++)
            Program[decToHex(binToDec(startPC) + idx * 4)][i] = address[i];
        }
        else if (oper == "beq")
        {
          offset = JumpIdx[target]-idx;
          for (int i = 0; i < 16; i++)
            Program[decToHex(binToDec(startPC) + idx * 4)][i] = offset[i];
        }
      }
    }


    std::map<std::string, std::bitset<32>>* getMem(){
      return &Mem;
    }

    std::map<std::string, std::bitset<32>> getStack(){
      return Stack;
    }

    std::map<std::string, std::bitset<32>> getProgram(){
      return Program;
    }

    std::bitset<32> getProgram(std::string key){
        return Program[key];
    }

    std::map<std::string, std::bitset<32>> getWordsAddress(){
      return WordsAddress;
    }

    std::map<std::string, int> getWords(){
      return Words;
    }

    std::map<std::string, int> getJumpIdx(){
      return JumpIdx;
    }

    std::bitset<32> getStartPC(){
      return startPC;
    }

    std::bitset<32> getStartSP(){
      return startSP;
    }

    std::bitset<32> getStartGP(){
      return startGP;
    }

    std::bitset<32> getStartData(){
      return startData;
    }

    // 16진수 string으로 받은 key를 기반으로 map Mem에서 key에 해당하는 value를 32비트 bitmap으로 리턴  
    // key가 map에 있는 경우에만 사용.
    std::bitset<32> getMemVal(std::string key){
      return Mem[key];
    }

    int getFileLength(){
      return fileLength;
    }

    // 주소를 16진수 string으로, 입력할 값을 32자리 bitset으로 받아 map Mem에 삽입한다.
    // 해당 주소가 이미 Mem에 key값으로 등록되어 있는 상황에 사용하는 setter method. 
    void setMem(std::string adr, std::bitset<32> val){
      Mem[adr] = val;
    }


};

#endif 






// int main(void)
// {
//   std::string fi = "test.s";
//   FileReader fr;

//   fr.fileRead(fi);

//   for (int i = 0; i <= fr.getFileLength(); i++){
//     std::string adr = decToHex(binToDec(fr.getStartPC())+i*4);
//     std::cout << adr << " " << binToHex(fr.getProgram()[adr]) << " " << i << "\n";
//   }

//   return 0;
// }
