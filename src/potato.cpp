#include "main.h"


double inchconverter (double inches){
    int gearratio = 1;
    int motorratio = 900;
    double wheeldiameter = 4.125;
    double PI = 3.1415926535;
    return inches*motorratio*gearratio/(wheeldiameter*PI);//somethign wrong ehre fix it eofadhv3gqruwofh
}



void Powerdrive(int forward, int turning){

	Left1 = forward + turning;
	Right1 = forward - turning;

		

}

void turntime (int speed, int time){
	Powerdrive(0,speed);
	delay(time);
	Powerdrive(0, 0);
}



void drivetime (int speed, int time){
	Powerdrive(speed,0);
	delay(time);
	Powerdrive(0, 0);
}

void drivencoder (int distance, double kp){
    Right1.tare_position();
    int integral = 0;
    int exitTime = 0;
    int time = 0;
    double kI = 0.00001;
    int error = inchconverter(distance) - Right1.get_position();
    int past_error = error;
    int derivative = 0;
    double kD = 3;
    while (exitTime<250){
        if(error>10)
            time = millis();
        exitTime = millis() - time; 
        past_error = error;
        error = inchconverter(distance) - Right1.get_position();
        derivative = error - past_error;

        if(abs(error)<10){
            integral+=error;
        }
        Powerdrive (error*kp + integral*kI+derivative*kD,0);
        delay(20);
    }
    Powerdrive(0,0);
}


void imuturn (int degrees, double kp){
    inertial.tare_rotation();
    int integral = 0;
    int exitTime = 0;
    int time = 0;
    double kI = 0.00001;
    int error = degrees - inertial.get_rotation();
    int past_error = error;
    int derivative = 0;
    double kD = 3;
    while (exitTime<250){
        if(error>1)
            time = millis();
        exitTime = millis() - time; 
        past_error = error;
        error = degrees - inertial.get_rotation();
        derivative = error - past_error;
        error = degrees - inertial.get_rotation();
        Powerdrive (0,error*kp + integral*kI+derivative*kD);
         delay(20);
    }
    Powerdrive(0,0);
}

   

