#pragma once

#include <vector>
#include <string>

struct  TextData
{
   int x;
   int y;
   int size;
   std::string str;
   COLORREF color;
   int weight;
   CDC *pDC;
};

class test_text
{
public:
   void show_test();
   void create_text(TextData data);
   void change_color(int r, int g, int b, TextData target);
   

   std::vector<TextData> text_data_vector;
   
};
