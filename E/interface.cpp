#include "interface.hpp"
#include "algorithm"

using namespace std;

Button::Button(coord first, int fill_col, int text_col): first(first), fill_col(fill_col), text_col(text_col) {}

coord Button::get_first(){return first;}

fun_ptr Button::get_func(){return func;}

void Button::set_func(fun_ptr function){func=function;}

void Button::set_type(int i){type = i;}

Rect_button::Rect_button(coord first, int fill_col, int text_col, int height, int lenght, string button_text, int offset_x, int offset_y): Button(first, fill_col, text_col), height(height), lenght(lenght), button_text(button_text), offset_x(offset_x), offset_y(offset_y) {}

void Rect_button::draw(){
   setfillstyle(SOLID_FILL, fill_col);
   bar(first.x, first.y, first.x+lenght, first.y+height);
   setcolor(text_col);
   setbkcolor(COLOR(80, 178, 192));
   settextstyle(TRIPLEX_FONT, HORIZ_DIR, 17);
   outtextxy(first.x+offset_x, first.y+offset_y, button_text.c_str());
}

bool Rect_button::in(int x, int y){
   if((first.x<=x&&x<=first.x+lenght)&&(first.y<=y&&y<=first.y+height)) return true;
   return false;
}

void Rect_button::press(){
   get_func()(type);
}

Field::Field(coord first, int lenght, int height, int fill_col): first(first), lenght(lenght), height(height), fill_col(fill_col) {}

Field &Field::instance(){
   coord temp;
   temp.x = 29; temp.y = 25;
   static Field sim_field(temp, 650, 650, COLOR(80, 178, 192));
   return sim_field;
}

Object* Field::nearest_obj(coord main_coord, const type_info& obj, int vis){
   int near_obj_index = -1;
   double nearest_dist = vis+10;
   for(int i=0; i<objects.size();i++){
      if(obj != typeid(*objects[i]))
         continue;
      double dist = hypot((main_coord.x-objects[i]->get_center().x),(main_coord.y-objects[i]->get_center().y));
      if(dist<nearest_dist){
         nearest_dist = dist;
         near_obj_index = i;
      }
   }
   if(near_obj_index == -1)
      return nullptr;
   return objects[near_obj_index];
}

void Field::replication(coord main_obj, const type_info& obj){
   coord temp;
   while(1){
      temp.x = main_obj.x + rand()%16-8;
      temp.y = main_obj.y + rand()%16-8;
      if(in_field(temp)) break;
   }
   if(obj == typeid(Predator)){
      objects.push_back(new Predator(temp, PRED_HP, PRED_NEED, PRED_SPEED));
      return;
   }
   if(obj == typeid(Herbivore)){
      objects.push_back(new Herbivore(temp, HERB_HP, HERB_NEED, HERB_SPEED, HERB_COST));
      return;
   }
   if(obj == typeid(Food)){
      objects.push_back(new Food(temp, FOOD_CAP, FOOD_COST));
      return;
   }
}

void Field::add(int i){
   coord temp;
   while(1){
      temp.x = (rand()+first.x+10)%(lenght-10);
      temp.y = (rand()+first.y+10)%(height-10);
      if(in_field(temp)) break;
   }
   if(i==0){
      objects.push_back(new Predator(temp, PRED_HP, PRED_NEED, PRED_SPEED));
   }
   if(i==1){
      objects.push_back(new Herbivore(temp, HERB_HP, HERB_NEED, HERB_SPEED, HERB_COST));
   }
   if(i==2){
      objects.push_back(new Food(temp, FOOD_CAP, FOOD_COST));
   }
   redraw_field(0);
}

bool Field::collision(coord main, coord target){
   if(sqrt((main.x-target.x)*(main.x-target.x)+(main.y-target.y)*(main.y-target.y))<16)
      return true;
   return false;
}

bool Field::in_field(coord obj){
   if(obj.x>first.x+10 && obj.x<first.x+lenght-10 && obj.y>first.y+10 && obj.y<first.y+height-10) return true;
   return false;
}

coord Field::get_f_c(){return first;}

int Field::get_lenght(){return lenght;}

int Field::get_height(){return height;}

int Field::get_obj_num(const type_info& obj){
   int count=0;
   for(int i=0; i<objects.size(); i++){
      if(obj == typeid(*objects[i]))
         count++;
   }
   return count;
}

void Field::remove_obj(Object* obj){
   *ranges::find(objects, obj) = nullptr;
   //~ objects.erase(ranges::find(objects, obj));
}

void Field::remove_last(){
   objects.pop_back();
   redraw_field(0);
}

void Field::redraw_field(int type){
   setfillstyle(SOLID_FILL, fill_col);
   bar(first.x, first.y, first.x + lenght, first.y + height);
   if(type){
      for(int i=0; i<objects.size();i++){
         objects[i]->step();
      }
      for(int i=0; i<objects.size();i++){
         if(objects[i] == nullptr){
            objects.erase(objects.begin()+i);
         }
      }
   }
   for(int i=0; i<objects.size(); i++){
      objects[i]->draw();
   }
}