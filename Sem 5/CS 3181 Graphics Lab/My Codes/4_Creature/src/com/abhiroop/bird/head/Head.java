package com.abhiroop.bird.head;

import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.bird.utils.Shape;

import java.awt.*;

public class Head implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final int bigRad;
    private final int smallRad;

    public Head(int xOrigin,
                int yOrigin) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.bigRad = 40;
        this.smallRad = 10;
    }

    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {
//        ellipseDrawer.draw(g, startX,startY, xRad, yRad);

        CircleGenerator
                .generate(startX, startY, bigRad)
                .generateFill()
                .draw(g, xOrigin, yOrigin, Color.WHITE);

        CircleGenerator
                .generate(startX, startY, bigRad)
                .draw(g, xOrigin, yOrigin, Color.BLACK);

        CircleGenerator
                .generate(startX - 10, startY + 10, smallRad)
                .draw(g, xOrigin, yOrigin, Color.BLACK);
    }
}
