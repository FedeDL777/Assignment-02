package SWDSystem;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;


class SWDSystemView extends JFrame implements ActionListener{

    private JButton restoreButton;
    private JButton emptyButton;
    private JTextField currentTemperature;
    private JTextField fillPercentage;

    private JTextField SWDState;
    private SWDSystemController controller;

    public SWDSystemView(){
        super("SWD System");
        setSize(600,300);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
        mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
        //mainPanel.add(new JLabel("Current Temperature:"));

        JPanel infoLine = new JPanel();
        infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.X_AXIS));
        SWDState = new JTextField("--");
        SWDState.setEditable(false);
        SWDState.setPreferredSize(new Dimension(200, 15));

        infoLine.add(new JLabel("SWD State: "));
        infoLine.add(SWDState);
        currentTemperature = new JTextField("--");
        currentTemperature.setEditable(false);
        currentTemperature.setPreferredSize(new Dimension(200, 15));
        infoLine.add(new JLabel("Current Temperature: "));
        infoLine.add(currentTemperature);

        fillPercentage = new JTextField("--");
        fillPercentage.setEditable(false);
        fillPercentage.setPreferredSize(new Dimension(200, 15));
        infoLine.add(new JLabel("Fill Percentage: %"));
        infoLine.add(fillPercentage);

        mainPanel.add(infoLine);
        mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
        mainPanel.setPreferredSize(new Dimension(200, 20));
        mainPanel.setBackground(Color.LIGHT_GRAY);

        JPanel buttonPanel = new JPanel();
        restoreButton = new JButton("Restore Problems");
        restoreButton.setEnabled(false);
        restoreButton.addActionListener(this);
        restoreButton.setBackground(Color.red);
        emptyButton = new JButton("Empty Container");
        emptyButton.setEnabled(false);
        emptyButton.addActionListener(this);
        emptyButton.setBackground(Color.yellow);


        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));
        buttonPanel.add(restoreButton);
        buttonPanel.add(emptyButton);

        mainPanel.add(buttonPanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
        setContentPane(mainPanel);

        addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.exit(-1);
			}
		});

    }

    public void registerController(SWDSystemController controller){
        this.controller = controller;
    }

    public void setSWDState(String state){
        SwingUtilities.invokeLater(() -> {
            SWDState.setText(state);
        });
    }

    public void setCurrentTemperature(double temp){
        SwingUtilities.invokeLater(() -> {
            currentTemperature.setText(String.format("%.2f", temp));
        });
    }

    public void setFillPercentage(double percentage){
        SwingUtilities.invokeLater(() -> {
            fillPercentage.setText(String.format("%.2f", percentage));
        });
    }
    public void enableRestore(){
        SwingUtilities.invokeLater(() -> {
            restoreButton.setEnabled(true);
        });
    }
    public void enableEmpty(){
        SwingUtilities.invokeLater(() -> {
            emptyButton.setEnabled(true);
        });
    }


    @Override
    public void actionPerformed(ActionEvent e) {
        try{
            if (e.getSource() == restoreButton){
                controller.notifyRestore();
            } else if (e.getSource() == emptyButton){
                controller.notifyEmptyContainer();
                
            }
        }catch (Exception ex){
            ex.printStackTrace();

        }
    }

    
}
/*
 * 
 */