package finale;

import java.net.URL;


import java.util.Arrays;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortList;

public class ArduinoFXMLController implements Initializable {

	
    // Qui vengono dichiarati i controlli e le variabili del programma
    
    @FXML
    private TextField servoTxt, tmaxTxt, tminTxt;	
    @FXML
    private TextArea console;
    @FXML
    private Button apriSeriale, chiudiSeriale;
    @FXML
    private Button manual, single, auto;
    @FXML
    private Button btnServo, btnPot;
    @FXML
    private ComboBox<String> cmb;
    @FXML 
    Pane pane;
    
    //SerialPort cmChannel;
    
    private String nomePorta;
    
    SerialCommChannel cmChannel;

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {

		//
        // Attraverso l'oggetto SerialPortList si ottiene un elenco
        // delle porte seriali sul pc memorizzate nel'array port
        //
        String[] port = SerialPortList.getPortNames();
        String porta = Arrays.toString(port);
        this.manual.setDisable(true);
        this.single.setDisable(true);
        this.auto.setDisable(true);
        this.btnPot.setDisable(true);
        this.btnServo.setDisable(true);
        this.chiudiSeriale.setDisable(true);
        for (String Porta : port) {
 
            if (porta.contains("[")) {
                porta = porta.replace("[", "");
                porta = porta.replace("]", "");
            }
            cmb.getItems().add(Porta); // Si riempie il cmbox con le porte disponibili
        }
		
	}
	
	@FXML
    void connetti(ActionEvent event) throws Exception {
		nomePorta = cmb.getValue();
        //cmChannel = new SerialPort(nomePorta);
        cmChannel = new SerialCommChannel(this.nomePorta, SerialPort.BAUDRATE_9600);
        this.auto.setDisable(false);
        this.manual.setDisable(false);
        this.single.setDisable(false);
        this.apriSeriale.setDisable(true);
        this.chiudiSeriale.setDisable(false);
        this.console.setText("Porta seriale aperta!\n");
        
        
 
        
    }
	
	@FXML
    void disconnetti(ActionEvent event) {

		this.cmChannel.close();
		this.manual.setDisable(true);
        this.single.setDisable(true);
        this.auto.setDisable(true);
        this.btnPot.setDisable(true);
        this.btnServo.setDisable(true);
        System.out.println("Ho chiuso il seriale!");
        this.console.setText("Ho chiuso il seriale!");
        this.manual.setDisable(true);
        this.apriSeriale.setDisable(false);

    }
	
	@FXML
	void attivaRotazione() throws SerialPortException, InterruptedException{
		
		int gradi = Integer.parseInt(servoTxt.getText());
		String gradiString = servoTxt.getText();
		if(gradi>=0 && gradi < 180) {
			System.out.println("Sending: " + gradiString);
			this.cmChannel.sendMsg(gradiString);
			String msg = this.cmChannel.receiveMsg();
			System.out.println("Received: "+msg);
		} else {
			System.out.println("Il servo deve ruotare di almeno 0 gradi o al massimo 179 gradi");
		}
		
		
	}
	
	@FXML
	void cambiaTempo() throws SerialPortException {
		
		int tmax = Integer.parseInt(tmaxTxt.getText());
		String tmaxString = tmaxTxt.getText();
		int tmin = Integer.parseInt(tminTxt.getText());
		String tminString = tminTxt.getText();
		if((tmax > 2 && tmax <= 12 ) && (tmin >= 2 && tmin < 12) && (tmax > tmin)){
//			this.cmChannel.writeInt(tmax);
//			this.cmChannel.writeInt(tmin);
//			System.out.println("Cambiamento tempo di ciclo:");
//			System.out.println("Tmax, Tmin = " + tmax + tmin);
			this.cmChannel.sendMsg(tmaxString);
			this.cmChannel.sendMsg(tminString);
		} else {
			System.out.println("Errore nel settaggio Tmax e Tmin");
		}
	}
	
	@FXML
	void setManual() {
		
		this.btnServo.setDisable(false);
		this.btnPot.setDisable(true);
		String mm = "manual";
		this.cmChannel.sendMsg(mm);
		System.out.println("attivo manual dal bottone");
		this.console.appendText("Attivata modalità manual\n");
	}
	
	@FXML
	void setAuto() {
		
		this.btnServo.setDisable(true);
		this.btnPot.setDisable(false);
		String ma = "auto";
		this.cmChannel.sendMsg(ma);
		System.out.println("attivo auto dal bottone");
		this.console.appendText("Attivata modalità auto\n");
	}
	
	@FXML
	void setSingle() {
		
		this.btnServo.setDisable(true);
		this.btnPot.setDisable(false);
		String ms = "single";
		this.cmChannel.sendMsg(ms);
		System.out.println("attivo single dal bottone");
		this.console.appendText("Attivata modalità single\n");
	}
	
	
    
}
