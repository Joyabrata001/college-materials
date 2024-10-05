package com.abhiroop.prereq;

import com.abhiroop.prereq.lineGenerator.BresenhamGenerator;
import com.abhiroop.prereq.lineGenerator.LineGenerator;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.AffineTransform;

public class BaseGraph extends Canvas implements MouseWheelListener {

    //center origin
    private final int xOrigin;
    private final int yOrigin;

    // for zooming
    private double zoomFactor;
    private double prevZoomFactor;
    private boolean zoomer;
    private double xOffset;
    private double yOffset;

    public int getXOrigin() {
        return xOrigin;
    }

    public int getYOrigin() {
        return yOrigin;
    }

    private final JFrame displayWindow;

    public BaseGraph(JFrame displayWindow) {
        //set Background Color
        setBackground(Color.white);

        //get origin of the displayWindow
        xOrigin = (displayWindow.getX() + displayWindow.getWidth()) / 2;
        yOrigin = (displayWindow.getY() + displayWindow.getHeight() / 2);

        this.displayWindow = displayWindow;

        //set zoom specifics
        addMouseWheelListener(this);
        zoomFactor = 1;
        prevZoomFactor = 1;
        xOffset = 0;
        yOffset = 0;
        zoomer = false;
    }

    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
        zoomer = true;

        //zoom in
        if(e.getWheelRotation() < 0)
            zoomFactor *=1.1;
            //zoom out
        else if(e.getWheelRotation() > 0)
            zoomFactor /=1.1;

        repaint();
    }

    private void drawLine(Graphics g, LineGenerator lineGenerator, Color color, int x1, int y1, int x2, int y2){
        lineGenerator.generate(x1, y1, x2, y2).draw(g, xOrigin, yOrigin, color);
    }

    private void drawString(Graphics g, Color color,  String str, int x, int y) {
        var offset = 4;
        g.setColor(color);
        g.drawString(str, xOrigin + x + offset, yOrigin + y + offset + g.getFont().getSize());
    }

    private void drawGraph(Graphics g){
        //going twice the window size to ensure zoom out works
        var axisColor = new Color(3,133,88);
//        var graphLineColor = Color.GRAY;
        var scale = 100;
//        var lineDrawer = new Bresenham(xOrigin, yOrigin);
        var lineGenerator = new BresenhamGenerator();

        var leftLimit = -1* (displayWindow.getWidth() - xOrigin) * 2;
        var rightLimit = (displayWindow.getWidth() - xOrigin)*2;
        var topLimit = (displayWindow.getHeight() - yOrigin) * 2;
        var bottomLimit = -1* (displayWindow.getHeight() - yOrigin) * 2;


        //x-axis
        drawLine(g, lineGenerator,axisColor,leftLimit, 0, rightLimit, 0);
        //y-axis
        drawLine(g, lineGenerator,axisColor, 0,topLimit, 0, bottomLimit);

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

    void zoom(Graphics g){
        Graphics2D g2 = (Graphics2D)g;
        AffineTransform at = new AffineTransform();

        double xRel = MouseInfo.getPointerInfo().getLocation().getX() - getLocationOnScreen().getX();
        double yRel = MouseInfo.getPointerInfo().getLocation().getY() - getLocationOnScreen().getY();
        double zoomDiv = zoomFactor / prevZoomFactor; //will be 1.1 or 0.9

        xOffset = (zoomDiv) * (xOffset) + (1 - zoomDiv) * xRel;
        yOffset = (zoomDiv) * (yOffset) + (1 - zoomDiv) * yRel;

        at.translate(xOffset, yOffset);
        at.scale(zoomFactor, zoomFactor);
        prevZoomFactor = zoomFactor;
        g2.transform(at);
        zoomer = false;
    }

    @Override
    public void paint(Graphics g) {
        if(zoomer)
            zoom(g);
        drawGraph(g);
        g.setColor(Color.BLACK);
    }
}
