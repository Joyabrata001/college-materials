package com.abhiroop.part3;

import com.abhiroop.part1.Bresenham;
import com.abhiroop.part1.LineDrawer;

import java.awt.*;

public abstract class Shape {
    private final LineDrawer lineDrawer;

    public Shape(int xOrigin, int yOrigin) {
        lineDrawer = new Bresenham(xOrigin, yOrigin); //further addition: make the LineDrawer object come from function parameter
    }

    void drawLine(Graphics g, int x1, int y1, int x2, int y2){
        lineDrawer.draw(g, x1, y1, x2,y2);
    }
    abstract void draw(Graphics g, int startX, int startY);
}
