package com.abhiroop.part3;

import com.abhiroop.part2.EllipseDrawer;
import com.abhiroop.prereq.lineDrawer.Bresenham;
import com.abhiroop.prereq.lineDrawer.LineDrawer;

import java.awt.*;
import java.util.Random;

public class Shape_Two implements Shape{
    private final EllipseDrawer ellipseDrawer;
    private final LineDrawer lineDrawer;

    private final int xRad;
    private final int yRad;
    private final int numLines;
    private final int lineLength;
    private final Random rand;

    public Shape_Two(int xOrigin, int yOrigin, int xRad, int yRad,int numLines, int lineLength) {
        this.xRad = xRad;
        this.yRad = yRad;
        this.numLines = numLines;
        this.lineLength = lineLength;
        this.ellipseDrawer = new EllipseDrawer(xOrigin, yOrigin);
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
        ellipseDrawer.draw(g, startX, startY, xRad, yRad);

        int xInitial, yInitial, xFinal, yFinal;
        double degree;

        for(var i = 0; i<numLines;i++){
            degree = rand(0,360) * Math.PI / 180;
            xInitial = startX + (int)((xRad - 50)*Math.cos(degree));
            yInitial = startY + (int)((yRad - 50)*Math.sin(degree));
            xFinal = xInitial + (int)(lineLength*Math.cos(degree));
            yFinal = yInitial + (int)(lineLength*Math.sin(degree));
            lineDrawer.draw(g, xInitial, yInitial, xFinal, yFinal);
        }
    }
}
