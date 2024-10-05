package com.abhiroop.utils;

import java.awt.*;

public class Pixel {
    private int x;
    private int y;

    public Integer getX() {
        return x;
    }

    public Integer getY() {
        return y;
    }

    public Pixel(int x, int y) {
        this.x = x;
        this.y = y;
    }

    void drawPoint(Graphics g, int xOrigin, int yOrigin){
        g.drawLine(xOrigin + x, yOrigin - y, xOrigin + x, yOrigin - y);
    }
}
