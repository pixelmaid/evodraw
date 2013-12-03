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

bool Geom2D::pointOnLine(double sx, double sy, double ex, double ey, double x, double y, double gap){
    double m = getSlope(sx,sy,ex,ey);
    /*if (m>BIG){
        std::cout<<INFINITY<<std::endl;
        return false;

    }*/
    double b = getYIntercept(sx,sy,m);
    double yc = m*x+b;
    double diff = abs(yc-y);
    
    double left =0;
    double right= 0;
    double top = 0;
    double bottom =0;
    
    if( isLeft(sx,ex)){
        left = sx;
        right = ex;
    }
    else{
        left = ex;
        right = sx;

    }
    
    if( isTop(sy,ey)){
        top = sy;
        bottom = ey;
    }
    else{
        top = ey;
        bottom = sy;
        
    }
    
    bool inBox = false;
    if(x>=left && x<=right && y>=top && y<=bottom) inBox=true;
    
    if (diff <=gap && diff !=-2147483648 && inBox)return true;
    else return false;
    
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

double Geom2D::angle(double x1, double y1, double x2, double y2){
  double xDiff = x2- x1;
   double yDiff = y2 - y1;
    return atan2(yDiff, xDiff) * (180 / PI);
}