package com.abhiroop.lineClipping.base;

import com.abhiroop.prereq.BaseGraph;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;

import javax.swing.*;
import java.awt.*;

public class Window extends BaseGraph {
    private final int xMin;
    private final int yMin;
    private final int xMax;
    private final int yMax;

    public Window(JFrame displayWindow, int xMin, int yMin, int xMax, int yMax) {
        super(displayWindow);
        this.xMin = xMin;
        this.yMin = yMin;
        this.xMax = xMax;
        this.yMax = yMax;
    }

    public int getXMin() {
        return xMin;
    }

    public int getYMin() {
        return yMin;
    }

    public int getXMax() {
        return xMax;
    }

    public int getYMax() {
        return yMax;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        BresenhamGenerator
                .generate(xMin, yMin, xMax, yMin)
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);

        BresenhamGenerator
                .generate(xMax, yMin, xMax, yMax)
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);

        BresenhamGenerator
                .generate(xMax, yMax, xMin, yMax)
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);

        BresenhamGenerator
                .generate(xMin, yMax, xMin, yMin)
                .draw(g, super.getXOrigin(), super.getYOrigin(), Color.red);
    }
}
