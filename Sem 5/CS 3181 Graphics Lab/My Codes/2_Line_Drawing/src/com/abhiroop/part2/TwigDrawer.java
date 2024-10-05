package com.abhiroop.part2;

import com.abhiroop.part1.Bresenham;
import com.abhiroop.part1.LineDrawer;

import javax.swing.*;
import java.awt.*;

public class TwigDrawer extends Canvas {
    private final int xOrigin;
    private final int yOrigin;
    private LineDrawer lineDrawer;
    private final JFrame displayWindow;

    public TwigDrawer(JFrame displayWindow) {
        //set Background Color
        setBackground(Color.white);

        //get origin of the displayWindow
        xOrigin = (displayWindow.getX() + displayWindow.getWidth()) / 2;
        yOrigin = (displayWindow.getY() + displayWindow.getHeight()) / 2;

        this.displayWindow = displayWindow;

    }

    private void drawLine(Graphics g, int x1, int y1, int x2, int y2, LineDrawer lineDrawer){
        lineDrawer.draw(g, x1, y1, x2, y2);
    }

    private void drawTwig(Graphics g, int startX, int startY, int numBranches, double lineLength, double drawDirection){
        if(numBranches > 0){
            int x2 = startX + (int)Math.round(lineLength * Math.cos(drawDirection * Math.PI /180));
            int y2 = startY + (int)Math.round(lineLength * Math.sin(drawDirection * Math.PI /180));
            drawLine(g, startX, startY, x2, y2, lineDrawer);
            drawTwig(g, x2, y2, numBranches -1 , lineLength/2, drawDirection +(45 + (30* Math.random())));
            drawTwig(g, x2, y2, numBranches -1 , lineLength/2, drawDirection - (45 + (30* Math.random())));
        }
    }

    private void drawString(Graphics g, Color color,  String str, int x, int y) {
        var offset = 4;
        g.setColor(color);
        g.drawString(str, xOrigin + x + offset, yOrigin + y + offset + g.getFont().getSize());
    }

    private void drawGraph(Graphics g){
        //going twice the window size to ensure zoom out works
        var axisColor = new Color(3,133,88);
        var graphLineColor = Color.GRAY;
        var scale = 100;
        var lineDrawer = new Bresenham(xOrigin, yOrigin);

        var leftLimit = -1* (displayWindow.getWidth() - xOrigin) * 2;
        var rightLimit = (displayWindow.getWidth() - xOrigin)*2;
        var topLimit = (displayWindow.getHeight() - yOrigin) * 2;
        var bottomLimit = -1* (displayWindow.getHeight() - yOrigin) * 2;

        g.setColor(axisColor);
        //x-axis
        drawLine(g, leftLimit, 0, rightLimit, 0, lineDrawer);
        //y-axis
        drawLine(g,  0,topLimit, 0, bottomLimit, lineDrawer);

        //origin
        drawString(g,axisColor,"0", 0, 0);

        //drawing Horizontal lines
        for (int y= scale; y <= topLimit;y+= scale) {
//            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y), 0, y);
        }
        for (int y= -scale  ; y >= bottomLimit;y-= scale ) {
//            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y), 0, y);
        }

        //drawing vertical lines
        for (int x= scale; x <= rightLimit;x+= scale ) {
//            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x), x, 0);
        }
        for (int x= -scale; x >= leftLimit;x-= scale ) {
//            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x), x, 0);
        }
    }

    @Override
    public void paint(Graphics g) {
        int length = 100;
        int drawDirection = 90;
        lineDrawer = new Bresenham(xOrigin, yOrigin);

        drawGraph(g);
        g.setColor(Color.black);
        drawTwig(g, -300, 300, 1, length, drawDirection);
        drawTwig(g, -100, 300, 2, length, drawDirection);
        drawTwig(g, 100, 300, 3, length, drawDirection);
        drawTwig(g, 300, 300, 4, length, drawDirection);

        drawTwig(g, 0, -300, 8, 300, drawDirection);
    }
}
