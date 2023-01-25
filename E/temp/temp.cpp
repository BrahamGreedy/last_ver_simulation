


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
   int dx, dy, sign_x = 0, sign_y = 0;
   int dist_bord_x, dist_bord_y;//дистанция до границ
   dist_bord_x = ((center.x-10-Field::instance().get_f_c().x)<(Field::instance().get_f_c().x+Field::instance().get_lenght()+10-center.x))?
   (center.x-10-Field::instance().get_f_c().x):(Field::instance().get_f_c().x+Field::instance().get_lenght()+10-center.x);
   dist_bord_y = ((center.y-10-Field::instance().get_f_c().y)<(Field::instance().get_f_c().y+Field::instance().get_height()+10-center.y))?
   (center.y-10-Field::instance().get_f_c().y):(Field::instance().get_f_c().y+Field::instance().get_height()+10-center.y);
   if(danger.x == -1 && danger.y == -1 && target.x == -1 && target.y == -1){//случай когда нет поблизости никого
      while(1){
         coord temp = center;
         temp.x+=(rand()%3-1)*speed;
         temp.y+=(rand()%3-1)*speed;
         if(Field::instance().in_field(temp)){
            center = temp;
            return;
         }
      }
   }
   if(target.x == -1 && target.y == -1){//случай когда есть опасность
      dx = center.x - danger.x;
      dy = center.y - danger.y;
      if(dist_bord_x>10)
         sign_x = -speed;
      else
         sign_x = speed;
      if(dist_bord_y>10)
         sign_y = -speed;
      else
         sign_y = speed;
   }
   else{//случай когда нет опасности, но есть цель
      dx = center.x - target.x;
      dy = center.y - target.y;
      if(dist_bord_x>10)
         sign_x = speed;
      else
         sign_x = -speed;
      if(dist_bord_y>10)
         sign_y = speed;
      else
         sign_y = -speed;
   }
   if(dx==0){
      if(dy<0)
         center.y-=sign_y;
      else
         center.y+=sign_y;
   }
   else (dx<0){
      if(dy==0)
         _abracadabra_cast(center);