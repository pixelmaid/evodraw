//
//  Geom2D.cpp
//  evodraw1
//
//  Created by jennifer mary jacobs on 11/12/13.
//
//

#include "Geom2D.h"
#include <math.h>       /* atan2 */

#define PI 3.14159265

//default constructor
Geom2D:: Geom2D(){
    
}


double Geom2D::euclidDist(double x1,double y1, double x2, double y2){
    double dx = x1-x2;
    double dy = y1-y2;
    double dist = sqrt (dx+dy);
    return dist;
    
}

double Geom2D::distanceToLine(double px, double py, double x1, double y1, double x2, double y2){
    Vec2D u = Vec2D(x2-x1,y2-y1);
    Vec2D v = Vec2D(px-x1,py-y1);
    Vec2D dUV =  Vec2D::projectOnto(u, v);
    double proPX = x1+dUV.x;
    double proPY = y1+dUV.y;
    Vec2D qL = Vec2D(px-proPX, py-proPY);
    double dist = qL.length();
    cout<<"distance ="<<dist<<endl;
    return dist;
    
}


int Geom2D::pointOnLine(double pX, double pY, double x1, double y1, double x2, double y2, double gap){
    double area = triangleArea(pX, pY, x1,y1,x2,y2);
    cout<<"triline area="<<area<<endl;
    if(area<=gap){
        return 1;
    }
    else return -1;
    
    /*double m = getSlope(x1,y1,x2,y2);
    
    double b = getYIntercept(x1,y1,m);
    double yc = m*pX+b;
    double diff = abs(yc-pY);
    
    double left =0;
    double right= 0;
    double top = 0;
    double bottom =0;
    
    if( isLeft(x1,x2)){
        left = x1;
        right = x2;
    }
    else{
        left = x2;
        right = x1;

    }
    
    if( isTop(y1,y2)){
        top = y1;
        bottom = y2;
    }
    else{
        top = y1;
        bottom = y2;
        
    }
    
    bool inBox = false;
    if(pX>=left && pX<=right && pY>=top && pY<=bottom) inBox=true;
    
    if (diff <=gap && diff !=-2147483648 && inBox)return 0;
    else return -1;
    */
}

double Geom2D::getSlope(double sx, double sy, double ex, double ey){
    double m = (sy - ey)/ (sx - ex); 
    
    if(m>BIG){
        return std::numeric_limits<double>::infinity();
    }
    else{
        return m;
    }
}

double Geom2D::getYIntercept(double sx, double sy, double m){
    if(m>BIG){
        //std::cout << "slope is infinite, no y intercept: " << std::endl;
        return std::numeric_limits<double>::infinity();
    }
    else{
        double b = sy - m * sx; //calculate the y intercept with y=mx+b
        return b;
    }
                                
}

vector<double> Geom2D::getMidpoint(double sx, double sy, double ex, double ey){
    double mx = (sx+ex)/2;
    double my = (sy+ey)/2;
    vector<double>m;
    m.push_back(mx);
    m.push_back(my);
    return m;
    
}


bool Geom2D::isLeft(double x1, double x2){
    if(x1<=x2) return true;
    else return false;
}

bool Geom2D::isTop(double y1, double y2){
    if(y1<=y2) return true;
    else return false;
}

//calculates mean and standard deviation
vector<double> Geom2D::meanSd(vector<double> values, bool forcesd){
    vector<double> result;
    double sum=0;
    double sd_sum=0;
    for(int i=0;i<values.size();i++){
        sum+=values[i];
        
    }
    double mean = sum/values.size();
    for(int i=0;i<values.size();i++){
        double v = (values[i]-mean)*(values[i]-mean);
        sd_sum += v;
    }
    double sd = sd_sum/values.size();

    result.push_back(mean);
    if(values.size()<10 && forcesd) result.push_back(20);
       else  result.push_back(sd);

    result.push_back(sd);
    
    return result;
    
    
}

vector<double> Geom2D::normalize(vector<double> values){
    vector<double> result;
    double sum=0;
    for(int i=0;i<values.size();i++){
        sum+=values[i];
        
    }
    for(int i=0;i<values.size();i++){
        result.push_back(values[i]/sum);
        
    }
    return result;
    
}

double Geom2D::angle(double x1, double y1, double x2, double y2){
  double xDiff = x2- x1;
   double yDiff = y2 - y1;
    return atan2(yDiff, xDiff) * (180 / PI);
}

double Geom2D::inEllipse(double x, double y, double ex, double ey, double ew, double eh){
    double val = pow((x-ex),2)/pow(ew,2)+pow((y-ey),2)/pow(eh,2);
    return val;
}

double Geom2D::inRect(double pX, double pY, double aX, double aY, double bX, double bY, double cX, double cY, double dX, double dY, double m){
    double a1 =triangleArea(aX,aY,pX,pY,dX,dY);
    double a2 =triangleArea(dX,dY,pX,pY,cX,cY);
    double a3 = triangleArea(cX,cY,pX,pY,bX,bY);
    double a4 = triangleArea(pX,pY,bX,bY,aX,aY);
    double rA = abs((bX-aX))*abs((cY-bY));
    double sA = a1+a2+a3+a4;
    cout <<"sum of triangles="<<sA<<" rectArea ="<<rA<<endl;
    double margin=m*rA;
    if ((m!=0)&&(margin<100)){
        margin = 100;
    }
    if ((m!=0)&&(margin>300)){
        margin = 300;
    }
    if(abs(sA-rA)>margin){
        return -1;
    }
    else {
        if((a1>=-margin && a1<=margin)||(a2>=-margin && a2<=margin)||(a3>=-margin && a3<=margin)||(a4>=-margin && a4<=margin)){
            return 0;
        }
        return 1;
    }
    
}

double Geom2D::triangleArea(double aX, double aY, double bX, double bY, double cX, double cY){
    return abs((aX*(bY-cY)+bX*(cY-aY)+cX*(aY-bY))/2);

}