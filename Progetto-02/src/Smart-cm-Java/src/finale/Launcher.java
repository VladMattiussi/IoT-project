package finale;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;



public class Launcher extends Application{

	
	@Override
	public void start(final Stage stage) throws Exception {
		
		final FXMLLoader loader = new FXMLLoader(getClass().getResource("arduinoFXML.fxml"));
		loader.setController(new ArduinoFXMLController());
		final Parent root = loader.load();
        Scene scene = new Scene(root);

        
        stage.setScene(scene);
        stage.setTitle("Arduino Controller");
        stage.show();

        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent e) {
                Platform.exit();
                System.exit(0);
            }
        });
		
	}
	
	/**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
