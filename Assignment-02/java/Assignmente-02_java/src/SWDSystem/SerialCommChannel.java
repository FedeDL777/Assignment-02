package SWDSystem;

import java.util.concurrent.*;
import jssc.*;

public class SerialCommChannel implements CommChannel, SerialPortEventListener {

    private SerialPort serialPort;
    private BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer();
    
    public SerialCommChannel(String port, int rate) throws Exception {
        queue = new ArrayBlockingQueue<>(100);

        try {
            serialPort = new SerialPort(port);
            serialPort.openPort();

            serialPort.setParams(rate, 
                                 SerialPort.DATABITS_8, 
                                 SerialPort.STOPBITS_1, 
                                 SerialPort.PARITY_NONE);

            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                                          SerialPort.FLOWCONTROL_RTSCTS_OUT);

            serialPort.addEventListener(this);
        } catch (Exception ex) {
            ex.printStackTrace();
            close();  // Assicura chiusura sicura in caso di errore
            throw new Exception("Error initializing SerialCommChannel", ex);
        }
    }

    @Override
    public void sendMsg(String msg) {
        char[] array = (msg + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.err.println("Error sending message: " + ex.getMessage());
        }
    }

    @Override
    public String receiveMsg() throws InterruptedException {
        return queue.take();
    }

    @Override
    public boolean isMsgAvailable() {
        return !queue.isEmpty();
    }

    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            System.err.println("Error closing serial port: " + ex.getMessage());
        }
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());
                msg = msg.replaceAll("\r", "");

                synchronized (currentMsg) {
                    currentMsg.append(msg);
                }

                processMessages();
            } catch (Exception ex) {
                ex.printStackTrace();
                System.err.println("Error in receiving string from COM-port: " + ex.getMessage());
            }
        }
    }

    private void processMessages() {
        synchronized (currentMsg) {
            boolean goAhead = true;

            while (goAhead) {
                String msg2 = currentMsg.toString();
                int index = msg2.indexOf("\n");
                if (index >= 0) {
                    try {
                        queue.put(msg2.substring(0, index).trim());
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        System.err.println("Interrupted while queuing message.");
                    }
                    currentMsg.delete(0, index + 1);
                } else {
                    goAhead = false;
                }
            }
        }
    }
}
