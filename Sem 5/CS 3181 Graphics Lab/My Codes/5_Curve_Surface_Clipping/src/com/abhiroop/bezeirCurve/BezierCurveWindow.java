package com.abhiroop.bezeirCurve;

import com.abhiroop.prereq.BaseGraph;
import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class BezierCurveWindow extends BaseGraph {

    public BezierCurveWindow(JFrame displayWindow) {
        super(displayWindow);
    }

    private void drawControlPoints(Graphics g, List<Point> controlPoints){

        g.setColor(Color.RED);

        for(int i = 0; i< controlPoints.size() - 1; i++)
            BresenhamGenerator
                    .generate(controlPoints.get(i), controlPoints.get(i+1))
                    .draw(g,super.getXOrigin(), super.getYOrigin(),Color.RED);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        {
            List<Point> controlPoints1 = new ArrayList<>(
                    List.of(
                            new Point(0, 0),
                            new Point(100, 100),
                            new Point(200, 0)
                    )
            );
            drawControlPoints(g, controlPoints1);
            BezierCurveGenerator
                    .generateCurve(controlPoints1)
                    .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);
        }

        {
            List<Point> controlPoints = new ArrayList<>(
                    List.of(
                            new Point(-200, 0),
                            new Point(-100, 0),
                            new Point(-100, 100),
                            new Point(0, 100)
                    )
            );
            drawControlPoints(g, controlPoints);
            BezierCurveGenerator
                    .generateCurve(controlPoints)
                    .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);
        }

        {
            List<Point> controlPoints = new ArrayList<>(
                    List.of(
                            new Point(0, -100),
                            new Point(-200, -100),
                            new Point(-200, -300),
                            new Point(-400, -100)
                    )
            );
            drawControlPoints(g, controlPoints);
            BezierCurveGenerator
                    .generateCurve(controlPoints)
                    .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);
        }

        {
            List<Point> controlPoints = new ArrayList<>(
                    List.of(
                            new Point(0, -200),
                            new Point(100, -100),
                            new Point(0, -400),
                            new Point(300, -100),
                            new Point(-100, -300)
                    )
            );
            drawControlPoints(g, controlPoints);
            BezierCurveGenerator
                    .generateCurve(controlPoints)
                    .draw(g, super.getXOrigin(), super.getYOrigin(), Color.BLACK);
        }
    }
}
