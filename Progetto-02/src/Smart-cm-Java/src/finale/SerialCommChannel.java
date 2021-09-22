package finale;


import java.util.concurrent.*;
import jssc.*;

/**
 * Comm channel implementation based on serial port.
 * 
 * @author aricci
 *
 */
public class SerialCommChannel implements CommChannel, SerialPortEventListener {

	private SerialPort serialPort;
	private BlockingQueue<String> queue;
	private StringBuffer currentMsg = new StringBuffer("");
	
	public StringBuffer getCurrentMsg() {
		return currentMsg;
	}

	public SerialCommChannel(String port, int rate) throws Exception {
		queue = new ArrayBlockingQueue<String>(100);

		serialPort = new SerialPort(port);
		try {
		    serialPort.openPort();

		    serialPort.setParams(rate,
		                         SerialPort.DATABITS_8,
		                         SerialPort.STOPBITS_1,
		                         SerialPort.PARITY_NONE);

		    serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
		                                  SerialPort.FLOWCONTROL_RTSCTS_OUT);

		    // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
			serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
			
		}
		catch (SerialPortException ex) {
		    System.out.println("There are an error on writing string to port т: " + ex);
		}
		
		// add event listeners

	}

	@Override
	public void sendMsg(String msg) {
		char[] array = (msg+"\n").toCharArray();
		byte[] bytes = new byte[array.length];
		for (int i = 0; i < array.length; i++){
			bytes[i] = (byte) array[i];
		}
		try {
			synchronized (serialPort) {
				serialPort.writeBytes(bytes);
			}
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		// TODO Auto-generated method stub
		return queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
		return !queue.isEmpty();
	}

	/**
	 * This should be called when you stop using the port.
	 * This will prevent port locking on platforms like Linux.
	 */
	public void close() {
		try {
			if (serialPort != null) {
				serialPort.removeEventListener();
				serialPort.closePort();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	/**
	 * Handle an event on the serial port. Read the data and print it.
	 */
//	public void serialEvent(SerialPortEvent event) {
//		/* if there are bytes received in the input buffer */
//		if (event.isRXCHAR()) {
//            try {
//            		/* 
//            		 * event.getEventValue()) => number of bytes in the input buffer
//            		 * readString() => read the specified number of bytes
//            		 */
//            		String msg = serialPort.readString(event.getEventValue());
//        			
//        			int index = msg.indexOf("\n");
//        			if (index >= 0) {
//        				currentMsg.append(msg.substring(0, index));
//        				queue.put(currentMsg.toString());
//        				currentMsg.setLength(0);
//        				if (index + 1 < msg.length()) {
//        					currentMsg.append(msg.substring(index + 1)); 
//        				}
//        			} else {
//        				currentMsg.append(msg);
//        			}
//        			System.out.println(msg);
//            } catch (Exception ex) {
//            		ex.printStackTrace();
//                System.out.println("Error in receiving string from COM-port: " + ex);
//            }
//        }
//	}


	public void serialEvent(SerialPortEvent event) {
		/* if there are bytes received in the input buffer */
		if (event.isRXCHAR()) {
            try {
            		String msg = serialPort.readString(event.getEventValue());
            		msg = msg.replaceAll("\r", "");
            		
            		currentMsg.append(msg);
            		
            		boolean goAhead = true;
            		
        			while(goAhead) {
        				String msg2 = currentMsg.toString();
        				int index = msg2.indexOf("\n");
            			if (index > 0) {
            				queue.put(msg2.substring(0, index));
            				currentMsg = new StringBuffer("");
            				if (index + 1 < msg2.length()) {
            					currentMsg.append(msg2.substring(index + 1)); 
            				}
            			} else {
            				goAhead = false;
            			}
        			}
        			if(queue.size()>6) {
        				queue.clear();
        			}
        			System.out.println(queue.toString());
            } catch (Exception ex) {
            		ex.printStackTrace();
                System.out.println("Error in receiving string from COM-port: " + ex);
            }
        }
	}
	
//	// Metodo di Ismam
//	public void serialEvent(SerialPortEvent event) {
//		if(event.isRXCHAR() && event.getEventValue() > 0) {
//			String recData = null;
//			try {
//				recData = serialPort.readString(event.getEventValue());
//			} catch (SerialPortException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//			boolean goAhead=true;
//			
//			while(goAhead) {
//				String msg2 = currentMsg.toString();
//				int index = msg2.indexOf("\n");
//    			if (index >= 0) {
//    				queue.put(msg2.substring(0, index));
//    				currentMsg = new StringBuffer("");
//    				if (index + 1 < msg2.length()) {
//    					currentMsg.append(msg2.substring(index + 1)); 
//    				}
//    			} else {
//    				goAhead = false;
//    			}
//			}
//		}
//	}
	
}