## Dependencies
Download [click on MotorWebUI.zip] the WEB part from libray here:
- [MotorWebUI](https://github.com/koanasta/MotorWebUI/releases/tag/v1.0.0)

Для встановлення бібліотеки для Web керування мотором, перейдіть у розділ Releases репозиторію (посилання вище) та завантажте файл MotorWebUI.zip. 

Для встановлення бібліотеки в Arduino IDE: Sketch → Include Library → Add .ZIP Library -> обираєте завантажений zip файл.

Після встановлення бібліотеки, скопіюйте цей код у ваш файл і додавайте свою c++ частину:
#include <MotorWebUI.h>
// решта потрібних бібліотек
// ваш код тут


void onMove(int deg, bool dir) {
  long steps = (long)(deg * STEPS_PER_DEGREE);
  if (dir) stepper.move(steps);
  else stepper.move(-steps);
}


void onStop() {
  stepper.stop();
  stepper.setCurrentPosition(stepper.currentPosition());
  // функція вимкнення котушок
}


void setup() {
  //ваш код


  initWeb(server);
}
void loop() {
  handleWeb();

  //ваш код
}

