package com.abhiroop.part1;

import java.awt.*;

public class CircleDrawer {
    private final int xOrigin;
    private final int yOrigin;

    public CircleDrawer(int xOrigin, int yOrigin) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
    }
    void drawPoint(Graphics g, int x, int y){
        g.drawLine(xOrigin + x, yOrigin - y, xOrigin + x, yOrigin - y);
    }

    public void draw(Graphics g, int xCenter, int yCenter, int radius){
        int x = 0;
        int y = radius;

        int p = 1-radius;

        while(x<= y){
            //1st quadrant
            drawPoint(g, x+xCenter, y+yCenter);
            drawPoint(g, y+xCenter, x+yCenter);

            //2nd quadrant
            drawPoint(g, -x+xCenter, y+yCenter);
            drawPoint(g, -y+xCenter, x+yCenter);

            //3rd quadrant
            drawPoint(g, -x+xCenter, -y+yCenter);
            drawPoint(g, -y+xCenter, -x+yCenter);

            //4th quadrant
            drawPoint(g, x+xCenter, -y+yCenter);
            drawPoint(g, y+xCenter, -x+yCenter);



            if(p < 0)
                p = p+ 2*x + 3;
            else{
                p = p + 2*(x-y) + 5;
                y--;
            }
            x++;
        }
    }
}
