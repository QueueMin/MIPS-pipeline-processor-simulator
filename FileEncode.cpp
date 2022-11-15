#ifndef FILEREAD_INCLUDED
#define FILEREAD_INCLUDED
#include <iostream>
#include <fstream>
#include <bitset>
#include <map>
#include <vector>
#include <string>
#include "Elements.cpp"
#include "Translate.cpp"

std::map<std::bitset<32>, std::bitset<32>> Mem;
std::bitset<32> program[100];
std::bitset<32> startPC = hexToBin("0x00400024");
std::map<std::string, int> words;
std::map<std::string, int> jumpIdx; // index 0 에서부터의 거리
int fileLength = -1;
struct ChechList
{
  std::string oper;
  std::string target;
  int num;
};
int registerNumber(std::string registerNum)
{
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
  if (registerNum == "$31" || registerNum == "$")
    return 31;
}
std::bitset<32> encode_J(std::string oper, std::string con)
{
  std::bitset<6> tmp6bit;
  std::bitset<26> JumpAddress;
  std::bitset<32> returnBitset;

  // opcode
  tmp6bit = OP_J;
  for (int i = 0; i < 6; i++)
    returnBitset[i + 26] = tmp6bit[i];

  // address
  if (jumpIdx.find(con) != jumpIdx.end())
  {
    JumpAddress = (binToDec(startPC) / 4) + jumpIdx[con];
  } // jumpIdx에 정보가 없을시 0으로 초기화, 이후에 순회하며 재정의
  for (int i = 0; i < 26; i++)
    returnBitset[i] = JumpAddress[i];
  std::cout << returnBitset << '\n';
  return returnBitset;
}
std::bitset<32> encode_I(std::string oper, std::string rt, std::string con, std::string rs = "")
{
  std::string tmp = "";
  std::bitset<5> tmp5bit;
  std::bitset<6> tmp6bit;
  std::bitset<16> tmpi;
  std::bitset<32> returnBitset;

  if (oper == "lw")
    tmp6bit = OP_LW;
  else if (oper == "sw")
    tmp6bit = OP_SW;
  else if (oper == "beq")
    tmp6bit = OP_BEQ;

  // opcode
  for (int i = 0; i < 6; i++)
    returnBitset[i + 26] = tmp6bit[i];

  // rt
  for(int i = 0;i<rt.length();i++){
    if(rt[i] == ','){
      rt.replace(rt.find(","), 1, "");
      break;
    }
  }

  tmp5bit = registerNumber(rt);
  for (int i = 0; i < 5; i++)
    returnBitset[i + 16] = tmp5bit[i];

  if (oper == "beq")
  {
    // rs
    for(int i = 0;i<rs.length();i++){
      if(rs[i] == ','){
        rs.replace(rs.find(","), 1, "");
        break;
      }
    }
    tmp5bit = registerNumber(rs);
    for (int i = 0; i < 5; i++)
      returnBitset[i + 21] = tmp5bit[i];
    // offset은 파일 두번째 순회시에 삽입
  }
  else // con을 rs와 상수로 분리 및 저장
  {
    for (int i = 0; i < con.length(); i++)
    {
      if (con[i] == '(')
        break;
      tmp += con[i];
    }
    tmpi = std::stoi(tmp);
    for (int i = 0; i < 16; i++)
      returnBitset[i] = tmpi[i];

    // rs
    rs = con.substr(tmp.length() - 1, con.length() - 1);
    rs.replace(rs.find("("), 1, "");
    rs.replace(rs.find(")"), 1, "");
    tmp5bit = registerNumber(rs);
    for (int i = 0; i < 5; i++)
      returnBitset[i + 21] = tmp5bit[i];
  }
  return returnBitset;
}
std::bitset<32> encode_R(std::string oper, std::string rd, std::string rs, std::string rt)
{
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
  for(int i = 0;i<rd.length();i++){
    if(rd[i] == ','){
      rd.replace(rd.find(","), 1, "");
      break;
    }
  }
  tmp5bit = registerNumber(rd);
  for (int i = 0; i < 5; i++)
    returnBitset[i + 11] = tmp5bit[i];

  // rt
  // rt.replace(rt.find(","), 1, "");
  tmp5bit = registerNumber(rt);
  for (int i = 0; i < 5; i++)
    returnBitset[i + 16] = tmp5bit[i];

  // rs
  for(int i = 0;i<rs.length();i++){
    if(rs[i] == ','){
      rs.replace(rs.find(","), 1, "");
      break;
    }
  }
  tmp5bit = registerNumber(rs);
  for (int i = 0; i < 5; i++)
    returnBitset[i + 21] = tmp5bit[i];

  return returnBitset;
}
void encode(std::string fileName)
{
  words.clear();
  jumpIdx.clear();
  int idx = -1;
  std::vector<ChechList> check;

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
    if (rd == ":") // jumpIdx 저장 beq 이동시 사용
    {
      jumpIdx.insert({oper, idx + 1});
      fin >> oper >> rd;
    }
    if (oper == ".word")
    {
      // storeWord() 미구현
    }
    else if (oper == ".data")
    {
      // storeData() 미구현
    }
    else if (oper == ".text")
    {
      startPC = hexToBin(rd);
    }
    else if (oper == ".globl")
    {
      // 항상 main에서 시작할것이기 때문에 생략
    }
    else if (oper == "j") // Jformat
    {
      program[++idx] = encode_J(oper, rd);
      ChechList elem;
      elem.oper = oper;
      elem.target = con;
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
        program[++idx] = encode_I(oper, rt, con, rd); // 디폴트 입력때문에 순서를 바꿈
        ChechList elem;
        elem.oper = oper;
        elem.target = con;
        elem.num = idx;
        check.push_back(elem);
      }
      else
        program[++idx] = encode_I(oper, rt, con);
    }
    else // Rformat
    {
      fin >> rs >> rt;
      program[++idx] = encode_R(oper, rd, rs, rt);
    }
    fileLength = std::max(fileLength, idx);
  }
  while (!check.empty()) // beq offset,j address
  {
    std::string oper = check.front().oper;
    std::string target = check.front().target;
    idx = check.front().num;
    check.pop_back();
    std::bitset<16> offset;
    std::bitset<26> address;
    if (oper == "j")
    {
      address = binToDec(startPC) / 4 + jumpIdx[target];
      for (int i = 0; i < 26; i++)
        program[idx][i] = address[i];
    }
    else if (oper == "beq")
    {
      offset = jumpIdx[target] * 4;
      for (int i = 0; i < 16; i++)
        program[idx][i] = offset[i];
    }
  }
}
// int main(void)
// {
//   std::cout << '!';
//   std::string fi = "t.s";
//   encode(fi);
//   std::cout << '\n' << startPC << '\n';
//   for (int i = 0; i <= fileLength; i++)
//   {
//     std::cout << binToHex(program[i]) << ' ' << program[i] << ' ' << i << '\n';
//   }
//   return 1;
//}
#endif