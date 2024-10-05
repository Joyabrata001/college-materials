package com.abhiroop.bird.tail;

import com.abhiroop.bird.utils.Shape;
import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;
import com.abhiroop.utils.DrawForm;

import java.awt.*;
import java.util.Random;

public class Tail implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final int dim;
    private final int tailType;
    private final Random rand;

    /**
     *
     * @param xOrigin xOrigin
     * @param yOrigin yOrigin
     * @param tailType three possible value 1,2,3
     */
    public Tail(int xOrigin,
                int yOrigin,
                int tailType) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.dim= 20;
        this.tailType = tailType;
        this.rand = new Random(System.currentTimeMillis());
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

       DrawForm shape;

       if(tailType == 0)
           shape = CircleGenerator.generate(startX, startY, dim);
       else if(tailType == 1){
           int y1 = startY - dim;
           int x2 = startX - dim;
           int x3 = startX + dim*2;
           int y3 = startY + dim*2;

           var line1 = new BresenhamGenerator().generate(startX,y1,x2, startY);
           var line2 = new BresenhamGenerator().generate(x2, startY,x3,y3);
           var line3 = new BresenhamGenerator().generate(x3,y3, startX,y1);

           shape = line1.append(line2).append(line3);
       }
       else if(tailType == 2)
           shape = CircleGenerator.generate(startX, startY, dim);
       else
           throw new IllegalArgumentException("tailType is incorrect");

        assert shape != null;
        shape.generateFill().draw(g,xOrigin, yOrigin, Color.WHITE);
        shape.draw(g, xOrigin, yOrigin, Color.BLACK);

        if(tailType == 2){
            CircleGenerator.generate(startX, startY, dim - 10)
                    .draw(g, xOrigin, yOrigin, Color.BLACK);

            for(var i = 0; i<10;i++){
                var degree = rand(0,60) * Math.PI / 180;
                var xInitial = startX + (int)((dim - 10)*Math.cos(degree));
                var yInitial = startY + (int)((dim - 10)*Math.sin(degree));
                var xFinal = xInitial + (int)(3*dim*Math.cos(degree));
                var yFinal = yInitial + (int)(3*dim*Math.sin(degree));

                new BresenhamGenerator().generate(xInitial, yInitial, xFinal, yFinal)
                        .draw(g, xOrigin, yOrigin, Color.BLACK);
            }
        }
    }
}
