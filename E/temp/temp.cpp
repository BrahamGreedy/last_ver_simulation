


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
         temp.x+=(rand()%2-1)*speed;
         temp.y+=(rand()%2-1)*speed;
         cout<<"x: "<<temp.x-_abracadabra_cast(center);