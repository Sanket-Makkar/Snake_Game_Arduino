/* lets set up pseudocode for the game snake
  set the led matrix command -- matrix.setLed(0, snake.row, snake.col, 1);
  array with two numbers -- 
        #include <utility>
        std::pair<int, int> order[100];

        void setFrame( int nextOrder, int nextContent )
        {
            order[count++] = { nextOrder, nextContent };
        }

* #include <utility>
  std::pair<int, int> order[64];
  void setPos( int nextOrder, int nextContent )
    {
        order[count++] = { nextOrder, nextContent };
    }

*  setup:
    figure out current position on accelerometer
    create one dot at center
    setPos(center, center);
    
*  loop:
    if direction1 = right:
        movedot right
    else if direction1 = left:
        move dot left
    else:
        move dot foreward
    
    iterate through order:
        if any value = any other value:
            end game
    
    after 20 loops: 
        add dot to order
    
    delay(50);
*/

#include "LedControl.h" 
#include "Wire.h" 
//control everything 
int maxRowBound = 7;
int minRowBound = -1;
int defualtValue = -2;
//

byte gameOver1[8] = {B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000};
byte gameOver2[8] = {B00000000, B00000000, B00100100, B00011000, B00011000, B00100100, B00000000, B00000000};
byte gameOver3[8] = {B00000000, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B00000000};
byte gameOver4[8] = {B10000001, B01000010, B00100100, B00011000, B00011000, B00100100, B01000010, B10000001};
byte gameOver5[8] = {B01000010, B00100100, B00011000, B00011000, B00011000, B00011000, B00100100, B01000010};
byte gameOver6[8] = {B00100100, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00100100};
byte gameOver7[8] = {B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
byte gameOver8[8] = {B00000000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
byte gameOver9[8] = {B00000000, B00000000, B00011000, B00011000, B00011000, B00011000, B00011000, B00011000};
byte gameOver10[8] = {B00000000, B00000000, B00000000, B00011000, B00011000, B00011000, B00011000, B00011000};
byte gameOver11[8] = {B00000000, B00000000, B00000000, B00000000, B00011000, B00011000, B00011000, B00011000};
byte gameOver12[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00011000, B00011000};
byte gameOver13[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00011000};
byte gameOver14[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011000};
byte gameOver15[8] = {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

const int MPU_ADDR = 0x68; 
const int button = 7;
const int buzzer = 5;

//manage the accelerometer
int16_t accelerometer_x, accelerometer_y, accelerometer_z; 
int16_t gyro_x, gyro_y, gyro_z; 
int16_t temperature;




int cycleCount = 0;
LedControl matrix=LedControl(12,11,10,1);

// std::pair<int, int> order[64];
//   void setPos( int nextOrder, int nextContent )
//     {
//         order[count++] = { nextOrder, nextContent };
//     }

struct Data{
    int first;
    int seccond;
};

Data order[64];
int count = 0;

//method for adding a new piece of information
void setPos(int nextOrder, int nextContent){
    order[count].first = nextOrder;
    order[count].seccond = nextContent;
    count++;
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

// void iterate7(byte var[]){
//     for (int regvar = 0; regvar < 8; regvar++){
//         matrix.setRow(0, i, var[i]);
//     }
// }

void gameOver(){
tone(buzzer, NOTE_G4, 390 * .9);
  matrix.setRow(0,0,gameOver1[0]);
  matrix.setRow(0,1,gameOver1[1]);
  matrix.setRow(0,2,gameOver1[2]);
  matrix.setRow(0,3,gameOver1[3]);
  matrix.setRow(0,4,gameOver1[4]);
  matrix.setRow(0,5,gameOver1[5]);
  matrix.setRow(0,6,gameOver1[6]);
  matrix.setRow(0,7,gameOver1[7]);
  delay(65);
  matrix.setRow(0,0,gameOver2[0]);
  matrix.setRow(0,1,gameOver2[1]);
  matrix.setRow(0,2,gameOver2[2]);
  matrix.setRow(0,3,gameOver2[3]);
  matrix.setRow(0,4,gameOver2[4]);
  matrix.setRow(0,5,gameOver2[5]);
  matrix.setRow(0,6,gameOver2[6]);
  matrix.setRow(0,7,gameOver2[7]);
  delay(65);
  matrix.setRow(0,0,gameOver3[0]);
  matrix.setRow(0,1,gameOver3[1]);
  matrix.setRow(0,2,gameOver3[2]);
  matrix.setRow(0,3,gameOver3[3]);
  matrix.setRow(0,4,gameOver3[4]);
  matrix.setRow(0,5,gameOver3[5]);
  matrix.setRow(0,6,gameOver3[6]);
  matrix.setRow(0,7,gameOver3[7]);
  delay(65);
  matrix.setRow(0,0,gameOver4[0]);
  matrix.setRow(0,1,gameOver4[1]);
  matrix.setRow(0,2,gameOver4[2]);
  matrix.setRow(0,3,gameOver4[3]);
  matrix.setRow(0,4,gameOver4[4]);
  matrix.setRow(0,5,gameOver4[5]);
  matrix.setRow(0,6,gameOver4[6]);
  matrix.setRow(0,7,gameOver4[7]);
  delay(65);
  matrix.setRow(0,0,gameOver5[0]);
  matrix.setRow(0,1,gameOver5[1]);
  matrix.setRow(0,2,gameOver5[2]);
  matrix.setRow(0,3,gameOver5[3]);
  matrix.setRow(0,4,gameOver5[4]);
  matrix.setRow(0,5,gameOver5[5]);
  matrix.setRow(0,6,gameOver5[6]);
  matrix.setRow(0,7,gameOver5[7]);
  delay(65);
  matrix.setRow(0,0,gameOver6[0]);
  matrix.setRow(0,1,gameOver6[1]);
  matrix.setRow(0,2,gameOver6[2]);
  matrix.setRow(0,3,gameOver6[3]);
  matrix.setRow(0,4,gameOver6[4]);
  matrix.setRow(0,5,gameOver6[5]);
  matrix.setRow(0,6,gameOver6[6]);
  matrix.setRow(0,7,gameOver6[7]);
  delay(65);

  tone(buzzer, NOTE_A4, 260 * 0.9);

  matrix.setRow(0,0,gameOver7[0]);
  matrix.setRow(0,1,gameOver7[1]);
  matrix.setRow(0,2,gameOver7[2]);
  matrix.setRow(0,3,gameOver7[3]);
  matrix.setRow(0,4,gameOver7[4]);
  matrix.setRow(0,5,gameOver7[5]);
  matrix.setRow(0,6,gameOver7[6]);
  matrix.setRow(0,7,gameOver7[7]);
  delay(65);
  matrix.setRow(0,0,gameOver8[0]);
  matrix.setRow(0,1,gameOver8[1]);
  matrix.setRow(0,2,gameOver8[2]);
  matrix.setRow(0,3,gameOver8[3]);
  matrix.setRow(0,4,gameOver8[4]);
  matrix.setRow(0,5,gameOver8[5]);
  matrix.setRow(0,6,gameOver8[6]);
  matrix.setRow(0,7,gameOver8[7]);
  delay(65);
  matrix.setRow(0,0,gameOver9[0]);
  matrix.setRow(0,1,gameOver9[1]);
  matrix.setRow(0,2,gameOver9[2]);
  matrix.setRow(0,3,gameOver9[3]);
  matrix.setRow(0,4,gameOver9[4]);
  matrix.setRow(0,5,gameOver9[5]);
  matrix.setRow(0,6,gameOver9[6]);
  matrix.setRow(0,7,gameOver9[7]);
  delay(65);
  matrix.setRow(0,0,gameOver10[0]);
  matrix.setRow(0,1,gameOver10[1]);
  matrix.setRow(0,2,gameOver10[2]);
  matrix.setRow(0,3,gameOver10[3]);
  matrix.setRow(0,4,gameOver10[4]);
  matrix.setRow(0,5,gameOver10[5]);
  matrix.setRow(0,6,gameOver10[6]);
  matrix.setRow(0,7,gameOver10[7]);
  delay(65);
  
  tone(buzzer, NOTE_DS4, 260 * .9);

  matrix.setRow(0,0,gameOver11[0]);
  matrix.setRow(0,1,gameOver11[1]);
  matrix.setRow(0,2,gameOver11[2]);
  matrix.setRow(0,3,gameOver11[3]);
  matrix.setRow(0,4,gameOver11[4]);
  matrix.setRow(0,5,gameOver11[5]);
  matrix.setRow(0,6,gameOver11[6]);
  matrix.setRow(0,7,gameOver11[7]);
  delay(65);
  matrix.setRow(0,0,gameOver12[0]);
  matrix.setRow(0,1,gameOver12[1]);
  matrix.setRow(0,2,gameOver12[2]);
  matrix.setRow(0,3,gameOver12[3]);
  matrix.setRow(0,4,gameOver12[4]);
  matrix.setRow(0,5,gameOver12[5]);
  matrix.setRow(0,6,gameOver12[6]);
  matrix.setRow(0,7,gameOver12[7]);
  delay(65);
  matrix.setRow(0,0,gameOver13[0]);
  matrix.setRow(0,1,gameOver13[1]);
  matrix.setRow(0,2,gameOver13[2]);
  matrix.setRow(0,3,gameOver13[3]);
  matrix.setRow(0,4,gameOver13[4]);
  matrix.setRow(0,5,gameOver13[5]);
  matrix.setRow(0,6,gameOver13[6]);
  matrix.setRow(0,7,gameOver13[7]);
  delay(65);
  matrix.setRow(0,0,gameOver14[0]);
  matrix.setRow(0,1,gameOver14[1]);
  matrix.setRow(0,2,gameOver14[2]);
  matrix.setRow(0,3,gameOver14[3]);
  matrix.setRow(0,4,gameOver14[4]);
  matrix.setRow(0,5,gameOver14[5]);
  matrix.setRow(0,6,gameOver14[6]);
  matrix.setRow(0,7,gameOver14[7]);
  delay(65);
  matrix.setRow(0,0,gameOver15[0]);
  matrix.setRow(0,1,gameOver15[1]);
  matrix.setRow(0,2,gameOver15[2]);
  matrix.setRow(0,3,gameOver15[3]);
  matrix.setRow(0,4,gameOver15[4]);
  matrix.setRow(0,5,gameOver15[5]);
  matrix.setRow(0,6,gameOver15[6]);
  matrix.setRow(0,7,gameOver15[7]);

  noTone(buzzer);

  while(digitalRead(button) != HIGH){
       for (int i = 0; i < 64; i++){
            if (order[i].first != defualtValue && order[i].seccond != defualtValue){
                matrix.setLed(0, order[i].first, order[i].seccond, HIGH);
            }
        }
        delay(100);
  }

    resetFunc();  //call reset

}


int sa = 0;

void setup() {
  for (int i = 0; i < 64; i++){
    order[i].first = defualtValue;
    order[i].seccond = defualtValue;
  }



    Wire.begin();
    Wire.beginTransmission(MPU_ADDR); 
    Wire.write(0x6B); 
    Wire.write(0);

    sa = Wire.read()<<8 | Wire.read(); 
    Wire.endTransmission(true);
    

    matrix.shutdown(0,false);
    matrix.setIntensity(0,1);
    matrix.clearDisplay(0); 

    setPos(4, 4);
    
    pinMode(button, INPUT);
    Serial.begin(9600);

}

int direction1 = 0;
int prev1 = 0;
int prev2 = 0;

int totalCount = 0;
int secCount = 0;

int prevbucket1 = 0;
int prevbucket2 = 0;

int mm = 0;
int prevdir = -1;

void loop() {

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);

    accelerometer_x = Wire.read()<<8 | Wire.read(); 
    accelerometer_y = Wire.read()<<8 | Wire.read();
    accelerometer_z = Wire.read()<<8 | Wire.read(); 
    temperature = Wire.read()<<8 | Wire.read(); 

    if (secCount == 0){
        secCount += 1;
        sa = accelerometer_y;
        mm = accelerometer_x;
    }
    if (sa - accelerometer_y > 2500){
        direction1 = -1;
        direction1 = 2;
        if (direction1 != prevdir){
            Serial.print("left ");
            Serial.println(direction1);
 //           tone(buzzer, NOTE_B4, 2 * .9);
        }
   //     delay(2);

        prevdir = direction1;
    }
    else if (sa - accelerometer_y < -2500){
        direction1 = -1;
        direction1 = 1;
        if (prevdir != direction1){
            Serial.print("right ");
            Serial.println(direction1);
//            tone(buzzer, NOTE_FS4, 10 * .9);
        }
 //       delay(2);

        prevdir = direction1;
    }
    else if (mm - accelerometer_x < -1000){
        direction1 = -1;
        direction1 = 0;

        if (prevdir != direction1){
            Serial.print("up ");
            Serial.println(direction1);
//            tone(buzzer, NOTE_G4, 10 * .9);
        }
 //       delay(2);

        prevdir = direction1;
    }
    else if (mm - accelerometer_x > 1000){
        direction1 = -1;
        direction1 = 3;

        if (prevdir != direction1){
            Serial.print("down ");
            Serial.println(direction1);
 //           tone(buzzer, NOTE_C5, 2 * .9);
        }
//        delay(2);

        prevdir = direction1;
    }
    noTone(buzzer);

    
    // if (sa - accelerometer_y > 2500){
    //     direction1 += 1;
    //     Serial.print("right ");
    //     Serial.println(direction1);
    // }
    // else if (sa - accelerometer_y < -2500){
    //     direction1 -= 1;
    //     Serial.print("left ");
    //     Serial.println(direction1);
    // }
    
    // if (direction1 == 3){
    //     direction1 = 0;
    // }
    // else if (direction1 == -1){
    //     direction1 = 2;
    // }

    if (totalCount == 5){
        totalCount == 0;
        
        

        //handle movement
        if (direction1 == 0){
            //down
            for (int i = 0; i < 64; i++){
                if (order[i].first != defualtValue && order[i].seccond != defualtValue){
                    

                    if (i == 0){
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].first += 1;
                    }
                    else{
                        prevbucket1 = prev1;
                        prevbucket2 = prev2;
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].first = prevbucket1;
                        order[i].seccond = prevbucket2;

                    }
                }
            }
        }
        else if (direction1 == 3){
            //up
            for (int i = 0; i < 64; i++){
                if (order[i].first != defualtValue && order[i].seccond != defualtValue){
                    if (i == 0){
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].first -= 1;
                    }
                    else{
                        prevbucket1 = prev1;
                        prevbucket2 = prev2;
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].first = prevbucket1;
                        order[i].seccond = prevbucket2;

                    }
                }
            }
        }
        else if (direction1 == 1){
            //right
            for (int i = 0; i < 64; i++){
                if (order[i].first != defualtValue && order[i].seccond != defualtValue){


                    if (i == 0){
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].seccond += 1;

                    }
                    else{
                        prevbucket1 = prev1;
                        prevbucket2 = prev2;
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].seccond = prevbucket2;
                        order[i].first = prevbucket1;

                    }
                }
            }
        }
        else if (direction1 == 2){
            //left
            for (int i = 0; i < 64; i++){
                if (order[i].first != defualtValue && order[i].seccond != defualtValue){


                    if (i == 0){
               
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].seccond -= 1;
                    }
                    else{
                        prevbucket1 = prev1;
                        prevbucket2 = prev2;
                        prev1 = order[i].first;
                        prev2 = order[i].seccond;
                        order[i].seccond = prevbucket2;
                        order[i].first = prevbucket1;
                    }
                }
            }
        }


        matrix.clearDisplay(0); 


        //set led matrix
        for (int i = 0; i < 64; i++){
            if (order[i].first != defualtValue && order[i].seccond != defualtValue){
                matrix.setLed(0, order[i].first, order[i].seccond, HIGH);
            }
        }

        //handle collisions
        for (int i = 0; i < 64; i++){
            if (order[i].first != defualtValue && order[i].seccond != defualtValue){
                if (order[i].first == minRowBound){
                    //game end
                    matrix.clearDisplay(0);
                    gameOver();
                }
                if (order[i].seccond == minRowBound){
                    //game end
                    matrix.clearDisplay(0);
                    gameOver();
                }
                if (order[i].first == maxRowBound){
                    //game end
                    matrix.clearDisplay(0);
                    gameOver();
                }
                if (order[i].seccond == maxRowBound){
                    //game end
                    matrix.clearDisplay(0);
                    gameOver();
                }
                for (int j = 0; j < 64; j++){
                    if (order[i].first == order[j].first && i != j && order[i].seccond == order[j].seccond){
                        //game end
                        matrix.clearDisplay(0);
                        gameOver();

                    }
                }
            }
        }
        
        //count 20 cycles and add a dot
        if (cycleCount == 5){
            // if (order[count].first - 1 == defualtValue && order[count].first != minRowBound && order[count].seccond != minRowBound && order[count].first != maxRowBound && order[count].seccond != maxRowBound){
            //     setPos(order[count].first - 1, order[count].seccond);
            // }
            // else if(order[count].seccond - 1 == defualtValue && order[count].first != minRowBound && order[count].seccond != minRowBound && order[count].first != maxRowBound && order[count].seccond != maxRowBound) {
            //     setPos(order[count].first, order[count].seccond - 1);
            // }
            // else if(order[count].seccond + 1 == defualtValue && order[count].first != minRowBound && order[count].seccond != minRowBound && order[count].first != maxRowBound && order[count].seccond != maxRowBound) {
            //     setPos(order[count].first, order[count].seccond + 1);
            // }
            setPos(order[count - 1].first, order[count - 1].seccond + 1);
            tone(buzzer, NOTE_FS4, 50 * .9);
            delay(50);
            tone(buzzer, NOTE_G4, 50 * 0.9);
            delay(50);
            noTone(buzzer);
            cycleCount = 0;
            delay(200);
        }
        else{
            delay(300);
            cycleCount++;
        }
        
    }
    else{
        totalCount = totalCount + 1;
        delay(10);
    }
}