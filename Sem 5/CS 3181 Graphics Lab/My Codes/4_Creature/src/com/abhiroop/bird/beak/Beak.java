package com.abhiroop.bird.beak;

import com.abhiroop.bird.utils.Shape;

import java.awt.*;

public class Beak implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final boolean big;
    private final boolean teeth;
    private final int seperation;
    public Beak(int xOrigin,
                int yOrigin,
                boolean big,
                boolean teeth) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.big = big;
        this.teeth = teeth;

        if(big)
            this.seperation = 10;
        else
            this.seperation = 7;

    }
    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g,
                          int startX,
                          int startY) {
        new BeakTopTriangle(xOrigin, yOrigin, big, teeth)
                .drawShape(g, startX, startY + seperation);

        new BeakBottomTriangle(xOrigin, yOrigin, big, teeth)
                .drawShape(g, startX, startY - seperation);
    }
}
