package com.abhiroop.part3;

import com.abhiroop.prereq.BaseGraph;

import javax.swing.*;
import java.awt.*;

public class ShapeDisplay extends BaseGraph {
    public ShapeDisplay(JFrame displayWindow) {
        super(displayWindow);
    }

    void drawShape(Graphics g, Shape shape, int startX, int startY){
        shape.drawShape(g, startX, startY);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        drawShape(g,
                new Shape_One(super.getXOrigin(), super.getYOrigin(), 200, 100,10, 20),
                -200,-200);

        drawShape(g,
                new Shape_Two(super.getXOrigin(), super.getYOrigin(), 200,100, 15, 100),
                0,200);

        drawShape(g,
                new Shape_Three(super.getXOrigin(), super.getYOrigin(), 20,10, 10, 100),
                200,-200);
    }
}
