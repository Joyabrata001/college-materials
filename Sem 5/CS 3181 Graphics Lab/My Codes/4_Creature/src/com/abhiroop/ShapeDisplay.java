package com.abhiroop;

import com.abhiroop.prereq.BaseGraph;
import com.abhiroop.bird.Bird;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class ShapeDisplay extends BaseGraph {
    public ShapeDisplay(JFrame displayWindow) {
        super(displayWindow);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        var bird1 = new Bird(super.getXOrigin(), super.getYOrigin());
        bird1.drawShape(g, -300, 400);

        var bird2 = new Bird(super.getXOrigin(), super.getYOrigin());
        bird2.drawShape(g, 150, 400);

        Bird.merge(bird1, bird2).drawShape(g, -300, -70);
    }
}
