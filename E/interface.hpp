#ifndef INTERFACE
#define INTERFACE

#include "graphics.h"
#include "simulation.hpp"
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "cmath"
#include <vector>
#include <string>
//��� ����������� �������������� �������� ���������
#define PRED_HP 200
#define PRED_SPEED 2
#define PRED_NEED 4
#define HERB_HP 200
#define HERB_COST 100
#define HERB_SPEED 2
#define HERB_NEED 2
#define FOOD_COST 100
#define FOOD_CAP 40

typedef void(*fun_ptr)(int);//��������������� ��� - ��������� �� �������

class Button{//������� ����� ��� ������
   protected:
      coord first;//��������� ����������
      int fill_col;//���� ������
      int text_col;//���� ������
      int type=-1;
      fun_ptr func;//�������
   public:
      Button(coord, int, int);
      coord get_first();//������ ��� ��������� ���������
      fun_ptr get_func();//������ ��� �������
      void set_func(fun_ptr);//������ ��� ��������� �������
      void set_type(int);//������������� ���� ��������� 0-predator, 1-herbivore, 2-food
      virtual bool in(int, int)=0;//��������� �� ���������� ������ ������?
      virtual void draw()=0;//��������� ������
      virtual void press()=0;//������� ������
};

class Rect_button: public Button{
      int height;//������ ������
      int lenght;//����� ������
      int offset_x;//������ ������ ������ ������ �����
      int offset_y;//������ ������ ������ ������ ������
      std::string button_text;//����� ������
   public:
      Rect_button(coord, int, int, int, int, std::string, int, int);
      bool in(int, int);
      void draw();
      void press();
};

class Field{
      coord first;//����� ������� ���������� ����
      int lenght, height;//����� � ������ ����
      int fill_col;//���� ������� ����
      std::vector<Object*> objects;//������ � ��������� ���������
      Field(coord, int, int, int);
   public:
      static Field &instance();
      Object* nearest_obj(coord, const std::type_info&, int);//������ ���������� ���������� ���������� ���� � ����������� ���
      void replication(coord, const std::type_info&);//�����������
      void add(int);//��������� ������ �� ���� ����� ������� ���������
      bool collision(coord, coord);//��������� �����������(�����������) �� �������
      bool in_field(coord);//��������� �� ������ ������ ����
      coord get_f_c();//������ ��� first
      int get_lenght();//������ ��� ����� ����
      int get_height();//������ ��� ������ ����
      int get_obj_num(const std::type_info&);//���������� �������� ������������� ���� �� ����
      void remove_obj(Object*);//������� ������
      void remove_last();//������� ��������� ����������� ������
      void redraw_field(int);//����������� ���� ���������
};

#endif