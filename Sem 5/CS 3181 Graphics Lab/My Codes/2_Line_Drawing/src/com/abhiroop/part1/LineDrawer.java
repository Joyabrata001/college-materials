package com.abhiroop.part1;

import java.awt.*;

public abstract class LineDrawer {
    private final int xOrigin;
    private final int yOrigin;

    public LineDrawer(int xOrigin, int yOrigin) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
    }

    /**
     * Draws a point in plane at position (x,y)
     * @param g  the Graphics Object
     */
    void drawPoint(Graphics g, int x, int y){
        g.drawOval(xOrigin + x +1 ,yOrigin - y + 1, 0,0 );
    }

    abstract public void draw(Graphics g, int x1, int y1, int x2, int y2);
}
