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
//тут прописываем характеристики объектов симул€ции
#define PRED_HP 200
#define PRED_SPEED 2
#define PRED_NEED 4
#define HERB_HP 200
#define HERB_COST 100
#define HERB_SPEED 2
#define HERB_NEED 2
#define FOOD_COST 100
#define FOOD_CAP 40

typedef void(*fun_ptr)(int);//вспомогательный тип - указатель на функцию

class Button{//базовый класс дл€ кнопок
   protected:
      coord first;//начальные координаты
      int fill_col;//цвет кнопки
      int text_col;//цвет текста
      int type=-1;
      fun_ptr func;//функци€
   public:
      Button(coord, int, int);
      coord get_first();//геттер дл€ начальных координат
      fun_ptr get_func();//геттер дл€ функции
      void set_func(fun_ptr);//сеттер дл€ установки функции
      void set_type(int);//устанавливаем кого добавл€ем 0-predator, 1-herbivore, 2-food
      virtual bool in(int, int)=0;//находитс€ ли координаты внутри кнопки?
      virtual void draw()=0;//отрисовка кнопки
      virtual void press()=0;//нажатие кнопки
};

class Rect_button: public Button{
      int height;//высота кнопки
      int lenght;//длина кнопки
      int offset_x;//отступ текста внутри кнопки слева
      int offset_y;//отступ текста внутри кнопки сверху
      std::string button_text;//текст кнопки
   public:
      Rect_button(coord, int, int, int, int, std::string, int, int);
      bool in(int, int);
      void draw();
      void press();
};

class Field{
      coord first;//лева€ верхн€€ координата пол€
      int lenght, height;//длина и высота пол€
      int fill_col;//цвет заливки пол€
      std::vector<Object*> objects;//вектор с объектами симул€ции
      Field(coord, int, int, int);
   public:
      static Field &instance();
      Object* nearest_obj(coord, const std::type_info&, int);//выдаем координаты ближайшего указанного типа к вызывающему еды
      void replication(coord, const std::type_info&);//размножение
      void add(int);//добавл€ем объект на поле перед началом симул€ции
      bool collision(coord, coord);//провер€ем столкнулись(встретились) ли объекты
      bool in_field(coord);//находитс€ ли объект внутри пол€
      coord get_f_c();//геттер дл€ first
      int get_lenght();//геттер дл€ длины пол€
      int get_height();//геттер дл€ высоты пол€
      int get_obj_num(const std::type_info&);//количество объектов определенного типа на поле
      void remove_obj(Object*);//удал€ем объект
      void remove_last();//удал€ем последний добавленный объект
      void redraw_field(int);//перерисовка пол€ симул€ции
};

#endif