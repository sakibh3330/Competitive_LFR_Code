#include <Servo.h>

Servo servo;

int sR2;
int sR1;
int sM;
int sL1;
int sL2;

int btn=11;
int led=13;

// Motor A pins
int pwmA = 3;
int a1 = 2;
int a2 = 4;
// Motor B pins
int pwmB = 5;
int b1 = 6;
int b2 = 7;

int speed = 150;
int pidSpeed = 100;
int tempSpd;
int base = 25;

char white = "r";
char tShape = "r";
char sideCross = "s";

void motor(int rightA,int rightB,int leftA,int leftB,int pwmR,int pwmL){
    digitalWrite(a1, rightA);
    digitalWrite(a2, rightB);
    digitalWrite(b1, leftA);
    digitalWrite(b2, leftB);
    // Set speed (0-255)
    analogWrite(pwmA, pwmR);
    analogWrite(pwmB, pwmL);
}

void moveForward(){
    while(true){
        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);

        if(sR2 && sR1 && sM && sL1 && sL2){
            delay(10);
            return;
        }

        motor(1,0,1,0,100,100);
    }
}

void tLeft(){
    while(true){
        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);
        
        if((sR2 && !sR1 && sM && sL1 && sL2)||(sR2 && sR1 && sM && !sL1 && sL2)){
            return;
        }
    }
    motor(1,0,0,1,100,100);
}

void tRight(){
    while(true){
        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);

        if((sR2 && !sR1 && sM && sL1 && sL2)||(sR2 && sR1 && sM && !sL1 && sL2)){
            return;
        }
    }
    motor(0,1,1,0,100,100);
}

void mainControll(){
    sR2 = digitalRead(A0);
    sR1 = digitalRead(A1);
    sM = digitalRead(A2);
    sL1 = digitalRead(A3);
    sL2 = digitalRead(A4);
    
    if(sR2 && sR1 && !sM && sL1 && sL2){
        motor(1,0,1,0,speed,speed);
    }else if(!sR2 && !sR1 && !sM && sL1 && sL2){
        //Right 90 degree
        digitalWrite(led,1);
        delay(10);

        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);

        if(sR2 && sR1 && sM && sL1 && sL2){
            tRight();
        }else if(sR2 && sR1 && !sM && sL1 && sL2){
            //Side cross like L
            if(sideCross=="s"){
              tRight();
            }
        }
        digitalWrite(led,0);
    }else if(sR2 && sR1 && !sM && !sL1 && !sL2){
        //Left 90 degree
        digitalWrite(led,1);
        delay(10);
        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);
        if(sR2 && sR1 && sM && sL1 && sL2){
            tLeft();
        }else if(sR2 && sR1 && !sM && sL1 && sL2){
            //Side cross like L
            if(sideCross=="s"){
              tLeft();  
            }
        }
        digitalWrite(led,0);
    }else if(!sR2 && sR1 && sM && sL1 && sL2){
        tempSpd = (base*2);
        motor(0,1,1,0,tempSpd,pidSpeed);
    }else if(sR2 && !sR1 && sM && sL1 && sL2){
        tempSpd = base;
        motor(0,1,1,0,tempSpd,pidSpeed);
    }else if(!sR2 && !sR1 && sM && sL1 && sL2){
        tempSpd = (base*1.5);
        motor(0,1,1,0,tempSpd,pidSpeed);
    }else if(sR2 && !sR1 && !sM && sL1 && sL2){
        tempSpd = (base/2);
        motor(0,1,1,0,tempSpd,pidSpeed);
    }else if(sR2 && sR1 && sM && sL1 && !sL2){
        //left controll
        tempSpd = (base*2);
        motor(1,0,0,1,pidSpeed,tempSpd);
    }else if(sR2 && sR1 && sM && !sL1 && sL2){
        tempSpd = base;
        motor(1,0,0,1,pidSpeed,tempSpd);
    }else if(sR2 && sR1 && sM && !sL1 && !sL2){
        tempSpd = (base*1.5);
        motor(1,0,0,1,pidSpeed,tempSpd);
    }else if(sR2 && sR1 && !sM && !sL1 && sL2){
        tempSpd = tempSpd-(base/2);
        motor(1,0,0,1,pidSpeed,tempSpd);
    }else if(sR2 && sR1 && sM && sL1 && sL2){
        // When bot in white area 
        if (white == "r"){
            tRight();
        }else if(white == "l"){
            tLeft();
        }
    }else if(sR2 && sR1 && !sM && sL1 && !sL2){
        //left 60 degree
        moveForward();
        tRight();
        
    }else if(!sR2 && sR1 && !sM && sL1 && sL2){
        //right 60 degree 
        moveForward();
        tLeft();
        
    }else if(!sR2 && !sR1 && !sM && !sL1 && !sL2){
        //T Cross code
        digitalWrite(led,1);
        delay(50);

        sR2 = digitalRead(A0);
        sR1 = digitalRead(A1);
        sM = digitalRead(A2);
        sL1 = digitalRead(A3);
        sL2 = digitalRead(A4);

        if(sR2 && sR1 && sM && sL1 && sL2){
            if(tShape=="r"){
                tRight();
                return;
            }else if(tShape=="l"){
                tLeft();
                return;
            }
        }
        while(true){
            motor(0,0,0,0,0,0);
        }
        digitalWrite(led,0);
    }else{
        motor(1,0,1,0,100,100);
    }
}

void setup() {
    servo.attach(12);
    servo.write(80);
    delay(1000);
    pinMode(btn,INPUT_PULLUP);
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    pinMode(A4,INPUT);
    pinMode(led,OUTPUT);
    
    pinMode(pwmA, OUTPUT);
    pinMode(a1, OUTPUT);
    pinMode(a2, OUTPUT);
    pinMode(pwmB, OUTPUT);
    pinMode(b1, OUTPUT);
    pinMode(b2, OUTPUT);

    while(true){
        if(!digitalRead(btn)){
            delay(100);
            digitalWrite(led,0);
            break;
        }
    }

}

void loop() {
    mainControll();
}