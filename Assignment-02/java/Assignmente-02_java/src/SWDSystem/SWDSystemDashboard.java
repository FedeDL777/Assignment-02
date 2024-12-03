package SWDSystem;

import javax.swing.SwingUtilities;

public class SWDSystemDashboard {
    
    static SWDSystemView view = null;
	static LogView log = null;
    public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/
		SwingUtilities.invokeAndWait(() -> {
			view = new SWDSystemView();
			log = new LogView();
		});
		String portName = "/dev/cu.usbmodem1442401";
		SWDSystemController contr = new SWDSystemController(portName,view,log);
		view.registerController(contr);
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			log.setVisible(true);
		});
	}
}
