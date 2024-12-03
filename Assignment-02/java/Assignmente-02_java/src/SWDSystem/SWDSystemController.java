package SWDSystem;

public class SWDSystemController {
    static final String MSG_RESTORE = "RESTORE";
    static final String MSG_EMPTY_CONTAINER = "EMPTY";

    SerialCommChannel channel;
	SWDSystemView view;
	LogView logger;
    //

    public SWDSystemController(String portName, SWDSystemView view, LogView log) throws Exception {
        this.view = view;
        this.logger = log;
        this.channel = new SerialCommChannel(portName, 9600);
        new DataReceiver(channel,view,logger).start();
        System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");	
    }

    public void notifyRestore() {
        channel.sendMsg(MSG_RESTORE);
  }
    public void notifyEmptyContainer() {
        channel.sendMsg(MSG_EMPTY_CONTAINER);
    }
}
