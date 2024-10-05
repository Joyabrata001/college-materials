package com.abhiroop.bird.legs;

import com.abhiroop.bird.utils.Shape;
import com.abhiroop.bird.utils.BodyEllipseDrawer;

import java.awt.*;

public class RightLeg implements Shape {
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
    public RightLeg(int xOrigin,
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
            new BodyEllipseDrawer(xOrigin, yOrigin+80, 50, 20, spotted, hair, 120)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin, yOrigin, 50, 35, spotted, hair, 90)
                    .drawShape(g, startX, startY);
//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin + 1, yOrigin+155, 3, 7, false, false, -4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 7, yOrigin+160, 3, 7, false, false, 0)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 15, yOrigin+160, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 23, yOrigin+155, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 27, yOrigin+150, 3, 7, false, false, 5.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 10, yOrigin+140, 15, 15, false, false, 120)
                    .drawShape(g, startX, startY);
        }
        else{
            new BodyEllipseDrawer(xOrigin, yOrigin+60, 40, 15, spotted, hair, 120)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin, yOrigin, 35, 15, spotted, hair, 90)
                    .drawShape(g, startX, startY);
//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin + 1, yOrigin+125, 3, 7, false, false, -4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 7, yOrigin+130, 3, 7, false, false, 0)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 15, yOrigin+130, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 23, yOrigin+125, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 27, yOrigin+120, 3, 7, false, false, 5.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 10, yOrigin+110, 10, 10, false, false, 120)
                    .drawShape(g, startX, startY);
        }
    }
}
