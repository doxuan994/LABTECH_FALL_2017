/* view.c -- view module for clock project
 *
 * Darren Provine, 17 July 2009
 * Xuan Do, 31 October 2017
 */

#include "clock.h"
#include "string.h"

/* VIEW */

/* We get a pointer to a "struct tm" object, put it in a string, and
 * then send it to the screen.
 */
void ledshow(struct tm *dateinfo, int ampm)
{
    char       timestring[9];
    digit *where = get_display_location();
    int i;

    /* Note that we have removed the colons to make this
     * part easier to write.
     */
    sprintf(timestring,
            "%02d%02d%02d",
            dateinfo->tm_hour,
            dateinfo->tm_min,
            dateinfo->tm_sec);

    for (i = 0; i < 6; i++) 
    {
        switch ( timestring[i] ) 
        {
            case ' ': where[i] = 0x00; break;
            case '1': where[i] = 0x24; break;
            case '2': where[i] = 0x5D; break;
            case '3': where[i] = 0x6D; break;
            case '4': where[i] = 0x2E; break;
            case '5': where[i] = 0x6B; break;
            case '6': where[i] = 0x7B; break;
            case '7': where[i] = 0x25; break;
            case '8': where[i] = 0x7F; break;
            case '9': where[i] = 0x2F; break;
            case '0': where[i] = 0x77; break;
       }
    }

    // colons + am/pm
    if ( dateinfo->tm_sec % 2 == 0 )
    {
        where[6] = 0x31;
    } else {
        where[6] = 0xc1;
    }

    display();
    fflush(stdout);
}

void show(struct tm *dateinfo, int ampm)
{
    char       timestring[9];
    char       ampmstring[3] = "";
    
    // TODO: handle "ampm" setting
    if ( dateinfo->tm_hour < 12 )
        strcpy(ampmstring, "am");
    else
        strcpy(ampmstring, "pm");

    sprintf(timestring,
            "%02d:%02d:%02d",
            dateinfo->tm_hour,
            dateinfo->tm_min,
            dateinfo->tm_sec);

    printf("\r%s %s ", timestring, ampmstring);
    fflush(stdout);
}
