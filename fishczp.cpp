#Include "fish.cpp"

class fishczp : public fish {
private:
  static const int mapSizeX, mapSizeY;
  static const int dir[4][2];
  int hp, att, sp, maxhp, level, temp, swx, swy, fishx, fishy, px, py, id, attackDir;
  bool pointflag, over;
  void addPoints() {
    if (!askPoint()) return;
    if (maxhp == 0) { 
      for (int i = 0; i < 4; ++i) {
	increaseHP();
	increaseAtt();
	increaseSp();
      }
      return;
    }
    if (maxhp / hp > 10 || hp < level * 0.8 + 2) {
      increaseHP();
      getCondition();
      addPoints();
    }
    if (pointflag) {
      increaseAtt();
      pointflag = !pointflag;
      getCondition();
      addPoints();
    }
    else {
      increaseSp();
      pointflag = !pointflag;
      getCondition();
      addPoints();
    }
  }
  void getCondition() {
    px = askX();
    py = askY();
    level = askLevel();
    hp = askHP();
    att = askAtt();
    sp = askSp();
    maxhp = askMaxHP();
    id = askWhat(px, py);
  }
  int dist(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
  }
  int abs(int x) { return (x>0)?x:-x;}
  bool canAttack(int x, int y, int step) {
    for (int k = 0; k < 4; ++k) {
      if (x + dir[k][0] >= 0 && x + dir[k][0] < mapSizeX &&
	  y + dir[k][1] >= 0 && y + dir[k][1] < mapSizeY && 
	  (askWhat(x + dir[k][0], y + dir[k][1]) == 0 || askWhat(x + dir[k][0], y + dir[k][1]) == id) &&
	  dist(x + dir[k][0], y + dir[k][1], px, py) <= sp * step) {
	attackDir = k;
        return true;
      }
    }
    return false;
  }
  void myAttack(int x, int y) {
    int xx = x + dir[attackDir][0], yy = y + dir[attackDir][1];
    moveTo(xx, yy);
    attack(x, y);
  }
  void moveforward(int x, int y) {
    int xx = (x + px) / 2, yy = (y + py) / 2;
    if (moveTo(xx, yy)) return;
    for (int k = 0; k < 4; ++k) {
      if (xx + dir[k][0] >= 0 && xx + dir[k][0] < mapSizeX &&
	  yy + dir[k][1] >= 0 && yy + dir[k][1] < mapSizeY && 
	  askWhat(xx + dir[k][0], yy + dir[k][1]) == 0 &&
	  dist(xx + dir[k][0], yy + dir[k][1], px, py) <= sp) {
	if (moveTo(xx, yy)) return;
      }
    }
  }
public:
  void play() {
    //get condition
    getCondition();
    //add points
    addPoints();
    //get ocndition
    getCondition();
    //find targets, move and attack
    swx = swy = fishx = fishy = 100;
    over = false;
    for (int i = 0; i < mapSizeX; ++i) {
      for (int j = 0; j < mapSizeY; ++j) {
	temp = askWhat(i, j);
	if (temp == id) continue;
	if (temp == 0) continue;
	if (temp < 0) {
	  if (dist(i, j, px, py) < dist(swx, swy, px, py)) {
	    swx = i;
	    swy = j;
	  }
	}
	if (temp > 0) {
	  if (askHP(temp) <= att && canAttack(i, j, 1)) {
	    myAttack(i, j);
	    over = true;
	    break;
	  }
	  if (askHP(temp) <= att && canAttack(i, j, 2)) {
	    moveforward(i, j);
	    over = true;
	    break;
	  }
	  if (dist(i, j, px, py) < dist(fishx, fishy, px, py)) {
	    fishx = i;
	    fishy = j;
	  }
	}
      }
      if (over) break;
    }
    if (over) return;
    if (dist(swx, swy, px, py) < dist(fishx, fishy, px, py)) {
      if (canAttack(swx, swy, 1)) 
	myAttack(swx, swy);
      else moveforward(swx, swy);
    }
    else { 
      if (canAttack(fishx, fishy, 1))
	myAttack(fishx, fishy);
      else moveforward(fishx, fishy);
    }
  }
};

const int fishczp::mapSizeX = 20, fishczp::mapSizeY = 20;
const int fishczp::dir[4][2] = {{-1, 0},{1, 0},{0, -1},{0, 1}};
