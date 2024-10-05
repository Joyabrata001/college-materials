package com.abhiroop.part2;

import com.abhiroop.prereq.BaseGraph;

import javax.swing.*;
import java.awt.*;

public class EllipseDisplay extends BaseGraph {
    public EllipseDisplay(JFrame displayWindow) {
        super(displayWindow);
    }

    @Override
    public void paint(Graphics g){
        super.paint(g);

        new EllipseDrawer(super.getXOrigin(), super.getYOrigin()).draw(g, 0,0,100, 200);
        new EllipseDrawer(super.getXOrigin(), super.getYOrigin()).draw(g, 0,0,200, 100);
        new EllipseDrawer(super.getXOrigin(), super.getYOrigin()).draw(g, 0,0,100, 100);

    }
}
