#ifndef __FACTION_H__
#define __FACTION_H__

class Faction
{
public:
  Faction();
  ~Faction();

  void run();

private:
  std::list<Colonized_planet> colonies_;
  Mother_land *motherland_;
  double       money_;

  void loose();
};

#endif /* end of include guard: __FACTION_H__ */
