#include "displayFuncs.h"
#include "graphics.h"
#include <conio.h> // for  _getch()

extern "C" void incA(int* p, int val);
extern "C" void initA(int* p, int val);

void initGraph() {
    // gm is Graphics mode which is
    // a computer display mode that
    // generates image using pixels.
    // DETECT is a macro defined in
    // "graphics.h" header file
    int gd = DETECT, gm;

    // initgraph initializes the
    // graphics system by loading
    // a graphics driver from disk
    initgraph(&gd, &gm, " ");
}

void closeGraph() {
    // closegraph function closes the
    // graphics mode and deallocates
    // all memory allocated by
    // graphics system
    closegraph();

    // getch function pauses the
    // Output Console untill
    // a key is pressed
    _getch();
}

void printByX(char* letters[], int clrz[],
        int sz, int* x, int y, int val) {
    int i;
    initA(&i, 0);
    for(; i < sz; i++) {
        setcolor(clrz[i]);
        outtextxy(*x, y, letters[i]);
        incA(x, val);
    }
}

void printByY(char* letters[], int sz,
              int x, int* y, int val) {
    int i = 0;
    initA(&i, 0);
    for(; i < sz; i++) {
        outtextxy(x, *y, letters[i]);
        incA(y, val);
    }
}

void printGoogleFeud() {
    // for setting text style:
    // front style = 8;
    // direction = 0;
    // front size = 5;
    settextstyle(8, 0, 5);

    // location of text
    int x, y, sz;
    initA(&x, 150);
    initA(&y, 30);
    initA(&sz, 6);

    char* google[sz] =
        { "G", "o", "o", "g", "l", "e" };
    int clrzGoogle[sz] =
        { 1, 4, 14, 1, 2, 4 };
    printByX(google, clrzGoogle, sz,
                &x, y, 30);
    delete[] google;


    initA(&sz, 4);
    char* feud[sz] =
        { "F", "e", "u", "d" };
    int clrzFeud[sz] =
        { 1, 4, 14, 2 };
    incA(&x, 20);
    printByX(feud, clrzFeud, sz,
                &x, y, 30);
    delete[] feud;
 }

void printNumerics() {
    setcolor(BLUE);
    int x, y, sz;
    initA(&x, 30);
    initA(&y, 200);
    initA(&sz, 5);

    char* numz1[sz] =
    { "1.",  "2.", "3.", "4.", "5." };
    printByY(numz1, sz, x, &y, 25);
    delete[] numz1;

    initA(&x, 325);
    initA(&y, 200);
    char* numz2[sz] =
    { "6.",  "7.", "8.", "9.", "10." };
    printByY(numz2, sz, x, &y, 25);
    delete[] numz2;

    setcolor(GREEN);
    initA(&x, 295);
    initA(&y, 200);
    char* numz3[sz] =
    { "10", "9", "8", "7", "6" };
    printByY(numz3, sz, x, &y, 25);
    delete[] numz3;

    initA(&x, 605);
    initA(&y, 200);
    char* numz4[sz] =
    { "5", "4", "3", "2", "1" };
    printByY(numz4, sz, x, &y, 25);
    delete[] numz4;

    setcolor(BLUE);
    line(322, 200, 322, 322);
    line(27, 200, 27, 322);
}

void drawRectangles() {
    int x, y;
    initA(&x, 448);
    initA(&y, 110);

    setcolor(15);
    settextstyle(8, 0, 1);
    outtextxy(x, y, "Next Round");

    setcolor(1);
    rectangle(442, 105, 564, 135);

    setcolor(15);
    rectangle(80, 100, 435, 140);
 }
