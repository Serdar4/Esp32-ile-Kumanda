#include <Arduino.h>
#include <BleGamepad.h>

BleGamepad gamepad("ESP32 Gamepad");

// Pin tanımlamaları

#define L_HomeButton 26
#define L_leftButton 25
#define L_bottomButton 14
#define L_rightButton 27

#define R_topButton 13
#define R_leftButton 12
#define R_bottomButton 2
#define R_rightButton 15

bool HomeButtonDurum;
bool AtamaMod = false;

double R_topButtonDeger,R_leftButtonDeger,R_bottomButtonDeger,R_rightButtonDeger;


void setup() {

  
  Serial.begin(115200);
  gamepad.begin();

  //Gerekli tuş tanımlamaları
  pinMode(L_HomeButton,INPUT);
  pinMode(L_leftButton,INPUT);
  pinMode(L_bottomButton,INPUT);
  pinMode(L_rightButton,INPUT);

  pinMode(R_topButton,INPUT);
  pinMode(R_leftButton,INPUT);
  pinMode(R_bottomButton,INPUT);
  pinMode(R_rightButton,INPUT);

}

void loop() {

  if(gamepad.isConnected()){

    //Sol Butonların tanımlanması

    if(digitalRead(L_HomeButton)){    // Mod Seçim Butonu kontorlü
      while(digitalRead(L_HomeButton));
      HomeButtonDurum = true;
    }
    if(HomeButtonDurum){  // Mod Seçim butonu aktifse çalışacaklar
      Serial.println("Girmek istediginiz modu seciniz: \n(Sol Butonlardan Seciniz)");
      Serial.println("Atama Mod[Sol Buton]");
      Serial.println("2. Mod[Alt Buton]");
      Serial.println("3. Mod[Sag Buton]");

      if(digitalRead(L_leftButton)){  // Sol Butona basıldığında çalışacaklar
        while(digitalRead(L_leftButton));
        Serial.println("Sol butona basildi");
        Serial.println("Atama Modu Aktif");

        AtamaMod = !AtamaMod;

        delay(100);

        // SAĞ BUTONLAR İÇİN ATAMA YAPMA MODU

        if(AtamaMod == true){
          Serial.println("Atama modu aktif\n Atama yapmak istediginiz Sag butona basiniz");

          if(digitalRead(R_leftButton)){  // Sol buton için Atama yapılması
            while(digitalRead(R_leftButton));

             R_leftButtonDeger = Serial.parseInt();

          }else if(digitalRead(R_topButton)){ // üst buton için atama yapılması
            while(digitalRead(R_topButton));

             R_topButtonDeger = Serial.parseInt();

          }else if(digitalRead(R_bottomButton)){  // Alt buton için atama yapılması
            while(digitalRead(R_bottomButton));

            R_bottomButtonDeger = Serial.parseInt();

          }else if(digitalRead(R_rightButton)){ // Sağ buton için atama yapılması
            while(digitalRead(R_rightButton));

            R_rightButtonDeger = Serial.parseInt();

          }

        }

      }else if(digitalRead(L_bottomButton)){  // Alt butona basıldığında çalışacaklar
        while(digitalRead(L_bottomButton));
        Serial.println("Alt butona basildi");
        Serial.println("2. Mod AKTIF");
        delay(100);

      }else if (digitalRead(L_rightButton)){  // Sağ butona basıldığında çalışacaklar
        while(digitalRead(L_rightButton));
        Serial.println("Sag butona basildi");
        Serial.println("3. Mod AKTIF");
        delay(100);
        
      }
      if(digitalRead(L_HomeButton)){  // Home butonuna tekrar basıldığında Mod seçim menüsü kapanacaktır
        while(digitalRead(L_HomeButton))
        HomeButtonDurum == false;
      }
      
      
    }

    // Sağ Butonların Tanımlanması

    if(digitalRead(R_topButton)){ // Üst butonun değerinin gösterilmesi
      while(digitalRead(R_topButton));

      Serial.println(R_topButtonDeger);
      gamepad.press(4);
      delay(250);
      gamepad.release(4);

    }else if(digitalRead(R_leftButton)){  // Sol butonun değerinin gösterilmesi
      while(digitalRead(R_leftButton));

      Serial.println(R_leftButtonDeger);
      gamepad.press(3);
      delay(250);
      gamepad.release(3);

    }else if(digitalRead(R_bottomButton)){  // Alt butonun değerinin gösterilmesi
      while(digitalRead(R_bottomButton));

      Serial.println(R_bottomButtonDeger);
      gamepad.press(1);
      delay(250);
      gamepad.release(1);

    }else if(digitalRead(R_rightButton)){ // Sağ butonun değerinin gösterilmesi
      while(digitalRead(R_rightButton));

      Serial.println(R_rightButtonDeger);
      gamepad.press(2);
      delay(250);
      gamepad.release(2);

    }
  }else{
    Serial.println("Bluetooth bağlantisi yok"); // Bluetoth bağlı değilse 
    delay(1000);

  }
}