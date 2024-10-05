package com.abhiroop.bird;

import com.abhiroop.bird.arm.BottomArm;
import com.abhiroop.bird.arm.TopArm;
import com.abhiroop.bird.beak.Beak;
import com.abhiroop.bird.body.Body;
import com.abhiroop.bird.ear.Ear;
import com.abhiroop.bird.head.Head;
import com.abhiroop.bird.legs.LeftLeg;
import com.abhiroop.bird.legs.RightLeg;
import com.abhiroop.bird.tail.Tail;
import com.abhiroop.bird.utils.Shape;

import java.awt.*;
import java.util.Random;

public class Bird implements Shape {
    private final int xOrigin;
    private final int yOrigin;
    private final boolean beakBig;
    private final boolean beakTeeth;
    private final boolean earCircle;
    private final boolean bodySpotted;
    private final boolean bodyHair;
    private final int tailType;
    private final boolean legSpotted;
    private final boolean legHair;
    private final boolean legLong;
    private final boolean armSpotted;
    private final boolean armHair;
    private final boolean armLong;

    private void printCharacteristics(){
        System.out.printf("%b,%b,%b,%b,%b,%d,%b,%b,%b,%b,%b,%b\n",
                 beakBig, beakTeeth, earCircle, bodySpotted, bodyHair, tailType, legSpotted, legHair, legLong, armSpotted, armHair, armLong);
    }

    public Bird(int xOrigin, int yOrigin) {
        var rand = new Random(System.currentTimeMillis());
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.beakBig = rand.nextInt() % 2 == 0;
        this.beakTeeth = rand.nextInt() % 2 == 0;
        this.earCircle = rand.nextInt() % 2 == 0;
        this.bodySpotted = rand.nextInt() % 2 == 0;
        this.bodyHair = rand.nextInt() % 2 == 0;
        this.tailType = rand.nextInt(3) % 3;
        this.legSpotted = rand.nextInt() % 2 == 0;
        this.legHair = rand.nextInt() % 2 == 0;
        this.legLong = rand.nextInt() % 2 == 0;
        this.armSpotted = rand.nextInt() % 2 == 0;
        this.armHair = rand.nextInt() % 2 == 0;
        this.armLong = rand.nextInt() % 2 == 0;

//        printCharacteristics();
    }

    private Bird
            (
                    int xOrigin,
                    int yOrigin,
                    boolean beakBig,
                    boolean beakTeeth,
                    boolean earCircle,
                    boolean bodySpotted,
                    boolean bodyHair,
                    int tailType,
                    boolean legSpotted,
                    boolean legHair,
                    boolean legLong,
                    boolean armSpotted,
                    boolean armHair,
                    boolean armLong
            ) {
        this.xOrigin = xOrigin;
        this.yOrigin = yOrigin;
        this.beakBig = beakBig;
        this.beakTeeth = beakTeeth;
        this.earCircle = earCircle;
        this.bodySpotted = bodySpotted;
        this.bodyHair = bodyHair;
        this.tailType = tailType;
        this.legSpotted = legSpotted;
        this.legHair = legHair;
        this.legLong = legLong;
        this.armSpotted = armSpotted;
        this.armHair = armHair;
        this.armLong = armLong;

//        printCharacteristics();
    }

    public static Bird merge(Bird bird1, Bird bird2){
        var rand = new Random(System.currentTimeMillis());
        return new Bird
                (
                        bird1.xOrigin,
                        bird2.yOrigin,
                        rand.nextBoolean()? bird1.isBeakBig()       : bird2.isBeakBig(),
                        rand.nextBoolean()? bird1.isBeakTeeth()     : bird2.isBeakTeeth(),
                        rand.nextBoolean()? bird1.isEarCircle()     : bird2.isEarCircle(),
                        rand.nextBoolean()? bird1.isBodySpotted()   : bird2.isBodySpotted(),
                        rand.nextBoolean()? bird1.isBodyHair()      : bird2.isBodyHair(),
                        rand.nextBoolean()? bird1.getTailType()     : bird2.getTailType(),
                        rand.nextBoolean()? bird1.isLegSpotted()    : bird2.isLegSpotted(),
                        rand.nextBoolean()? bird1.isLegHair()       : bird2.isLegHair(),
                        rand.nextBoolean()? bird1.isLegLong()       : bird2.isLegLong(),
                        rand.nextBoolean()? bird1.isArmSpotted()    : bird2.isArmSpotted(),
                        rand.nextBoolean()? bird1.isArmHair()       : bird2.isArmHair(),
                        rand.nextBoolean()? bird1.isArmLong()       : bird2.isArmLong()
                );
    }

    /**
     * Draws the shape
     *
     * @param g      the Graphics Object
     * @param startX start x-position of the Shape
     * @param startY start y-position of the Shape
     */
    @Override
    public void drawShape(Graphics g, int startX, int startY) {

        new Tail(xOrigin, yOrigin, tailType)
                .drawShape(g, startX + 220, startY - 150);

        new LeftLeg(xOrigin, yOrigin, legSpotted, legHair, legLong)
                .drawShape(g, startX+150, startY - 240);

        new TopArm(xOrigin, yOrigin, armSpotted, armHair, armLong)
                .drawShape(g, startX + 30, startY - 90);

        new Body(xOrigin, yOrigin, bodySpotted, bodyHair)
                .drawShape(g, startX + 140, startY - 100);

        new RightLeg(xOrigin, yOrigin, legSpotted, legHair, legLong)
                .drawShape(g, startX+200, startY - 200);

        new BottomArm(xOrigin, yOrigin, armSpotted, armHair, armLong)
                .drawShape(g, startX + 30, startY - 130);

        if(beakBig)
            new Head(xOrigin, yOrigin)
                    .drawShape(g, startX + 70, startY);
        else
            new Head(xOrigin, yOrigin)
                    .drawShape(g, startX + 55, startY);

        new Ear(xOrigin, yOrigin, earCircle)
                .drawShape(g, startX + 100, startY + 30);

        new Beak(xOrigin, yOrigin, beakBig, beakTeeth)
                .drawShape(g, startX, startY);
    }

    public int getxOrigin() {
        return xOrigin;
    }

    public int getyOrigin() {
        return yOrigin;
    }

    public boolean isBeakBig() {
        return beakBig;
    }

    public boolean isBeakTeeth() {
        return beakTeeth;
    }

    public boolean isEarCircle() {
        return earCircle;
    }

    public boolean isBodySpotted() {
        return bodySpotted;
    }

    public boolean isBodyHair() {
        return bodyHair;
    }

    public int getTailType() {
        return tailType;
    }

    public boolean isLegSpotted() {
        return legSpotted;
    }

    public boolean isLegHair() {
        return legHair;
    }

    public boolean isLegLong() {
        return legLong;
    }

    public boolean isArmSpotted() {
        return armSpotted;
    }

    public boolean isArmHair() {
        return armHair;
    }

    public boolean isArmLong() {
        return armLong;
    }
}
