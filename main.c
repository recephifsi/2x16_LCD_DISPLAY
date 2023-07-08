#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "io.h"
#include "lcdm.h"

void init(void)
{
  // System Clock init
  Sys_ClockInit();

  // I/O port init
  Sys_IoInit();

  // LED init
  IO_Write(IOP_LED, 1);
  IO_Init(IOP_LED, IO_MODE_OUTPUT);

  // LCDM init
  LCD_Init();
}

void Task_LED(void)
{
  static enum {
    I_LED_OFF,
    S_LED_OFF,
    I_LED_ON,
    S_LED_ON,
  } state = I_LED_OFF;

  static clock_t t0; // Duruma ilk gecis saati
  clock_t t1;        // Guncel saat degeri

  t1 = clock();

  switch (state)
  {
  case I_LED_OFF:
    t0 = t1;
    IO_Write(IOP_LED, 1); // LED off
    state = S_LED_OFF;
    break;
  case S_LED_OFF:
    if (t1 >= t0 + 9 * CLOCKS_PER_SEC / 10)
      state = I_LED_ON;
    break;

  case I_LED_ON:
    t0 = t1;
    IO_Write(IOP_LED, 0); // LED On
    state = S_LED_ON;
    break;
  case S_LED_ON:
    if (t1 >= t0 + CLOCKS_PER_SEC / 10)
      state = I_LED_OFF;
    break;
  }
}

int main()
{
  // general init
  init();

  LCD_DisplayOn(LCD_MODE_ON | LCD_MODE_CURSOR);

  LCD_SetCursor(0x04); // ilk satir basi
  LCD_PutChar('D');
  LCD_PutChar('e');
  LCD_PutChar('n');
  LCD_PutChar('e');
  LCD_PutChar('m');
  LCD_PutChar('e');

  LCD_SetCursor(0x40); // ikinci satir basi
  LCD_PutChar('T');
  LCD_PutChar('e');
  LCD_PutChar('s');
  LCD_PutChar('t');

  while (1)
  {
    Task_LED();
  }

  return 0;
}
