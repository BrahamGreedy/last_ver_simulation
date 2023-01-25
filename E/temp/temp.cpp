


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
   int dx, dy, sign_x, sign_y;
   coord temp;
   temp.x++;temp.y++;
   if(danger.x != -1 && danger.y != -1){
      dx = fabs(center.x - danger.x);
      dy = fabs(center.y - danger.y);
      sign_x = center.x<danger.x?-speed:speed;
      sign_y = center.y<danger.y?-speed:speed;
   }      
   else if(target.x==-1&&target.y==-1){
      while(1){
         temp.x+=(rand()%2-1)*speed;
         temp.y+=(rand()%2-1)*speed;
         if(Field::instance().in_field(temp)){
            center.x+=temp.x;
            center.y+=temp.y;
            return;
         }
      }
   }
   else{
      dx = fabs(center.x - target.x);
      dy = fabs(center.y - target.y);
      sign_x = center.x<target.x?speed:-speed;
      sign_y = center.y<target.y?speed:-speed;
   }
   int error = (dx-dy)*2;
   if(error>-dy){
      temp.x+=sign_x;
      if(temp.x != Field::instance().get_f_c().x && temp.x != Field::instance().get_f_c().x + Field::instance().get_lenght())
         center.x+=temp.x;
   }
   if(error<dx){
      temp.y+=sign_y;
      if(temp.y != Field::instance().get_f_c().y && temp.y != Field::instance().get_f_c().y + _abracadabra_cast(Field::instance());