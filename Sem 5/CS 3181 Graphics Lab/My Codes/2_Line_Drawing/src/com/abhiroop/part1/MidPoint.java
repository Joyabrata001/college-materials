package com.abhiroop.part1;

import java.awt.*;

public class MidPoint extends LineDrawer{

    public MidPoint(int xOrigin, int yOrigin) {
        super(xOrigin, yOrigin);
    }

    @Override
    public void draw(Graphics g, int x1, int y1, int x2, int y2) {
        int dx = Math.abs(x2 - x1);
        int dy = Math.abs(y2 - y1);

        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;

        int err = dx-dy;
        int e2;

        while (true) {
            drawPoint(g, x1, y1);

            if (x1 == x2 && y1 == y2)
                break;

            e2 = 2 * err;

            if (e2 > -dy) {
                err = err - dy;
                x1 = x1 + sx;
            }

            if (e2 < dx) {
                err = err + dx;
                y1 = y1 + sy;
            }
        }
    }
}
