package com.abhiroop;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;

import static java.awt.event.MouseEvent.BUTTON1;
import static java.awt.event.MouseEvent.BUTTON2;

public class MouseEventPainter extends Canvas implements  MouseWheelListener {
    private double zoomFactor ;
    private double prevZoomFactor ;
    private boolean zoomer;

    /**
     * Constructs a new Canvas.
     */
    public MouseEventPainter() {
        addMouseWheelListener(this);
        zoomFactor = 1;
        prevZoomFactor = 1;
    }

    /**
     * Invoked when the mouse wheel is rotated.
     *
     * @param e the event to be processed
     * @see MouseWheelEvent
     */
    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
        zoomer = true;

        //Zoom in
        if(e.getWheelRotation() < 0){
            zoomFactor *= 1.1;
            repaint();
        }
        else if (e.getWheelRotation() > 0){
            zoomFactor /=1.1;
            repaint();
        }
    }

    /**
     * Paints this canvas.
     * <p>
     * Most applications that subclass {@code Canvas} should
     * override this method in order to perform some useful operation
     * (typically, custom painting of the canvas).
     * The default operation is simply to clear the canvas.
     * Applications that override this method need not call
     * super.paint(g).
     *
     * @param g the specified Graphics context
     * @see #update(Graphics)
     * @see Component#paint(Graphics)
     */
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2 = (Graphics2D) g;

        if(zoomer){
            AffineTransform at = new AffineTransform();
            at.scale(zoomFactor, zoomFactor);
            prevZoomFactor = zoomFactor;
            g2.transform(at);
            zoomer = false;
        }

        g2.drawLine(10,10,100,100);
    }
}
