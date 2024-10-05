package com.abhiroop;

import javax.swing.*;
import java.awt.*;

public class Main {

    private static JFrame getDisplayWindow(){
        var displayWindow = new JFrame();
        displayWindow.setVisible(true); //generates a window where Canvas can be shown
        displayWindow.setSize(1000,1000); //set default size of the window
        displayWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //makes sure the process is terminated after window closed
        return displayWindow;
    }

    public static void main(String[] args) {

        //this defines how much pixel is 1unit
        int scale = 100;

	    var displayWindow = getDisplayWindow();
	    displayWindow.add(new Graph(displayWindow, Color.white, new Color(1,77,208), scale));
    }
}
