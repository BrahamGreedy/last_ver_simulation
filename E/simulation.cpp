#include "interface.hpp"
#include "simulation.hpp"

using namespace std;

Object::Object(coord center): center(center) {}

coord Object::get_center(){return center;}

int Object::get_cost(){return hp_cost;}

void Object::set_cost(int cost){hp_cost = cost;}

Entity::Entity(coord center, int hp, int need_food, int speed): Object(center), hp(hp), need_food(need_food), speed(speed) {}

void Entity::restore_hp(int heal){
   hp += heal;
}

void Entity::move(){//переделать чтоб была проверка на выход из поля
   //~ int dx, dy, sign_x = 0, sign_y = 0;
   //~ int dist_bord_x, dist_bord_y;//дистанция до границ
   //~ dist_bord_x = ((center.x-10-Field::instance().get_f_c().x)<(Field::instance().get_f_c().x+Field::instance().get_lenght()+10-center.x))?
   //~ (center.x-10-Field::instance().get_f_c().x):(Field::instance().get_f_c().x+Field::instance().get_lenght()+10-center.x);
   //~ dist_bord_y = ((center.y-10-Field::instance().get_f_c().y)<(Field::instance().get_f_c().y+Field::instance().get_height()+10-center.y))?
   //~ (center.y-10-Field::instance().get_f_c().y):(Field::instance().get_f_c().y+Field::instance().get_height()+10-center.y);
   //~ if(danger.x == -1 && danger.y == -1 && target.x == -1 && target.y == -1){//случай когда нет поблизости никого
      //~ while(1){
         //~ coord temp = center;
         //~ temp.x+=(rand()%3-1)*speed;
         //~ temp.y+=(rand()%3-1)*speed;
         //~ if(Field::instance().in_field(temp)){
            //~ center = temp;
            //~ return;
         //~ }
      //~ }
   //~ }
   //~ if(target.x == -1 && target.y == -1){//случай когда есть опасность
      //~ dx = center.x - danger.x;
      //~ dy = center.y - danger.y;
      //~ if(dist_bord_x>10)
         //~ sign_x = -speed;
      //~ else
         //~ sign_x = speed;
      //~ if(dist_bord_y>10)
         //~ sign_y = -speed;
      //~ else
         //~ sign_y = speed;
   //~ }
   //~ else{//случай когда нет опасности, но есть цель
      //~ dx = center.x - target.x;
      //~ dy = center.y - target.y;
      //~ if(dist_bord_x>10)
         //~ sign_x = speed;
      //~ else
         //~ sign_x = -speed;
      //~ if(dist_bord_y>10)
         //~ sign_y = speed;
      //~ else
         //~ sign_y = -speed;
   //~ }
  int dx, dy, sign_x, sign_y;
   if(danger.x != -1 && danger.y != -1){
      dx = fabs(center.x - danger.x);
      dy = fabs(center.y - danger.y);
      sign_x = center.x<danger.x?-speed:(center.x==danger.x?0:speed);
      sign_y = center.y<danger.y?-speed:(center.y==danger.y?0:speed);
   }
   else if(target.x==-1&&target.y==-1){
      //возможно нужно сделать псевдорандом
      center.x+=(rand()%3-1)*speed;
      center.y+=(rand()%3-1)*speed;
      return;
   }
   else{
      dx = fabs(center.x - target.x);
      dy = fabs(center.y - target.y);
      sign_x = center.x<target.x?speed:(center.x==danger.x?0:-speed);
      sign_y = center.y<target.y?speed:(center.y==danger.y?0:-speed);
   }
   int error = dx-dy;
   int error2 = error*2;
   if(error2>-dy){
      error-=dy;
      center.x+=sign_x;
   }
   if(error2<dx){
      error+=dx;
      center.y+=sign_y;
   }
}

Predator::Predator(coord center, int hp, int need_food, int speed): Entity(center, hp, need_food, speed) {}

void Predator::draw(){
   setcolor(BLACK);
   setfillstyle(SOLID_FILL, RED);
   fillellipse(center.x, center.y, 8, 8);
}

void Predator::step(){
   if(Field::instance().nearest_obj(center, typeid(Herbivore), PRED_VIS) != nullptr){
      target = Field::instance().nearest_obj(center, typeid(Herbivore), PRED_VIS)->get_center();
      if(target.x != -1 && target.y != -1 && Field::instance().collision(center, target)){
         eated_food++;
         Field::instance().remove_obj(Field::instance().nearest_obj(center, typeid(Herbivore), PRED_VIS));
         restore_hp(Field::instance().nearest_obj(center, typeid(Herbivore), PRED_VIS)->get_cost());
         if(eated_food == need_food){
            eated_food=0;
            Field::instance().replication(center, typeid(Predator));
         }
      }
   }
   if(hp!=0){
      hp--;
      move();
   }
   else{
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, COLOR(84,66,107));
      fillellipse(center.x, center.y, 8, 8);
      delay(10);
      Field::instance().remove_obj(this);
   }
}

Herbivore::Herbivore(coord center, int hp, int need_food, int speed, int hp_cost): Entity(center, hp, need_food, speed) {set_cost(hp_cost);}

void Herbivore::draw(){
   setcolor(BLACK);
   setfillstyle(SOLID_FILL, BLUE);
   fillellipse(center.x, center.y, 8, 8);
}

void Herbivore::step(){
   if(Field::instance().nearest_obj(center, typeid(Predator), HERB_VIS) != nullptr){
      danger = Field::instance().nearest_obj(center, typeid(Predator), HERB_VIS)->get_center();
      if((danger.x == -1 && danger.y == -1) && Field::instance().nearest_obj(center, typeid(Food), HERB_VIS) != nullptr){
         target = Field::instance().nearest_obj(center, typeid(Food), HERB_VIS)->get_center();
         if(target.x != -1 && target.y != -1 && Field::instance().collision(center, target)){
            eated_food++;
            Field::instance().remove_obj(Field::instance().nearest_obj(center, typeid(Herbivore), HERB_VIS));
            restore_hp(Field::instance().nearest_obj(center, typeid(Food), HERB_VIS)->get_cost());
            if(eated_food == need_food){
               eated_food=0;
               Field::instance().replication(center, typeid(Herbivore));
            }
         }
      }
   }
   if(hp!=0){
      hp--;
      move();
   }
   else{
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, COLOR(84,66,107));
      fillellipse(center.x, center.y, 8, 8);
      delay(10);
      Field::instance().remove_obj(this);
   }
}

Food::Food(coord center, int cap, int hp_cost): Object(center), cap(cap), cap_max(cap) {set_cost(hp_cost);}

bool Food::is_cap(){
   if(cap==0){
      cap = cap_max;
      return true;
   }
   cap--;
   return false;
}

void Food::draw(){
   setfillstyle(SOLID_FILL, GREEN);
   bar(center.x-8, center.y-8, center.x+8, center.y+8);
}

void Food::step(){
   if(is_cap()){
      for(int i=0; i<2; i++)
         Field::instance().replication(center, typeid(Food));
   }
}