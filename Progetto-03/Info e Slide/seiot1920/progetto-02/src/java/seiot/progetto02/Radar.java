package seiot.progetto02;

import java.util.*;

public class Radar {
	
	private int currentPos;
	private double[] objDetected;
	
	public Radar() {
		currentPos = 0;
		objDetected = new double[180];
		clear();
	}
	
	public void clear() {
		for (int i = 0; i < 180; i++) {
			objDetected[i] = -1;
		}
	}
	
	public void setCurrentPos(int angle) {
		currentPos = angle;
	}
	
	public int getCurrentPos() {
		return currentPos;
	}
	
	public double[] getCurrentObjDetected() {
		return objDetected;
	}
	
	public void addDectedObj(int angle, double dist) {
		objDetected[angle] = dist;
	}
	
}
