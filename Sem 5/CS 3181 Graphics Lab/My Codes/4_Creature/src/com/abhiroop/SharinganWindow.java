package com.abhiroop;

import com.abhiroop.prereq.BaseGraph;
import com.abhiroop.prereq.circleGenerator.CircleGenerator;
import com.abhiroop.prereq.ellipseGenerator.EllipseGenerator;

import javax.swing.*;
import java.awt.*;

public class SharinganWindow extends BaseGraph {
    public SharinganWindow(JFrame displayWindow) {
        super(displayWindow);
    }

    @Override
    public void paint(Graphics g){
        super.paint(g);

        CircleGenerator
                .generate(0,0,200)
                .generateFill()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);

        EllipseGenerator
                .generate(0,0,50,200)
                .generateFill()
                .draw(g,super.getXOrigin(), super.getYOrigin(), Color.RED);

        EllipseGenerator
                .generate(0,0,50,200)
                .generateFill()
                .toMatrix()
                .rotateInPlace(45)
                .toDrawForm()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);

        EllipseGenerator
                .generate(0,0,50,200)
                .generateFill()
                .toMatrix()
                .rotateInPlace(-45)
                .toDrawForm()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);

        EllipseGenerator
                .generate(0,0,50,200)
                .draw(g,super.getXOrigin(), super.getYOrigin(), Color.BLACK);

        EllipseGenerator
                .generate(0,0,50,200)
                .toMatrix()
                .rotateInPlace(45)
                .toDrawForm()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);

        EllipseGenerator
                .generate(0,0,50,200)
                .toMatrix()
                .rotateInPlace(-45)
                .toDrawForm()
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);

        CircleGenerator
                .generate(0,0,20)
                .generateFill()
                .draw(g,super.getXOrigin(), super.getYOrigin(), Color.black);
    }
}
