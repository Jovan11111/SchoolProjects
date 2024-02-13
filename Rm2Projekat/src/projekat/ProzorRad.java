package projekat;

import org.snmp4j.CommunityTarget;
import org.snmp4j.PDU;
import org.snmp4j.Snmp;
import org.snmp4j.TransportMapping;
import org.snmp4j.event.ResponseEvent;
import org.snmp4j.event.ResponseListener;
import org.snmp4j.mp.SnmpConstants;
import org.snmp4j.smi.*;
import org.snmp4j.transport.DefaultUdpTransportMapping;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ProzorRad extends JFrame {
    private Label timerLabel;
    private int secondsLeft;
    private Font labelFont = new Font("SansSerif", Font.BOLD, 16);
    private Button stopButton;
    private boolean stopLoop = false;

    private String dolazniPaketi = ".1.3.6.1.2.1.11.1";
    private String odlazniPaketi = ".1.3.6.1.2.1.11.2";
    private String getZahtevi = ".1.3.6.1.2.1.11.4";
    private String setZahtevi = ".1.3.6.1.2.1.11.15";
    private String generisaniTrapovi = ".1.3.6.1.2.1.11.17";
    private String nepravilniCommunity = ".1.3.6.1.2.1.11.29";
    private String[] atributi = {
            dolazniPaketi,
            odlazniPaketi,
            getZahtevi,
            setZahtevi,
            generisaniTrapovi,
            nepravilniCommunity
    };
    private String[] atributiImena = {
    		"Dolazni paketi", "Odlazni paketi", "Get Zahtevi", "Set Zahtevi", "Generisani Trapovi", "Nepravilni Community"
    };
    private String comm = "si2019";
    private String R1 = "192.168.10.1";
    private String R2 = "192.168.20.1";
    private String R3 = "192.168.30.1";
    private String[] ruteri = {R1, R2, R3};

    private int port = 161;
    private int listenerPort = 1620;
	private List<Map<String, JLabel>> data = new ArrayList<>();

    public ProzorRad() throws IOException, InterruptedException {
        this.setTitle("ProzorRad");
        this.setSize(600, 600);
        this.setLocationRelativeTo(null);
        this.setBackground(new Color(255, 237, 243));

        secondsLeft = 10;
        timerLabel = new Label("Time: " + secondsLeft);
        timerLabel.setFont(labelFont);
        timerLabel.setAlignment(Label.RIGHT);
        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                timerLabel.setText("Time: " + secondsLeft);
                secondsLeft--;
                if (secondsLeft < 0) {
                    secondsLeft = 9;
                }
            }
        };
        timer.scheduleAtFixedRate(task, 0, 1000);
        this.add(timerLabel, BorderLayout.NORTH);

        stopButton = new Button("Stop");
        stopButton.setFont(labelFont);
        stopButton.setBackground(new Color(159, 195, 233));
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                stopLoop = true;
            }
        });
        stopButton.setFocusable(false);

        Panel buttonPanel = new Panel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        Button backButton = new Button("Nazad na Main");
        backButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                try {
                    Main main = new Main();
                    main.setVisible(true);
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
        backButton.setFocusable(false);
        backButton.setFont(labelFont);
        backButton.setBackground(new Color(159, 195, 233));
        buttonPanel.add(backButton);
        buttonPanel.add(stopButton);

        this.add(buttonPanel, BorderLayout.SOUTH);

        this.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                System.out.println("Window closed");
                System.exit(0);
            }
        });


        this.setVisible(true);
    }
    
    public void startProveri() {
        new Thread(() -> {
            try {
                proveri();
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }).start();
    }

    public void proveri() throws IOException, InterruptedException {
    	while (!stopLoop) {
            for (int i = 0; i < ruteri.length; ++i) {
                Snmp snmp = new Snmp(new DefaultUdpTransportMapping());
                snmp.listen();

                CommunityTarget target = new CommunityTarget();
                target.setAddress(GenericAddress.parse("udp:" + ruteri[i] + "/161"));
                target.setCommunity(new OctetString("si2019"));
                target.setVersion(org.snmp4j.mp.SnmpConstants.version2c);

                JPanel pane = new JPanel();
                pane.setLayout(new GridLayout(atributi.length, 2));
                data.add(new HashMap<>());

                for (int j = 0; j < atributi.length; ++j) {
                	JLabel ime = new JLabel(atributiImena[j]);
                	JLabel vrednost = new JLabel("0");
                	ime.setFont(labelFont);
                	vrednost.setFont(labelFont);
                	if(j%2 == 0) {
                		ime.setBackground(new Color(255, 237, 243));
                    	vrednost.setBackground(new Color(255, 237, 243));
                	}
                	else {
                		ime.setBackground(new Color(200, 247, 155));
                    	vrednost.setBackground(new Color(200, 247, 155));
                	}
                	
                	ime.setOpaque(true);
                	vrednost.setOpaque(true);
                	ime.setHorizontalAlignment(SwingConstants.CENTER);
                	ime.setVerticalAlignment(SwingConstants.CENTER);
                	vrednost.setHorizontalAlignment(SwingConstants.CENTER);
                	vrednost.setVerticalAlignment(SwingConstants.CENTER);
                	pane.add(ime);
                	pane.add(vrednost);
                	data.get(i).put(atributi[j], vrednost);

                }

                final int index = i;

                ResponseListener listener = new ResponseListener() {
                    @Override
                    public void onResponse(ResponseEvent responseEvent) {
                        if (responseEvent.getResponse() != null) {
                            PDU responsePDU = responseEvent.getResponse();
                            VariableBinding[] binds = responsePDU.toArray();

                            for (int j = 0; j < binds.length; ++j) {
                                data.get(index).get(atributi[j]).setText(binds[j].getVariable().toString());
                            }
                        }
                    }
                };

                snmp.send(getPDU(atributi), target, null, listener);
                getContentPane().add(pane);
            }

            Thread.sleep(10000);
        }
    	
    }

    private PDU getPDU(String[] properties) {
        PDU pdu = new PDU();

        for (String property : properties) {
            pdu.add(new VariableBinding(new OID(property)));
        }

        pdu.setType(PDU.GETNEXT);
        return pdu;
    }
    
    public static void main(String[] args) throws IOException, InterruptedException {
    	ProzorRad p = new ProzorRad();
    	p.proveri();
    }
}
