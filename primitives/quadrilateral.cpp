#include <cmath>
#include <stdlib.h>

class Quadrilateral: public Primitive {
  public:
    Point point1, point2, point3, point4;
    Vector normal;

    float getIntersection(Ray ray) {
      float t;
      static const float eps = 0.000000001;
      
      Vector edge_12 = point2 - point1;
      Vector edge_14 = point4 - point1;
      Vector P = ray.direction.cross(edge_14);
      
      float determinant = edge_12.dot(P);
      
      if (abs(determinant) < 0.0000001) {
        return false;
      }
      
      float inverse_determinant = 1.0 / determinant;
      Vector T = ray.origin - point1;
      float alpha = T.dot(P) * inverse_determinant;
      
      if ((alpha < 0.0) || (alpha > 1.0)) {
        return false;
      }
      
      Vector Q = T.cross(edge_12);
      float beta = ray.direction.dot(Q) * inverse_determinant;
      
      if ((beta < 0.0) || (beta > 1.0)) {
        return false; 
      }
      
      if ((alpha + beta) > 1.0) {
        Vector edge_34 = point4 - point3;
        Vector edge_32 = point2 - point3;
        Vector P_prime = ray.direction.cross(edge_32);
        float determinant_prime = edge_34.dot(P_prime);
        
        if (abs(determinant_prime) < eps) {
          return false;
        }
        
        float inverse_determinant_prime = 1.0 / determinant_prime;
        Vector T_prime = ray.origin - point3;
        float alpha_prime = T_prime.dot(P_prime) * inverse_determinant_prime;
        
        if (alpha_prime < 0.0) {
          return false;
        }
        
        Vector Q_prime = T_prime.cross(edge_34);
        float beta_prime = ray.direction.dot(Q_prime) * inverse_determinant_prime;
        
        if (beta_prime < 0.0) {
          return false;
        }
      }

      t = edge_14.dot(Q) * inverse_determinant;
      
      if (t < 0.0) {
        return false;
      } else {
        return t;
      }
    }
    
    BoundingBox* createBoundingBox() {
      BoundingBox* box = new BoundingBox();
      cout << "BBox Quad1" << endl;
      box->corner1 = Point(min(min(point1.x, point2.x), min(point3.x, point4.x)),
                           min(min(point1.y, point2.y), min(point3.y, point4.y)), 
                           min(min(point1.z, point2.z), min(point3.z, point4.z)));
      cout << "BBox Quad2" << endl;
      box->corner2 = Point(max(max(point1.x, point2.x), max(point3.x, point4.x)),
                           max(max(point1.y, point2.y), max(point3.y, point4.y)), 
                           max(max(point1.z, point2.z), max(point3.z, point4.z)));
      cout << "BBox Quad3" << endl;
      boundingBox = box;
      return box;
    }
      
    Vector getNormal(Point position) {
      return normal;
    }
};
