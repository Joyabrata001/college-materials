package com.abhiroop.bird.beak;

import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;
import com.abhiroop.bird.utils.Shape;

import java.awt.*;

public class BeakBottomTriangle implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final int baseLength;
    private final int heightLength;
    private final int hairLength;

    public BeakBottomTriangle(int xOrigin,
                              int yOrigin,
                              boolean big,
                              boolean teeth) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;

        if(big){
            baseLength = 40;
            heightLength = 20;
        }
        else{
            baseLength = 20;
            heightLength = 10;
        }

        if(teeth)
            hairLength = 5;
        else
            hairLength = 0;
    }
    /**
     *
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape (x-center of the oval)
     * @param startY    start y-position of the Shape (y-center of the oval)
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {
        var line1 = new BresenhamGenerator()
                .generate(
                        startX,
                        startY,
                        startX + baseLength,
                        startY
                );

        var line2 = new BresenhamGenerator()
                .generate(
                        startX + baseLength,
                        startY,
                        startX + baseLength,
                        startY - heightLength
                );

        var line3 = new BresenhamGenerator()
                .generate(
                        startX + baseLength,
                        startY - heightLength,
                        startX,
                        startY
                );

        var triangle = line1.
                append(line2).
                append(line3);

        triangle.generateFill().draw(g, xOrigin, yOrigin, Color.WHITE);
        triangle.draw(g, xOrigin, yOrigin, Color.BLACK);

        if(hairLength > 0)
            for(var i = startX + hairLength; i < startX + baseLength; i += hairLength) {
                new BresenhamGenerator()
                        .generate(i, startY, i, startY + hairLength)
                        .draw(g, xOrigin, yOrigin, Color.BLACK);
            }
    }
}
