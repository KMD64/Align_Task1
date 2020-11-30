#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct vector2f{
    double x;
    double y;
    //модуль векторного произведения
    double cross(const vector2f &other) const{
        return (x*other.y-y*other.x);
    }
    vector2f operator +(const vector2f &other) const{
        return {x+other.x,y+other.y};
    }
    vector2f operator -(const vector2f &other) const{
        return {x-other.x,y-other.y};
    }

};

istream& operator>>(istream& in,vector2f & vect){
    in>>vect.x>>vect.y;
    return in;
}

ostream &operator<<(ostream &out,const vector2f &vect){
    out<<"["<<vect.x<<","<<vect.y<<"]";
    return out;
}

//Функция приближенного сравнения double чисел
bool fuzzy_compare(double a,double b, double e=0.0001){
    return fabs(a-b)<e;
}

//Функция проверки позиции точки
bool is_inside(const vector<vector2f> &curve, vector2f point){
    vector2f svect = curve[curve.size()-1]-point;

    //проверка последней вершины на соответствие точке
    if(fuzzy_compare(svect.x,0)&&fuzzy_compare(svect.y,0)){
        return false;
    }

    //Алгоритм Вейлера
    int acc = 0;
    for(unsigned int i=0;i<curve.size();++i){
        vector2f evect = curve[i]-point;

        //Исключение точек вершин и ребер
        if(fuzzy_compare(evect.y,0)){
            if(fuzzy_compare(evect.x,0))
                return false;
            else{
                if(fuzzy_compare(svect.y,0)&&((evect.x>0)==(svect.x<0))){
                    return false;
                }
            }
        }

        bool right_crossing = (svect.cross(evect)>0)==(curve[i].y>curve[(i-1)%curve.size()].y);
        int addition = 2*(curve[i].y>curve[(i-1)%curve.size()].y)-1;//1 или -1

        if((svect.y>0)^(evect.y>0)){
            if(svect.x>=0){
                if(evect.x>0){
                    acc+=addition;
                }
                else{
                    if(right_crossing)
                        acc+=addition;
                }
            }
            else{
                if(evect.x>0&&right_crossing)
                    acc+=addition;
            }
        }
        svect = evect;
    }
    return acc!=0;
}

int main()
{
    uint16_t a,b;
    cin>>a>>b;
    vector<vector2f> points(a);
    vector2f point;
    for(uint16_t i = 0;i<a;++i){
        //начальная точка, совпадает с предыдущей конечной точкой (проверка?)
        cin>>point;
        //конечная точка
        cin>>points[i];
    }
    int counter =0;
    for(uint16_t i = 0;i<b;++i){
        cin>>point;
        counter += is_inside(points,point);
    }
    cout<<counter<<endl;
    return 0;
}
