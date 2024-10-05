package com.abhiroop;

//import com.abhiroop.bird.ShapeDisplay;

import com.abhiroop.bezeirCurve.BezierCurveWindow;
import com.abhiroop.lineClipping.LineClippingDisplay;

import javax.swing.*;

public class Main {

    private static JFrame getDisplayWindow(){
        var displayWindow = new JFrame();
        displayWindow.setVisible(true); //generates a window where Canvas can be shown
        displayWindow.setSize(1000,1000); //set default size of the window
        displayWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //makes sure the process is terminated after window closed
        return displayWindow;
    }
    public static void main(String[] args) {
        var lineClippingWindow = getDisplayWindow();
        lineClippingWindow.add(new LineClippingDisplay(
                lineClippingWindow, -400, -400, 400, 400
        ));

        var bezierCurveFrame = getDisplayWindow();
        bezierCurveFrame.add(new BezierCurveWindow(bezierCurveFrame));
    }
}
