package com.abhiroop.bird.body;

import com.abhiroop.bird.utils.Shape;
import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.prereq.ellipseGenerator.EllipseGenerator;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;

import java.awt.*;
import java.util.Random;

public class Body implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final Random rand;
    private final int xRad;
    private final int yRad;
    private final int numEntities;
    private final int entityDimension;
    private final boolean spotted;
    private final boolean hair;

    /**
     * Draws an ellipse and then multiple circles inside it
     * @param xOrigin xOrigin of the Frame
     * @param yOrigin yOrigin of the Frame
     */
    public Body(int xOrigin,
                int yOrigin,
                boolean spotted,
                boolean hair) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.xRad = 100;
        this.yRad = 70;
        this.numEntities = 20;
        this.entityDimension = 5;
        this.rand = new Random(System.currentTimeMillis());
        this.spotted = spotted;
        this.hair = hair;
    }

    private int rand(int min, int max){
        return rand.nextInt(max - min) + min;
    }

    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {

        EllipseGenerator
                .generate(startX, startY, xRad, yRad)
                .generateFill()
                .toMatrix()
                .rotateInPlace(-45)
                .toDrawForm()
                .draw(g, xOrigin, yOrigin, Color.WHITE);

        EllipseGenerator
                .generate(startX, startY, xRad, yRad)
                .toMatrix()
                .rotateInPlace(-45)
                .toDrawForm()
                .draw(g, xOrigin, yOrigin, Color.BLACK);



        if(spotted){
            for(var i = 0; i< numEntities; i++)
                CircleGenerator
                        .generate(
                                startX + rand(-(xRad - entityDimension - 20), xRad - entityDimension - 20),
                                startY + rand(-(yRad - entityDimension - 20), yRad - entityDimension - 20),
                                entityDimension)
                        .toMatrix()
                        .rotateInPlace(-45, startX, startY)
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
                new BresenhamGenerator()
                        .generate(xInitial, yInitial, xFinal, yFinal)
                        .toMatrix()
                        .rotateInPlace(-45, startX, startY)
                        .toDrawForm()
                        .draw(g, xOrigin, yOrigin, Color.BLACK);
            }
        }
    }
}
