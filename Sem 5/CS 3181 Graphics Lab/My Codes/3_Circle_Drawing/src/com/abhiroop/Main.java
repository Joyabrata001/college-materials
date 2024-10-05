package com.abhiroop;

import com.abhiroop.part1.CircleDisplay;
import com.abhiroop.part2.EllipseDisplay;
import com.abhiroop.part3.ShapeDisplay;

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
	    var displayWindow1 = getDisplayWindow();
        displayWindow1.add(new CircleDisplay(displayWindow1));

        var displayWindow2 = getDisplayWindow();
        displayWindow2.add(new EllipseDisplay(displayWindow2));

        var displayWindow3 = getDisplayWindow();
        displayWindow3.add(new ShapeDisplay(displayWindow3));
    }
}
