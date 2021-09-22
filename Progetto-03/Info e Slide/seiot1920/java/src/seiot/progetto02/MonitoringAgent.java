package seiot.progetto02;

import seiot.modulo_lab_2_2.msg.*;
import seiot.progetto02.View.Mode;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	View view;
	Radar radar;
	LogView logger;
	String port;
	private int mode;
	
	static final String CM_PREFIX 		= "sr:";
	static final String LOG_PREFIX 		= "lo:";
	
	static final String MSG_READY 			= "ok";
	static final String MSG_SELFTEST			= "te";
	static final String MSG_MODE 			= "mo";
	static final String MSG_NEW_SCAN 		= "sc";
	static final String MSG_SCAN_POS 		= "po";
	static final String MSG_SCAN_DET 		= "de";
	static final String MSG_SCAN_ALARM_ON	= "a1";
	static final String MSG_SCAN_ALARM_OFF 	= "a0";
	static final String MSG_PARAMS 			= "pa";

	static final int MODE_SINGLE = 1;
	static final int MODE_MANUAL = 2;
	static final int MODE_AUTO = 3;
	
	public MonitoringAgent(String port, Radar radar, View view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.radar = radar;
		this.port = port;
	}
	
	public void run(){
		view.registerController(this);
		view.setNotConnectedStatus();
		
		while (true) {
			try {
				channel = new SerialCommChannel(port, 115200);	
				break;
			} catch (Exception ex) {
				logger.log("[Console] Not found. Retrying in 1 secs");
				try {
					sleep(1000);
				} catch (Exception ex1) {}
			}
		}

		try {
			sleep(4000);
		} catch (Exception ex1) {}
		
		logger.log("[Console] Connected.");
		view.setConnectedStatus();
		channel.sendMsg("ok");

		while (true){
			try {
				String msg = channel.receiveMsg();
				if (msg.startsWith(CM_PREFIX)){
					String cmd = msg.substring(CM_PREFIX.length()); 
					if (cmd.startsWith(MSG_READY)){
						// logger.log("[Console] New notification from device: "+cmd);						
						view.setReadyStatus();
					} else if (cmd.startsWith(MSG_SELFTEST)){
						view.setSelfTestStatus();
					} else if (cmd.startsWith(MSG_MODE)){
						// logger.log("[Console] New notification from device: "+cmd);						
						radar.clear();
						mode = Integer.parseInt(cmd.substring(3));
						if (mode == MODE_SINGLE) {
							view.setMode(Mode.SINGLE);
							logger.log("[Console] set to SINGLE mode.");
						} else if (mode == MODE_AUTO) {
							view.setMode(Mode.AUTO);
							logger.log("[Console] set to AUTO mode.");
						} else if (mode == MODE_MANUAL) {
							logger.log("[Console] set to MANUAL mode.");
							view.setMode(Mode.MANUAL);
						}
					} else if (cmd.startsWith(MSG_NEW_SCAN)) {
						radar.clear();
						view.refresh();
					} else if (cmd.startsWith(MSG_PARAMS)) {
						try {
							String st = cmd.substring(3);
							int index = st.indexOf('|');
							double dnear = Double.parseDouble(st.substring(0,index));
							st = st.substring(index + 1);
							index = st.indexOf('|');
							double dfar = Double.parseDouble(st.substring(0,index));
							st = st.substring(index + 1);
							double dmax = Double.parseDouble(st);
							logger.log("New params: " + dnear + " " + dfar + " " + dmax);
							view.setParams(dnear, dfar, dmax);
						} catch (Exception ex) {
							logger.log("ERROR in " + cmd);
						}
					} else if (cmd.startsWith(MSG_SCAN_POS)) {
						try {
							if (mode == MODE_MANUAL) {
								radar.clear();
							}
							int angle = Integer.parseInt(cmd.substring(3));
							radar.setCurrentPos(angle);
							view.refresh();
						} catch (Exception ex) {
							logger.log("ERROR - angle in " + cmd);
						}
					} else if (cmd.startsWith(MSG_SCAN_DET)) {
						try {
							String cmdde = cmd.substring(3);
							int index = cmdde.indexOf('|');
							int angle = Integer.parseInt(cmdde.substring(0,index));
							double dist = Double.parseDouble(cmdde.substring(index + 1));
							radar.setCurrentPos(angle);
							if (mode == MODE_MANUAL) {
								radar.clear();
							}
							radar.addDectedObj(angle, dist);
							view.refresh();
						} catch (Exception ex) {
							logger.log("ERROR - in " + cmd);
						}
					} else if (cmd.startsWith(MSG_SCAN_ALARM_ON)) {
						view.setAlarm(true);
					} else if (cmd.startsWith(MSG_SCAN_ALARM_OFF)) {
						view.setAlarm(false);
					}
				} else if (msg.startsWith(LOG_PREFIX)){
					this.logger.log(msg.substring(LOG_PREFIX.length()));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
	
	public void notifyLeftCmd() {
		channel.sendMsg("le");
	}

	public void notifyRightCmd() {
		channel.sendMsg("ri");
	}

	public void notifyModeSingleCmd() {
		channel.sendMsg("m1");
	}

	public void notifyModeManualCmd() {
		channel.sendMsg("m2");
	}

	public void notifyModeAutoCmd() {
		channel.sendMsg("m3");
	}

}
