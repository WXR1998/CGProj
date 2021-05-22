#include <vector>

#include "utils.hpp"

class PointSet{
private:
    std::vector<Point> points;
public:
    PointSet();
    PointSet(const PointSet &);
    void clear();
    void add(Point &);
};

class AnnulusSolver{
private:
    PointSet ps;
public:
    AnnulusSolver();
    
};

class SquareAnnulusSolver{
};

class RectAnnulusSolver{
};