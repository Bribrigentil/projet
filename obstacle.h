#ifndef obstacle_H
#define obstacle_H

class obstacle {
public:
  double x;  //position selon x
  double y;  // position selon y
  double vx;  //vitesse selon x
  double vy;  //vitesse selon y

  obstacle();
  virtual ~obstacle();
};

#endif
