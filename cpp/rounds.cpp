#include "graphics.h"

#include <iostream>
#include <string>
#include <charconv>
using namespace std;

extern "C" int checkA(char *strg1, char *strg2);
extern "C" void initA(int* p, int val);
extern "C" void incA(int* p, int val);
extern "C" int clickedA(int x, int y);
extern "C" char* getsA(char *s);

#define sz 5
#define numq 10
int x1[sz] = { 250, 320, 390, 460, 530};
int x2[sz] = { 246, 316, 386, 456, 526};

int y_green, y_yellow;
int totalScores[sz] = {};
int roundScores[sz] = {};

char* scores[10] = {
    "10", "9", "8", "7", "6",
    "5", "4", "3", "2", "1"
};

char* players[sz] = {
    "Anri: ",  "Nutsa: ",  "Lasha: ",
    "Tamta: ",  "Giorgi:  "
};

char* qnz[numq] = {
        "what happens if you microwave", "google are you",
        "i drank too much", "i'm too", "giraffes are",
        "do astronauts", "is it fun to be a",
        "i think i swallowed a",
        "do cats", "google" };

char* q0[numq] = {
        "nothing", "an egg", "metal", "dry ice",
        "a spoon", "a turkey", "fire", "an iphone",
        "a grape", "plastic" };

char* q1[numq] = {
        "there", "stupid", "here", "listening",
        "my friend", "dumb", "working",
        "listening to me", "smart",
        "a boy or a girl" };

char* q2[numq] = {
        "water", "and that's an issue", "wine",
        "cranberry juice", "damn beer",
        "last night", "soda", "milk",
        "beer", "baking soda" };

char* q3[numq] = {
        "old for this", "effing high club", "tired",
        "nice", "high", "busy", "good for you",
        "young to feel so numb", "excited to sleep",
        "cocky" };

char* q4[numq] = {
        "heartless creatures", "herbivores",
        "endangered", "mammals", "selfish", "fake",
        "not real", "dinosaurs", "awesome", "real" };

char* q5[numq] = {
        "smoke weed in space", "get sick",
        "take showers in space", "sleep in bed",
        "age slower in space", "get paid",
        "get bored in space", "wear diapers",
        "get taller in space", "use vr in space" };

char* q6[numq] = {
        "girl", "boy", "cat", "teacher",
        "doctor", "lawyer", "pilot", "cop",
        "celebrity", "flight attendant" };

char* q7[numq] = {
        "bug", "bone", "fly", "nickel",
        "chicken bone", "spider", "fish bone",
        "hair", "bee", "piece of glass" };

char* q8[numq] = {
        "fart", "see color", "get cold",
        "dream", "have nine lives", "cry",
        "drink milk", "sweat", "like music",
        "blink" };

char* q9[numq] = {
        "news", "translate", "photos",
        "earth", "maps", "meet", "classroom",
        "flights", "scholar", "calendar" };

char** ans[numq] = {
        q0, q1, q2, q3, q4,
        q5, q6, q7, q8, q9 };

void displayScoreTexts() {
    int x, y;
    initA(&x, 51);
    initA(&y, 350);

    setcolor(RED);
    outtextxy(x, y, " Attempt");
    initA(&x, 52);
    incA(&y, 25);

    setcolor(GREEN);
    outtextxy(x, y, "This Round");
    initA(&x, 50);
    incA(&y, 25);
    setcolor(YELLOW);
    outtextxy(x, y, "Total Score");

    initA(&y, 350);
    setcolor(RED);
    char* numz[sz] =
        { "1", "2", "3", "4", "5" };
    int i;
    initA(&i, 0);
    for(; i < sz; i++) {
        x = x1[i];
        outtextxy(x, y, numz[i]);
    }
}

void setScoresToZero(int y, int color, int thisRound = 1) {
    if(thisRound) {
       for(int i = 0; i < sz; i++) {
            roundScores[i] = 0;
        }
    }
    int x, i;
    initA(&i, 0);
    for(; i < sz; i++) {
        setcolor(0);
        x = x2[i];
        outtextxy(x, y, "000");
        setcolor(color);
        x = x1[i];
        outtextxy(x, y, "0");
    }
}

void question(int* x, int* y, int j, int color) {
    setcolor(color);
    initA(x, 90);
    initA(y, 110);
    outtextxy(*x, *y, qnz[j]);
}

