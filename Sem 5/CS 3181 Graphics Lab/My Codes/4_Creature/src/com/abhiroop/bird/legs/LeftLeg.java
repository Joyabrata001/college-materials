package com.abhiroop.bird.legs;

import com.abhiroop.bird.utils.Shape;
import com.abhiroop.bird.utils.BodyEllipseDrawer;

import java.awt.*;

public class LeftLeg implements Shape {
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
    public LeftLeg(int xOrigin,
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
            new BodyEllipseDrawer(xOrigin - 10, yOrigin + 50, 40, 20, spotted, hair, 120)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin, yOrigin -20, 40, 20, spotted, hair, 120)
                    .drawShape(g, startX, startY);
//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin - 9, yOrigin+115, 3, 7, false, false, -4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 17, yOrigin+120, 3, 7, false, false, 0)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 25, yOrigin+120, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 33, yOrigin+115, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 37, yOrigin+110, 3, 7, false, false, 5.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 20, yOrigin+100, 15, 15, false, false, 120)
                    .drawShape(g, startX, startY);
        }
        else{
            new BodyEllipseDrawer(xOrigin - 10, yOrigin + 30, 35, 15, spotted, hair, 120)
                .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin, yOrigin - 30, 35, 15, spotted, hair, 120)
                    .drawShape(g, startX, startY);
//        -----------------------Fingers (right to left)-------------
            new BodyEllipseDrawer(xOrigin - 9, yOrigin+80, 3, 7, false, false, -4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 17, yOrigin+85, 3, 7, false, false, 0)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 25, yOrigin+85, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 33, yOrigin+80, 3, 7, false, false, 4.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 37, yOrigin+75, 3, 7, false, false, 5.5)
                    .drawShape(g, startX, startY);

            new BodyEllipseDrawer(xOrigin - 20, yOrigin+70, 10, 10, false, false, 120)
                    .drawShape(g, startX, startY);
        }
    }
}
