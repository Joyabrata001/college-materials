package com.abhiroop;

import javax.swing.JFrame; // The Window that will be displaye

public class Main {

    private static JFrame getDisplayWindow() {
        JFrame displayWindow = new JFrame();
        displayWindow.setVisible(true); // generates a window on operating system
        displayWindow.setSize(600, 600); // set the window's default size
        displayWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // makes sure to close program execution when window closed
        return displayWindow;
    }

    public static void main(String[] args) {
        JFrame displayWindow = getDisplayWindow();
        displayWindow.add(new Painter(displayWindow)); // displays the graphic drawing
    }
}
