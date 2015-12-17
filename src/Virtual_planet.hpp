#ifndef __VIRTUAL_PLANET_H__
#define __VIRTUAL_PLANET_H__

class Virtual_planet
{
public:
  Virtual_planet();
  ~Virtual_planet();

  void run();

private:
  double production_rate_;
  double natural_defense_;
};

#endif /* end of include guard: __VIRTUAL_PLANET_H__ */
