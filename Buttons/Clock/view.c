/* view.c -- view module for clock project
 *
 * Darren Provine, 17 July 2009
 * Xuan Do, 10 November 2017
 */

#include "clock.h"

static __attribute__((used)) const char rcsid[] =
    "$Id: view.c,v 1.5 2017/11/07 14:35:19 dox0 Exp $";


/* VIEW */

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

view_t view_props = 0x01; // default is 24-hour mode, plain text

// returns old properties so you can save them if needed
void set_view_properties(view_t newbits)
{
    view_props = newbits;
}

view_t get_view_properties()
{
    return view_props;
}

void do_test(struct tm *dateinfo)
{
    // set up bits somehow to show all the LEDs work
    digit *where = get_display_location();

    where[0] = 0xFF;
    where[1] = 0xFF;
    where[2] = 0xFF;
    where[3] = 0xFF;
    where[4] = 0xFF;
    where[5] = 0xFF;
    where[6] = 0xFF;

    display();
    fflush(stdout);
}

/* We get a pointer to a "struct tm" object, put it in a string, and
 * then send it to the screen.
 */
void show_led(struct tm *dateinfo)
{
    char   timestring[9];
    digit *where = get_display_location();
    int    i;
    digit  bitvalues = 0;
    int    hour;
    int    indicator;

    /**********************************************/
    /*                  TEST MODE                 */
    /**********************************************/
    // test mode takes highest precedence
    if (view_props & TEST ) 
    {
        do_test(dateinfo);
        return;
    }

    /**********************************************/
    /*         AM_PM MODE (FULLY WORKED)          */
    /**********************************************/
    hour=dateinfo->tm_hour;
    if ( view_props & AM_PM ) 
    {

        // copy your code from part 1
        indicator = 0x02;
        strftime (timestring, 9, "%I%M%S", dateinfo);

    } 
    /**********************************************/
    /*          24H MODE (FULLY WORKED)           */
    /**********************************************/
    else 
    {
        indicator = 0x01;
        sprintf(timestring,
                "%02d%02d%02d",
                hour,
                dateinfo->tm_min,
                dateinfo->tm_sec);
    }

    /**********************************************/
    /*          DATE MODE (FULLY WORKED)          */
    /**********************************************/
    /* if date mode, override all that */
    if ( view_props & DATE ) 
    {
        // show the date instead of the time

        indicator = 0x08;
        sprintf(timestring,
            "%02d%02d%02d",
            1 + dateinfo->tm_mon,
            dateinfo->tm_mday,
            dateinfo->tm_year % 100);
    }


    /**********************************************/
    /*           CODE TO CREATE DIGIGTS           */
    /**********************************************/
    for (i = 0; i < 6; i++) 
    {
        switch ( timestring[i] ) 
        {
            case '0': bitvalues = 0x77; break;
            case '1': bitvalues = 0x24; break;
            case '2': bitvalues = 0x5d; break;
            case '3': bitvalues = 0x6d; break;
            case '4': bitvalues = 0x2e; break;
            case '5': bitvalues = 0x6b; break;
            case '6': bitvalues = 0x7b; break;
            case '7': bitvalues = 0x25; break;
            case '8': bitvalues = 0x7f; break;
            case '9': bitvalues = 0x6f; break;
        }
        where[i] = bitvalues;
    }


    /**********************************************/
    /*                 INDICATOR                  */
    /**********************************************/
    if ( view_props & DATE ) 
    {
        where[6] = indicator;
    } 
    else 
    {
        where[6] = indicator;
        // turn on/off the dots in addition to the indicator
    }

    display();
    fflush(stdout);
}


/**********************************************/
/*              FULLY WORKED                  */
/**********************************************/
void show_text(struct tm *dateinfo)
{
    char   timestring[15];
    char   ampmstring[3] = "am"; // assume AM
    int    hour;
    
    hour=dateinfo->tm_hour;
    if ( view_props & AM_PM ) 
    {
        // copy stuff from before

        strftime (timestring, 15, "%I:%M:%S", dateinfo);

        if ( dateinfo->tm_hour < 12 )
            strcpy(ampmstring, "am");
        else
            strcpy(ampmstring, "pm");
       
    } 
    else 
    {
        sprintf(timestring,
                "%02d:%02d:%02d",
                hour,
                dateinfo->tm_min,
                dateinfo->tm_sec);
        strcpy(ampmstring, "");
    }

    printf("\r%s %s", timestring, ampmstring);
    fflush(stdout);
}


void show(struct tm *dateinfo)
{
    if ( view_props & LED_MODE )
        show_led(dateinfo);
    else
        show_text(dateinfo);
}
