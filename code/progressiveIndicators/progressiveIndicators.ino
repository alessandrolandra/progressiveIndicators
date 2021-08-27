#include <Adafruit_NeoPixel.h>

#define LED_PIN_R       1
#define LED_PIN_L       3
#define TURN_RIGHT      2
#define TURN_LEFT       4
#define NUM_LEDS        17
#define MATRIX_LENGTH   21

uint8_t matrix[] = {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Adafruit_NeoPixel strip_l = Adafruit_NeoPixel(NUM_LEDS, LED_PIN_L, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip_r = Adafruit_NeoPixel(NUM_LEDS, LED_PIN_R, NEO_RGB + NEO_KHZ800);

void setup() {
    uint8_t i,k,arr[2];
    pinMode(TURN_RIGHT,INPUT);
    pinMode(TURN_LEFT,INPUT);
    pinMode(LED_PIN_L,OUTPUT);
    pinMode(LED_PIN_R,OUTPUT);

    strip_l.begin();
    strip_r.begin();    

    delay(1000);
    emptyStrips();
}


void loop()
{
    static int off,cnt_l=MATRIX_LENGTH,cnt_r=MATRIX_LENGTH;
    
    if(!digitalRead(TURN_LEFT) && cnt_l>10){  
          off=3;
          cnt_l=0;
          emptyStrips();
    }
    if(!digitalRead(TURN_RIGHT) && cnt_r>10){
          off=3;
          cnt_r=0;
          emptyStrips();
    }
    if(cnt_l<MATRIX_LENGTH){
        for(int i=0;i<NUM_LEDS;i++){
            if(matrix[(off+i)%MATRIX_LENGTH]){
                strip_l.setPixelColor(i, strip_l.Color(40,255,0));
            }else{
                strip_l.setPixelColor(i, strip_l.Color(0,0,0));
            }
        }
        strip_l.show();
        off--;
        if(off<0)
          off+=MATRIX_LENGTH;
        cnt_l++;
    }else if(cnt_r<MATRIX_LENGTH){
        for(int i=0;i<NUM_LEDS;i++){
            if(matrix[(off+i)%MATRIX_LENGTH]){
                strip_r.setPixelColor(i, strip_r.Color(40,255,0));
            }else{
                strip_r.setPixelColor(i, strip_r.Color(0,0,0));
            }
        }
        strip_r.show();
        off--;
        if(off<0)
          off+=MATRIX_LENGTH;
        cnt_r++;       
    }    
    delay(40);
}

void emptyStrips(){
    for( int i = 0; i < NUM_LEDS; ++i) {
        strip_l.setPixelColor(i, strip_l.Color(0,0,0));
        strip_r.setPixelColor(i, strip_r.Color(0,0,0));
        strip_l.show();
        strip_r.show();
    }
}
