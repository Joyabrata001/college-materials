package com.abhiroop.lineClipping;

import com.abhiroop.lineClipping.base.Line;
import com.abhiroop.lineClipping.base.Window;
import com.abhiroop.prereq.BaseGraph;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;

import javax.swing.*;
import java.awt.*;

public class LineClippingDisplay extends Window {
    public LineClippingDisplay(JFrame displayWindow, int xMin, int yMin, int xMax, int yMax) {
        super(displayWindow, xMin, yMin, xMax, yMax);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);


        new Line(-600,-300,600,200)
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.RED);

        new Line(-600,-300,600,200)
                .clip(super.getXMin(), super.getYMin(), super.getXMax(), super.getYMax())
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);



        new Line(-100,-100,500,500)
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.RED);

        new Line(-100,-100,500,500)
                .clip(super.getXMin(), super.getYMin(), super.getXMax(), super.getYMax())
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLUE);



        new Line(0, 600,600,600)
                .clip(super.getXMin(), super.getYMin(), super.getXMax(), super.getYMax())
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), new Color(34,139,34));

        new Line(0, 600,500,600)
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.RED);



        new Line(0, 500,500,500)
                .clip(super.getXMin(), super.getYMin(), super.getXMax(), super.getYMax())
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), new Color(34,139,34));

        new Line(-200, -300, 300,100)
                .clip(super.getXMin(), super.getYMin(), super.getXMax(), super.getYMax())
                .generate()
                .draw(g, super.getXOrigin(), super.getYOrigin(), new Color(34,139,34));
    }
}
