package seiot.progetto02;

import java.util.Date;

import javax.swing.*;

class LogView  {

	private LogFrame frame;
	
	public LogView(){
		frame = new LogFrame();
	}

	public void log(String msg){
		frame.log(msg);
	}
	
	public void show() {
		SwingUtilities.invokeLater(() -> {
			frame.setVisible(true);
		});
	}

	class LogFrame extends JFrame {

		private JTextArea log;

		public LogFrame(){
			super("Log ");
			setSize(600,600);

			JPanel mainPanel = new JPanel();
			log = new JTextArea(30,40);
			log.setEditable(false);
			JScrollPane scrol = new JScrollPane(log);
			mainPanel.add(scrol);
			this.getContentPane().add(mainPanel);
		}
		
		public void log(String msg){
			SwingUtilities.invokeLater(() -> {
				String date = new Date().toString();
				log.append("["+date+"] "+ msg +"\n");
			});
		}
		
		
	}
}
