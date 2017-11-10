/* view.h -- #defines for view options
 *
 * D Provine, 17 October 2017
 */

/* VIEW OPTIONS
 *
 * AM / PM mode ---------------+ 
 * unused -------------------+ |
 * date -------------------+ | |
 * LED mode--------------+ | | |
 *                       | | | |
 * unused ---------+     | | | |
 * unused -------+ |     | | | |
 * unused -----+ | |     | | | |
 * unused ---+ | | |     | | | |
 *           | | | |     | | | |
 *           V V V V     V V V V
 *           0 0 0 0     0 0 0 0
 */
#define  AM_PM     0x01
#define  DATE      0x04
#define  LED_MODE  0x08
#define  TEST      0x10

typedef unsigned int view_t;

// set packed bits for what you want
void set_view_properties( view_t );
view_t get_view_properties( void );

void show(struct tm *);

