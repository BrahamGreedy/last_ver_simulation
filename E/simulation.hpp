#ifndef SIMULATION
#define SIMULATION

//radius of vision of the entity's
#define PRED_VIS 60
#define HERB_VIS 40

struct coord{
   int x=-1, y=-1;
   void reset(){
      x = -1; y = -1;
   }
};

class Object{
   protected:
      int hp_cost;//сколько восстановит хп того кто съел
      coord center;//координаты центра фигуры
      coord target;//координаты центра цели дл€ преследовани€
      coord danger;//координаты центра опасности дл€ бега от него
   public:
      Object(coord);
      virtual ~Object() {}
      coord get_center();//геттер дл€ координат центра фигуры
      int get_cost();//возвращаем сколько восстанавливает хп
      void set_cost(int);//устанавливаем значение hp_cost
      virtual void draw()=0;//отрисовка объектов
      virtual void step()=0;//шаг симул€ции
};

class Entity: public Object{
   protected:
      int hp;//текущее хп
      int eated_food;//количество съеденной еды
      int need_food;//количество необходимой еды дл€ размножени€
      int speed;//скорость перемещени€
   public:
      Entity(coord, int, int, int);
      void restore_hp(int);//восстановление хп в зависимости от еды
      void move();//передвижение
      virtual void draw()=0;
      virtual void step()=0;
};

class Predator: public Entity{
public:
   Predator(coord, int, int, int);
   void draw();
   void step();
};

class Herbivore: public Entity{
public:
   Herbivore(coord, int, int, int, int);
   void draw();
   void step();
};

class Food: public Object{
   int cap;//оставшиес€ количество ходов
   int cap_max;//количество ходов необходимое дл€ размножени€
public:
   Food(coord, int, int);
   bool is_cap();//достиг времени размножени€?
   void draw();
   void step();
};

#endif