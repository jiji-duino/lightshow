 
enum LEDS {red1=8, yellow1=9, green1=10, red2=11, yellow2=12, green2=13, red3=2, green3=3, yellow3=4, red4=5, green4=6, yellow4=7}; // leds=pins
int leds1[] = {red1, yellow1, green1, red2, yellow2, green2, red3, green3, yellow3, red4, green4, yellow4};         // table of led enum first order
int leds2[] = {red3, green3, yellow3, red4, green4, yellow4, red1, yellow1, green1, red2, yellow2, green2};         // table of led enum second order
int leds3[] = {green1, yellow1, red1, yellow4, green4, red4};  // table of led enum third and fourth order
int leds4[] = {red2, yellow2, green2, red3, green3, yellow3};  // table of led enum third andfourth order
int alternate[] = {red1, green1, yellow2, red3, yellow3, green4, yellow4, yellow1, red2, green2, green3, red4}; // table of alternation order

int rows[4][6] = { {red1, yellow1, green1, red2, yellow2, green2} , {red3, yellow3, green3, red4, yellow4, green4} }; // table of rows (row1, row2, row1, row2)

int colors[3][4] = { {red1, red2, red3, red4} , {yellow1, yellow2, yellow3, yellow4} , {green1, green2, green3, green4} }; // table of colors order

int parity[6][2] = { {red1, yellow1} , {red4, yellow3} , {yellow2, green2} , {red3, green3} , {red2, green1} , {green4, yellow4} }; // table of parity order


void setup() {

  for (int i=0; i<12; i++) { //Set all LEDs as outputs
    pinMode(leds1[i], OUTPUT);
  }
  Serial.begin(9600);    // Starting Serial communication
  Serial.println("Type start to start the lightshow!"); 
}

void loop() {
  int count_color = 0;   // count to repeat color animation cause I like it :)
  int count_row = 0;     // Same thing for rows  
  if (Serial.readString() == "start") {   //Condition to start (you have to type "start")
    Serial.println("Show started!");      // Tells you the show has started

  // 1. first order
    for (int i=0; i<12; i++) {      //Turns all of them on
      digitalWrite(leds1[i], HIGH);
      delay(70);
    }
    for (int i=11; i>=0; i--) {     //Turns all of them off in reverse
      digitalWrite(leds1[i], LOW);
      delay(70);
    }
    delay(150);   // little delay between animations

  // 2. second order
    for (int i=0; i<12; i++) {      //Turns all of them on 
      digitalWrite(leds2[i], HIGH);
      delay(70);
    }
    for (int i=11; i>=0; i--) {     //Turns all of them off in reverse
      digitalWrite(leds2[i], LOW);
      delay(70);
    }
    delay(150);   // little delay between animations

  // 3. third order
    for (int i=0; i<6; i++) {
      digitalWrite(leds3[i], HIGH);
      digitalWrite(leds4[i], HIGH);
      delay(100);
    }
    for (int i=5; i>=0; i--) {
      digitalWrite(leds3[i], LOW);
      digitalWrite(leds4[i], LOW);
      delay(100);
    }
    delay(200);

  // 4. fourth order
    for (int i=5; i>=0; i--) {
      digitalWrite(leds3[i], HIGH);
      digitalWrite(leds4[i], HIGH);
      delay(70);
    }
    for (int i=0; i<6; i++) {
      digitalWrite(leds3[i], LOW);
      digitalWrite(leds4[i], LOW);
      delay(100);
    }
    delay(200);

  // 5. color order
    while (count_color != 2) {     // To repeat color order 2 times
      for (int i=0; i<3; i++) {
        for (int j=0; j<4; j++) {
          digitalWrite(colors[i][j], HIGH);  // all on (red then yellow then green then repeat)
        }
        delay(150);

        for (int j=0; j<4; j++) {
          digitalWrite(colors[i][j], LOW);   // all off (red then yellow then green then repeat)
        }
      }
      delay(200);
      count_color ++;
    }

  // 6. row order
    while (count_row != 2) {
      for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
          digitalWrite(rows[i][j], HIGH);    //all on (row 1 then row 2 then repeat)
        }
        delay(150);

        for (int j=0; j<6; j++) {
          digitalWrite(rows[i][j], LOW);     // all off (row 1 then row 2 then repeat)
        }  
      }
      delay(200);
      count_row ++;
    }

  // 7. parity order
    for (int i=0; i<6; i++) {
      for (int j=0; j<2; j++) {
        digitalWrite(parity[i][j], HIGH);    //all on
      }
      delay(150);
    }
    delay(200);
  
  // - stop all
    for (int i=0; i<12; i++) {      //all off 
      digitalWrite(leds1[i], LOW);
    }
    delay(1000);

  // 8. alternation order
    for (int i=0; i<12; i++) {
      digitalWrite(alternate[i],HIGH);    //all on
      delay(150);
    }
    delay(200);

    for (int i=11; i>=0; i--) {           // all off
      digitalWrite(alternate[i],LOW);
    }
    delay(200);

  // 9. fading sequence 
    // Breathe IN (0 → 255)
    for (int b = 0; b <= 255; b++) {     // brightness increase control
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
          analogWrite(colors[i][j], b);  //just chose random table when all leds are present
        }
      }
      delay(10);
    }

    // Breathe OUT (255 → 0)  
    for (int b = 255; b >= 0; b--) {    // brightness decrease control
      for (int i = 2; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
          analogWrite(colors[i][j], b);
        }
      }
      delay(10);
    }
    delay(200);
    // The reason why in the middle of the fading sequence all LEDs litup is because the ones who support PWM fade but those who don't only response when it's 255
  Serial.println("Show stopped!");        // Tells you the show has ended
  }
}
