package com.abhiroop.part1;

import com.abhiroop.prereq.BaseGraph;

import javax.swing.*;
import java.awt.*;

public class CircleDisplay  extends BaseGraph {
    public CircleDisplay(JFrame displayWindow) {
        super(displayWindow);
    }

    @Override
    public void paint(Graphics g){
        super.paint(g);

        new CircleDrawer(super.getXOrigin(), super.getYOrigin()).draw(g, 0,0,100);
    }
}
