package com.abhiroop.bird.utils;

import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.prereq.ellipseGenerator.EllipseGenerator;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;

import java.awt.*;
import java.util.Random;

import static java.lang.Math.min;

public class BodyEllipseDrawer{
    private final int xOrigin;
    private final int yOrigin;
    private final Random rand;
    private final int xRad;
    private final int yRad;
    private final int numEntities;
    private final int entityDimension;
    private final boolean spotted;
    private final boolean hair;
    private final double rotationAngle;

    /**
     * Draws an ellipse and then multiple circles inside it
     * @param xOrigin xOrigin of the Frame
     * @param yOrigin yOrigin of the Frame
     */
    public BodyEllipseDrawer(int xOrigin,
                             int yOrigin,
                             int xRad,
                             int yRad,
                             boolean spotted,
                             boolean hair,
                             double rotationAngle) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.xRad = xRad;
        this.yRad = yRad;
        this.numEntities = 5;
        this.entityDimension = min(xRad, yRad)/5;
        this.rand = new Random(System.currentTimeMillis());
        this.spotted = spotted;
        this.hair = hair;
        this.rotationAngle = rotationAngle;
    }

    private int rand(int min, int max){
        return rand.nextInt(max - min) + min;
    }

    public void drawShape(Graphics g, int startX, int startY) {
        EllipseGenerator
                .generate(startX, startY, xRad, yRad)
                .generateFill()
                .toMatrix()
                .rotateInPlace(rotationAngle)
                .toDrawForm()
                .draw(g, xOrigin, yOrigin, Color.WHITE);

        EllipseGenerator
                .generate(startX, startY, xRad, yRad)
                .toMatrix()
                .rotateInPlace(rotationAngle)
                .toDrawForm()
                .draw(g, xOrigin, yOrigin, Color.BLACK);

        if(spotted){
            for(var i = 0; i< numEntities; i++)
                CircleGenerator
                        .generate(
                                startX + rand(-(xRad - entityDimension - 2), xRad - entityDimension - 2),
                                startY + rand(-(yRad - entityDimension - 2), yRad - entityDimension - 2),
                                entityDimension)
                        .toMatrix()
                        .rotateInPlace(rotationAngle, startX, startY)
                        .toDrawForm()
                        .draw(g, xOrigin, yOrigin, Color.BLACK);
        }


        if(hair){
            for(var i = 0; i<numEntities;i++){
                var degree = rand(0,360) * Math.PI / 180;
                int xInitial = startX + (int)((xRad - entityDimension/2)*Math.cos(degree));
                int yInitial = startY + (int)((yRad - entityDimension/2)*Math.sin(degree));
                int xFinal = xInitial + (int)(3*entityDimension*Math.cos(degree));
                int yFinal = yInitial + (int)(3*entityDimension*Math.sin(degree));

                //draw line from (xInitial, yInitial) to (xFinal, yFinal)
                new BresenhamGenerator()
                        .generate(xInitial, yInitial, xFinal, yFinal)
                        .toMatrix()
                        .rotateInPlace(rotationAngle, startX, startY)
                        .toDrawForm()
                        .draw(g, xOrigin, yOrigin, Color.BLACK);
            }
        }
    }
}
