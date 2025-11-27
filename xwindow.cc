export module Xwindow;

import<string>;
import xwindow;

// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <unistd.h>

export class Xwindow {
        Display *d;
        Window w;
        int s;
        GC gc;
        unsigned long colours[10]; //can we do this
    public:
        Xwindow(int width=500, int height=500);
        ~Xwindow();
        Xwindow(const Xwindow&) = delete;

        // Available colours
    enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

    // Drawing functions
    void fillRectangle(int x, int y, int width, int height, int colour=Black);
    void drawString(int x, int y, const string& msg);
};
