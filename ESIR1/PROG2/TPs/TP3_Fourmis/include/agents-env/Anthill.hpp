 #ifndef ANTHILL_H
 #define ANTHILL_H
 
 #include "agents-ant/Agent.hpp"
 class Anthill : public Agent {
  protected:
   float m_quantity = 0;
   /** 100 => 20 fourmis qui donnent à manger = une nouvelle fourmis */
   int number_of_ants = 50;
   static constexpr float QUANTITY_THRESHOLD = 50.0;
   static constexpr int INITIAL_ANT_COUNT = 50;
 public:
   Anthill(Environment *environment, const Vector2<float> &pos);
   void depositFood(float quantity);
   void deathsignal();
   void update() override;
 };
 
 #endif