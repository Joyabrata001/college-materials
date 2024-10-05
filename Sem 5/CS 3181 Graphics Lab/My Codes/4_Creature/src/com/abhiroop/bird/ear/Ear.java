package com.abhiroop.bird.ear;

import com.abhiroop.bird.utils.Shape;
import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;
import com.abhiroop.utils.DrawForm;

import java.awt.*;

public class Ear implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final int dim;
    private boolean earCircle;

    public Ear(int xOrigin,
               int yOrigin,
               boolean earCircle) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.dim = 15;
        this.earCircle = earCircle;
    }

    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {
        DrawForm upperShape, lowerShape;

        if(earCircle){
            upperShape = CircleGenerator
                    .generate(startX - 5, startY + 10, dim);

            lowerShape = CircleGenerator
                    .generate(startX, startY, dim);
        }
        else{
            int x1 = 0;
            int y1 = dim;

            int x2 = (int)(dim * Math.sin(Math.PI/3));
            int y2 = -(int)(dim * Math.cos(Math.PI/3));

            int x3 = - (int)(dim * Math.sin(Math.PI/3));
            int y3 = -(int)(dim * Math.cos(Math.PI/3));

            var line1 = new BresenhamGenerator()
                    .generate(
                            startX + x1,
                            startY + y1,
                            startX + x2,
                            startY + y2
                    );

            var line2 = new BresenhamGenerator()
                    .generate(
                            startX + x2,
                            startY + y2,
                            startX + x3,
                            startY + y3
                    );

            var line3 = new BresenhamGenerator()
                    .generate(
                            startX + x3,
                            startY + y3,
                            startX + x1,
                            startY + y1
                    );

            lowerShape = line1.append(line2).append(line3);
            upperShape = lowerShape
                    .toMatrix()
                    .translate(-5, 10)
                    .toDrawForm();
        }

        upperShape.generateFill().draw(g, xOrigin, yOrigin, Color.WHITE);
        upperShape.draw(g, xOrigin, yOrigin, Color.BLACK);

        lowerShape.generateFill().draw(g, xOrigin, yOrigin, Color.WHITE);
        lowerShape.draw(g, xOrigin, yOrigin, Color.BLACK);
    }
}
