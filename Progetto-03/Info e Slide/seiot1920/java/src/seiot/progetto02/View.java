package seiot.progetto02;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.*;

import javax.swing.*;

class View  {

	enum Mode {MANUAL, AUTO, SINGLE};
	private ViewFrame viewFrame;
	private DetectedObjFrame detectedObjs;
	private MonitoringAgent controller;
	private Mode mode;
	private Radar radar;
	private double dnear, dfar, dmax;
	private boolean alarm;
	
	public View(Radar radar){
		this.radar = radar;
		viewFrame = new ViewFrame();
		detectedObjs = new DetectedObjFrame();
		dnear = 0.1;
		dfar = 0.3;
		dmax = 1;
	}

	public void registerController(MonitoringAgent contr){
		controller = contr;
	}

	public void show() {
		SwingUtilities.invokeLater(() -> {
			viewFrame.setVisible(true);
			detectedObjs.setVisible(true);
		});
	}
	
	void setMode(Mode mode) {
		this.mode = mode;
		if (mode.equals(Mode.MANUAL)) {
			viewFrame.setManualMode();
		} else if (mode.equals(Mode.AUTO)) {
			viewFrame.setAutoMode();
		} else {
			viewFrame.setSingleMode();
		}
	}
	
	void setParams(double dnear, double dfar, double dmax) {
		this.dnear = dnear;
		this.dfar = dfar;
		this.dmax = dmax;
	}
	
	void setReadyStatus() {
		viewFrame.setStatus("Ready.");
	}

	void setSelfTestStatus() {
		viewFrame.setStatus("Self Test ongoing...");
	}

	void setConnectedStatus() {
		viewFrame.setStatus("Connected.");
	}

	void setNotConnectedStatus() {
		viewFrame.setStatus("Not connected.");
	}
	
	void refresh() {
		detectedObjs.updateDetectedObjs();
		viewFrame.repaint();
	}

	void setScanning() {
		viewFrame.setStatus("Scanning.");
	}
	
	void setAlarm(boolean alarm) {
		this.alarm = alarm;
	}
	
	private void notifyLeftCmd() {
		controller.notifyLeftCmd();
	}	

	private void notifyRightCmd() {
		controller.notifyRightCmd();
	}
	
	private void notifyManualMode() {
		controller.notifyModeManualCmd();
	}

	private void notifyAutoMode() {
		controller.notifyModeAutoCmd();
	}

	private void notifySingleMode() {
		controller.notifyModeSingleCmd();
	}

	class RadarPanel extends JPanel {

        int maxRadius = 180;
        // double maxDistance = 2.5;
        int x0 = 25 + 180;
        int y0 = 200;

		public void paintComponent(Graphics g) {
			super.paintComponent(g);   
	        Graphics2D g2 = (Graphics2D)g;
	        // g2.drawRect(25,20,360,280);
	        
	        g2.drawArc(x0 - maxRadius, y0 - maxRadius, maxRadius*2, maxRadius*2, 0, 180);

	        int dnearRadius = (int) ((double)maxRadius*dnear/dmax);
	        int dfarRadius = (int) ((double)maxRadius*dfar/dmax);
	        
	        g2.drawArc(x0 - maxRadius, y0 - maxRadius, maxRadius*2, maxRadius*2, 0, 180);
	        g2.drawArc(x0 - dnearRadius, y0 - dnearRadius, dnearRadius*2, dnearRadius*2, 0, 180);
	        g2.drawArc(x0 - dfarRadius, y0 - dfarRadius, dfarRadius*2, dfarRadius*2, 0, 180);

	        int angle = radar.getCurrentPos();
			double[] objs = radar.getCurrentObjDetected();
			for (int i = 0; i < 180; i++) {
				if (objs[i] >= 0) {
	        	   		double rad = objs[i]*maxRadius/dmax;
	        	   		int xd = x0 - (int) (Math.cos(i*Math.PI/180)*rad);
	        	   		int yd = y0 - (int) (Math.sin(i*Math.PI/180)*rad);
	        	   		g2.drawOval(xd, yd, 3, 3);
				}
			}
	        g2.drawLine(x0, x0, x0 - (int) (Math.cos(angle*Math.PI/180)*maxRadius), y0 - (int)(Math.sin(angle*Math.PI/180)*maxRadius));
	        
	        if (alarm) {
	        		g2.drawString("ALARM", 20, 20);
	        }
		}		
	}

	class ViewFrame extends JFrame implements ActionListener {

		private RadarPanel radarPanel;
		private JLabel mode, status;
		private JPanel inputLine;
		private JButton auto, manual, single;
		private JButton left, right;
		private JTextArea objDetected;
		
