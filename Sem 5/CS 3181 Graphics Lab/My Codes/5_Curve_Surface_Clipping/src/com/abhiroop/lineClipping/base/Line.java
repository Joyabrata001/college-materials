package com.abhiroop.lineClipping.base;

import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;
import com.abhiroop.prereq.utils.DrawForm;
import com.abhiroop.prereq.utils.Pixel;

import java.awt.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Line class which supports Generating of Line Points using Bresenham Algorithm.
 * This Class also support Line Clipping using Liang Barsky Clipping Algorithm
 */
public class Line {
    private Point start;
    private Point end;

    /**
     * Constructor which defines start and end points of the Line
     * @param start the start point of the line
     * @param end the end point of the line
     */
    public Line(Point start, Point end) {
        this.start = start;
        this.end = end;
    }
    public Line(int x1, int y1, int x2, int y2) {
        this.start = new Point(x1, y1);
        this.end = new Point(x2, y2);
    }

    /**
     * generate all the points between start and end
     * @return DrawForm Class of the Line
     */
    public DrawForm generate(){
        return BresenhamGenerator.generate(start, end);
    }

    /**
     * fix the line such that it draws only inside the clip region
     * @param xMin minimum x of the window
     * @param yMin minimum y of the window
     * @param xMax maximum x of the window
     * @param yMax maximum y of the window
     * @return Line Object with new set of points
     */
    public Line clip(int xMin, int yMin, int xMax, int yMax){

        List<Double> entering = new ArrayList<>(List.of(0.0));
        List<Double> exiting = new ArrayList<>(List.of(1.0));

        int p1 = -(end.x - start.x);
        int q1 = start.x - xMin;
        if(p1 < 0)
            entering.add( ((double)q1) / ((double)p1) );
        else if(p1 > 0)
            exiting.add( ((double)q1) / ((double)p1) );
        else if(q1 < 0)
            return new Line(0,0,0,0);

        int p2 = end.x - start.x;
        int q2 = xMax - start.x;
        if(p2 < 0)
            entering.add( ((double)q2) / ((double)p2) );
        else if(p2 > 0)
            exiting.add( ((double)q2) / ((double)p2) );
        else if(q2 < 0)
            return new Line(0,0,0,0);

        int p3 = -(end.y - start.y);
        int q3 = start.y - yMin;
        if(p3 < 0)
            entering.add( ((double)q3) / ((double)p3) );
        else if(p3 > 0)
            exiting.add( ((double)q3) / ((double)p3) );
        else if(q3 < 0)
            return new Line(0,0,0,0);

        int p4 = end.y - start.y;
        int q4 = yMax - start.y;
        if(p4 < 0)
            entering.add( ((double)q4) / ((double)p4) );
        else if(p4 > 0)
            exiting.add( ((double)q4) / ((double)p4) );
        else if(q4 < 0)
            return new Line(0,0,0,0);

        double uMax = exiting.stream().min(Double::compareTo).orElse(1.0);
        double uMin = entering.stream().max(Double::compareTo).orElse(0.0);

        return new Line(
                new Point((int)Math.round(start.x + (end.x - start.x)*uMin), (int)Math.round(start.y + (end.y - start.y)*uMin)),
                new Point((int)Math.round(start.x + (end.x - start.x)*uMax), (int)Math.round(start.y + (end.y - start.y)*uMax))
        );
    }
}
