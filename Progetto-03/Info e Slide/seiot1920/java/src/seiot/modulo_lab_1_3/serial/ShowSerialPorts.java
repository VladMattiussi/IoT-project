package seiot.modulo_lab_1_3.serial;

import java.io.IOException;

import jssc.*;

public class ShowSerialPorts {

	public static void main(String[] args) {
		
		/* detect serial ports */
		String[] portNames = SerialPortList.getPortNames();
		for (int i = 0; i < portNames.length; i++){
		    System.out.println(portNames[i]);
		}

	}

}
