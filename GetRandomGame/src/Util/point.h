#ifndef POINT_H
#define POINT_H


class point
{
    public:
        point(int nx, int ny){
            x=nx;
            y=ny;
        }
        virtual ~point(){}

        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }
    protected:
    private:
        int x;
        int y;
};

#endif // POINT_H
