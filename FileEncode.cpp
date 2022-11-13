#ifndef FILEREAD_INCLUDED
#define FILEREAD_INCLUDED
#include <iostream>
#include <fstream>
#include <bitset>
#include <map>
#include "Elements.cpp"
#include "Translate.cpp"
std::map<std::string,int> words;
std::map<std::string,int> jumpIdx; //ind 0 에서부터의 거리

void encode(std::string fileName, std::bitset<32> *program, int idx) // 0x00000000부터 저장할것임
{
  std::ifstream fin(fileName);
  std::string oper, rs, rt, rd, con, tmp = "";

  std::bitset<16> tmpi;
  std::bitset<6> tmp6bit;
  std::bitset<5> tmp5bit;
  while (!fin.eof())
  {
    fin >> oper;
    if (oper == "lui") // 입력 2개
    {
      fin >> rd >> con;

      // opcode 저장
      tmp6bit = OP_LUI;
      for (int i = 0; i < 6; i++)
        program[idx][i] = tmp6bit[i];

      // rd 저장 
      for (int i = 0; i < rd.length(); i++)
      {
        if (isdigit(rd[i]))
          tmp += rd[i];
      }
      rd = tmp;
      tmp = "";
      tmp5bit = std::stoi(rd);

      for (int i = 0; i < 5; i++)
        program[idx][6 + i] = '0';
      for (int i = 0; i < 5; i++)
        program[idx][11 + i] = tmp5bit[i];

      // 상수 저장
      if (con[1] == 'x') // 16진수
      {
        con.replace(0, 2, "");
        tmpi = hexToDec(con);
      }
      else // 10진수
        tmpi = std::stoi(con);

      for (int i = 0; i < 16; i++)
        program[idx][16 + i] = tmpi[i];

    }
    else if (oper == "lw" || oper == "sw") //입력 3개 하지만 붙어있음
    {
      fin >> rt >> con;

      // opcode 저장
      if(oper == "lw")tmp6bit = OP_LW;
      else tmp6bit = OP_SW;
      for (int i = 0; i < 6; i++)
        program[idx][i] = tmp6bit[i];

      // rt 저장
      for (int i = 0; i < rt.length(); i++)
      {
        if (isdigit(rt[i]))
          tmp += rt[i];
      }
      rt = tmp;
      tmp = "";
      tmp5bit = std::stoi(rt);
      for (int i = 0; i < 5; i++)
        program[idx][11 + i] = tmp5bit[i];

      //i를 rd와 상수로 분리 및 저장
      for (int i = con.length()-4; i < con.length(); i++)
      {
        if (isdigit(con[i])){
          tmp += con[i];
        }
      }
      tmp5bit = std::stoi(tmp);
      tmp = "";
      for (int i = 0; i < 6; i++)
        program[idx][6+i] = tmp5bit[i];

      for (int i = 0; i < con.length()-4; i++)
      {
        if (isdigit(con[i])){
          tmp += con[i];
        }
      }
      tmpi = std::stoi(tmp);
      tmp = "";
      for (int i = 0; i < 16; i++)
        program[idx][16+i] = tmpi[i];


    }
    else //입력 3개
    {
    }//미완성 insteruction을 제외한 .text, main:, ..etc 구현
    idx++;
  }
}
#endif