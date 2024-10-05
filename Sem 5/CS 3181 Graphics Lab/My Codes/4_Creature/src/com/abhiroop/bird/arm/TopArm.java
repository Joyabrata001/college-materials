package com.abhiroop.bird.arm;

import com.abhiroop.bird.utils.BodyEllipseDrawer;
import com.abhiroop.bird.utils.Shape;

import java.awt.*;

public class TopArm implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final boolean spotted;
    private final boolean hair;
    private  final boolean sizeLong;

    /**
     *
     * @param xOrigin xOrigin
     * @param yOrigin yOrigin
     */
    public TopArm(int xOrigin,
                  int yOrigin,
                  boolean spotted,
                  boolean hair,
                  boolean sizeLong) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.spotted = spotted;
        this.hair = hair;
        this.sizeLong = sizeLong;
    }

    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {

        if(sizeLong){
            new BodyEllipseDrawer(xOrigin - 80, yOrigin + 20, 50, 20, spotted, hair, 80)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin, yOrigin, 50, 20, spotted, hair, 100)
                    .drawShape(g, startX, startY);

//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin - 150, yOrigin+30, 3, 7, false, false,  1)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 157, yOrigin+23, 3, 7, false, false,  1.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 160, yOrigin+16, 3, 7, false, false,  2)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 160, yOrigin+9, 3, 7, false, false,  2.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 155, yOrigin, 3, 7, false, false,  3)
                    .drawShape(g, startX, startY);
//---------------------
            new BodyEllipseDrawer(xOrigin - 140, yOrigin + 10, 15, 15, false, false, 120)
                    .drawShape(g, startX, startY);
        }
        else{
            new BodyEllipseDrawer(xOrigin - 50, yOrigin + 20, 40, 20, spotted, hair, 80)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin + 10, yOrigin, 40, 20, spotted, hair, 100)
                    .drawShape(g, startX, startY);

//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin - 110, yOrigin+30, 3, 7, false, false,  1)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 117, yOrigin+23, 3, 7, false, false,  1.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 120, yOrigin+16, 3, 7, false, false,  2)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 120, yOrigin+9, 3, 7, false, false,  2.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 115, yOrigin, 3, 7, false, false,  3)
                    .drawShape(g, startX, startY);
//---------------------
            new BodyEllipseDrawer(xOrigin - 100, yOrigin + 10, 15, 15, false, false, 120)
                    .drawShape(g, startX, startY);
        }
    }
}
