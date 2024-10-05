package com.abhiroop.part3;

import com.abhiroop.part1.Bresenham;
import com.abhiroop.part1.LineDrawer;

import javax.swing.*;
import java.awt.*;

public class ShapeDrawer extends Canvas {
    private final int xOrigin;
    private final int yOrigin;
    private  final JFrame displayWindow;

    public ShapeDrawer(JFrame displayWindow) {
        //set Background Color
        setBackground(Color.white);

        //get origin of the displayWindow
        xOrigin = (displayWindow.getX() + displayWindow.getWidth()) / 2;
        yOrigin = (displayWindow.getY() + displayWindow.getHeight()) / 2;

        this.displayWindow = displayWindow;

    }

    void drawShape(Graphics g, Shape shape, int startX, int startY){
        shape.draw(g, startX, startY);
    }

    private void drawString(Graphics g, Color color,  String str, int x, int y) {
        var offset = 4;
        g.setColor(color);
        g.drawString(str, xOrigin + x + offset, yOrigin + y + offset + g.getFont().getSize());
    }

    private void drawLine(Graphics g, int x1, int y1, int x2, int y2, LineDrawer lineDrawer){
        lineDrawer.draw(g, x1, y1, x2, y2);
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
        drawGraph(g);
        g.setColor(Color.BLACK);
        drawShape(g, new TopRightTriangleWithHair(xOrigin, yOrigin,
                        450,200, 50),
                -400, 200);
        drawShape(g, new BottomRightTriangleWithHair(xOrigin, yOrigin,
                        450,200, 50),
                -400, 50);
    }
}