		public ViewFrame(){
			super(".:: Smart Radar ::.");
			setSize(420,460);

			JPanel mainPanel = new JPanel();
			mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

			mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

			JPanel modeLine = new JPanel();
			modeLine.setLayout(new BoxLayout(modeLine, BoxLayout.LINE_AXIS));
			modeLine.setPreferredSize(new Dimension(380,25));
			modeLine.add(Box.createRigidArea(new Dimension(20,0)));
			modeLine.add(new JLabel("Mode "));
			modeLine.add(Box.createRigidArea(new Dimension(20,0)));
			mode = new JLabel("------");
			modeLine.add(mode);
			modeLine.add(Box.createRigidArea(new Dimension(20,0)));
			manual = new JButton("manual");
			single = new JButton("single");
			auto = new JButton("auto");
			modeLine.add(manual);
			modeLine.add(Box.createRigidArea(new Dimension(5,0)));
			modeLine.add(single);
			modeLine.add(Box.createRigidArea(new Dimension(5,0)));
			modeLine.add(auto);
			modeLine.add(Box.createRigidArea(new Dimension(5,0)));
			manual.addActionListener(this);
			single.addActionListener(this);
			auto.addActionListener(this);
			mainPanel.add(modeLine);

			mainPanel.add(Box.createRigidArea(new Dimension(0,15)));

			radarPanel = new RadarPanel();
			radarPanel.setPreferredSize(new Dimension(390,300));
			mainPanel.add(radarPanel);

			mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
			
			/*
			JPanel text = new JPanel();
			text.setPreferredSize(new Dimension(390,200));
			objDetected = new JTextArea(20,40);
			text.add(objDetected);
			mainPanel.add(text);
			
			mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
			*/
			inputLine = new JPanel();
			inputLine.setLayout(new BoxLayout(inputLine, BoxLayout.LINE_AXIS));
			left = new JButton("Left");
			right = new JButton("Right");
			inputLine.add(left);
			inputLine.add(Box.createRigidArea(new Dimension(20,0)));
			inputLine.add(right);
			inputLine.add(Box.createRigidArea(new Dimension(20,0)));
			left.addActionListener(this);
			right.addActionListener(this);
			mainPanel.add(inputLine);

			mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
			JPanel statusLine = new JPanel();
			statusLine.setLayout(new BoxLayout(statusLine, BoxLayout.LINE_AXIS));
			statusLine.setPreferredSize(new Dimension(380,25));
			statusLine.add(Box.createRigidArea(new Dimension(20,0)));
			statusLine.add(new JLabel("Status "));
			statusLine.add(Box.createRigidArea(new Dimension(20,0)));
			status = new JLabel("------");
			statusLine.add(status);
			mainPanel.add(statusLine);

			this.getContentPane().add(mainPanel);

			addWindowListener(new WindowAdapter(){
				public void windowClosing(WindowEvent ev){
					System.exit(-1);
				}
			});
		}
		
		void setStatus(String st) {
			SwingUtilities.invokeLater(() -> {
				status.setText(st);
			});
		}
		
		void setManualMode() {
			inputLine.setEnabled(true);
			left.setEnabled(true);
			right.setEnabled(true);
			mode.setText("MANUAL");
			manual.setEnabled(false);
			auto.setEnabled(true);
			single.setEnabled(true);
		}

		void setAutoMode() {
			inputLine.setEnabled(false);
			left.setEnabled(false);
			right.setEnabled(false);
			mode.setText("AUTO");
			manual.setEnabled(true);
			auto.setEnabled(false);
			single.setEnabled(true);
		}
		
		void setSingleMode() {
			inputLine.setEnabled(false);
			left.setEnabled(false);
			right.setEnabled(false);
			mode.setText("SINGLE");
			manual.setEnabled(true);
			auto.setEnabled(true);
			single.setEnabled(false);
		}

		@Override
		public void actionPerformed(ActionEvent e) {
			Object src = e.getSource();
			if (src == single) {
				setSingleMode();
				notifySingleMode();
			} else if (src == manual) {
				setManualMode();
				notifyManualMode();
			} else if (src == auto) {
				setAutoMode();
				notifyAutoMode();
			} else if (src == left) {
				notifyLeftCmd();
			} else if (src == right) {
				notifyRightCmd();
			}
		}		
	}
	
	class DetectedObjFrame extends JFrame {

		private JTextArea log;

		public DetectedObjFrame(){
			super(".:: Detected Objects Data ::.");
			setSize(400,400);

			JPanel mainPanel = new JPanel();
			log = new JTextArea(20,30);
			log.setEditable(false);
			JScrollPane scrol = new JScrollPane(log);
			mainPanel.add(scrol);
			this.getContentPane().add(mainPanel);
		}
		
		void updateDetectedObjs() {
			SwingUtilities.invokeLater(() -> {
				StringBuffer sb = new StringBuffer();
				double[] objs = radar.getCurrentObjDetected();
				for (int i = 0; i < 180; i++) {
					if (objs[i] >= 0) {
						sb.append("Angle: " + i + " - distance: " + objs[i] + "\n");
					}
				}
				log.setText(sb.toString());
			});
		}
		
	}
	

}
