#include "interface.hpp"

using namespace std;

Button *controls[6];

void add(int i){
   Field::instance().add(i);
}

void remove_last(int i){
   Field::instance().remove_last();
}

void init_buttons(){
   coord temp;
   temp.x = 694; temp.y = 25;
   controls[0] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Добавить хищника", 64, 14);
   controls[0]->set_type(0);
   controls[0]->set_func(add);
   temp.x = 694; temp.y = 98;
   controls[1] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Добавить травоядное", 62, 14);
   controls[1]->set_type(1);
   controls[1]->set_func(add);
   temp.x = 694; temp.y = 171;
   controls[2] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Добавить еду", 90, 14);
   controls[2]->set_type(2);
   controls[2]->set_func(add);
   temp.x = 694; temp.y = 244;
   controls[3] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Удалить последнего", 62, 14);
   controls[3]->set_func(remove_last);
   temp.x = 694; temp.y = 308;
   controls[4] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Начать симуляцию", 62, 14);
   temp.x = 694; temp.y = 381;
   controls[5] = new Rect_button(temp, COLOR(80, 178, 192), BLACK, 50, 285, "Стоп", 122, 14);
   for(int i=0; i<6; i++)
      controls[i]->draw();
}

int main(){
   srand(time(NULL));
   initwindow(1000, 700, "Simulation");
   setfillstyle(SOLID_FILL, WHITE);
   bar(0,0,1000,700);
   Field::instance().redraw_field(0);
   init_buttons();
   while(1){
      while(mousebuttons() != 1);
      for(int i=0;i<4;i++){
         if(controls[i]->in(mousex(), mousey()))
            controls[i]->press();
            delay(100);
      }
      if(controls[4]->in(mousex(), mousey())){
         while(1){
            while(mousebuttons() != 1){
               Field::instance().redraw_field(1);
               delay(200);
            }
            if(controls[5]->in(mousex(), mousey())) break;
         }
      }
   }
}