void allAnsz(int* x, int* y, int j, int color) {
    int i;
    initA(x, 62);
    initA(y, 200);
    initA(&i, 0);
    for(; i < 5; i++) {
        outtextxy(*x, *y, ans[j][i]);
        incA(y, 25);
    }

    initA(x, 357);
    initA(y, 200);
    initA(&i, 5);
    for(; i < 10; i++) {
        outtextxy(*x, *y, ans[j][i]);
        incA(y, 25);
    }
}

void ansByIndex(int j, int ansIndex) {
    int x, y, i;
    if(ansIndex < 5) {
        initA(&i, ansIndex);
        initA(&x, 62);
    }
    else {
        initA(&i, ansIndex - 5);
        initA(&x, 357);
    }
    initA(&y, 200 + i * 25);
    outtextxy(x, y, ans[j][ansIndex]);
}

void updateScore(int ansIndx, int attemptIndx){
    int x, y;

    // for the round score
    y = y_green;
    // add score
    if(ansIndx)
        initA(&x, x1[attemptIndx]);
    else
        initA(&x, x2[attemptIndx]);
    char* point = scores[ansIndx];
    setcolor(GREEN);
    outtextxy(x, y, point);

    // for total score
    y = y_yellow;

    // clear score
    initA(&x, x2[attemptIndx]);
    setcolor(0);
    outtextxy(x, y, "000");
    // update and add score
    int total = 10 - ansIndx +
        totalScores[attemptIndx];
    totalScores[attemptIndx] = total;
    if(total < 10){
        initA(&x, x1[attemptIndx]);
    }
    string ttlpoint = to_string(total);
    char* ttlptr = new char[ttlpoint.length()];
    strcpy(ttlptr, ttlpoint.c_str());
    setcolor(YELLOW);
    outtextxy(x, y, ttlptr);

    delete point;
    delete ttlptr;
    setcolor(WHITE);
}

void lastQScreen() {
    int x, y;
    initA(&x, 448);
    initA(&y, 110);

    setcolor(BLACK);
    settextstyle(8, 0, 1);
    outtextxy(x, y, "Next Round");

    setcolor(RED);
    incA(&x, 35);
    settextstyle(8, 0, 1);
    outtextxy(x, y, "Exit");
}

void deletePtrs() {
    for(int i = 0; i < numq; i++) {
        delete[] ans[i];
    }
}

void rounds() {
    displayScoreTexts();
    initA(&y_green, 375);
    initA(&y_yellow, 400);
    setScoresToZero(y_yellow, YELLOW, 0);

    int x, y, j;
    initA(&j, 0);
    while(j < numq) {
        setScoresToZero(y_green, GREEN);
        // Display a question
        question(&x, &y, j, WHITE);

        // Get and Check
        int maxInputSize;
        // input size must not exceed 30 chars
        initA(&maxInputSize, 30);
        char* guess = (char*)malloc(sizeof(char) *
                                   (maxInputSize + 1));

        for(int i = 0; i < sz; i++) {
            cout << players[i];
            // get input
            guess = getsA(guess);
            if(guess != nullptr) {
                // compare to answers and update scores
                int ansIndex = checkA(*ans[j], guess);
                if(ansIndex) {
                    ansIndex--;
                    ansByIndex(j, ansIndex);
                    updateScore(ansIndex, i);
                }
            }
        }

        // Display answers
        cout << "Wait for answers...\n";
        delay(2000);
        allAnsz(&x, &y, j, WHITE);

        // Let the user move
        // to the next question
        if(numq - 1 != j) {
            cout << "Click 'Next Round' to"
            << " move to the next question.\n";
            do {
            while (!ismouseclick(WM_LBUTTONDOWN))
            {}
            getmouseclick(WM_LBUTTONDOWN, x, y);
            } while(clickedA(x, y));

            // Clear text
            question(&x, &y, j, BLACK);
            allAnsz(&x, &y, j, BLACK);

            // update the index
            incA(&j, 1);
            if(numq-1 == j)
                lastQScreen();
        }
        else {
            incA(&j, 1);
            cout << "click 'Exit' to exit.\n";
            do {
            while (!ismouseclick(WM_LBUTTONDOWN))
            {}
            getmouseclick(WM_LBUTTONDOWN, x, y);
            } while(clickedA(x, y));
        }

    }

    // delete pointers
    deletePtrs();
}
