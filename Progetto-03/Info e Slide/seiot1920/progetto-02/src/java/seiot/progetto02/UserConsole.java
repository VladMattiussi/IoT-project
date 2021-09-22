package seiot.progetto02;

class UserConsole   {

	static View view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}
		
		String portName = args[0]; // "/dev/cu.usbmodem14201"
		
		Radar radar = new Radar();
		view = new View(radar);
		log = new LogView();
		view.show();
		log.show();

		MonitoringAgent agent = new MonitoringAgent(portName, radar, view, log);
		agent.start();

	}
}