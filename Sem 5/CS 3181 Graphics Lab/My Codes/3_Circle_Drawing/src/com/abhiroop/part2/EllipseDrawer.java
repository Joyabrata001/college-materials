package com.abhiroop.part2;

import java.awt.*;

public class EllipseDrawer {
    private final int xOrigin;
    private final int yOrigin;

    public EllipseDrawer(int xOrigin, int yOrigin) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
    }
    void drawPoint(Graphics g, int x, int y){
        g.drawLine(xOrigin + x, yOrigin - y, xOrigin + x, yOrigin - y);
    }

    public void draw(Graphics g, int xCenter, int yCenter, int radX, int radY){
        int x = 0;
        int y = radY;

        double d1 = radX*radY - (radX * radX * radY) + (0.25 * radX * radX);
        int dx = 0;
        int dy = 2*radX * radX *y;

        //region 1
        while(dx < dy){
            drawPoint(g, x+ xCenter, y + yCenter);
            drawPoint(g, -x+ xCenter, y + yCenter);
            drawPoint(g, -x+ xCenter, -y + yCenter);
            drawPoint(g, x+ xCenter, -y + yCenter);

            if(d1 < 0){
                x++;
                dx = dx + (2* radY * radY);
                d1 = d1 + dx + (radY * radY);
            }
            else{
                x++;
                y--;
                dx = dx + (2* radY * radY);
                dy = dy - (2* radX * radX);
                d1 = d1 + dx - dy + (radX * radY);
            }
        }

        double d2 = ((radY*radY) * ((x + 0.5) * (x + 0.5)))
                    + ((radX*radX) * ((y-1)*(y-1)))
                    - (radX * radX * radY * radY);

        while(y>= 0){
            drawPoint(g, x+ xCenter, y + yCenter);
            drawPoint(g, -x+ xCenter, y + yCenter);
            drawPoint(g, -x+ xCenter, -y + yCenter);
            drawPoint(g, x+ xCenter, -y + yCenter);

            if(d2 > 0){
                y--;
                dy = dy - (2* radX * radX);
                d2 = d2 + (radX * radX) - dy;
            }
            else{
                y--;
                x++;
                dx = dx + (2* radY * radY);
                dy = dy - (2* radX * radX);
                d2 = d2 + dx - dy + (radX * radX);
            }
        }
    }
}
