package com.abhiroop.part1;

import java.awt.*;

public class DDA extends LineDrawer{

    public DDA(int xOrigin, int yOrigin) {
        super(xOrigin, yOrigin);
    }

    @Override
    public void draw(Graphics g, int x1, int y1, int x2, int y2) {
        int dx = x2 - x1;
        int dy = y2 - y1;

        int numPoints = Math.max(Math.abs(dx), Math.abs(dy));

        float xInc = (float)dx / numPoints;
        float yInc = (float)dy / numPoints;

        float x = x1;
        float y = y1;

        for (int i = 0; i < numPoints; i++) {
            drawPoint(g, Math.round(x), Math.round(y));
            x = x + xInc;
            y = y + yInc;
        }
    }
}
