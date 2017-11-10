/* monsters.c - monster abilities and vulnerabilities.
 *
 * Xuan Do Fall 2017
 */

 #include <stdio.h>
 #include <string.h>
 #include <strings.h>
 
 /* MONSTER ATTACKS AND BIT POSITIONS
  *
  * fire -------------------+
  * bite -----------------+ |
  * claw ---------------+ | |
  * acid -------------+ | | |
  * frost --------+   | | | |
  * poison -----+ |   | | | |
  *             | |   | | | |
  *             V V   V V V V
  *         0 0 0 0   0 0 0 0
  */
 #define  FIRE    0x01
 #define  BITE    0x02
 #define  CLAW    0x04
 #define  ACID    0x08
 #define  FROST   0x10
 #define  POISON  0x20
 
 /* MONSTER TYPES
  * (note use of bitwise OR; each bit is a different kind of attack)
  */
 #define WOLF    ( BITE )
 #define COUGAR  ( BITE | CLAW )
 #define TIGER   ( BITE | CLAW )
 #define COBRA   ( BITE | POISON )
 #define DRAGON  ( FIRE | BITE | CLAW )
 #define YETI    ( BITE | CLAW | FROST )
 #define ALIEN   ( BITE | ACID )
 
 /* DEFENSES
  * (again; "|" means defense protects against all things listed)
  */
 #define  NONE        ( 0x00 )
 #define  INSULATION  ( FIRE | FROST )
 #define  ARMOR       ( BITE | CLAW )
 #define  AMULET      ( POISON | ACID )
 
 
 // for input buffer reading monsters and equipment
 #define BUFSIZE 64
 
 /* INPUT FORMAT: monster name followed by equipment name(s).
  * Examples:
  *   dragon
  *   tiger none
  *   wolf armor amulet
  *   cobra insulation
  * Equipment can be in any order.
  * WARNING: does minimal error-checking!  Bogus input may cause
  * random results!
  */
 
 /* This main routine just has driver code: it runs values
  * through the report_danger() function.
  * You have to write that function (at the bottom), but
  * don't make any changes to main().
  */
 int main()
 {
     void report_danger(int, int); // function prototype
     int  equipment;
     int  monster;
     int  itemsread;
     char monster_name[20];
     char equipment_name[20];
     char line[BUFSIZE];
     int  offset; // for multiple sscanf() calls on one line
     char *data;  // pointer to where on line we want to read
 
     while ( fgets(line, BUFSIZE, stdin) != NULL ) {
         // reset for start of loop
         offset = 0;
         data = &line[0]; // beginning of line
 
         itemsread = sscanf(line, "%s%n", monster_name, &offset);
 
         if ( ! strncasecmp(monster_name, "wolf", 4) ) {
             monster = WOLF;
         } else if ( ! strncasecmp(monster_name, "cougar", 6) ) {
             monster = COUGAR;
         } else if ( ! strncasecmp(monster_name, "tiger",  5) ) {
             monster = TIGER;
         } else if ( ! strncasecmp(monster_name, "cobra",  5) ) {
             monster = COBRA;
         } else if ( ! strncasecmp(monster_name, "dragon", 6) ) {
             monster = DRAGON;
         } else if ( ! strncasecmp(monster_name, "yeti",   4) ) {
             monster = YETI;
         } else if ( ! strncasecmp(monster_name, "alien",  5) ) {
             monster = ALIEN;
         } else {
             monster = NONE;
         }
 
         // move our start point ahead to the next part of the line
         data += offset;
 
         // blank out all the bits to start
         equipment = NONE;
         while ( (itemsread = sscanf(data, "%s%n", equipment_name, &offset) )
                 != EOF ) {
             if ( ! strncasecmp(equipment_name, "insulation", 10) ) {
                 equipment |= INSULATION;
             } else if ( ! strncasecmp(equipment_name, "armor",  5) ) {
                 equipment |= ARMOR;
             } else if ( ! strncasecmp(equipment_name, "amulet", 6) ) {
                 equipment |= AMULET;
             }
             data += offset;
         }
 
         // get rid of newline from input
         line[strcspn(line, "\n")] = '\0';
 
         printf("%35s - ", line);
 
         report_danger(equipment, monster);
     }
 
     return 0;
 }
 
 
 
 /* void function - does not return anything
  *
  * report_danger takes two arguments:
  *   1) What defenses the user has
  *   2) What kind of monster it is (which attacks it has)
  *
  * report_danger should print out what things the
  * user has to worry about.
  */
 
 void report_danger(int defenses, int monster)
 {
     // DECLARE SOME VARIABLES, IF NEEDED
     printf("beware of: ");

 
     // YOU WRITE THIS PART
     // You have to find bits that are ON in the monster
     // but OFF in the defenses.


    // if monster is wolf check if defenses with 0x02 on
    // if not then warn for bite
    if (  monster == WOLF ) {
        if ( ( defenses & BITE ) != 2 ) 
            printf(" bite");
    } 
    // continue to check if monster is cougar or tiger
    // check if defenses with 0x02 or 0x04 on 
    // if not then warn for bite or claw 
    else if ( monster == COUGAR || monster == TIGER ) {
        if ( ( defenses & CLAW ) != 4 ) 
            printf(" claw");
        if ( ( defenses & BITE ) != 2 ) 
            printf(" bite");
    }
    // continue to check if monster is cobra 
    // check if defenses with 0x02 or 0x20 on 
    // if not then warn for bite or poison
    else if ( monster == COBRA ) {
        if ( ( defenses & POISON ) != 20 )
            printf(" poison");
        if ( ( defenses & BITE ) != 2 ) {
            printf(" bite");
        }
    } 
    // continue to check if monster is dragon
    // check if defenses with 0x01, 0x02 or 0x04 on
    // if not then warn for fire, bite or claw
    else if ( monster == DRAGON ) {
        if ( ( defenses & CLAW ) != 4 )
            printf(" claw");
        if ( ( defenses & BITE ) != 2 ) 
            printf(" bite");
        if ( ( defenses & FIRE ) != 1 )
            printf(" fire");
    } 
    // continue to check if monster is yeti
    // check if defenses with 0x02, 0x04 or 0x10 on
    // if not then warn for bite or claw frost
    else if ( monster == YETI ) {
        if ( ( defenses & FIRE ) != 2 )
            printf(" fire");
        if ( ( defenses & BITE ) != 4 ) 
            printf(" bite");
        if ( ( defenses & CLAW ) != 10 )
            printf(" frost");
    } 
    // continue to check if monster is alien
    // check if defenses with 0x02 or 0x08 on
    // if not then warn for bite or acid
    else if ( monster == ALIEN ) {
        if ( ( defenses & ACID ) != 8 ) 
            printf(" acid");
        if ( ( defenses & BITE ) != 2 )
            printf(" bite");
    }
    printf("\n");
    return;
}
