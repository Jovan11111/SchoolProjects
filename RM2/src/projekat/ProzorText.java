package projekat;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ProzorText extends Frame {

    private String text = "Na ruteru R3 konfigurisati da sve rute koje dolaze od R1 dobiju Local Preference (LP) "
            + "vrednost 100, a da sve rute koje dolaze od R2 da dobijaju LP vrednost 150. Na R3 "
            + "konfigurisati da kada za neku rutu primi rutu uz koju je dodata community vrednost "
            + "3:50, da se za tu rutu postavlja vrednost LP na 50, a da kada primi rutu sa Community "
            + "vrednošću 3:200 da se za tu rutu postavlja LP na 200. Na ruteru R1 konfigurisati da se "
            + "uz rutu 192.168.10.0/24 kada se oglašava ka R3 pridružuje Community vrednost "
            + "3:200. \n \n"
            + "Napraviti aplikaciju koja prati rad SNMP protokola na svim ruterima. Koristiti SNMP deo "
            + "MIB-2. Aplikacija treba da svakih 10s prikuplja sledeće statističke parametre o radu "
            + "SNMP na ruteru: Broj dolaznih SNMP paketa, broj odlaznih SNMP paketa, broj get "
            + "zahteva, broj set zahteva, broj generisanih trap-ova, broj neispravnih community "
            + "vrednosti u zahtevima.";

    public ProzorText() {
        setTitle("Tekst Zadatka");
        setSize(600, 400);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());
        setBackground(new Color(255, 237, 243));

        Panel mainPanel = new Panel(new BorderLayout());
        mainPanel.setBackground(new Color(255, 237, 243));

        TextArea textArea = new TextArea(text, 10, 40, TextArea.SCROLLBARS_VERTICAL_ONLY);
        textArea.setEditable(false);
        textArea.setFont(new Font("Serif", Font.BOLD, 16));
        textArea.setBackground(new Color(255, 237, 243));

        mainPanel.add(textArea, BorderLayout.CENTER);

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
        backButton.setFont(new Font("Serif", Font.BOLD, 16));
        backButton.setBackground(new Color(159, 195, 233));
        mainPanel.add(backButton, BorderLayout.SOUTH);

        add(mainPanel);

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
                System.exit(0);
            }
        });

        setVisible(true);
    }

    public static void main(String[] args) {
        new ProzorText();
    }
}
