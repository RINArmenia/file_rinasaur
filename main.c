#include "main.h"
#include "client.h"
#include "server.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
//functions
// void loadInput();

int main(int argc, char** argv) {


    printf("\nServer [s] or Client [c], that is the question!\n");

    //choosing server or client side
    while (1) {
        scanf("%c", &app_side);
        switch (app_side) {
        case 'c':
            loadClient();
            break;
        case 's':
            loadServer();
            break;
            //          default:
            //                  printf("Try again bitch!\n");
            //                  continue;
        }
    }

    // endwin();
    // loadInput();
    // rina_unregister(open_fd, NULL, appl_name, 0);
    return 0;
}

// void loadInput(){
//
//         int y;
//         int x;
//
//         int action = 1;
//
//         while (action == 1) {
//
//                 y = 1;
//                 x = 2;
//                 //rows
//                 while (y < input_h - 1) {
//                         //letters in row
//                         while (x < input_w - 2) {
//                                 action = mvwgetch(inputwin, y, x);
//                                 //start OK
//                                 if (action == KEY_BACKSPACE) {
//                                         printf("hello");
//                                 }
//                                 //end OK
//                                 x++;
//                         }
//                         y++;
//                         x = 2;
//                 }
//
//                 //      reset the window because it's full
//                 wclear(inputwin);
//                 box(inputwin, 0, 0);
//                 mvwprintw(inputwin, 0,1, " Input ");
//                 wrefresh(inputwin);
//                 endwin();
//         }
// }
