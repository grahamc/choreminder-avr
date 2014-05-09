#include "chores.h"

char * tasks[CHORE_COUNT] = {
/*
  "                \n              ",
*/
/// Week
  "Wipe front of   \nappliances    ",
  "Trash can       \n              ",
  "Tidy books,     \nlinens        ",
  "Organize the    \nfront closet  ",
  "Fridge, Freezer \nwipe & tidy   ",
  "Wipe cabinets   \n(front)       ",
  "Mop floor       \n              ",
// Week
  "Wipe front of   \nappliances    ",
  "Utensil holders \nFridge top    ",
  "Fridge, Stove   \n(under)       ",
  "Seals: disposal/\nfridge/washer ",
  "Windows, and    \nSills         ",
  "Wipe decorations\n              ",
  "Mop floor       \n              ",
// Week
  "Wipe front of   \nappliances    ",
  "Tidy cabinets   \n              ",
  "Cycle cloths    \nsponge        ",
  "Cabinet         \ninteriors     ",
  "Wipe walls      \n              ",
  "Wipe cabinets   \n(front)       ",
  "Mop floor       \n              ",
// Week
  "Wipe front of   \nappliances    ",
  "Organize pots   \npans, drawers ",
  "Scrub sink      \nwipe faucet   ",
  "Fridge, Freezer \nwipe & tidy   ",
  "Clean microwave \nOven->Clean   ",
  "Wipe            \nbaseboards    ",
  "Mop floor       \n              ",
// Week
  "Wipe front of   \nappliances    ",
  "Dust: switches, \nlights, vents ",
  "Wipe down bike  \nsmears        ",
  "Clean hallway   \nand stoop     ",
  "Clean the mantel\n              ",
  "Organize the    \nback closet   ",
  "Mop floor       \n              "
};

void write_next_chore()
{
  uint8_t chore_pointer = get_chore_location();

  USART0SendString(tasks[chore_pointer++]);

  chore_pointer++;
  set_chore_location(chore_pointer);
}

uint8_t get_chore_location() {
 uint8_t chore_pointer = eeprom_read_byte(0);

  if (chore_pointer >= CHORE_COUNT) {
    chore_pointer = 0;
  }

  return chore_pointer;
}

void set_chore_location(uint8_t i) {
  eeprom_write_byte(0, i);
}

