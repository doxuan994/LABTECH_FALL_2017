/* clock.c -- controller part of the clock project
 *
 * Darren Provine, 17 July 2009
 * Xuan Do, 10 November 2017
 */

#include "clock.h"

static __attribute__((used)) const char rcsid[] =
    "$Id: clock.c,v 1.4 2017/11/07 14:39:28 dox0 Exp $";


/* CONTROLLER */

static char bugaddress[]="kilroy@elvis.rowan.edu";

// version -- say which version this is and exit
// (note simple output; you could also print the rcsid too)
void version()
{
    fprintf(stderr, "simple clock version 3\n");
    exit(0);
}

// usage -- print brief summary and instructions
void usage(char *progname)
{
    fprintf(stderr, "This program displays a realtime clock.\n");
    fprintf(stderr, "Usage: %s [-avh] [-o number]\n", progname);
    fprintf(stderr, "  -a    : am/pm instead of 24 hour\n");
    fprintf(stderr, "  -l    : use simulated LED display\n");
    fprintf(stderr, "  -o #  : offset the time by # seconds \n");
    fprintf(stderr, "  -v    : show version information\n");
    fprintf(stderr, "  -h    : this help message\n");
    fprintf(stderr, "report bugs to %s \n", bugaddress);
    exit (0);
}

/* This has to be global because tick() is called automatically;
 * we can't pass it any arguments because we don't call it.
 */
int offset = 0;

// These store when the different modes end.
int test_expires = 0;
int date_expires = 0;

void process_key(keybits KeyCode)
{
    void    stop_clock(void);
    int     KeyRow, KeyCol;
    int     view_props;

    // Do something with KeyCode

    /**********************************************/
    /*          MOUSE HIT (FULLY WORKED)          */
    /**********************************************/
    if (KeyCode & 0x80) {  // mouse hit

        // manipulate bits to set KeyCol and KeyRow
        KeyRow = 0;
        KeyCol = KeyCode & 0x0F;

        // mandatory keys
        if (KeyRow == 0) 
        {
            switch (KeyCol) 
            {
                case 0: // 24-hour mode
                    view_props = get_view_properties();
                    view_props &= ( ~ AM_PM );
                    set_view_properties (view_props);
                    break;
                case 1: // AM/PM
                    view_props = get_view_properties();
                    view_props |= ( AM_PM );
                    set_view_properties (view_props);
                    break;
                case 2: // Date
                    view_props = get_view_properties();
                    view_props |= ( DATE );
                    set_view_properties (view_props);
                    date_expires = time( (time_t *) NULL) + 5;
                    break;
                case 3: // Test
                    view_props = get_view_properties();
                    view_props |= ( TEST );
                    set_view_properties (view_props);
                    test_expires = time( (time_t *) NULL) + 5;
                    break;
                case 4:
                    stop_clock();
                    break;
            }
        } 
        else if (KeyRow == 1) 
        {
            // make up your own buttons
        }
    } 
    /**********************************************/
    /*          KEYSTROKE (FULLY WORKED)          */
    /**********************************************/
    else 
    { // keystroke
        switch(KeyCode) 
        {
            case '2':
                view_props = get_view_properties();
                view_props &= ( ~ AM_PM );
                set_view_properties (view_props);
                break;
            case 'a':
                view_props = get_view_properties();
                view_props |= ( AM_PM );
                set_view_properties (view_props);
                break;
            case 'd':
                view_props = get_view_properties();
                view_props |= ( DATE );
                set_view_properties (view_props);
                date_expires = time( (time_t *) NULL) + 5;
                break;
            case 't':
                view_props = get_view_properties();
                view_props |= ( TEST );
                set_view_properties (view_props);
                date_expires = time( (time_t *) NULL) + 5;
                break;
            case 'q':
                stop_clock();
                break;
        }
    }

    // force update when keys are hit
    tick(0);
}

void stop_clock()
{
    end_display();
    exit(0);
}

int main(int argc, char *argv[])
{
    char title_text[79] = " A digital clock for LABTECH project fall 2017. Welcome to Xuan Do 's Clock!";
    int letter;  // option character

    view_t view_props = 0; // clear all bits -> 24hr text mode
    int    ampm = 0;       // default to 24hr
    int    LED  = 0;       // default to text

    // loop through all the options; getopt() can handle together or apart
    while ( ( letter = getopt(argc, argv, "alo:vh")) != -1 ) 
    {
        switch (letter) 
        {
            case 'a':  ampm = 1;               break;
            case 'l':  LED  = 1;               break;
            case 'o':  offset = atoi(optarg);  break;
            case 'v':  version();              break;
            case 'h':  usage(argv[0]);         break;

            case '?':  // unknown flag; fall through to next case
            default:   // shouldn't happen, but Just In Case
                       // note that getopt() warns about the unknown flag
                  fprintf(stderr, "run \"%s -h\" for help\n", argv[0]);
                  exit(1);
        }
    }

    // All the flags have been scanned.
    // "optind" is now the index of the first non-option item

    // set view properties
    if ( ampm )
        view_props = AM_PM;
    if ( LED )
        view_props |= LED_MODE; // note |= to switch on a bit

    set_view_properties (view_props);

    if (LED) { // set up the fancy display
        start_display();
        // has to be exactly 78 chars
        set_title_bar(title_text);
        register_keyhandler(process_key);

        // turn on some keys in row 2; max 6 chars
        set_key_text(0, "click");
        set_key_text(1, " here");
    
    }

    /* get the model running */
    start_timer();

    while (1) 
    {
        if ( LED )
            get_key(); /* read keys if in LED mode */
        else
            pause();
    }

    /* no return because never reached */
}


/* This function is called when the timer ticks.
 * Then it calls the show() function, which is our View.
 * The Controller talks to the Model and the View.
 *
 * Note we ignore the argument!
 * sigaction() arranges to pass us the signal that caused the function
 * to be called, so you can use one signal handler for multiple signals.
 * But we only catch one signal, so no need to worry about it.
 */
void tick(int sig)
{
    time_t       now;
    struct tm   *dateinfo;  // localtime() returns a pointer, so it
                            // allocates space.  We just need a pointer.
    int     view_props;

    /* get current time into "struct tm" object */
    (void) time(&now);

    /* check special mode expirations - have to do BEFORE offset */
    if ( now > date_expires ) {
        view_props = get_view_properties();
        view_props &= ( ~ DATE );
        set_view_properties (view_props);
    }

    if ( now > test_expires ) {
        view_props = get_view_properties();
        view_props &= ( ~ TEST );
        set_view_properties (view_props);
    }

    now += offset;
    dateinfo = localtime( &now );

    /* call View to show the time */
    show(dateinfo);
}
