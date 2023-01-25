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
      int hp_cost;//������� ����������� �� ���� ��� ����
      coord center;//���������� ������ ������
      coord target;//���������� ������ ���� ��� �������������
      coord danger;//���������� ������ ��������� ��� ���� �� ����
   public:
      Object(coord);
      virtual ~Object() {}
      coord get_center();//������ ��� ��������� ������ ������
      int get_cost();//���������� ������� ��������������� ��
      void set_cost(int);//������������� �������� hp_cost
      virtual void draw()=0;//��������� ��������
      virtual void step()=0;//��� ���������
};

class Entity: public Object{
   protected:
      int hp;//������� ��
      int eated_food;//���������� ��������� ���
      int need_food;//���������� ����������� ��� ��� �����������
      int speed;//�������� �����������
   public:
      Entity(coord, int, int, int);
      void restore_hp(int);//�������������� �� � ����������� �� ���
      void move();//������������
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
   int cap;//���������� ���������� �����
   int cap_max;//���������� ����� ����������� ��� �����������
public:
   Food(coord, int, int);
   bool is_cap();//������ ������� �����������?
   void draw();
   void step();
};

#endif