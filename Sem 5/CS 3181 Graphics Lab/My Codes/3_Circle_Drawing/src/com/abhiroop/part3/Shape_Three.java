package com.abhiroop.part3;

import com.abhiroop.part1.CircleDrawer;
import com.abhiroop.part2.EllipseDrawer;
import com.abhiroop.prereq.lineDrawer.Bresenham;
import com.abhiroop.prereq.lineDrawer.LineDrawer;

import java.awt.*;
import java.util.Random;

public class Shape_Three implements Shape{
    private final CircleDrawer circleDrawer;
    private final LineDrawer lineDrawer;

    private final int rad;
    private final int offset;
    private final int numLines;
    private final int lineLength;
    private final Random rand;

    public Shape_Three(int xOrigin, int yOrigin, int rad, int offset, int numLines, int lineLength) {
        this.rad = rad;
        this.offset = offset;
        this.numLines = numLines;
        this.lineLength = lineLength;
        this.circleDrawer = new CircleDrawer(xOrigin, yOrigin);
        this.lineDrawer = new Bresenham(xOrigin, yOrigin);
        this.rand = new Random(System.currentTimeMillis());
    }

    private int rand(int min, int max){
        return rand.nextInt(max - min) + min;
    }

    /**
     * Draws the shape
     *
     * @param g      the Graphics Object
     * @param startX start x-position of the Shape
     * @param startY start y-position of the Shape
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {
        circleDrawer.draw(g, startX, startY, rad);
        circleDrawer.draw(g, startX, startY, rad + offset);

        int xInitial, yInitial, xFinal, yFinal;
        double degree;

        for(var i = 0; i<numLines;i++){
            degree = rand(0,120) * Math.PI / 180;
            xInitial = startX + (int)(rad*Math.cos(degree));
            yInitial = startY + (int)(rad*Math.sin(degree));
            xFinal = xInitial + (int)(lineLength*Math.cos(degree));
            yFinal = yInitial + (int)(lineLength*Math.sin(degree));
            lineDrawer.draw(g, xInitial, yInitial, xFinal, yFinal);
        }
    }
}
