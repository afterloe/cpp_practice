#ifndef __LINE_H__
#define __LINE_H__

class Line
{
public:
    void setLength(int);
    int getLength(void);
    Line(int);
    ~Line();

private:
    int line;
};

#endif